
#include "InfoView.h"
#include "Font.h"

constexpr char default_info[] = "";
constexpr char default_title[] = "";

InfoView::InfoView()
{
    if ( juce::Desktop::getInstance().getMainMouseSource().canHover() )
    {
        // same as the juce::TooltipWindow
        startTimer( 123 );
    }
    
    setText( default_info, default_title );
    addAndMakeVisible( m_infoMessage );
}

void InfoView::resized()
{
    const auto area = getLocalBounds();
    const int leftMargin = 10;
    const int topMargin = 10;
    m_infoMessage.setBounds( leftMargin,
                            topMargin,
                             getWidth() - leftMargin * 2,
                             area.getHeight() - 2*topMargin);
}

void InfoView::timerCallback()
{
    // find the component under the mouse
    auto             mousePos              = juce::Desktop::getInstance().getMousePosition();
    juce::Component* infoComponent         = nullptr;
    bool             needToResearchDesktop = true;

    // special case if mouse is inside info view (since it could be on top of another component)
    if ( getLocalBounds().contains( getLocalPoint( nullptr, mousePos ) ) )
    {
        setText( default_info, default_title );
        return;
    }

    // try searching within the parent of the showing component (sibling could also have info)
    if ( m_infoComponent != nullptr && m_infoComponent->isShowing() )
    {
        auto parent = m_infoComponent->getParentComponent();
        if ( parent != nullptr && parent->isShowing() && parent->getParentComponent() != nullptr )
        {
            auto relative = parent->getLocalPoint( nullptr, mousePos );
            if ( parent->getLocalBounds().contains( relative ) )
            {
                infoComponent         = findComponentWithInfoAt( parent, relative );
                needToResearchDesktop = false;
            }
        }
    }

    if ( needToResearchDesktop )
    {
        for ( int i = juce::Desktop::getInstance().getNumComponents(); --i >= 0 && infoComponent == nullptr; )
        {
            auto comp = juce::Desktop::getInstance().getComponent( i );
            if ( comp->isShowing() )
            {
                auto relative = comp->getLocalPoint( nullptr, mousePos );
                if ( comp->contains( relative ) )
                {
                    infoComponent = findComponentWithInfoAt( comp, relative );
                }
            }
        }
    }

    // reset the info text
    if ( infoComponent != m_infoComponent )
    {
        m_infoComponent = infoComponent;
        if ( m_infoComponent != nullptr )
        {
            auto props   = m_infoComponent->getProperties();
            auto message = props.getVarPointer( info_message_property );
            auto title   = props.getVarPointer( info_title_property );
            if ( title != nullptr && message != nullptr )
            {
                setText( message->toString().toStdString(), title->toString().toStdString() );
            }
            else
            {
                setText( default_info, default_title );
            }
        }
        else
        {
            setText( default_info, default_title );
        }
    }
}

juce::Component* InfoView::findComponentWithInfoAt( juce::Component* component, juce::Point<int> point )
{
    for ( int i = component->getNumChildComponents(); --i >= 0; )
    {
        auto comp = component->getChildComponent( i );
        if ( comp->isShowing() )
        {
            auto relative = comp->getLocalPoint( component, point );
            if ( comp->getLocalBounds().contains( relative ) )
            {
                if ( auto childComp = findComponentWithInfoAt( comp, relative ) )
                {
                    if ( childComp->getProperties().contains( info_message_property )
                         && childComp->getProperties().contains( info_title_property ) )
                    {
                        return childComp;
                    }
                }
            }
        }
    }
    if ( component->getProperties().contains( info_message_property )
         && component->getProperties().contains( info_title_property ) )
    {
        return component;
    }
    return nullptr;
}

void InfoView::setText( const std::string& text, const std::string& title )
{
    std::string separator = " | ";
    if ( title.empty() )
    {
        separator = "";
    }
    juce::AttributedString msg( title );
    msg.setFont( shout::Font::mainFont(16.0) );
    msg.setJustification( juce::Justification::topLeft );
    msg.setColour( Colours::white );
    msg.setWordWrap( juce::AttributedString::WordWrap::byWord );
    msg.append(separator + text, shout::Font::labelFont(14.0), Colours::white.withAlpha(0.9f));
    m_infoMessage.setText( std::move( msg ) );
}

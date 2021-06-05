
#include "PresetInfoView.h"
#include "Font.h"

using namespace shout;

PresetInfoView::PresetInfoView(PresetInfo& _info)
: m_presetInfo( _info )
{
    addAndMakeVisible( m_infoLabel );
    addAndMakeVisible( m_authorLabel );
    addAndMakeVisible( m_urlClick );
    
    m_presetInfo.info.onChangedAndNow([this](const auto& info){
        setText( info.author.name, info.description, info.title );
        
        m_urlClick.setEnabled( !info.author.url.empty() );
        
        auto mouseCursor = MouseCursor( juce::MouseCursor::StandardCursorType::PointingHandCursor );
        if (info.author.url.empty())
        {
            mouseCursor = MouseCursor( juce::MouseCursor::StandardCursorType::NormalCursor);
        }
        m_urlClick.setMouseCursor( mouseCursor );

    });
    
    m_urlClick.onClick = [this](){
        m_presetInfo.openUrl();
    };    
}

void PresetInfoView::resized()
{
    const auto area = getLocalBounds();
#if JUCE_WINDOWS
    const int leftMargin = 0;
#else
    const int leftMargin = 10;
#endif
    const int topMargin = 0;
    m_infoLabel.setBounds( leftMargin,
                            topMargin,
                             getWidth() - leftMargin * 2,
                             area.getHeight() - 2*topMargin);
    
    const int authorWidth = 100;
    m_urlClick.setBounds( getWidth() - authorWidth, topMargin, authorWidth, area.getHeight() - 2*topMargin );
    m_authorLabel.setBounds( getWidth() - 2*authorWidth - leftMargin, topMargin, 2*authorWidth, area.getHeight() - 2*topMargin );
}

void PresetInfoView::paint(juce::Graphics &g)
{
    const auto area = getLocalBounds();

    g.fillAll( juce::Colour(0xaa000000));
    
    g.setColour(Colour(0xbb000000));
    g.drawLine(0, 0, area.getWidth(), 0, 1.0);
}

void PresetInfoView::setText( const std::string& author, const std::string& description, const std::string& title )
{
    juce::AttributedString msg( title );
    msg.setFont( shout::Font::mainFont(14.0) );
    msg.setJustification( juce::Justification::centredLeft );
    msg.setColour( Colours::white.withAlpha( 0.7f ) );
    msg.setWordWrap( juce::AttributedString::WordWrap::byWord );
    
    if ( !description.empty() )
    {
        msg.append( " | " + description, shout::Font::labelFont(13.0).withExtraKerningFactor(0.01), Colours::white.withAlpha(0.7f) );
    }
    
    if ( !author.empty() )
    {
        juce::AttributedString auth( "by " + author );
        auth.setFont( shout::Font::mainFont(14.0) );
        auth.setJustification( juce::Justification::centredRight );
        auth.setColour( Colours::white.withAlpha( 0.7f ) );
        
        m_authorLabel.setText( auth );
    }
    else
    {
        m_authorLabel.setText( juce::AttributedString("") );
    }
    
    m_infoLabel.setText( std::move( msg ) );
}


#include "KeySwitcher.h"

#include "Font.h"
#include "InfoView.h"
#include "ArrowLeftAnimation.h"
#include "ArrowRightAnimation.h"

KeySwitcher::KeySwitcher( MainController* mc, TargetKey& _targetKey )
: juce::Component("KeySwitcher")
, m_nextButton( mc, String(arrowright_json, arrowright_jsonSize) )
, m_prevButton( mc, String(arrowleft_json, arrowleft_jsonSize) )
, m_targetKey(_targetKey)
{
    setupLabel();

    addAndMakeVisible( &m_prevButton );
    addAndMakeVisible( &m_nextButton );
    
    m_nextButton.onClick = [this](){
        m_targetKey.nextKey();
    };
    
    m_prevButton.onClick = [this](){
        m_targetKey.prevKey();
    };

    
    m_targetKey.targetKey.onChangedAndNow([this](const auto& val){
        auto key = hise::tonalKeyToString( val );
        setText( key );
    });
    
    m_targetKey.hasTonalKey.onChangedAndNow([this](const auto& isTonal){
        setVisible( isTonal );
    });
    
    getProperties().set(info_title_property, TRANS("key"));
    getProperties().set(info_message_property, TRANS("Click left and right arrows to change the musical key"));
}

void KeySwitcher::resized()
{
    const int buttonWidth = 40;
    auto area = getLocalBounds();
    
    m_prevButton.setBounds(0, 0, buttonWidth, area.getHeight());
    m_nextButton.setBounds(area.getWidth()-buttonWidth, 0, buttonWidth, area.getHeight());
    m_label.setBounds(0, 0, area.getWidth(), area.getHeight());
}

void KeySwitcher::setupLabel()
{
    addAndMakeVisible( &m_label );
//    m_label.setText( "", dontSendNotification );
//    m_label.setJustificationType( Justification::centred );
//    m_label.setEditable( false );
//    m_label.setFont( shout::Font::symbolJPFont(16.0));
//    m_label.setColour( juce::Label::textColourId, Colour( 0xffffffff) );
}

void KeySwitcher::setText(const String& text)
{
    juce::AttributedString msg( text.substring(0, 1) );
    msg.setFont( shout::Font::mainFont(16.0) );
    msg.setJustification( juce::Justification::centred );
    msg.setColour( Colours::white );
    msg.setWordWrap( juce::AttributedString::WordWrap::byWord );
    if (text.length() > 1)
    {
        msg.append(text.substring(1, 2), shout::Font::symbolJPFont(12.0).withExtraKerningFactor(-0.01), Colours::white.withAlpha(0.95f));
    }
    
    m_label.setText( std::move( msg ) );
    
}

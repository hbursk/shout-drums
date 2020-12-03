//
//  PresetTile.cpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 11/18/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#include "PresetTile.h"
#include "Font.h"
#include "DrumPadsAnimation.h"

PresetTile::PresetTile(MainController* mc, const std::string& name)
: m_icon( mc, String(drumpads_json, drumpads_jsonSize))
{
    setInterceptsMouseClicks(false, true);
    setupLabel( name );
    setupIcon();
}

void PresetTile::resized()
{
    const auto area = getLocalBounds();
    const float height = 20;
    m_label.setBounds(0, area.getHeight() - height - 5.0, area.getWidth(), height);
    m_icon.centreWithSize(area.getWidth(), area.getWidth());
}

void PresetTile::paint(Graphics& g)
{
    const auto area = getLocalBounds();
    const auto thickness = 3.0f;
    auto color = juce::Colour(0x00000000);
    g.fillAll(color);
    if (m_selected)
    {
        g.setColour(Colour(0xffffa0cd));
        g.drawLine(0, area.getHeight() - thickness, area.getWidth(), area.getHeight() - thickness, thickness);
    }
}

void PresetTile::text(const std::string& text)
{
    m_label.setText( text, dontSendNotification );
}

void PresetTile::setupLabel(const std::string& name)
{
    addAndMakeVisible( &m_label );
    text( name );
    m_label.setJustificationType( Justification::centred );
    m_label.setEditable( false );
    m_label.setFont( shout::Font::mainFont( 16.f ) );
    m_label.setColour( juce::Label::textColourId, Colour( 0xffffffff) );
}

void PresetTile::setupIcon()
{
    addAndMakeVisible(&m_icon);
    m_icon.animateOn(LottieButton::AnimateOn::Click);
    m_icon.onClick = [this](){
        
        auto mms = juce::Desktop::getInstance().getMainMouseSource();
        const juce::Point<float> center(getLocalBounds().getCentreX(), getLocalBounds().getCentreY());
            
        auto fakeEvent = juce::MouseEvent(mms, center, ModifierKeys::leftButtonModifier, 0, 0, 0, 0, 0, getParentComponent(), this, juce::Time::getCurrentTime(), center, juce::Time::getCurrentTime(), 1, false);
       getParentComponent()->mouseDown(fakeEvent);
       getParentComponent()->mouseUp(fakeEvent);
    };
}

void PresetTile::row(int row)
{
    m_row = row;
    repaint();
}

void PresetTile::selected(bool selected)
{
    if ( selected != m_selected)
    {
        m_selected = selected;
        repaint();
    }
}

//
//  Knob.cpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 8/18/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#include "PresetSwitcher.h"

#include "Font.h"
#include "InfoView.h"
#include "ArrowLeftAnimation.h"
#include "ArrowRightAnimation.h"

PresetSwitcher::PresetSwitcher( Presets& _presets, MainController* mc )
: juce::Component("PresetSwitcher")
, m_nextButton( mc, String(arrowright_json, arrowright_jsonSize) )
, m_prevButton( mc, String(arrowleft_json, arrowleft_jsonSize) )
, m_presets(_presets)
{
    addAndMakeVisible( &m_prevButton );
    addAndMakeVisible( &m_nextButton );
    
    m_nextButton.onClick = [this](){
        m_presets.nextPreset();
    };
    
    m_prevButton.onClick = [this](){
        m_presets.prevPreset();
    };

    setupLabel();
    
    m_presets.presetName.onChangedAndNow([this](const auto& val){
        m_label.setText( val, dontSendNotification );
    });
    
    getProperties().set(info_title_property, "presets");
    getProperties().set(info_message_property, TRANS("Click left and right arrows to load different sounds"));
}

void PresetSwitcher::resized()
{
    const int buttonWidth = 40;
    auto area = getLocalBounds();
    
    auto fb = juce::FlexBox();
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignContent = juce::FlexBox::AlignContent::center;

    fb.items.add (juce::FlexItem (m_prevButton).withMinWidth (buttonWidth).withMinHeight (buttonWidth));
    fb.items.add (juce::FlexItem (m_label).withMinWidth (area.getWidth() - 2*buttonWidth).withMinHeight (buttonWidth));
    fb.items.add (juce::FlexItem (m_nextButton).withMinWidth (buttonWidth).withMinHeight (buttonWidth));

    fb.performLayout (area.toFloat() );
}

void PresetSwitcher::setupLabel()
{
    addAndMakeVisible( &m_label );
    m_label.setText( "", dontSendNotification );
    m_label.setJustificationType( Justification::centred );
    m_label.setEditable( false );
    m_label.setFont( shout::Font::mainFont( 18.0 ) );
    m_label.setColour( juce::Label::textColourId, Colour( 0xffffffff) );
}

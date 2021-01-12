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
#include "KeysAnimation.h"
#include "MouthAnimation.h"
#include "SpeakerAnimation.h"
#include "WaveformAnimation.h"

PresetTile::PresetTile(MainController* mc, const Preset& preset)
: m_icon( mc, animationForCategoryType(preset.category.type))
{
    category(preset.category);
    setInterceptsMouseClicks(false, true);
    setupLabel( preset.name );
    setupIcon();
}

void PresetTile::resized()
{
    const auto area = getLocalBounds();
    const float height = 20;
    updateIconScale();
    m_label.setBounds(0, area.getHeight() - height - 5.0, area.getWidth(), height);
}

void PresetTile::paint(Graphics& g)
{
    const auto area = getLocalBounds();
    const auto thickness = 3.0f;

    if (m_selected)
    {
        g.setColour(m_selectionColor);
        g.drawLine(0, area.getHeight() - thickness, area.getWidth(), area.getHeight() - thickness, thickness);
    }
}

void PresetTile::text(const std::string& text)
{
    m_label.setText( text, dontSendNotification );
}

void PresetTile::preset(const Preset& preset)
{
    m_label.setText( preset.name, dontSendNotification);
    if ( m_lastCategoryType != preset.category.type )
    {
        category(preset.category);
        m_icon.animation( animationForCategoryType(preset.category.type));
        updateIconScale();
    }
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

void PresetTile::updateIconScale()
{
    float scale = 1.f;
    switch (m_lastCategoryType)
    {
        case CategoryType::Bass:
        case CategoryType::Vox:
            scale = 0.8f;
            break;
            
        case CategoryType::FX:
            scale = 2.f;
            break;
            
        default:
            scale = 1.f;
            break;
    }
    const auto area = getLocalBounds();
    m_icon.centreWithSize(area.getWidth() * scale, area.getWidth() * scale);
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

String PresetTile::animationForCategoryType(const CategoryType& type)
{
    switch (type)
    {
        case CategoryType::Drums:
            return String(drumpads_json, drumpads_jsonSize);

        case CategoryType::Lead:
            return String(keys_json, keys_jsonSize);

        case CategoryType::FX:
            return String(waveform_json, waveform_jsonSize);

        case CategoryType::Vox:
            return String(mouth_json, mouth_jsonSize);

        case CategoryType::Bass:
            return String(speaker_json, speaker_jsonSize);

        default:
            throw std::runtime_error("Uknown category type");
    }
}

void PresetTile::category(CategoryTypeAndColor category_)
{
    if ( m_lastCategoryType != category_.type )
    {
        m_lastCategoryType = category_.type;
        m_selectionColor = category_.color;
        
        repaint();
    }

}


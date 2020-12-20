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

PresetTile::PresetTile(MainController* mc, const Preset& preset)
: m_icon( mc, animationForCategoryType(preset.type))
{
    category(preset.type);
    setInterceptsMouseClicks(false, true);
    setupLabel( preset.name );
    setupIcon();
}

void PresetTile::resized()
{
    const auto area = getLocalBounds();
    const float height = 20;
    const float scale = m_lastCategoryType == CategoryType::Vox ? 0.8f : 1.f;
    m_label.setBounds(0, area.getHeight() - height - 5.0, area.getWidth(), height);
    m_icon.centreWithSize(area.getWidth() * scale, area.getWidth() * scale);
}

void PresetTile::paint(Graphics& g)
{
    const auto area = getLocalBounds();
    const auto thickness = 3.0f;
//    auto color = juce::Colour(0x00000000);
//    g.fillAll(color);
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
    if ( m_lastCategoryType != preset.type )
    {
        category(preset.type);
        m_icon.animation( animationForCategoryType(preset.type));
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
            return String(keys_json, keys_jsonSize);

        case CategoryType::Vox:
            return String(mouth_json, mouth_jsonSize);

        case CategoryType::Bass:
            return String(keys_json, keys_jsonSize);

        default:
            throw std::runtime_error("Uknown category type");
    }

}

void PresetTile::category(CategoryType type)
{
    if ( m_lastCategoryType != type )
    {
        m_lastCategoryType = type;
        
        switch (m_lastCategoryType)
        {
            case CategoryType::Drums:
                m_selectionColor = shout::spec::color::drums_pink;
                break;
                
            case CategoryType::Vox:
                m_selectionColor = shout::spec::color::vox_pink;
                break;

            default:
                m_selectionColor = shout::spec::color::drums_pink;
                break;
        }
        
        repaint();
    }

}


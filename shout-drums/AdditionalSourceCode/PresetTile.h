//
//  PresetTile.hpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 11/18/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#pragma once

#include "JuceHeader.h"
#include "LottieButton.h"
#include "Presets.h"
#include "Colors.h"

#include <string>

class PresetTile : public juce::Component
{
public:
    PresetTile(MainController* mc, const Preset& preset);
    virtual ~PresetTile() = default;
    
    void resized() override;

    void paint(Graphics& g) override;

    void text(const std::string& text);
    void row( int row );
    void selected(bool selected);
    void preset(const Preset& preset);
    
private:
    void setupLabel(const std::string& name);
    void setupIcon();
    void category(CategoryTypeAndColor category);
    void updateIconScale();
    
    String animationForCategoryType(const CategoryType& type);
    
    juce::Label m_label;
    LottieButton m_icon;
    CategoryType m_lastCategoryType = CategoryType::Unknown;
    juce::Colour m_selectionColor = shout::spec::color::drums_pink;
    int m_row = -1;
    bool m_selected = false;
    
};

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
#include <string>

class PresetTile : public juce::Component
{
public:
    PresetTile(MainController* mc, const std::string& name);
    virtual ~PresetTile() = default;
    
    void resized() override;

    void paint(Graphics& g) override;

    void text(const std::string& text);
    void row( int row );
    void selected(bool selected);
    
private:
    void setupLabel(const std::string& name);
    void setupIcon();
    
    juce::Label m_label;
    LottieButton m_icon;
    int m_row = -1;
    bool m_selected = false;
    
};

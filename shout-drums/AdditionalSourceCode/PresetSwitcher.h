//
//  Knob.hpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 8/18/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#pragma once

#include "JuceHeader.h"
#include "Presets.h"
#include "LottieButton.h"

class PresetSwitcher : public juce::Component
{
public:
    PresetSwitcher() = delete;
    PresetSwitcher( Presets& _presets, MainController* mc );
    ~PresetSwitcher() = default;
    
    void resized() override;
    
private:
    void setupLabel();
    
    LottieButton m_prevButton;
    LottieButton m_nextButton;
    juce::Label  m_label;
    
    Presets& m_presets;
    
};

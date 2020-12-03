//
//  PresetBarContainer.hpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 11/17/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#pragma once

#include "JuceHeader.h"
#include "Presets.h"
#include "PresetScrollingPicker.h"
#include "PresetSwitcher.h"
#include "MidiBarComponent.h"
#include "MidiListener.h"

class PresetBarContainer : public juce::Component
{
public:
    enum class State
    {
        Closed,
        Open
    };
    
    PresetBarContainer(MainController* mc, Presets& presets, MidiListener& midiListener);
    ~PresetBarContainer() = default;
    
    void resized() override;

    void paint(Graphics& g) override;
    
    void closePresetBar();

private:
    
    void animateOpen();
    void animateClose();
    
    PresetSwitcher m_presetSwitcher;
    MidiBarComponent m_midiBarComponent;
    juce::ImageButton m_expandButton;
    juce::ImageButton m_presetTitleButton;
    State m_state = State::Closed;
    Rectangle<int> m_closedPos;
    Rectangle<int> m_openedPos;
    RLottieComponent m_expandAnimation;
    PresetScrollingPicker m_presetPicker;
    
};

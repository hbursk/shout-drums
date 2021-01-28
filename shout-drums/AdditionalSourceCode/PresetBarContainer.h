//
//  PresetBarContainer.hpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 11/17/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#pragma once

#include "JuceHeader.h"
#include "App.h"
#include "Presets.h"
#include "PresetInfoView.h"
#include "PresetScrollingPicker.h"
#include "PresetSwitcher.h"
#include "MidiBarComponent.h"
#include "MidiListener.h"
#include "LottieButton.h"
#include "PowerButton.h"
#include "KeySwitcher.h"

class PresetBarContainer : public juce::Component
{
public:
    
    PresetBarContainer(MainController* mc, shout::App& app, MidiListener& midiListener);
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
    Rectangle<int> m_closedPos;
    Rectangle<int> m_openedPos;
    RLottieComponent m_expandAnimation;
    PresetScrollingPicker m_presetPicker;
    LottieButton m_arpButton;
    Presets& m_presets;
    KeySwitcher m_keySwitcher;
    shout::PresetInfoView m_presetInfoView;
};

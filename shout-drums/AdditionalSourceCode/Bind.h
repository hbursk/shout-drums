//
//  Bind.h
//  DrumTest - App
//
//  Created by Hayden Bursk on 8/18/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#pragma once

#include "JuceHeader.h"

class Binder : public hise::MainController::UserPresetHandler::Listener
{
public:
    Binder( hise::MainController* mc );
    ~Binder();

    void bind( juce::Slider& slider, const std::string& processor, int paramId );
    void bindDB( juce::Slider& slider, const std::string& processor, int paramId );
    void update();

    // UserPresetHandler::Listener
    void presetChanged( const File& newPreset ) override;
    void presetListUpdated() override;

private:
    void storeUpdate( std::function<void()> _update );

    hise::MainController*              m_mainController = nullptr;
    std::vector<std::function<void()>> m_updateBindings;
};

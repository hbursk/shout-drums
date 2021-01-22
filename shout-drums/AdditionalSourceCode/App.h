//
//  Knob.hpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 8/18/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#pragma once

#include "JuceHeader.h"

#include "Localizations.h"
#include "MidiListener.h"
#include "Presets.h"
#include "TargetKey.h"
#include "SampleMaps.h"

namespace shout
{
class App
{
public:
    App() = delete;
    App( hise::MainController* );
    ~App() = default;

    Presets&      presets();
    SampleMaps&   sampleMaps();
    MidiListener& midiListener();
    TargetKey&    targetKey();

private:
    hise::MainController* m_mainController = nullptr;

    Presets       m_presets;
    SampleMaps    m_sampleMaps;
    MidiListener  m_midiListener;
    Localizations m_localizations;
    TargetKey     m_targetKey;
};
} // namespace shout

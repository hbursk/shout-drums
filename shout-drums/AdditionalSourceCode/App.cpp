//
//  Knob.cpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 8/18/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#include "App.h"

using namespace shout;

App::App( hise::MainController* _mc )
: m_mainController( _mc )
, m_presets( _mc )
, m_presetInfo( m_presets )
, m_sampleMaps( _mc )
, m_midiListener( _mc->getKeyboardState() )
, m_targetKey( _mc, m_presets)
{
    assert( m_mainController );
}

Presets& App::presets()
{
    return m_presets;
}

PresetInfo& App::presetInfo()
{
    return m_presetInfo;
}

SampleMaps& App::sampleMaps()
{
    return m_sampleMaps;
}

MidiListener& App::midiListener()
{
    return m_midiListener;
}

TargetKey& App::targetKey()
{
    return m_targetKey;
}

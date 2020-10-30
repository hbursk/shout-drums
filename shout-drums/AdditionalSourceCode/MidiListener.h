//
//  MidiListener.hpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 9/20/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#pragma once

#include "JuceHeader.h"
#include "Property.h"

class MidiListener : public MidiKeyboardStateListener
{
public:
    MidiListener(MidiKeyboardState& state);
    ~MidiListener();
    
    void handleNoteOn (MidiKeyboardState* source,
                       int midiChannel, int midiNoteNumber, float velocity) override;
    
    void handleNoteOff (MidiKeyboardState* source,
                        int midiChannel, int midiNoteNumber, float velocity) override;
    
    Property<std::vector<int>> activeNotes;
    
    MidiKeyboardState& m_keyboardState;
};

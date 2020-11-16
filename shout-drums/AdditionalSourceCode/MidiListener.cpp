//
//  MidiListener.cpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 9/20/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#include "MidiListener.h"

MidiListener::MidiListener(MidiKeyboardState& state)
: m_keyboardState(state)
{
    m_keyboardState.addListener(this);
}

MidiListener::~MidiListener()
{
    m_keyboardState.removeListener(this);
}

void MidiListener::handleNoteOn (MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity)
{
    auto notes = activeNotes();

    notes.push_back( midiNoteNumber );
    activeNotes( notes );
}

void MidiListener::handleNoteOff (MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity)
{
    auto notes = activeNotes();
    
    auto dying = dyingNotes();
    dying.clear();
    
    for (auto it = notes.begin(); it != notes.end(); it++ )
    {
        if (midiNoteNumber == *it )
        {
            notes.erase( it );
            dying.push_back(midiNoteNumber);
            break;
        }
    }
    
    activeNotes( notes );
    dyingNotes( dying );
}

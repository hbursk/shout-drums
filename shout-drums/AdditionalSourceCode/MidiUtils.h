#pragma once

#include "JuceHeader.h"

#include <string>

class MidiUtils
{
public:
    static juce::String noteNumberToString( int noteNumber );
    static juce::String noteNumberToStringWithOctave( int noteNumber );
    
};

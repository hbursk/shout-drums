#pragma once

#include <string>

class MidiUtils
{
public:
    static std::string noteNumberToString( int noteNumber );
    static std::string noteNumberToStringWithOctave( int noteNumber );
    
};

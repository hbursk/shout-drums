//
//  MidiUtils.cpp
//  Snackage - Shared Code
//
//  Created by Hayden Bursk on 12/30/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#include "MidiUtils.h"

#include <cmath>

std::string MidiUtils::noteNumberToString( int noteNumber )
{
    // mod 12 to get the scale note
    std::string note;
    
    auto moddedNote = noteNumber % 12;
    switch (moddedNote)
    {
        case 0:
            note = "C";
            break;
            
        case 1:
            note = "C♯";
            break;
            
        case 2:
            note = "D";
            break;
            
        case 3:
            note = "D♯";
            break;
            
        case 4:
            note = "E";
            break;
            
        case 5:
            note = "F";
            break;
            
        case 6:
            note = "F♯";
            break;
            
        case 7:
            note = "G";
            break;
            
        case 8:
            note = "G♯";
            break;
            
        case 9:
            note = "A";
            break;
            
        case 10:
            note = "A♯";
            break;
            
        case 11:
            note = "B";
            break;
    }
    
    return note;
}

std::string MidiUtils::noteNumberToStringWithOctave( int noteNumber )
{
    auto note = noteNumberToString(noteNumber);
    
    int range = std::floor( noteNumber / 12);
    int rangeOffset = range - 2;
    
    note += std::to_string(rangeOffset);
    
    return note;
}


//
//  MidiBarComponent.hpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 9/20/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#pragma once

#include "JuceHeader.h"
#include "MidiListener.h"

class MidiBarComponent : public juce::Component
{
public:
    struct Range
    {
        Range( int low_, int high_, juce::Colour color_ )
        : low( low_ )
        , high( high_ )
        , color( color_ )
        {
            
        }
        
        int low = 0;
        int high = 127;
        juce::Colour color = juce::Colours::grey;
    };
    
    MidiBarComponent( MidiListener& listener );
    virtual ~MidiBarComponent() = default;
    
    void paint(Graphics& g) override;

private:
    void clearRanges();
    void addRange(int low, int high, juce::Colour color);
    
    MidiListener& m_midiListener;
    std::vector<Range> m_ranges;
    int m_lowest = 0;
    int m_highest = 127;
    
};

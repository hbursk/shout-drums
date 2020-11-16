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

class MidiBarComponent : public juce::Component, public juce::Timer
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
    
    struct DyingNote
    {
        DyingNote() = default;
        
        int note = 0;
        float alpha = 1.0f;
        float decrementValue = 1.0f/( 0.3f * 60.f);
        
        void decrement()
        {
            alpha -= decrementValue;
            if ( alpha <= 0 )
            {
                alpha = 0;
            }
        }
        
        float valueThenDecrement()
        {
            float a = alpha;
            decrement();
            return a;
        }
    };
    
    MidiBarComponent( MidiListener& listener );
    virtual ~MidiBarComponent() = default;
    
    void paint(Graphics& g) override;
    
    void timerCallback() override;

private:
    void clearRanges();
    void addRange(int low, int high, juce::Colour color);
    
    void updateDyingNotes();
    void clearDeadNotes();
    
    MidiListener& m_midiListener;
    std::vector<Range> m_ranges;
    std::vector<DyingNote> m_dyingNotes;
    int m_lowest = 0;
    int m_highest = 127;
    
};

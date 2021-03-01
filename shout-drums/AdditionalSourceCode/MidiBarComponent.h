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
#include "Presets.h"

constexpr float frame_rate = 60.0;

class MidiBarComponent : public juce::Component, public juce::Timer
{
public:
    struct Range
    {
        Range( int low_, int high_, juce::Colour barColor_, juce::Colour lightColor_, bool primary_ )
        : low( low_ )
        , high( high_ )
        , barColor( barColor_ )
        , lightColor( lightColor_ )
        , primary( primary_ )
        {
        }
        
        bool primary = false;
        int low = 0;
        int high = 127;
        juce::Colour barColor = juce::Colours::grey;
        juce::Colour lightColor = juce::Colours::white;
    };
    
    struct DyingNote
    {
        DyingNote() = default;
        
        int note = 0;
        float alpha = 1.0f;
        float decrementValue = 1.0f/( 0.3f * frame_rate);
        
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
    
    MidiBarComponent( MidiListener& listener, Presets& presets );
    virtual ~MidiBarComponent();
    
    void paint(Graphics& g) override;
    
    void timerCallback() override;

private:
    void clearRanges();
    void addRange(int low, int high, juce::Colour barColor, juce::Colour lightColor, bool primary);
    void updateRanges(CategoryType type);
    
    void updateDyingNotes();
    void clearDeadNotes();
    
    MidiListener& m_midiListener;
    Presets& m_presets;
    
    std::vector<Range> m_ranges;
    std::vector<DyingNote> m_dyingNotes;
    int m_lowest = 0;
    int m_highest = 127;
    
};

//
//  MidiBarComponent.cpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 9/20/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#include "MidiBarComponent.h"

#include "InfoView.h"
#include <cmath>


MidiBarComponent::MidiBarComponent( MidiListener& listener )
: m_midiListener( listener )
{
    addRange( 12, 35, juce::Colour( 0xff73aceb ), juce::Colour( 0xff73aceb ).brighter(1.25) );
    addRange( 36, 59, juce::Colour( 0xff5fbe75 ), juce::Colour( 0xff5fbe75 ).brighter(1.25) );
    addRange( 60, 84, juce::Colour( 0xffffb72c ),  juce::Colour( 0xffffb72c ).brighter(1.25) );
    
    m_midiListener.activeNotes.onChanged( [this](const auto&){
        juce::MessageManager::callAsync([this](){
            repaint();
        });
    });
    
    m_midiListener.dyingNotes.onChanged([this](const auto& notes){
        juce::MessageManager::callAsync([this, &notes](){
            for (const auto& note : notes)
            {
                DyingNote dying;
                dying.note = note;
                m_dyingNotes.push_back(dying);
            }
            
            startTimer(1000.0/frame_rate);
        });
    });
    
    getProperties().set(info_title_property, "midi bar");
    getProperties().set(info_message_property, "Shows the notes you're playing and where on the keyboard the sounds pitch down and up");
}


void MidiBarComponent::paint(Graphics& g)
{
    if ( m_ranges.empty() )
    {
        return;
    }
    
    auto notes = m_midiListener.activeNotes();
    
    const int numSegments = m_highest - m_lowest;
    const auto area = getLocalBounds();
    const int segmentWidth = area.getWidth() / numSegments;
    
    // draw ranges
    for ( const auto& range : m_ranges )
    {
        const auto x = ( range.low - m_lowest ) * segmentWidth;
        const auto width = ( range.high - range.low + 1 ) * segmentWidth;
        g.setColour( range.barColor );
        g.fillRect( x, 0, width, area.getHeight() );
        
        // draw notes
        for ( const auto& note : notes )
        {
            if ( note < range.low )
            {
                continue;
            }
            else if ( note > range.high )
            {
                continue;
            }
            
            const auto noteX = ( note - m_lowest ) * segmentWidth;
            g.setColour( range.lightColor );
            g.fillRect( noteX, 0, segmentWidth, area.getHeight() );
        }
        
        // draw fading notes
        for ( auto& dying : m_dyingNotes)
        {
            if ( dying.note < range.low )
            {
                continue;
            }
            else if ( dying.note > range.high )
            {
                continue;
            }
            
            const auto noteX = ( dying.note - m_lowest ) * segmentWidth;
            g.setColour( range.lightColor.withAlpha(dying.alpha) );
            g.fillRect( noteX, 0, segmentWidth, area.getHeight() );
        }
    }
}

void MidiBarComponent::clearRanges()
{
    m_ranges.clear();
}

void MidiBarComponent::addRange(int low, int high, juce::Colour barColor, juce::Colour lightColor)
{
    m_ranges.push_back( Range(low, high, barColor, lightColor) );
    
    m_lowest = 127;
    m_highest = 0;
    for ( const auto& range : m_ranges )
    {
        m_lowest = std::min(m_lowest, range.low);
        m_highest = std::max(m_highest, range.high);
    }
}

void MidiBarComponent::updateDyingNotes()
{
    for (auto& note : m_dyingNotes)
    {
        note.decrement();
    }
    
    repaint();
}

void MidiBarComponent::clearDeadNotes()
{
    auto it = m_dyingNotes.begin();
    while (it != m_dyingNotes.end())
    {
        auto note = *it;
        if (note.alpha == 0)
        {
            m_dyingNotes.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void MidiBarComponent::timerCallback()
{
    updateDyingNotes();
    
    clearDeadNotes();
    
    if (m_dyingNotes.empty())
    {
        stopTimer();
    }
}

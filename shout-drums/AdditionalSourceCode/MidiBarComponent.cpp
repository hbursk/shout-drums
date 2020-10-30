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
    addRange( 12, 35, juce::Colour( 255, 109, 107 ) );
    addRange( 36, 59, juce::Colour( 255, 201, 243 ) );
    addRange( 60, 84, juce::Colour( 177, 247, 227 ) );
    
    m_midiListener.activeNotes.onChanged( [this](const auto&){
        juce::MessageManager::callAsync([this](){
            repaint();
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
        g.setColour( range.color.withBrightness( 0.7f ) );
        g.fillRect(x, 0, width, area.getHeight() );
        
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
            g.setColour( range.color );
            g.fillRect( noteX, 0, segmentWidth, area.getHeight() );
        }
    }
}

void MidiBarComponent::clearRanges()
{
    m_ranges.clear();
}

void MidiBarComponent::addRange(int low, int high, juce::Colour color)
{
    m_ranges.push_back( Range(low, high, color) );
    
    m_lowest = 127;
    m_highest = 0;
    for ( const auto& range : m_ranges )
    {
        m_lowest = std::min(m_lowest, range.low);
        m_highest = std::max(m_highest, range.high);
    }
}

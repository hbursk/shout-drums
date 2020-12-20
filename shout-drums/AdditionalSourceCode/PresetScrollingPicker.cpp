//
//  PresetScrollingPicker.cpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 11/18/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#include "PresetScrollingPicker.h"
#include "PresetTile.h"

constexpr int row_height = 128;
constexpr int list_height = 128;

PresetScrollingPicker::PresetScrollingPicker(MainController* mc, Presets& presets)
: m_presets(presets)
, m_listBox("Presets", this)
, m_mainController(mc)
{
    addAndMakeVisible(&m_listBox);
    m_listBox.setInterceptsMouseClicks(false, true);
    m_listBox.setRowHeight(row_height);
    m_listBox.getViewport()->setClipBoundsForScrollbar(false);
    m_listBox.getViewport()->setScrollBarThickness(8.0);
    m_listBox.getViewport()->setScrollBarPosition(true, true);
    m_listBox.getViewport()->setScrollOnDragEnabled(true);
    m_listBox.setTransform(AffineTransform::rotation(-1.0 * float_Pi/2.0));
    
    m_presets.presetSelection.onChanged([this](const auto& selection){
        m_listBox.selectRow(static_cast<int>(selection.linearIndex));
    });
}

void PresetScrollingPicker::resized()
{
    const auto area = getLocalBounds();
    m_listBox.setBounds(-1.0 * area.getHeight(), 0, area.getHeight(), area.getWidth());
}

void PresetScrollingPicker::paint(Graphics& g)
{
    g.fillAll(juce::Colour(0x00000000));
    
    const auto area = getLocalBounds();
    g.setColour(Colour(0xbb000000));
    g.drawLine(0, 0, area.getWidth(), 0, 1.0);
}

// ListBoxModel
int PresetScrollingPicker::getNumRows()
{
    return static_cast<int>(m_presets.numPresets());
}

void PresetScrollingPicker::paintListBoxItem( int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
    g.fillAll(juce::Colour(0x44000000));
}
    
Component* PresetScrollingPicker::refreshComponentForRow (int rowNumber, bool isRowSelected,
                                           Component* existingComponentToUpdate)
{
    if ( rowNumber >= getNumRows())
    {
        if (existingComponentToUpdate != nullptr )
        {
            delete existingComponentToUpdate;
        }
        
        return nullptr;
    }
    
    auto preset = m_presets.presetForIndex(rowNumber);
    if (existingComponentToUpdate == nullptr)
    {
        auto presetTile = new PresetTile( m_mainController, preset );
        existingComponentToUpdate = presetTile;
        presetTile->row(rowNumber);
        presetTile->selected(isRowSelected);
        presetTile->setCentrePosition(0, 0);
        presetTile->setTransform(AffineTransform::rotation(float_Pi/2.0).translated(list_height, 0) );
    }
    else
    {
        auto presetTile = static_cast<PresetTile*>(existingComponentToUpdate);
        presetTile->row(rowNumber);
        presetTile->preset(preset);
        presetTile->selected(isRowSelected);
    }
    
    return existingComponentToUpdate;
}

void PresetScrollingPicker::listBoxItemClicked (int row, const MouseEvent&)
{
    m_presets.loadPreset(row);
}

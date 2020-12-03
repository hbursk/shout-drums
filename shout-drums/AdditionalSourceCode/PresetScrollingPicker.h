//
//  PresetScrollingPicker.hpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 11/18/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#pragma once

#include "JuceHeader.h"
#include "Presets.h"

class PresetScrollingPicker : public juce::Component, public juce::ListBoxModel
{
public:
    PresetScrollingPicker(MainController* mc, Presets& presets);
    virtual ~PresetScrollingPicker() = default;
    
    void resized() override;

    void paint(Graphics& g) override;
    
    // ListBoxModel
    int getNumRows() override;
    void paintListBoxItem( int rowNumber, Graphics& g, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForRow (int rowNumber, bool isRowSelected,
                                               Component* existingComponentToUpdate) override;
    void listBoxItemClicked (int row, const MouseEvent&) override;
    
private:
    Presets& m_presets;
    juce::ListBox m_listBox;
    MainController* m_mainController;
};

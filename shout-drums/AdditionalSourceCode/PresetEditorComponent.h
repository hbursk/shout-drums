//
//  PresetEditorComponent.hpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 9/15/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#pragma once

#include "JuceHeader.h"

#include "BrightComboBox.h"
#include "PowerButton.h"
#include "SampleMaps.h"

class PresetEditorComponent : public juce::Component
{
public:
    PresetEditorComponent( hise::MainController* mc, SampleMaps& sampleMaps );
    virtual ~PresetEditorComponent() = default;
    
    void resized() override;

    void paint(Graphics& g) override;

private:
    void fillSampleMapList(const std::vector<std::string>& list, const std::string& name, BrightComboBox<raw::Data<String>::SampleMap>& comboMap);
    
    BrightComboBox<raw::Data<String>::SampleMap> m_sampleMapSelector;
    BrightComboBox<raw::Data<String>::SampleMap> m_kickMapSelector;
    BrightComboBox<raw::Data<String>::SampleMap> m_snareMapSelector;
    BrightComboBox<raw::Data<String>::SampleMap> m_hatMapSelector;
    BrightComboBox<raw::Data<String>::SampleMap> m_clapMapSelector;
    BrightComboBox<raw::Data<String>::SampleMap> m_cymbalMapSelector;
    BrightComboBox<raw::Data<String>::SampleMap> m_percMapSelector;
    BrightComboBox<raw::Data<String>::SampleMap> m_tomsMapSelector;
    
    PowerButton m_samplerMuter;
    PowerButton m_kicksMuter;
    PowerButton m_snaresMuter;
    PowerButton m_hatsMuter;
    PowerButton m_clapsMuter;
    PowerButton m_cymbalsMuter;
    PowerButton m_percMuter;
    PowerButton m_tomsMuter;
    
    juce::TextButton m_savePresetButton;
    
    hise::PresetBrowser m_presetBrowser;
    
    SampleMaps& m_sampleMaps;
};

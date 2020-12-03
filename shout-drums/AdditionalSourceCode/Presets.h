//
//  Knob.hpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 8/18/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#pragma once

#include "JuceHeader.h"

#include "Property.h"

#include <vector>

struct Preset
{
    std::string name;
    juce::File file;
};

struct Category
{
    std::string name;
    std::vector<Preset> presets;
};

struct Bank
{
    std::string name;
    std::vector<Category> categories;
};

struct PresetSelection
{
    int bank = -1;
    int category = -1;
    int preset = -1;
    int linearIndex = -1;
    
    inline bool operator==(const PresetSelection& other ) const
    {
        return bank == other.bank &&
               category == other.category &&
               preset == other.preset;
    }
    
    inline bool operator!=(const PresetSelection& other) const
    {
        return bank != other.bank ||
               category != other.category ||
               preset != other.preset;
    }
};

class Presets : public hise::MainController::UserPresetHandler::Listener
{
public:
    Presets() = delete;
    Presets(hise::MainController*);
    ~Presets();

    // UserPresetHandler::Listener
    void presetChanged(const File& newPreset) override;
    void presetListUpdated() override;
    
    void loadPreset( PresetSelection selection );
    void loadPreset( size_t index );
    void nextPreset();
    void prevPreset();
    
    Property<std::string> presetName;
    Property<std::string> presetBank;
    Property<std::string> presetCategory;
    Property<PresetSelection> presetSelection;
    
    const std::vector<Bank>& banks() const;
    
    const std::string presetNameForIndex(size_t index) const;
    
    size_t numPresets() const;

private:
    void buildPresets();
    void updateSelection();
    
    Preset presetForIndex(size_t index) const;
    int indexForPreset(int bank, int category, int preset) const;
    
    std::string lowercase(const std::string& str);
    
    hise::MainController* m_mainController = nullptr;
    std::vector<Bank> m_banks;
};

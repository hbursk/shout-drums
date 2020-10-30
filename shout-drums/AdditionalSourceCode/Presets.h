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
    size_t bank = 0;
    size_t category = 0;
    size_t preset = 0;
    
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
    void nextPreset();
    void prevPreset();
    
    Property<std::string> presetName;
    Property<std::string> presetBank;
    Property<std::string> presetCategory;
    Property<PresetSelection> presetSelection;

private:
    void buildPresets();
    void updateSelection();
    std::string lowercase(const std::string& str);
    
    hise::MainController* m_mainController = nullptr;
    std::vector<Bank> m_banks;
};

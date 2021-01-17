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

enum class CategoryType
{
    Drums,
    FX,
    Vox,
    Lead,
    Bass,
    Unknown
};

enum class PickerState
{
    Closed,
    Open
};


struct CategoryTypeAndColor
{
    CategoryTypeAndColor() = default;
    CategoryTypeAndColor( CategoryType type_, juce::Colour color_)
    : type(type_)
    , color(color_)
    {
    }
    
    CategoryType type = CategoryType::Unknown;
    juce::Colour color = juce::Colours::grey;
    
    inline bool operator==(const CategoryTypeAndColor& other ) const
    {
        return type == other.type;
    }
    
    inline bool operator!=(const CategoryTypeAndColor& other) const
    {
        return type != other.type;
    }

};

struct Preset
{
    std::string name;
    juce::File file;
    CategoryTypeAndColor category;
};

struct Category
{
    std::string name;
    std::vector<Preset> presets;
    CategoryType type = CategoryType::Unknown;
    juce::Colour color = juce::Colours::grey;
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
    Property<CategoryTypeAndColor> presetCategory;
    Property<PresetSelection> presetSelection;
    Property<bool> supportsArpeggiator{false};
    Property<PickerState> pickerState{PickerState::Closed};
    
    const std::vector<Bank>& banks() const;
    
    const std::string presetNameForIndex(size_t index) const;
    Preset presetForIndex(size_t index) const;

    size_t numPresets() const;

private:
    void buildPresets();
    void updateSelection();
    
    int indexForPreset(int bank, int category, int preset) const;
    CategoryType categoryStringToType(const std::string& category) const;
    std::string categoryTypeToString(const CategoryType& type) const;
    juce::Colour categoryTypeToColor(const CategoryType& type) const;

    std::string lowercase(const std::string& str);
    
    hise::MainController* m_mainController = nullptr;
    std::vector<Bank> m_banks;
};

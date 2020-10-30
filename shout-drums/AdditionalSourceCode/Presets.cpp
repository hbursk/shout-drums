//
//  Knob.cpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 8/18/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#include "Presets.h"

#include <algorithm>

Presets::Presets(hise::MainController* _mc)
: m_mainController( _mc )
{
    assert( m_mainController );
    m_mainController->getUserPresetHandler().addListener( this );

    buildPresets();

    updateSelection();
}

Presets::~Presets()
{
    m_mainController->getUserPresetHandler().removeListener( this );
}

void Presets::presetChanged(const File& newPreset)
{
    updateSelection();
}

void Presets::presetListUpdated()
{
    buildPresets();
}

void Presets::loadPreset( PresetSelection selection )
{
    auto preset = m_banks[selection.bank]
                  .categories[selection.category]
                  .presets[selection.preset];
    
    m_mainController->getUserPresetHandler().loadUserPreset(preset.file);
}

void Presets::nextPreset()
{
    m_mainController->getUserPresetHandler().incPreset( true, false );
}

void Presets::prevPreset()
{
    m_mainController->getUserPresetHandler().incPreset( false, false );
}

void Presets::buildPresets()
{
    m_banks.clear();
    
    Array<File> allPresets;

    auto userDirectory = FrontendHandler::getUserPresetDirectory();

    userDirectory.findChildFiles(allPresets, File::findFiles, true, "*.preset");
    PresetBrowser::DataBaseHelpers::cleanFileList(m_mainController, allPresets);
    allPresets.sort();
    
    Bank currentBank;
    Category currentCategory;
    
    m_banks.push_back( currentBank );
    size_t bankIndex = 0;
    size_t catIndex = 0;
    for ( const auto& preset : allPresets )
    {
        auto name = lowercase( preset.getFileNameWithoutExtension().toStdString() );
        auto category = preset.getParentDirectory();
        auto categoryName = category.getFileNameWithoutExtension().toStdString();
        auto bankName = category.getParentDirectory().getFileNameWithoutExtension().toStdString();
        
        Preset p;
        p.name = name;
        p.file = preset;
        
        auto& b = m_banks[bankIndex];
        if ( b.name.empty() )
        {
            // first entry
            b.name = bankName;
            Category c;
            c.name = categoryName;
            c.presets.push_back( p );
            b.categories.push_back( c );
            continue;
        }
        
        auto& c = b.categories[catIndex];

        if ( b.name == bankName)
        {
            // still on the same bank
            if ( c.name != categoryName )
            {
                // next category
                catIndex++;
                Category nextC;
                nextC.name = categoryName;
                nextC.presets.push_back( p );
                b.categories.push_back( nextC );
            }
            else
            {
                // same category
                c.presets.push_back( p );
            }
            
        }
        else if ( b.name != bankName )
        {
            // need new bank
            bankIndex++;
            
            Bank nextBank;
            nextBank.name = bankName;
            
            Category nextCategory;
            nextCategory.name = categoryName;
            nextCategory.presets.push_back( p );
            
            nextBank.categories.push_back( nextCategory );
            m_banks.push_back( nextBank );
            
            catIndex = 0;
        }
    }
}

void Presets::updateSelection()
{
    auto file = m_mainController->getUserPresetHandler().getCurrentlyLoadedFile();
    auto fileName = file.getFileNameWithoutExtension();
    
    if ( fileName.isEmpty() )
    {
        presetName( TRANS("load a preset").toStdString() );
        presetBank( "Factory" );
        presetCategory( "Drums" );
        presetSelection( PresetSelection() );
        return;
    }
    
    auto catDir = file.getParentDirectory();
    auto bankDir = catDir.getParentDirectory();
    auto presetStr = lowercase( fileName.toStdString() );
    
    size_t bank = 0;
    size_t cat = 0;
    size_t preset = 0;
    for ( bank=0; bank < m_banks.size(); bank++ )
    {
        if ( m_banks[bank].name == bankDir.getFileNameWithoutExtension() )
        {
            break;
        }
    }
    
    for ( cat=0; cat < m_banks[bank].categories.size(); cat++ )
    {
        if ( m_banks[bank].categories[cat].name == catDir.getFileNameWithoutExtension() )
        {
            break;
        }
    }
    
    for ( preset=0; preset < m_banks[bank].categories[cat].presets.size(); preset++ )
    {
        if ( m_banks[bank].categories[cat].presets[preset].name == presetStr )
        {
            break;
        }
    }
    
    presetBank( m_banks[bank].name );
    presetCategory( m_banks[bank].categories[cat].name );
    presetName( presetCategory() + " | " + presetStr );

    PresetSelection sel;
    sel.bank = bank;
    sel.category = cat;
    sel.preset = preset;
    presetSelection( sel );
}

std::string Presets::lowercase(const std::string& str)
{
    auto copy = str;
    std::transform(copy.begin(), copy.end(), copy.begin(),
    [](unsigned char c){ return std::tolower(c); });
    
    return copy;
}



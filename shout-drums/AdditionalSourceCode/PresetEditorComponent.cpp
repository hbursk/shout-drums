//
//  PresetEditorComponent.cpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 9/15/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#include "PresetEditorComponent.h"
#include "ProcessorKeys.h"

PresetEditorComponent::PresetEditorComponent( hise::MainController *mc, SampleMaps& sampleMaps )
:m_sampleMapSelector(mc, "InstrumentSelector", sampler_id)
,m_kickMapSelector(mc, "KickSelector", drum_kicks_id)
,m_snareMapSelector(mc, "SnareSelector", drum_snares_id)
,m_hatMapSelector(mc, "HatSelector", drum_hats_id)
,m_clapMapSelector(mc, "ClapsSelector", drum_claps_id)
,m_cymbalMapSelector(mc, "CymbalSelector", drum_cymbals_id)
,m_percMapSelector(mc, "PercSelector", drum_perc_id)
,m_tomsMapSelector(mc, "TomsSelector", drum_toms_id)
,m_samplerMuter(mc, "SamplerMuter", midi_muter_id)
,m_kicksMuter(mc, "KicksMuter", kicks_muter_id)
,m_snaresMuter(mc, "SnaresMuter", snare_muter_id)
,m_hatsMuter(mc, "HatsMuter", hats_muter_id)
,m_clapsMuter(mc, "ClapsMuter", claps_muter_id)
,m_cymbalsMuter(mc, "CymbalsMuter", cymbals_muter_id)
,m_percMuter(mc, "PercMuter", perc_muter_id)
,m_tomsMuter(mc, "HatsMuter", toms_muter_id)
,m_savePresetButton()
,m_presetBrowser( mc )
,m_sampleMaps( sampleMaps )
{
    addAndMakeVisible( m_sampleMapSelector );
    addAndMakeVisible( m_kickMapSelector );
    addAndMakeVisible( m_snareMapSelector );
    addAndMakeVisible( m_hatMapSelector );
    addAndMakeVisible( m_clapMapSelector );
    addAndMakeVisible( m_cymbalMapSelector );
    addAndMakeVisible( m_percMapSelector );
    addAndMakeVisible( m_tomsMapSelector );
    addAndMakeVisible( m_savePresetButton );
    
    addAndMakeVisible( m_samplerMuter );
    addAndMakeVisible( m_kicksMuter );
    addAndMakeVisible( m_snaresMuter );
    addAndMakeVisible( m_hatsMuter );
    addAndMakeVisible( m_clapsMuter );
    addAndMakeVisible( m_cymbalsMuter );
    addAndMakeVisible( m_percMuter );
    addAndMakeVisible( m_tomsMuter );

    addChildComponent( m_presetBrowser );

    m_savePresetButton.setButtonText( "Presets" );
    m_savePresetButton.onClick = [this](){
        m_presetBrowser.setVisible( !m_presetBrowser.isVisible() );
    };
    
    PresetBrowser::Options newOptions;

    newOptions.backgroundColour = Colours::black;
    newOptions.textColour = Colour(0xFF545454);
    newOptions.highlightColour = Colour(0xFF545454);
    newOptions.showNotesLabel = false;
    newOptions.showFavoriteIcons = false;
    newOptions.numColumns = 1;

    m_presetBrowser.setOptions(newOptions);
    
    fillSampleMapList( m_sampleMaps.instrumentMaps(), "Instrument", m_sampleMapSelector );
    fillSampleMapList( m_sampleMaps.kickMaps(), "Kicks", m_kickMapSelector );
    fillSampleMapList( m_sampleMaps.snareMaps(), "Snares", m_snareMapSelector );
    fillSampleMapList( m_sampleMaps.hatMaps(), "Hats", m_hatMapSelector );
    fillSampleMapList( m_sampleMaps.clapMaps(), "Claps", m_clapMapSelector );
    fillSampleMapList( m_sampleMaps.percMaps(), "Perc", m_percMapSelector );
    fillSampleMapList( m_sampleMaps.tomsMaps(), "Toms", m_tomsMapSelector );
    fillSampleMapList( m_sampleMaps.cymbalMaps(), "Cymbals", m_cymbalMapSelector );
}

void PresetEditorComponent::resized()
{
    auto area = getLocalBounds();
    
    const int width = 180;
    const int height = 32;
    
    m_savePresetButton.setBounds( area.getWidth() - 60, 0, 60, 40 );

    // combo boxes
    auto fb = juce::FlexBox();
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignContent = juce::FlexBox::AlignContent::center;

    fb.items.add (juce::FlexItem (m_sampleMapSelector).withMinWidth (width).withMinHeight (height));
    fb.items.add (juce::FlexItem (m_kickMapSelector).withMinWidth (width).withMinHeight (height));
    fb.items.add (juce::FlexItem (m_snareMapSelector).withMinWidth (width).withMinHeight (height));
    fb.items.add (juce::FlexItem (m_hatMapSelector).withMinWidth (width).withMinHeight (height));
    fb.items.add (juce::FlexItem (m_clapMapSelector).withMinWidth (width).withMinHeight (height));
    fb.items.add (juce::FlexItem (m_cymbalMapSelector).withMinWidth (width).withMinHeight (height));
    fb.items.add (juce::FlexItem (m_percMapSelector).withMinWidth (width).withMinHeight (height));
    fb.items.add (juce::FlexItem (m_tomsMapSelector).withMinWidth (width).withMinHeight (height));

    fb.performLayout (area.withRight( 200 ) );
    
    // Muter buttons
    fb = juce::FlexBox();
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignContent = juce::FlexBox::AlignContent::center;
    
    const int buttonWidth = 32;
    const int buttonHeight = 32;
    
    fb.items.add (juce::FlexItem (m_samplerMuter).withMinWidth (buttonWidth).withMinHeight (buttonHeight));
    fb.items.add (juce::FlexItem (m_kicksMuter).withMinWidth (buttonWidth).withMinHeight (buttonHeight));
    fb.items.add (juce::FlexItem (m_snaresMuter).withMinWidth (buttonWidth).withMinHeight (buttonHeight));
    fb.items.add (juce::FlexItem (m_hatsMuter).withMinWidth (buttonWidth).withMinHeight (buttonHeight));
    fb.items.add (juce::FlexItem (m_clapsMuter).withMinWidth (buttonWidth).withMinHeight (buttonHeight));
    fb.items.add (juce::FlexItem (m_cymbalsMuter).withMinWidth (buttonWidth).withMinHeight (buttonHeight));
    fb.items.add (juce::FlexItem (m_percMuter).withMinWidth (buttonWidth).withMinHeight (buttonHeight));
    fb.items.add (juce::FlexItem (m_tomsMuter).withMinWidth (buttonWidth).withMinHeight (buttonHeight));

    fb.performLayout (area.withLeft( 200 ).withRight(232) );

    m_presetBrowser.setBounds( 0, 50, area.getWidth(), area.getHeight() - 50 );
}

void PresetEditorComponent::paint(Graphics& g)
{
    g.fillAll(Colours::grey);
}

void PresetEditorComponent::fillSampleMapList(const std::vector<std::string>& list, const std::string& name, BrightComboBox<raw::Data<String>::SampleMap>& comboMap)
{
    StringArray items;
    for ( const auto& item : list )
    {
        items.add( item );
    }
    
    comboMap.addItemList(items, 1);
    comboMap.setTextWhenNothingSelected( "Select " + name );
    comboMap.setConnectionMode(raw::UIConnection::ComboBox::Text);
}


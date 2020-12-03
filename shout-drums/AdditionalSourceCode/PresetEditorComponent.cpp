//
//  PresetEditorComponent.cpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 9/15/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#include "PresetEditorComponent.h"
#include "ProcessorKeys.h"

PresetEditorComponent::PresetEditorComponent( hise::MainController *mc, shout::App& app )
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
,m_reverbMixSlider( TRANS("reverb").toStdString(), mc, "Convolution Reverb", app.presets() )
,m_saturationMixSlider( TRANS("drive").toStdString(), mc, "Shape FX1", app.presets() )
,m_widthSlider( TRANS("width").toStdString(), mc, "Simple Gain1", app.presets() )
,m_delayMixSlider( TRANS("delay").toStdString(), mc, "Delay1", app.presets() )
,m_attackSlider( TRANS("attack").toStdString(), mc, "AHDSR Envelope1", app.presets() )
,m_releaseSlider( TRANS("release").toStdString(), mc, "AHDSR Envelope1", app.presets())
,m_savePresetButton()
,m_presetBrowser( mc )
,m_sampleMaps( app.sampleMaps() )
,m_samplerGain( "", mc, sampler_id, app.presets())
,m_kickGain( "", mc, drum_kicks_id, app.presets())
,m_snareGain( "", mc, drum_snares_id, app.presets())
,m_hatGain( "", mc, drum_hats_id, app.presets())
,m_clapGain( "", mc, drum_claps_id, app.presets())
,m_cymbalGain( "", mc, drum_cymbals_id, app.presets())
,m_percGain( "", mc, drum_perc_id, app.presets())
,m_tomsGain( "", mc, drum_toms_id, app.presets())
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
    
    addAndMakeVisible( &m_reverbMixSlider );
    m_reverbMixSlider.rangeAndSkewPoint( -100.f, 0.f, -30.f );
    
    addAndMakeVisible( &m_saturationMixSlider );
    
    addAndMakeVisible( &m_delayMixSlider );
    m_delayMixSlider.rangeAndSkewPoint(0.0, 0.5, 0.2);

    addAndMakeVisible( &m_widthSlider );
    m_widthSlider.rangeAndSkewPoint(0, 200, 100);
    
    addAndMakeVisible( &m_attackSlider );
    m_attackSlider.slider().setRange(juce::Range<double>(0, 20000), 1);
    
    addAndMakeVisible( &m_releaseSlider );
    m_releaseSlider.slider().setRange(juce::Range<double>(80,20000), 1);
    
    addAndMakeVisible(&m_samplerGain);

    addAndMakeVisible(&m_kickGain);

    addAndMakeVisible(&m_snareGain);

    addAndMakeVisible(&m_hatGain);

    addAndMakeVisible(&m_clapGain);

    addAndMakeVisible(&m_cymbalGain);

    addAndMakeVisible(&m_percGain);

    addAndMakeVisible(&m_tomsGain);
    
    addChildComponent( m_presetBrowser );
}

void PresetEditorComponent::resized()
{
    auto area = getLocalBounds();
    
    const int width = 180;
    const int height = 32;
    
    m_savePresetButton.setBounds( area.getWidth() - 130, 10, 120, 30 );

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
    
    // Gains
    fb = juce::FlexBox();
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignContent = juce::FlexBox::AlignContent::center;
    
    const int gainWidth = 32;
    const int gainHeight = 32;
        
    fb.items.add (juce::FlexItem (m_samplerGain).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_kickGain).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_snareGain).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_hatGain).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_clapGain).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_cymbalGain).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_percGain).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_tomsGain).withMinWidth (gainWidth).withMinHeight (gainHeight));

    fb.performLayout (area.withLeft( 232 ).withRight(264) );


    m_presetBrowser.setBounds( 0, 50, area.getWidth(), area.getHeight() - 50 );
    
    // Effect knobs
    fb = juce::FlexBox();
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignContent = juce::FlexBox::AlignContent::center;
    
    const int knobWidth = 64;
    const int knobHeight = 96;
    
    fb.items.add (juce::FlexItem (m_saturationMixSlider).withMinWidth (knobWidth).withMinHeight (knobHeight));
    fb.items.add (juce::FlexItem (m_delayMixSlider).withMinWidth (knobWidth).withMinHeight (knobHeight));
    fb.items.add (juce::FlexItem (m_reverbMixSlider).withMinWidth (knobWidth).withMinHeight (knobHeight));
    fb.items.add (juce::FlexItem (m_widthSlider).withMinWidth (knobWidth).withMinHeight (knobHeight));
    fb.items.add (juce::FlexItem (m_attackSlider).withMinWidth (knobWidth).withMinHeight (knobHeight));
    fb.items.add (juce::FlexItem (m_releaseSlider).withMinWidth (knobWidth).withMinHeight (knobHeight));

    fb.performLayout (area.withLeft(area.getWidth()-400).withRight(area.getWidth()) );
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


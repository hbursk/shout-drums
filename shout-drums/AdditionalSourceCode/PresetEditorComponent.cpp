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
:m_sample1MapSelector(mc, "InstrumentSelector", sampler1_id)
,m_sample2MapSelector(mc, "InstrumentSelector2", sampler2_id)
,m_kickMapSelector(mc, "KickSelector", drum_kicks_id)
,m_snareMapSelector(mc, "SnareSelector", drum_snares_id)
,m_hatMapSelector(mc, "HatSelector", drum_hats_id)
,m_clapMapSelector(mc, "ClapsSelector", drum_claps_id)
,m_cymbalMapSelector(mc, "CymbalSelector", drum_cymbals_id)
,m_percMapSelector(mc, "PercSelector", drum_perc_id)
,m_tomsMapSelector(mc, "TomsSelector", drum_toms_id)
,m_synthMuter(mc, "SynthMuter", midi_muter_id)
,m_kicksMuter(mc, "KicksMuter", kicks_muter_id)
,m_snaresMuter(mc, "SnaresMuter", snare_muter_id)
,m_hatsMuter(mc, "HatsMuter", hats_muter_id)
,m_clapsMuter(mc, "ClapsMuter", claps_muter_id)
,m_cymbalsMuter(mc, "CymbalsMuter", cymbals_muter_id)
,m_percMuter(mc, "PercMuter", perc_muter_id)
,m_tomsMuter(mc, "HatsMuter", toms_muter_id)
,m_sampler1Enabled(mc, "Sampler1 Enabled", sampler1_id)
,m_sampler2Enabled(mc, "Sampler2 Enabled", sampler2_id)
,m_reverbMixSlider( TRANS("reverb").toStdString(), mc, convolution_reverb_id, app.presets() )
,m_saturationMixSlider( TRANS("drive").toStdString(), mc, shape_fx_id, app.presets() )
,m_widthSlider( TRANS("width").toStdString(), mc, simple_gain_id, app.presets() )
,m_delayMixSlider( TRANS("delay").toStdString(), mc, delay_id, app.presets() )
,m_delayFeedbackLeftSlider( TRANS("dly fL").toStdString(), mc, delay_id, app.presets() )
,m_delayFeedbackRightSlider( TRANS("dly fR").toStdString(), mc, delay_id, app.presets() )
,m_delayLeftTimeSlider( TRANS("dly L").toStdString(), mc, delay_id, app.presets() )
,m_delayRightTimeSlider( TRANS("dly R").toStdString(), mc, delay_id, app.presets() )
,m_attackSlider( TRANS("attack").toStdString(), mc, synth_group_ahdsr_id, app.presets() )
,m_releaseSlider( TRANS("release").toStdString(), mc, synth_group_ahdsr_id, app.presets())
,m_savePresetButton()
,m_presetBrowser( mc )
,m_sampleMaps( app.sampleMaps() )
,m_sampler1Gain( "", mc, sampler1_id, app.presets())
,m_sampler2Gain( "", mc, sampler2_id, app.presets())
,m_kickGain( "", mc, drum_kicks_id, app.presets())
,m_snareGain( "", mc, drum_snares_id, app.presets())
,m_hatGain( "", mc, drum_hats_id, app.presets())
,m_clapGain( "", mc, drum_claps_id, app.presets())
,m_cymbalGain( "", mc, drum_cymbals_id, app.presets())
,m_percGain( "", mc, drum_perc_id, app.presets())
,m_tomsGain( "", mc, drum_toms_id, app.presets())
,m_sampler1Pan( "", mc, sampler1_id, app.presets())
,m_sampler2Pan( "", mc, sampler2_id, app.presets())
,m_kickPan( "", mc, drum_kicks_id, app.presets())
,m_snarePan( "", mc, drum_snares_id, app.presets())
,m_hatPan( "", mc, drum_hats_id, app.presets())
,m_clapPan( "", mc, drum_claps_id, app.presets())
,m_cymbalPan( "", mc, drum_cymbals_id, app.presets())
,m_percPan( "", mc, drum_perc_id, app.presets())
,m_tomsPan( "", mc, drum_toms_id, app.presets())
,m_waveformGeneratorContainer(mc, app)
{
    addAndMakeVisible( m_sample1MapSelector );
    addAndMakeVisible( m_sample2MapSelector );
    addAndMakeVisible( m_kickMapSelector );
    addAndMakeVisible( m_snareMapSelector );
    addAndMakeVisible( m_hatMapSelector );
    addAndMakeVisible( m_clapMapSelector );
    addAndMakeVisible( m_cymbalMapSelector );
    addAndMakeVisible( m_percMapSelector );
    addAndMakeVisible( m_tomsMapSelector );
    addAndMakeVisible( m_savePresetButton );
    addAndMakeVisible( m_waveformButton );
    
    addAndMakeVisible( m_synthMuter );
    addAndMakeVisible( m_kicksMuter );
    addAndMakeVisible( m_snaresMuter );
    addAndMakeVisible( m_hatsMuter );
    addAndMakeVisible( m_clapsMuter );
    addAndMakeVisible( m_cymbalsMuter );
    addAndMakeVisible( m_percMuter );
    addAndMakeVisible( m_tomsMuter );

    addAndMakeVisible( m_sampler1Enabled );
    addAndMakeVisible( m_sampler2Enabled );
    
    m_savePresetButton.setButtonText( "Presets" );
    m_savePresetButton.onClick = [this](){
        m_presetBrowser.setVisible( !m_presetBrowser.isVisible() );
    };
    
    m_waveformButton.setButtonText( "Waveform" );
    m_waveformButton.onClick = [this](){
        m_waveformGeneratorContainer.setVisible( !m_waveformGeneratorContainer.isVisible() );
    };

    PresetBrowser::Options newOptions;

    newOptions.backgroundColour = Colours::black;
    newOptions.textColour = Colour(0xFF545454);
    newOptions.highlightColour = Colour(0xFF545454);
    newOptions.showNotesLabel = false;
    newOptions.showFavoriteIcons = false;
    newOptions.numColumns = 1;

    m_presetBrowser.setOptions(newOptions);
    
    fillSampleMapList( m_sampleMaps.instrumentMaps(), "Instrument", m_sample1MapSelector );
    fillSampleMapList( m_sampleMaps.instrumentMaps(), "Instrument", m_sample2MapSelector );
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
    
    addAndMakeVisible( &m_delayFeedbackLeftSlider );

    addAndMakeVisible( &m_delayFeedbackRightSlider );
    
    addAndMakeVisible( &m_delayLeftTimeSlider );
    m_delayLeftTimeSlider.slider().setRange(0, 19, 1);

    addAndMakeVisible( &m_delayRightTimeSlider );
    m_delayRightTimeSlider.slider().setRange(0, 19, 1);

    addAndMakeVisible( &m_widthSlider );
    m_widthSlider.rangeAndSkewPoint(0, 200, 100);
    
    addAndMakeVisible( &m_attackSlider );
    m_attackSlider.slider().setRange(juce::Range<double>(0, 20000), 1);
    
    addAndMakeVisible( &m_releaseSlider );
    m_releaseSlider.slider().setRange(juce::Range<double>(80,20000), 1);
    
    addAndMakeVisible(&m_sampler1Gain);
    addAndMakeVisible(&m_sampler2Gain);
    addAndMakeVisible(&m_kickGain);
    addAndMakeVisible(&m_snareGain);
    addAndMakeVisible(&m_hatGain);
    addAndMakeVisible(&m_clapGain);
    addAndMakeVisible(&m_cymbalGain);
    addAndMakeVisible(&m_percGain);
    addAndMakeVisible(&m_tomsGain);
    
    addAndMakeVisible(&m_sampler1Pan);
    m_sampler1Pan.rangeAndSkewPoint(-1.0, 1.0, 0.0);
    addAndMakeVisible(&m_sampler2Pan);
    m_sampler2Pan.rangeAndSkewPoint(-1.0, 1.0, 0.0);

    addAndMakeVisible(&m_kickPan);
    m_kickPan.rangeAndSkewPoint(-1.0, 1.0, 0.0);

    addAndMakeVisible(&m_snarePan);
    m_snarePan.rangeAndSkewPoint(-1.0, 1.0, 0.0);

    addAndMakeVisible(&m_hatPan);
    m_hatPan.rangeAndSkewPoint(-1.0, 1.0, 0.0);

    addAndMakeVisible(&m_clapPan);
    m_clapPan.rangeAndSkewPoint(-1.0, 1.0, 0.0);

    addAndMakeVisible(&m_cymbalPan);
    m_cymbalPan.rangeAndSkewPoint(-1.0, 1.0, 0.0);

    addAndMakeVisible(&m_percPan);
    m_percPan.rangeAndSkewPoint(-1.0, 1.0, 0.0);

    addAndMakeVisible(&m_tomsPan);
    m_tomsPan.rangeAndSkewPoint(-1.0, 1.0, 0.0);

    addChildComponent( m_presetBrowser );
    addChildComponent( m_waveformGeneratorContainer );
}

void PresetEditorComponent::resized()
{
    auto area = getLocalBounds();
    
    const int width = 180;
    const int height = 32;
    
    m_savePresetButton.setBounds( area.getWidth() - 130, 10, 120, 30 );
    m_waveformButton.setBounds( area.getWidth() - 130*2, 10, 120, 30 );
    
    // combo boxes
    auto fb = juce::FlexBox();
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignContent = juce::FlexBox::AlignContent::center;

    fb.items.add (juce::FlexItem (m_sample1MapSelector).withMinWidth (width).withMinHeight (height));
    fb.items.add (juce::FlexItem (m_sample2MapSelector).withMinWidth (width).withMinHeight (height));
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
    
    fb.items.add (juce::FlexItem (m_synthMuter).withMinWidth (buttonWidth).withMinHeight (buttonHeight));
    fb.items.add (juce::FlexItem(buttonWidth, buttonHeight));
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
        
    fb.items.add (juce::FlexItem (m_sampler1Gain).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_sampler2Gain).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_kickGain).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_snareGain).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_hatGain).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_clapGain).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_cymbalGain).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_percGain).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_tomsGain).withMinWidth (gainWidth).withMinHeight (gainHeight));

    fb.performLayout (area.withLeft( 232 ).withRight(264) );

    // Pans
    fb = juce::FlexBox();
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignContent = juce::FlexBox::AlignContent::center;
            
    fb.items.add (juce::FlexItem (m_sampler1Pan).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_sampler2Pan).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_kickPan).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_snarePan).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_hatPan).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_clapPan).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_cymbalPan).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_percPan).withMinWidth (gainWidth).withMinHeight (gainHeight));
    fb.items.add (juce::FlexItem (m_tomsPan).withMinWidth (gainWidth).withMinHeight (gainHeight));

    fb.performLayout (area.withLeft( 264 ).withRight(296) );

    m_presetBrowser.setBounds( 0, 50, area.getWidth(), area.getHeight() - 50 );
    m_waveformGeneratorContainer.setBounds( 0, 0, area.getWidth(), area.getHeight() );
    
    m_sampler1Enabled.setBounds( m_sampler1Pan.getX() + m_sampler1Pan.getWidth(), m_sampler1Pan.getY(), gainWidth, gainHeight);
    m_sampler2Enabled.setBounds( m_sampler2Pan.getX() + m_sampler2Pan.getWidth(), m_sampler2Pan.getY(), gainWidth, gainHeight);
    
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
    fb.items.add (juce::FlexItem (m_delayFeedbackLeftSlider).withMinWidth (knobWidth).withMinHeight (knobHeight));
    fb.items.add (juce::FlexItem (m_delayFeedbackRightSlider).withMinWidth (knobWidth).withMinHeight (knobHeight));
    fb.items.add (juce::FlexItem (m_delayLeftTimeSlider).withMinWidth (knobWidth).withMinHeight (knobHeight));
    fb.items.add (juce::FlexItem (m_delayRightTimeSlider).withMinWidth (knobWidth).withMinHeight (knobHeight));

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


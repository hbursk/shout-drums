//
//  WaveformGeneratorComponent.cpp
//  Snackage - App
//
//  Created by Hayden Bursk on 1/6/21.
//  Copyright © 2021 Shout Audio. All rights reserved.
//

#include "WaveformGeneratorComponent.h"
#include "ProcessorKeys.h"

WaveformGeneratorComponent::WaveformGeneratorComponent( hise::MainController *mc, shout::App& app )
:m_waveform1Selector(mc, "WaveformSelector1", waveform_generator_id)
,m_waveform2Selector(mc, "WaveformSelector2", waveform_generator_id)
,m_octaveTranspose1("octave 1", mc, waveform_generator_id, app.presets())
,m_octaveTranspose2("octave 2", mc, waveform_generator_id, app.presets())
,m_detune1("detune 1", mc, waveform_generator_id, app.presets())
,m_detune2("detune 2", mc, waveform_generator_id, app.presets())
,m_pan1("pan 1", mc, waveform_generator_id, app.presets())
,m_pan2("pan 2", mc, waveform_generator_id, app.presets())
,m_pulseWidth1("pulse 1", mc, waveform_generator_id, app.presets())
,m_pulseWidth2("pusle 2", mc, waveform_generator_id, app.presets())
,m_mix("mix", mc, waveform_generator_id, app.presets())
,m_gain("gain", mc, waveform_generator_id, app.presets())
,m_balance("balance", mc, waveform_generator_id, app.presets())
,m_unisonoVoice("voices", mc, synth_group_id, app.presets() )
,m_unisonoDetune("detune", mc, synth_group_id, app.presets() )
,m_unisonoSpread("spread", mc, synth_group_id, app.presets() )
,m_enableSecondOsc(mc, "2nd Osc", waveform_generator_id)
,m_enabled(mc, "Enabled", waveform_generator_id)
,m_arpEnabled(mc, "Arp Enabled", arp_id )
{
    /*
     OctaveTranspose1 = ModulatorSynth::numModulatorSynthParameters, ///< -5 ... **0** ... 5 | The octave transpose factor for the first Oscillator.
     WaveForm1, ///< Sine, Triangle, **Saw**, Square, Noise | the waveform type
     Detune1, ///< -100ct ... **0.0ct** ... 100ct | The pitch detune of the first oscillator in cent (100 cent = 1 semitone).
     Pan1, ///< -100 ... **0** ... 100 | the stereo panning of the first oscillator
     OctaveTranspose2, ///< -5 ... **0** ... 5 | the octave transpose factor for the first oscillator
     WaveForm2, ///< Sine, Triangle, **Saw**, Square, Noise | the waveform type
     Detune2, ///< -100ct ... **0ct** ... 100ct | the pitch detune of the first oscillator in cent (100 cent = 1 semitone)
     Pan2, ///< -100 ... **0** ... 100 | the stereo panning of the first oscillator
     Mix, ///< 0 ... **50%** ... 100% | the balance between the two oscillators (0% is only the left oscillator, while 100% is the right oscillator). This can be modulated using the Mix Modulation chain (if there are some Modulators, this control will be disabled.
     EnableSecondOscillator, ///< **On** ... Off | Can be used to mute the second oscillator to save CPU cycles
     PulseWidth1, ///< 0 ... **1** | Determines the first pulse width for waveforms that support this (eg. square)
     PulseWidth2, ///< 0 ... **1** | Determines the second pulse width for waveforms that support this (eg. square)

     */
    addAndMakeVisible( &m_waveform1Selector );
    addAndMakeVisible( &m_waveform2Selector );
    
    addAndMakeVisible( &m_octaveTranspose1 );
    m_octaveTranspose1.slider().setRange(-5, 5, 1);
    
    addAndMakeVisible( &m_octaveTranspose2 );
    m_octaveTranspose2.slider().setRange(-5, 5, 1);

    addAndMakeVisible( &m_detune1 );
    m_detune1.slider().setRange(-100, 100, 1);
    
    addAndMakeVisible( &m_detune2 );
    m_detune2.slider().setRange(-100, 100, 1);

    addAndMakeVisible( &m_pan1 );
    m_pan1.rangeAndSkewPoint(-1.0, 1.0, 0.0);

    addAndMakeVisible( &m_pan2 );
    m_pan2.rangeAndSkewPoint(-1.0, 1.0, 0.0);

    addAndMakeVisible( &m_pulseWidth1 );
    addAndMakeVisible( &m_pulseWidth2 );
    addAndMakeVisible( &m_mix );
    addAndMakeVisible( &m_gain );
    addAndMakeVisible( &m_balance );
    m_balance.rangeAndSkewPoint(-1.0, 1.0, 0.0);
    
    addAndMakeVisible( &m_unisonoVoice );
    m_unisonoVoice.slider().setRange(1,16,1);
    
    addAndMakeVisible( &m_unisonoDetune );
    m_unisonoDetune.rangeAndSkewPoint(0.0, 6.0, 3.0);
    
    addAndMakeVisible( &m_unisonoSpread );
    m_unisonoSpread.rangeAndSkewPoint(0.0, 2.0, 1.0);

    addAndMakeVisible( &m_enableSecondOsc );
    addAndMakeVisible( &m_enabled );
    addAndMakeVisible( &m_arpEnabled );
    
    StringArray items;
    items.add("Sine");
    items.add("Triangle");
    items.add("Saw");
    items.add("Square");
    items.add("Noise");
    items.add("Triangle2");
    items.add("Square2");
    items.add("Trapezoid1");
    items.add("Trapezoid2");

    m_waveform1Selector.addItemList(items, 1);
    m_waveform1Selector.setTextWhenNothingSelected( "Select Waveform1");
    m_waveform1Selector.setConnectionMode(raw::UIConnection::ComboBox::Id);
    m_waveform2Selector.addItemList(items, 1);
    m_waveform2Selector.setTextWhenNothingSelected( "Select Waveform2");
    m_waveform2Selector.setConnectionMode(raw::UIConnection::ComboBox::Id);
    
    addAndMakeVisible(&m_closeButton);
    m_closeButton.setButtonText( "X" );
    m_closeButton.onClick = [this](){
        setVisible(false);
    };

}

void WaveformGeneratorComponent::resized()
{
    auto area = getLocalBounds();
    
    const int knobWidth = 96;
    const int knobHeight = 128;
    
    // controls
    auto fb = juce::FlexBox();
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignContent = juce::FlexBox::AlignContent::center;

    fb.items.add (juce::FlexItem (m_octaveTranspose1).withMinWidth (knobWidth).withMinHeight (knobHeight));
    fb.items.add (juce::FlexItem (m_octaveTranspose2).withMinWidth (knobWidth).withMinHeight (knobHeight));
    fb.items.add (juce::FlexItem (m_detune1).withMinWidth (knobWidth).withMinHeight (knobHeight));
    fb.items.add (juce::FlexItem (m_detune2).withMinWidth (knobWidth).withMinHeight (knobHeight));
    fb.items.add (juce::FlexItem (m_pan1).withMinWidth (knobWidth).withMinHeight (knobHeight));
    fb.items.add (juce::FlexItem (m_pan2).withMinWidth (knobWidth).withMinHeight (knobHeight));
    fb.items.add (juce::FlexItem (m_pulseWidth1).withMinWidth (knobWidth).withMinHeight (knobHeight));
    fb.items.add (juce::FlexItem (m_pulseWidth2).withMinWidth (knobWidth).withMinHeight (knobHeight));
    fb.items.add (juce::FlexItem (m_mix).withMinWidth (knobWidth).withMinHeight (knobHeight));
    fb.items.add (juce::FlexItem (m_gain).withMinWidth (knobWidth).withMinHeight (knobHeight));
    fb.items.add (juce::FlexItem (m_balance).withMinWidth (knobWidth).withMinHeight (knobHeight));
    fb.items.add (juce::FlexItem (m_unisonoVoice).withMinWidth (knobWidth).withMinHeight (knobHeight));
    fb.items.add (juce::FlexItem (m_unisonoSpread).withMinWidth (knobWidth).withMinHeight (knobHeight));
    fb.items.add (juce::FlexItem (m_unisonoDetune).withMinWidth (knobWidth).withMinHeight (knobHeight));

    fb.items.add (juce::FlexItem (m_enableSecondOsc).withMinWidth (knobWidth).withMinHeight (knobHeight));

    fb.performLayout (area );
    
    m_waveform1Selector.setBounds( 10, 10, 200, 32 );
    m_waveform2Selector.setBounds( 10, 42, 200, 32 );
    m_enabled.setBounds( area.getWidth()/2 - 32/2, 10, 32, 32);
    m_closeButton.setBounds(area.getWidth() - 42, 10, 32, 32 );
    m_arpEnabled.setBounds(232, 10, 32, 32);
}

void WaveformGeneratorComponent::paint(Graphics& g)
{
    g.fillAll(Colours::darkgrey);
}

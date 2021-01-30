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
#include "Knob.h"
#include "MidiNotePowerButton.h"
#include "App.h"
#include "WaveformGeneratorComponent.h"

class PresetEditorComponent : public juce::Component
{
public:
    PresetEditorComponent( hise::MainController* mc, shout::App& app );
    virtual ~PresetEditorComponent() = default;
    
    void resized() override;

    void paint(Graphics& g) override;

private:
    void fillSampleMapList(const std::vector<std::string>& list, const std::string& name, BrightComboBox<raw::Data<String>::SampleMap>& comboMap);
    
    BrightComboBox<raw::Data<String>::SampleMap> m_sample1MapSelector;
    BrightComboBox<raw::Data<String>::SampleMap> m_sample2MapSelector;
    BrightComboBox<raw::Data<String>::SampleMap> m_kickMapSelector;
    BrightComboBox<raw::Data<String>::SampleMap> m_snareMapSelector;
    BrightComboBox<raw::Data<String>::SampleMap> m_hatMapSelector;
    BrightComboBox<raw::Data<String>::SampleMap> m_clapMapSelector;
    BrightComboBox<raw::Data<String>::SampleMap> m_cymbalMapSelector;
    BrightComboBox<raw::Data<String>::SampleMap> m_percMapSelector;
    BrightComboBox<raw::Data<String>::SampleMap> m_tomsMapSelector;
    
    MidiNotePowerButton m_synthMuter;
    MidiNotePowerButton m_kicksMuter;
    MidiNotePowerButton m_snaresMuter;
    MidiNotePowerButton m_hatsMuter;
    MidiNotePowerButton m_clapsMuter;
    MidiNotePowerButton m_cymbalsMuter;
    MidiNotePowerButton m_percMuter;
    MidiNotePowerButton m_tomsMuter;
    
    PowerButton<raw::Data<bool>::Bypassed<true>> m_sampler1Enabled;
    PowerButton<raw::Data<bool>::Bypassed<true>> m_sampler2Enabled;

    Knob<hise::ConvolutionEffect::Parameters::WetGain> m_reverbMixSlider;
    Knob<hise::ShapeFX::SpecialParameters::Mix> m_saturationMixSlider;
    Knob<hise::GainEffect::Parameters::Width> m_widthSlider;
    Knob<hise::DelayEffect::Parameters::Mix> m_delayMixSlider;
    Knob<hise::DelayEffect::Parameters::FeedbackLeft> m_delayFeedbackLeftSlider;
    Knob<hise::DelayEffect::Parameters::FeedbackRight> m_delayFeedbackRightSlider;
    Knob<hise::DelayEffect::Parameters::DelayTimeLeft> m_delayLeftTimeSlider;
    Knob<hise::DelayEffect::Parameters::DelayTimeRight> m_delayRightTimeSlider;
    Knob<hise::DelayEffect::Parameters::LowPassFreq> m_delayLowpassSlider;
    Knob<hise::DelayEffect::Parameters::HiPassFreq> m_delayHipassSlider;

    Knob<hise::AhdsrEnvelope::SpecialParameters::Attack> m_attackSlider;
    Knob<hise::AhdsrEnvelope::SpecialParameters::Release> m_releaseSlider;
    
    Knob<hise::ModulatorSynth::Parameters::Gain> m_sampler1Gain;
    Knob<hise::ModulatorSynth::Parameters::Gain> m_sampler2Gain;
    Knob<hise::ModulatorSynth::Parameters::Gain> m_kickGain;
    Knob<hise::ModulatorSynth::Parameters::Gain> m_snareGain;
    Knob<hise::ModulatorSynth::Parameters::Gain> m_hatGain;
    Knob<hise::ModulatorSynth::Parameters::Gain> m_clapGain;
    Knob<hise::ModulatorSynth::Parameters::Gain> m_cymbalGain;
    Knob<hise::ModulatorSynth::Parameters::Gain> m_percGain;
    Knob<hise::ModulatorSynth::Parameters::Gain> m_tomsGain;
    
    Knob<hise::ModulatorSynth::Parameters::Balance> m_sampler1Pan;
    Knob<hise::ModulatorSynth::Parameters::Balance> m_sampler2Pan;
    Knob<hise::ModulatorSynth::Parameters::Balance> m_kickPan;
    Knob<hise::ModulatorSynth::Parameters::Balance> m_snarePan;
    Knob<hise::ModulatorSynth::Parameters::Balance> m_hatPan;
    Knob<hise::ModulatorSynth::Parameters::Balance> m_clapPan;
    Knob<hise::ModulatorSynth::Parameters::Balance> m_cymbalPan;
    Knob<hise::ModulatorSynth::Parameters::Balance> m_percPan;
    Knob<hise::ModulatorSynth::Parameters::Balance> m_tomsPan;

    WaveformGeneratorComponent m_waveformGeneratorContainer;

    juce::TextButton m_savePresetButton;
    juce::TextButton m_waveformButton;

    hise::PresetBrowser m_presetBrowser;
    
    SampleMaps& m_sampleMaps;
};

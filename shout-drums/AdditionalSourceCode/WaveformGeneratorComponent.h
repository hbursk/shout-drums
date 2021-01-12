
#pragma once

#include "JuceHeader.h"
#include "App.h"
#include "BrightComboBox.h"
#include "Knob.h"
#include "PowerButton.h"

class WaveformGeneratorComponent : public juce::Component
{
public:
    WaveformGeneratorComponent( hise::MainController* mc, shout::App& app );
    virtual ~WaveformGeneratorComponent() = default;
    
    void resized() override;

    void paint(Graphics& g) override;
    
private:
    BrightComboBox<raw::Data<int>::Attribute<hise::WaveSynth::SpecialParameters::WaveForm1>> m_waveform1Selector;
    BrightComboBox<raw::Data<int>::Attribute<hise::WaveSynth::SpecialParameters::WaveForm2>> m_waveform2Selector;
    
    Knob<hise::WaveSynth::SpecialParameters::OctaveTranspose1> m_octaveTranspose1;
    Knob<hise::WaveSynth::SpecialParameters::OctaveTranspose2> m_octaveTranspose2;
    Knob<hise::WaveSynth::SpecialParameters::Detune1> m_detune1;
    Knob<hise::WaveSynth::SpecialParameters::Detune2> m_detune2;
    Knob<hise::WaveSynth::SpecialParameters::Pan1> m_pan1;
    Knob<hise::WaveSynth::SpecialParameters::Pan2> m_pan2;
    Knob<hise::WaveSynth::SpecialParameters::PulseWidth1> m_pulseWidth1;
    Knob<hise::WaveSynth::SpecialParameters::PulseWidth2> m_pulseWidth2;
    Knob<hise::WaveSynth::SpecialParameters::Mix> m_mix;
    Knob<hise::ModulatorSynth::Parameters::Gain> m_gain;
    Knob<hise::ModulatorSynth::Parameters::Balance> m_balance;
    
    Knob<hise::ModulatorSynthGroup::SpecialParameters::UnisonoVoiceAmount> m_unisonoVoice;
    Knob<hise::ModulatorSynthGroup::SpecialParameters::UnisonoDetune> m_unisonoDetune;
    Knob<hise::ModulatorSynthGroup::SpecialParameters::UnisonoSpread> m_unisonoSpread;

    PowerButton<raw::Data<bool>::Attribute<hise::WaveSynth::SpecialParameters::EnableSecondOscillator>> m_enableSecondOsc;
    PowerButton<raw::Data<bool>::Bypassed<true>> m_enabled;
    PowerButton<raw::Data<bool>::Bypassed<true>> m_arpEnabled;

    juce::TextButton m_closeButton;
    
};

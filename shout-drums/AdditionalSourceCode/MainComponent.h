#pragma once

#include "JuceHeader.h"

#include "App.h"
#include "InfoView.h"
#include "MidiBarComponent.h"
#include "PresetEditorComponent.h"
#include "PresetSwitcher.h"
#include "ShoutLookAndFeel.h"
#include "Knob.h"


/** This will be our custom interface for the HISE project.

    You have to subclass it from FloatingTileContent and Component.

*/

using namespace shout;

class MainComponent : public juce::Component
//#if !defined( USE_RAW_FRONTEND )
//                      ,public hise::FloatingTileContent
//#endif
{
public:

    // This line will define the ID of the component and has to be the EXACT same String that
    // you've used in the Javascript code as `Type` property...
#if !defined( USE_RAW_FRONTEND )
    SET_PANEL_NAME("ExternalTestComponent");
    MainComponent(juce::FloatingTile* parent);
#else
    MainComponent( MainController* mc );
#endif
    
    ~MainComponent();

    void resized() override;

    void paint(Graphics& g) override;
    

protected:
        
    juce::ScopedPointer<juce::MidiKeyboardComponent> m_stockKeyboard;
    
    App m_app;
    
    Knob<hise::GainEffect::Parameters::Gain> m_gainSlider;
    Knob<hise::ConvolutionEffect::Parameters::WetGain> m_reverbMixSlider;
    Knob<hise::ShapeFX::SpecialParameters::Mix> m_saturationMixSlider;
    Knob<hise::GainEffect::Parameters::Width> m_widthSlider;
    Knob<hise::DelayEffect::Parameters::Mix> m_delayMixSlider;
    
    Knob<hise::AhdsrEnvelope::SpecialParameters::Attack> m_attackSlider;
    Knob<hise::AhdsrEnvelope::SpecialParameters::Release> m_releaseSlider;
    
    InfoView m_infoView;
    
    juce::Component m_attackReleaseContainer;
    
    PresetSwitcher m_presetSwitcher;
    juce::ImageComponent m_backgroundImage;
    juce::Image          m_bgImage;
    
    ShoutLookAndFeel m_shoutLookAndFeel;
    
    PresetEditorComponent m_presetEditorComponent;
    
    juce::TextButton m_editButton;
    
    MidiBarComponent m_midiBarComponent;
    
    MainController* m_mainController = nullptr;
    
    
};

#if !defined( USE_RAW_FRONTEND )

// This method needs to be defined and used for registering all external panels we define in our project scoped C++ code
void hise::FloatingTileContent::Factory::registerExternalPanelTypes()
{
    // Just use this handy macro for registering
    REGISTER_EXTERNAL_FLOATING_TILE(MainComponent);
}

#endif

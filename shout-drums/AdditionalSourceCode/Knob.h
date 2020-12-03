//
//  Knob.hpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 8/18/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#pragma once

#include "JuceHeader.h"

#include "Font.h"
#include "InfoView.h"
#include "Presets.h"

template <int ParameterIndex>
class Knob : public juce::Component
{
public:
    Knob() = delete;
    Knob( const std::string& name, MainController* mc, const std::string& procId, Presets& presets )
    : juce::Component( name )
    , m_connection(&m_slider, mc, procId)
    , m_processorId( procId )
    , m_mainController( mc )
    , m_processorReference( mc, String(procId), true )
    , m_presets( presets )
    {
        addChildComponent(m_iconAnimation = new RLottieComponent(mc->getRLottieManager()));
        m_iconAnimation->setBackgroundColour(Colours::transparentBlack);

        setupSlider();
        setupLabel( name );
        
        hise::raw::Reference<Processor>::ParameterCallback update = [this](float newValue)
        {
            if (m_iconAnimation)
            {
                auto normalized = m_slider.valueToProportionOfLength( newValue );
                auto scaled = normalized * (m_animationEnd - m_animationStart) + m_animationStart;
                m_iconAnimation->setFrameNormalised( scaled );
            }
        };

        m_processorReference.addParameterToWatch(ParameterIndex, update);
        
        m_presets.presetSelection.onChanged([this](const auto&){
            updateDoubleClickValue();
        });
    }
    
    ~Knob()
    {
    }
    
    void resized() override
    {
        auto area = getLocalBounds();
        
        const float margin = 8.0;
        
        m_iconAnimation->setBounds(margin/2+1,margin,area.getWidth()-margin,area.getWidth()-margin);
        
        m_slider.setBounds(0, 0, area.getWidth(), area.getWidth() );
        m_label.setBounds( 0, area.getWidth() - 1, area.getWidth(), 22 );
    }

    
    juce::Slider& slider()
    {
        return m_slider;
    }
    
    void rangeAndSkewPoint( double min, double max, double skew )
    {
        m_slider.setRange( min, max );
        m_slider.setSkewFactorFromMidPoint( skew );
        
        auto p = ProcessorHelpers::getFirstProcessorWithName(m_mainController->getMainSynthChain(), m_processorId);
        m_slider.setValue( p->getAttribute( ParameterIndex ), dontSendNotification );
        
        m_slider.repaint();
    }
    
    void mouseEnter (const MouseEvent& event) override{}
    void mouseExit( const MouseEvent& event ) override{}
    
    void setInfoText(const std::string& title, const std::string& text)
    {
        getProperties().set(info_title_property, String(CharPointer_UTF8(title.c_str())));
        getProperties().set(info_message_property, String(CharPointer_UTF8(text.c_str())));
    }
    
    void setIconAnimation(const char* animation, size_t animationSize, float start = 0.f, float end = 1.f)
    {
        m_iconAnimation->loadAnimation(String(animation, animationSize), true);
        m_iconAnimation->setVisible(true);
        m_animationStart = start;
        m_animationEnd = end;
        updateIconAnimation();
    }
    
    void updateIconAnimation()
    {
        auto normalized = m_slider.valueToProportionOfLength( m_slider.getValue() );
        auto scaled = normalized * (m_animationEnd - m_animationStart) + m_animationStart;
        m_iconAnimation->setFrameNormalised( scaled );
    }
    
    void updateDoubleClickValue()
    {
        auto p = ProcessorHelpers::getFirstProcessorWithName(m_mainController->getMainSynthChain(), m_processorId);
        m_slider.setDoubleClickReturnValue(true, (double)p->getAttribute(ParameterIndex));
    }
    
private:
    void setupSlider()
    {
        addAndMakeVisible( &m_slider );

        m_slider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
        m_slider.setTextBoxStyle(Slider::NoTextBox, false, getLocalBounds().getWidth(), getLocalBounds().getWidth() );
        m_slider.setRange(0.0, 1.0);
        m_slider.setRotaryParameters(juce::MathConstants<float>::pi, juce::MathConstants<float>::pi * 3, true);
    }
    
    void setupLabel( const std::string& name )
    {
        if (name.empty())
        {
            return;
        }
        
        addAndMakeVisible( &m_label );
        m_label.setText( name, dontSendNotification );
        m_label.setJustificationType( Justification::centred );
        m_label.setEditable( false );
        m_label.setFont( shout::Font::mainFont( 20.f ) );
        m_label.setColour( juce::Label::textColourId, Colour( 0xffffffff) );
    }

    
    juce::Slider m_slider;
    juce::Label  m_label;
    raw::UIConnection::Slider<ParameterIndex> m_connection;
    std::string m_processorId;
    MainController* m_mainController = nullptr;
    
    ScopedPointer<RLottieComponent> m_iconAnimation;
    float m_animationStart = 0.0f;
    float m_animationEnd = 1.0f;
    hise::raw::Reference<Processor> m_processorReference;
    Presets& m_presets;

};

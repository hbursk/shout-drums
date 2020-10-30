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

template <int ParameterIndex>
class Knob : public juce::Component
{
public:
    Knob() = delete;
    Knob( const std::string& name, MainController* mc, const std::string& procId )
    : juce::Component( name )
    , m_connection(&m_slider, mc, procId)
    , m_processorId( procId )
    , m_mainController( mc )
    {
        setupSlider();
        setupLabel( name );
    }
    
    ~Knob() = default;
    
    void resized() override
    {
        auto area = getLocalBounds();
        
        m_slider.setBounds(0, 0, area.getWidth(), area.getWidth() );
        m_label.setBounds( 0, area.getWidth(), area.getWidth(), 20 );
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
        
        //m_connection.template setData<raw::Data<float>::Attribute<ParameterIndex>>();
    }
    
    void mouseEnter (const MouseEvent& event) override{}
    void mouseExit( const MouseEvent& event ) override{}
    
    void setInfoText(const std::string& title, const std::string& text)
    {
        getProperties().set(info_title_property, String(CharPointer_UTF8(title.c_str())));
        getProperties().set(info_message_property, String(CharPointer_UTF8(text.c_str())));
    }

    
private:
    void setupSlider()
    {
        addAndMakeVisible( &m_slider );

        m_slider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
        m_slider.setTextBoxStyle(Slider::NoTextBox, false, getLocalBounds().getWidth(), getLocalBounds().getWidth() );
        m_slider.setRange(0.0, 1.0);
        m_slider.setRotaryParameters(juce::MathConstants<float>::pi, juce::MathConstants<float>::pi * 3, true);
        
//        auto p = ProcessorHelpers::getFirstProcessorWithName(m_mainController->getMainSynthChain(), m_processorId);
//        m_slider.setDoubleClickReturnValue(true, (double)p->getDefaultValue(ParameterIndex));
    }

    void setupLabel( const std::string& name )
    {
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
    
};

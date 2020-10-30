//
//  Bind.cpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 8/18/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#include "Bind.h"

Binder::Binder( hise::MainController* mc )
: m_mainController( mc )
{
    assert( mc );
    m_mainController->getUserPresetHandler().addListener( this );
}

Binder::~Binder()
{
    m_mainController->getUserPresetHandler().removeListener( this );
}

void Binder::bind( juce::Slider& slider, const std::string& processor, int paramId )
{
    auto p = hise::ProcessorHelpers::getFirstProcessorWithName( m_mainController->getMainSynthChain(), processor );
    slider.onValueChange = [p, paramId, &slider]() {
        p->setAttribute( paramId, slider.getValue(), dontSendNotification );
    };

    storeUpdate( [p, paramId, &slider]() { slider.setValue( p->getAttribute( paramId ), dontSendNotification ); } );
}

void Binder::bindDB( juce::Slider& slider, const std::string& processor, int paramId )
{
    auto p = hise::ProcessorHelpers::getFirstProcessorWithName( m_mainController->getMainSynthChain(), processor );
    slider.onValueChange = [p, paramId, &slider]() {
        const auto db = juce::Decibels::gainToDecibels( slider.getValue() );
        p->setAttribute( paramId, db, dontSendNotification );
    };

    storeUpdate( [p, paramId, &slider]() {
        slider.setValue( juce::Decibels::decibelsToGain( p->getAttribute( paramId ) ), dontSendNotification );
    } );
}

void Binder::update()
{
    for ( const auto& binding : m_updateBindings )
    {
        binding();
    }
}

void Binder::storeUpdate( std::function<void()> _update )
{
    _update();
    m_updateBindings.push_back( std::move( _update ) );
}

void Binder::presetChanged( const File& newPreset )
{
    update();
}

void Binder::presetListUpdated()
{
}

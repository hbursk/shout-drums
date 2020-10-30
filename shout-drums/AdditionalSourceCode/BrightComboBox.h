//
//  BrightComboBox.h
//  DrumTest - App
//
//  Created by Hayden Bursk on 9/15/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#pragma once

#include "JuceHeader.h"

template <class ConnectionType>
class BrightComboBox : public juce::ComboBox, public ControlledObject
{
public:
    BrightComboBox( MainController* mc, const String& name, const String& processorId )
    : ControlledObject( mc )
    , connection( this, mc, processorId )
    {
        setName( name );
        mc->skin( *this );

        setColour( HiseColourScheme::ComponentTextColourId, Colours::black );
        setColour( HiseColourScheme::ComponentBackgroundColour, Colours::transparentBlack );
        setColour( HiseColourScheme::ComponentOutlineColourId, Colours::transparentBlack );
        setColour( HiseColourScheme::ComponentFillTopColourId, Colour( 0x11333333 ) );
        setColour( HiseColourScheme::ComponentFillBottomColourId, Colour( 0x20111111 ) );

        connection.setData<ConnectionType>();
    }

    void setConnectionMode( raw::UIConnection::ComboBox::Mode newMode )
    {
        connection.setMode( newMode );
    }

private:
    raw::UIConnection::ComboBox connection;
};

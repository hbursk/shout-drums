//
//  PowerButton.hpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 9/16/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#pragma once

#include "JuceHeader.h"

class PowerButton : public juce::Button,
    public ControlledObject
{
public:

    PowerButton(MainController* mc, const String& name, const String& processorId);

    void paintButton(Graphics& g, bool isMouseOverButton, bool isButtonDown);

    Path p;
    raw::UIConnection::Button connection;
};


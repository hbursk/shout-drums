//
//  Knob.hpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 8/18/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#pragma once

#include "JuceHeader.h"

namespace shout
{
class Font
{
public:
    Font()  = delete;
    ~Font() = default;

    static const juce::Font mainFont( float pointSize );
    static const juce::Font labelFont( float pointSize );
};
} // namespace shout

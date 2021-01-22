//
//  Knob.hpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 8/18/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#pragma once

#include "JuceHeader.h"
#include "TargetKey.h"
#include "LottieButton.h"
#include "AttributedLabel.h"

class KeySwitcher : public juce::Component
{
public:
    KeySwitcher() = delete;
    KeySwitcher( MainController* mc,TargetKey& _targetKey );
    ~KeySwitcher() = default;
    
    void resized() override;
    
private:
    void setText(const String& text);
    void setupLabel();
    
    LottieButton m_prevButton;
    LottieButton m_nextButton;
    AttributedLabel  m_label;
    
    TargetKey& m_targetKey;
    
};

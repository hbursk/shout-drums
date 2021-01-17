//
//  LottieButton.hpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 11/27/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#pragma once

#include "JuceHeader.h"

class LottieButton : public juce::Component
{
public:
    enum class AnimateOn
    {
        Click,
        Hover,
        None
    };
    
    LottieButton(MainController* mc, String animationJson);
    virtual ~LottieButton() = default;
    
    void animateOn( AnimateOn on );
    
    std::function<void()> onClick;
    
    void resized() override;
    
    void reset();
    
    void animation( String animationJson );
    
    void setupConnection( const String& processorId );
        
    void setInfoText(const std::string& title, const std::string& text);
    
    bool isToggled() const;

protected:
    MainController *m_mainController = nullptr;
    juce::ImageButton m_button;
    RLottieComponent m_lottieComponent;
    AnimateOn m_animateOn = AnimateOn::Click;
    Button::ButtonState m_previousState = Button::ButtonState::buttonNormal;
    bool m_previouslySelected = false;
    
    juce::ScopedPointer<raw::UIConnection::Button> m_connection = nullptr;

};

//
//  LottieButton.cpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 11/27/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#include "LottieButton.h"

LottieButton::LottieButton(MainController* mc, String animationJson)
: m_lottieComponent(mc->getRLottieManager())
{
    m_lottieComponent.setBackgroundColour(Colours::transparentBlack);
    animation(animationJson);

    addAndMakeVisible(&m_lottieComponent);
    addAndMakeVisible(&m_button);
    
    m_button.onClick = [this](){
        if (m_animateOn == AnimateOn::Click)
        {
            m_lottieComponent.play(RLottieComponent::PlaybackMode::OneShotForward);
        }
        
        if (onClick)
        {
            onClick();
        }
    };
    
    m_button.onStateChange = [this](){
        
        auto state = m_button.getState();
        if ( state == Button::ButtonState::buttonOver && m_previousState != Button::ButtonState::buttonDown)
        {
            if (m_animateOn == AnimateOn::Hover)
            {
                juce::Timer::callAfterDelay(500, [this](){
                    if (m_button.getState() == Button::ButtonState::buttonOver)
                    {
                        m_lottieComponent.play(RLottieComponent::PlaybackMode::OneShotForward);
                    }
                });
            }
        }
        
        m_previousState = state;
    };
}

void LottieButton::animateOn( LottieButton::AnimateOn on)
{
    m_animateOn = on;
}

void LottieButton::resized()
{
    const auto area = getLocalBounds();
    
    m_button.setBounds(0, 0, area.getWidth(), area.getHeight());
    m_lottieComponent.setBounds(0, 0, area.getWidth(), area.getHeight());
}

void LottieButton::reset()
{
    m_lottieComponent.stop();
    m_lottieComponent.setFrameNormalised(0);
}

void LottieButton::animation( String animationJson )
{
    m_lottieComponent.stop( true );
    m_lottieComponent.loadAnimation(animationJson, true);
}

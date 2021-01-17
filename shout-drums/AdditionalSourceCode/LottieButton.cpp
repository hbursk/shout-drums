//
//  LottieButton.cpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 11/27/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#include "LottieButton.h"
#include "InfoView.h"

LottieButton::LottieButton(MainController* mc, String animationJson)
: m_mainController(mc)
, m_lottieComponent(mc->getRLottieManager())
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
        
        if ( m_connection && m_previouslySelected != m_button.getToggleState())
        {
            if ( m_button.getToggleState() )
            {
                m_lottieComponent.play(RLottieComponent::PlaybackMode::OneShotForward);
            }
            else
            {
                m_lottieComponent.play(RLottieComponent::PlaybackMode::OneShotBackward);
            }
        }
            
        m_previousState = state;
        m_previouslySelected = m_button.getToggleState();
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

void LottieButton::setupConnection( const String& processorId )
{
    m_animateOn = AnimateOn::None;
    m_button.setClickingTogglesState(true);
    m_connection = new raw::UIConnection::Button(&m_button, m_mainController, processorId );
    
    m_connection->setData<raw::Data<bool>::Bypassed<true>>();
}

void LottieButton::setInfoText(const std::string& title, const std::string& text)
{
    getProperties().set(info_title_property, String(CharPointer_UTF8(title.c_str())));
    getProperties().set(info_message_property, String(CharPointer_UTF8(text.c_str())));
}

bool LottieButton::isToggled() const
{
    return m_button.getToggleState();
}


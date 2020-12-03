//
//  PresetBarContainer.cpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 11/17/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#include "PresetBarContainer.h"
#include "ExpandAnimation.h"

constexpr int switcherHeight = 60;
constexpr int switcherWidth = 300;
constexpr int midiBarHeight = 4;

PresetBarContainer::PresetBarContainer(MainController* mc, Presets& presets, MidiListener& midiListener)
: m_presetSwitcher(presets, mc)
, m_midiBarComponent(midiListener)
, m_expandAnimation(mc->getRLottieManager())
, m_presetPicker(mc, presets)
{
    m_expandAnimation.setBackgroundColour(Colours::transparentBlack);
    m_expandAnimation.loadAnimation(String(expand_json, expand_jsonSize), true);
    //m_expandAnimation.setFrameNormalised(0.5);
    
    addAndMakeVisible(&m_presetSwitcher);
    addAndMakeVisible(&m_midiBarComponent);
    addAndMakeVisible(&m_expandAnimation);
    addAndMakeVisible(&m_expandButton);
    addAndMakeVisible(&m_presetTitleButton);
    addAndMakeVisible(&m_presetPicker);
    
    auto expand = [this](){
        
        if (m_state == State::Closed)
        {
            animateOpen();
        }
        else
        {
            animateClose();
        }
    };
    m_expandButton.onClick = expand;
    m_presetTitleButton.onClick = expand;
}

void PresetBarContainer::resized()
{
    const auto area = getLocalBounds();
    
    if (m_closedPos.getWidth() == 0)
    {
        m_closedPos = getBoundsInParent();
        const auto offset = getHeight() - switcherHeight - midiBarHeight;
        m_openedPos = getBoundsInParent().withY(getBoundsInParent().getY() - offset);
    }
    
    m_presetSwitcher.setBounds((area.getWidth() - switcherWidth)/2, midiBarHeight, switcherWidth, switcherHeight );
    m_presetTitleButton.setBounds(m_presetSwitcher.getX() + 40, m_presetSwitcher.getY(), m_presetSwitcher.getWidth() - 80, m_presetSwitcher.getHeight());
    m_midiBarComponent.setBounds( 0, 0, area.getWidth(), midiBarHeight );
    m_presetPicker.setBounds(0, midiBarHeight+switcherHeight, area.getWidth(), area.getHeight() - midiBarHeight - switcherHeight);
    m_expandButton.setBounds( area.getWidth() - switcherHeight, midiBarHeight, switcherHeight, switcherHeight);
    m_expandAnimation.setBounds( area.getWidth() - switcherHeight, midiBarHeight, switcherHeight, switcherHeight);//midiBarHeight + 17, 20, 20);
    m_expandAnimation.resized();
}

void PresetBarContainer::paint(Graphics& g)
{
    g.fillAll(juce::Colour(0xaa000000));
}

void PresetBarContainer::closePresetBar()
{
    animateClose();
}

void PresetBarContainer::animateOpen()
{
    if ( m_state == State::Open )
    {
        return;
    }
    
    m_state = State::Open;
        
    juce::Desktop::getInstance().getAnimator().animateComponent(this, m_openedPos, 1.0, 300, false, 2.0, 0);
    m_expandAnimation.play(RLottieComponent::PlaybackMode::OneShotForward);
}

void PresetBarContainer::animateClose()
{
    if ( m_state == State::Closed )
    {
        return;
    }
    
    m_state = State::Closed;
    
    juce::Desktop::getInstance().getAnimator().animateComponent(this, m_closedPos, 1.0, 300, false, 2.0, 0);
    m_expandAnimation.play(RLottieComponent::PlaybackMode::OneShotBackward);
}

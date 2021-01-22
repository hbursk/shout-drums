//
//  PresetBarContainer.cpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 11/17/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#include "PresetBarContainer.h"
#include "ExpandAnimation.h"
#include "ProcessorKeys.h"
#include "LightningAnimation.h"

constexpr int switcherHeight = 60;
constexpr int switcherWidth = 300;
constexpr int midiBarHeight = 8;

PresetBarContainer::PresetBarContainer(MainController* mc, shout::App& app, MidiListener& midiListener)
: m_presetSwitcher(app.presets(), mc)
, m_midiBarComponent(midiListener, app.presets())
, m_expandAnimation(mc->getRLottieManager())
, m_presetPicker(mc, app.presets())
, m_arpButton( mc, String(lightning_json, lightning_jsonSize) )
, m_presets( app.presets() )
, m_keySwitcher( mc, app.targetKey())
{
    m_expandAnimation.setBackgroundColour(Colours::transparentBlack);
    m_expandAnimation.loadAnimation(String(expand_json, expand_jsonSize), true);
    
    addAndMakeVisible(&m_presetSwitcher);
    addAndMakeVisible(&m_midiBarComponent);
    addAndMakeVisible(&m_expandAnimation);
    addAndMakeVisible(&m_expandButton);
    addAndMakeVisible(&m_presetTitleButton);
    addAndMakeVisible(&m_presetPicker);
    addAndMakeVisible(&m_arpButton);
    addChildComponent(&m_keySwitcher);
    
    auto &presets = app.presets();
    auto expand = [this, &presets](){
        
        if ( presets.pickerState() == PickerState::Open )
        {
            presets.pickerState( PickerState::Closed );
        }
        else
        {
            presets.pickerState( PickerState::Open );
        }
    };
    
    presets.pickerState.onChanged([this](const auto& pickerState){
        if ( pickerState == PickerState::Open )
        {
            animateOpen();
        }
        else
        {
            animateClose();
        }
    });
    m_expandButton.onClick = expand;
    m_presetTitleButton.onClick = expand;
    
    presets.supportsArpeggiator.onChangedAndNow([this](const auto& support){
        m_arpButton.setEnabled(support);
        m_arpButton.setAlpha(support ? 1.0 : 0.5 );
    });
    
    m_arpButton.setupConnection( arp_id );
    
    m_arpButton.setInfoText(TRANS("arpeggiator").toStdString(), TRANS("Some presets support rhythmic patterns you can turn on and off").toStdString());
    
    m_arpButton.onClick = [this](){
        printf( "ArpButton::onclick selected:%d\n", m_arpButton.isToggled() );
    };
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
    m_arpButton.setBounds(m_presetSwitcher.getX()/2 - switcherHeight/2 + 5, midiBarHeight, switcherHeight, switcherHeight);
    m_arpButton.resized();
    
    m_keySwitcher.setBounds(area.getWidth() - switcherHeight*3, midiBarHeight, switcherHeight*1.7, switcherHeight);
}

void PresetBarContainer::paint(Graphics& g)
{
    const auto area = getLocalBounds();
    g.setColour(juce::Colour(0xaa000000));
    g.fillRect( 0, midiBarHeight/2, area.getWidth(), area.getHeight() - midiBarHeight/2);
}

void PresetBarContainer::closePresetBar()
{
    m_presets.pickerState( PickerState::Closed );
}

void PresetBarContainer::animateOpen()
{
    juce::Desktop::getInstance().getAnimator().animateComponent(this, m_openedPos, 1.0, 300, false, 2.0, 0);
    m_expandAnimation.play(RLottieComponent::PlaybackMode::OneShotForward);
}

void PresetBarContainer::animateClose()
{    
    juce::Desktop::getInstance().getAnimator().animateComponent(this, m_closedPos, 1.0, 300, false, 2.0, 0);
    m_expandAnimation.play(RLottieComponent::PlaybackMode::OneShotBackward);
}

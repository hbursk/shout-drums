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
#include "Spec.h"

PresetBarContainer::PresetBarContainer(MainController* mc, shout::App& app, MidiListener& midiListener)
: m_presetSwitcher(app.presets(), mc)
, m_midiBarComponent(midiListener, app.presets())
, m_expandAnimation(mc->getRLottieManager())
, m_presetPicker(mc, app.presets())
, m_arpButton( mc, String(lightning_json, lightning_jsonSize) )
, m_presets( app.presets() )
, m_keySwitcher( mc, app.targetKey())
, m_presetInfoView( app.presetInfo() )
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
    addAndMakeVisible(&m_presetInfoView);
    
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
    
    m_arpButton.onClick = [this, mc](){
        if (!m_arpButton.isToggled())
        {
            // send note off to prevent stuck notes
            auto arp = static_cast<hise::Arpeggiator*>(ProcessorHelpers::getFirstProcessorWithName(mc->getMainSynthChain(), arp_id));
            arp->stopCurrentNote();
        }
    };
}

void PresetBarContainer::resized()
{
    const auto area = getLocalBounds();
    
    if (m_closedPos.getWidth() == 0)
    {
        m_closedPos = getBoundsInParent();
        const auto offset = getHeight() - shout::spec::preset::switcherHeight - shout::spec::preset::midiBarHeight;
        m_openedPos = getBoundsInParent().withY(getBoundsInParent().getY() - offset);
    }
    
    m_presetSwitcher.setBounds((area.getWidth() - shout::spec::preset::switcherWidth)/2, shout::spec::preset::midiBarHeight, shout::spec::preset::switcherWidth, shout::spec::preset::switcherHeight );
    m_presetTitleButton.setBounds(m_presetSwitcher.getX() + 40, m_presetSwitcher.getY(), m_presetSwitcher.getWidth() - 80, m_presetSwitcher.getHeight());
    m_midiBarComponent.setBounds( 0, 0, area.getWidth(), shout::spec::preset::midiBarHeight );
    m_presetPicker.setBounds(0, shout::spec::preset::midiBarHeight+shout::spec::preset::switcherHeight, area.getWidth(), area.getHeight() - shout::spec::preset::midiBarHeight - shout::spec::preset::switcherHeight - shout::spec::preset::presetInfoHeight);
    m_expandButton.setBounds( area.getWidth() - shout::spec::preset::switcherHeight, shout::spec::preset::midiBarHeight, shout::spec::preset::switcherHeight, shout::spec::preset::switcherHeight);
    m_expandAnimation.setBounds( area.getWidth() - shout::spec::preset::switcherHeight, shout::spec::preset::midiBarHeight, shout::spec::preset::switcherHeight, shout::spec::preset::switcherHeight);//midiBarHeight + 17, 20, 20);
    m_expandAnimation.resized();
    m_arpButton.setBounds(m_presetSwitcher.getX()/2 - shout::spec::preset::switcherHeight/2 + 5, shout::spec::preset::midiBarHeight, shout::spec::preset::switcherHeight, shout::spec::preset::switcherHeight);
    m_arpButton.resized();
    
    m_keySwitcher.setBounds(area.getWidth() - shout::spec::preset::switcherHeight*3, shout::spec::preset::midiBarHeight, shout::spec::preset::switcherHeight*1.7, shout::spec::preset::switcherHeight);
    
    m_presetInfoView.setBounds(0, area.getHeight() - shout::spec::preset::presetInfoHeight, area.getWidth(), shout::spec::preset::presetInfoHeight );
}

void PresetBarContainer::paint(Graphics& g)
{
    const auto area = getLocalBounds();
    g.setColour(juce::Colour(0xaa000000));
    g.fillRect( 0, shout::spec::preset::midiBarHeight/2, area.getWidth(), area.getHeight() - shout::spec::preset::midiBarHeight/2);
}

void PresetBarContainer::closePresetBar()
{
    m_presets.pickerState( PickerState::Closed );
}

void PresetBarContainer::animateOpen()
{
    juce::Desktop::getInstance().getAnimator().animateComponent(this, m_openedPos, 1.0, shout::spec::preset::switcherWidth + shout::spec::preset::presetInfoHeight, false, 2.0, 0);
    m_expandAnimation.play(RLottieComponent::PlaybackMode::OneShotForward);
}

void PresetBarContainer::animateClose()
{    
    juce::Desktop::getInstance().getAnimator().animateComponent(this, m_closedPos, 1.0, shout::spec::preset::switcherWidth + shout::spec::preset::presetInfoHeight, false, 2.0, 0);
    m_expandAnimation.play(RLottieComponent::PlaybackMode::OneShotBackward);
}

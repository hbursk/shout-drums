
#pragma once

#include "JuceHeader.h"

#include "Font.h"
#include "InfoView.h"
#include "Presets.h"

#include <memory>

template <int MacroIndex>
class MacroKnob : public juce::Component,
                  public MacroControlBroadcaster::MacroConnectionListener
{
public:
    MacroKnob() = delete;
    MacroKnob( const std::string& name, MainController* mc, Presets& presets )
    : juce::Component( name )
    , m_mainController( mc )
    , m_presets( presets )
    {
        m_mainController->getMacroManager().getMacroChain()->addMacroConnectionListener(this);
        
        addChildComponent(m_iconAnimation = new RLottieComponent(mc->getRLottieManager()));
        m_iconAnimation->setBackgroundColour(Colours::transparentBlack);

        setupSlider();
        setupLabel( name );
        
        m_slider.onValueChange = [this](){
            m_mainController->getMacroManager().getMacroChain()->setMacroControl( MacroIndex, m_slider.getValue() * 127, dontSendNotification );
        };
                
        m_presets.presetSelection.onChanged([this](const auto&){
            updateDoubleClickValue();
        });
        
        setupParameterWatcher();
        
        // set initial value
        auto value = m_mainController->getMacroManager().getMacroChain()->getMacroControlData(MacroIndex)->getCurrentValue();

        m_slider.setValue( value / 127.0, dontSendNotification );
        updateIconAnimation();
    }
    
    ~MacroKnob()
    {
        m_mainController->getMacroManager().getMacroChain()->removeMacroConnectionListener(this);
    }
    
    void resized() override
    {
        auto area = getLocalBounds();
        
        const float margin = 8.0;
        
        m_iconAnimation->setBounds(margin/2.0 + 1.0, margin,area.getWidth()- (margin + 1.0), area.getWidth()-(margin+1.0));

        m_slider.setBounds(0, 0, area.getWidth(), area.getWidth() );
        m_label.setBounds( 0, area.getWidth() - 1, area.getWidth(), 22 );
    }

    
    juce::Slider& slider()
    {
        return m_slider;
    }
        
    void mouseEnter (const MouseEvent& event) override{}
    void mouseExit( const MouseEvent& event ) override{}
    
    void setInfoText(const std::string& title, const std::string& text)
    {
        getProperties().set(info_title_property, String(CharPointer_UTF8(title.c_str())));
        getProperties().set(info_message_property, String(CharPointer_UTF8(text.c_str())));
    }
    
    void setIconAnimation(const char* animation, size_t animationSize, float start = 0.f, float end = 1.f)
    {
        m_iconAnimation->loadAnimation(String(animation, animationSize), true);
        m_iconAnimation->setVisible(true);
        m_animationStart = start;
        m_animationEnd = end;
        updateIconAnimation();
    }
    
    void updateIconAnimation()
    {
        auto normalized = m_slider.valueToProportionOfLength( m_slider.getValue() );
        auto scaled = normalized * (m_animationEnd - m_animationStart) + m_animationStart;
        m_iconAnimation->setFrameNormalised( scaled );
    }
    
    void updateDoubleClickValue()
    {
        auto value = m_mainController->getMacroManager().getMacroChain()->getMacroControlData(MacroIndex)->getCurrentValue();
        
        m_slider.setDoubleClickReturnValue(true, value);
    }
    
    void macroConnectionChanged(int macroIndex, Processor* p, int parameterIndex, bool wasAdded)
    {
        
    }
    
    void macroLoadedFromValueTree(int macroIndex, float value)
    {
        if (macroIndex == MacroIndex)
        {
            juce::MessageManager::callAsync([this, value](){
                m_slider.setValue(value/127.0, dontSendNotification);
            });

            setupParameterWatcher();
        }
    }
    
    void macroChangedByAutomation(int macroIndex, float value)
    {
        if (macroIndex == MacroIndex)
        {
            juce::MessageManager::callAsync([this, value](){
                m_slider.setValue(value/127.0, dontSendNotification);
            });
        }
    }
    
private:
    void setupSlider()
    {
        addAndMakeVisible( &m_slider );

        m_slider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
        m_slider.setTextBoxStyle(Slider::NoTextBox, false, getLocalBounds().getWidth(), getLocalBounds().getWidth() );
        m_slider.setRange(0.0, 1.0);
        m_slider.setRotaryParameters(juce::MathConstants<float>::pi, juce::MathConstants<float>::pi * 3, true);
    }
    
    void setupLabel( const std::string& name )
    {
        if (name.empty())
        {
            return;
        }
        
        addAndMakeVisible( &m_label );
        m_label.setText( name, dontSendNotification );
        m_label.setJustificationType( Justification::centred );
        m_label.setEditable( false );
        m_label.setFont( shout::Font::mainFont( 20.f ) );
        m_label.setColour( juce::Label::textColourId, Colour( 0xffffffff) );
    }
    
    void setupParameterWatcher()
    {
        if (auto data = m_mainController->getMacroManager().getMacroChain()->getMacroControlData(MacroIndex))
        {
            if ( data->getNumParameters() == 0 )
            {
                return;
            }
            
            auto pData = data->getParameter(0);
            auto proc = pData->getProcessor();
            auto pIndex = pData->getParameter();
            
            if ( proc != nullptr )
            {
                m_processorReference = std::make_unique<hise::raw::Reference<Processor>>( m_mainController, proc->getId(), true);
                
                hise::raw::Reference<Processor>::ParameterCallback update = [this](float newValue)
                {
                    auto data = m_mainController->getMacroManager().getMacroChain()->getMacroControlData(MacroIndex);
                    
                    auto pData = data->getParameter(0);
                    if (m_iconAnimation)
                    {
                        auto range = pData->getParameterRange();
                        auto n = range.convertTo0to1(newValue);
                        auto normalized = m_slider.valueToProportionOfLength( n );
                        auto scaled = normalized * (m_animationEnd - m_animationStart) + m_animationStart;
                        juce::MessageManager::callAsync([this, scaled](){
                            m_iconAnimation->setFrameNormalised( scaled );
                        });

                    }
                };

                m_processorReference->addParameterToWatch(pIndex, update);
            }
        }
    }

    
    juce::Slider m_slider;
    juce::Label  m_label;
    MainController* m_mainController = nullptr;
    
    ScopedPointer<RLottieComponent> m_iconAnimation;
    float m_animationStart = 0.0f;
    float m_animationEnd = 1.0f;
    Presets& m_presets;
    
    std::unique_ptr<hise::raw::Reference<Processor>> m_processorReference;


};

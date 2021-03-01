#pragma once

#include "JuceHeader.h"

#include "AttributedLabel.h"
#include "Presets.h"

namespace {
constexpr char info_title_property[] = "InfoTitleProperty";
constexpr char info_message_property[] = "InfoMessageProperty";
};


class InfoView : public juce::Component, private juce::Timer
{
public:
    InfoView(Presets& presets);
    virtual ~InfoView();

    void resized() override;
    
    void refresh();
    void clear();
    void disableDisplay(bool disable);

private:
    void timerCallback() override;
    void setText( const std::string& text, const std::string& title );

    juce::Component* findComponentWithInfoAt( juce::Component* component, juce::Point<int> point );

    AttributedLabel   m_infoMessage;

    juce::Component::SafePointer<juce::Component> m_infoComponent = nullptr;
    std::string m_text;
    std::string m_title;
    bool m_displayDisabled = false;
};

#pragma once

#include "JuceHeader.h"

class AttributedLabel : public juce::Component
{
public:
    using super_t = juce::Component;

    void setText( juce::AttributedString );

    void paint( juce::Graphics& ) override;
    void resized() override;
    void enablementChanged() override;

private:
    juce::AttributedString m_text;
};

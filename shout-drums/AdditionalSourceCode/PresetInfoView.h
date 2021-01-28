#pragma once

#include "JuceHeader.h"

#include "AttributedLabel.h"
#include "PresetInfo.h"

namespace shout
{
class PresetInfoView : public juce::Component
{
public:
    PresetInfoView(PresetInfo& presetInfo);

    void resized() override;
    
    void paint(juce::Graphics& g) override;
    
private:
    void setText( const std::string& author, const std::string& description, const std::string& title );

    AttributedLabel   m_infoLabel;
    AttributedLabel   m_authorLabel;

    juce::Component::SafePointer<juce::Component> m_infoComponent = nullptr;
    juce::ImageButton m_urlClick;
    
    PresetInfo& m_presetInfo;
};
}

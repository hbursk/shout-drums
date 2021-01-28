
#pragma once

#include "JuceHeader.h"

namespace shout {

class HorizontalListBox : public juce::ListBox
{
public:
    HorizontalListBox(const String& componentName = String(),
                       ListBoxModel* model = nullptr);
    
    virtual ~HorizontalListBox() = default;
    
    void mouseWheelMove(const MouseEvent&, const MouseWheelDetails&) override;

};
}

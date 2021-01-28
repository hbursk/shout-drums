
#include "HorizontalListBox.h"

using namespace shout;

HorizontalListBox::HorizontalListBox(const String& componentName,
                                     ListBoxModel* model)
: ListBox( componentName, model)
{
    
}

void HorizontalListBox::mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel)
{
    bool eventWasUsed = false;

    if (wheel.deltaX != 0.0f && getHorizontalScrollBar().isVisible())
    {
        eventWasUsed = true;
        getHorizontalScrollBar().mouseWheelMove (e, wheel);
    }

    if (wheel.deltaY != 0.0f && getVerticalScrollBar().isVisible() && !isTransformed())
    {
        eventWasUsed = true;
        getVerticalScrollBar().mouseWheelMove(e, wheel);
    }

    if (! eventWasUsed)
    {
        Component::mouseWheelMove (e, wheel);
    }
}

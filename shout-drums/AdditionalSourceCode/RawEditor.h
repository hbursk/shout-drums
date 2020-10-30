#pragma once

#include "Raw.h"

#include <memory>

#if USE_RAW_FRONTEND

class MainComponent;
class DrumsInterface : public Component, public ControlledObject
{
public:

	DrumsInterface(DrumsData* data);

	void paint(Graphics& g) override;

	void resized() override;

private:
    std::unique_ptr<MainComponent> m_mainComponent;
    

};

#endif 

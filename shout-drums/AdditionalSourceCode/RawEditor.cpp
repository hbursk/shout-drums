#include "RawEditor.h"

#if USE_RAW_FRONTEND
#include "MainComponent.h"

DrumsInterface::DrumsInterface(DrumsData* data) :
	ControlledObject(data->getMainController())
    , m_mainComponent(std::make_unique<MainComponent>(data->getMainController()) )
{
    addAndMakeVisible( m_mainComponent.get() );

	setSize(800, 600);    
}

void DrumsInterface::paint(Graphics& g)
{
}

void DrumsInterface::resized()
{
    m_mainComponent->setBounds( getLocalBounds() );
}

Component* DrumsData::createEditor()
{
	return new DrumsInterface(this);
}

#endif

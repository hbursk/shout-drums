#pragma once

#include "JuceHeader.h"

#if USE_RAW_FRONTEND


class DrumsData : public hise::raw::DataHolderBase
{
public:

	DrumsData(MainController* mc);

	template <class FunctionType> void addToUserPreset(const String& storageId, const String& processorId)
	{
		auto p = ProcessorHelpers::getFirstProcessorWithName(getMainController()->getMainSynthChain(), processorId);
		storedData.add(new raw::Storage<FunctionType>(storageId, p));
	}

	void addParameter(AudioProcessorParameter* p)
	{
		auto fp = dynamic_cast<FrontendProcessor*>(getMainController());

		fp->addParameter(p);
	}

	void restoreFromValueTree(const ValueTree& v) override
	{
        int size = v.getNumChildren();
		if (v.getNumChildren() != storedData.size())
		{
            auto xml = v.toXmlString();
            printf("Preset\n%s\n", xml.toStdString().c_str());
            if ( size > storedData.size() )
            {
                size = storedData.size();
            }
            else
            {
                jassertfalse;
                return;
            }
		}

		for (int i = 0; i < size; i++)
		{
			storedData[i]->restoreFromValueTree(v.getChild(i));
		}
	}

	ValueTree exportAsValueTree() const
	{
		ValueTree v("Preset");

		for (auto s : storedData)
			v.addChild(s->exportAsValueTree(), -1, nullptr);

		return v;
	}
    
    void addDrumSampler( const std::string& id, const std::string& muterId, raw::Builder& builder,  hise::ModulatorSynthChain* root, MainController* mc, String mapName );

	Component* createEditor() override;

private:
    void createModules(MainController* mc);
    void createPluginParameters(MainController* mc);

	OwnedArray<raw::GenericStorage> storedData;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DrumsData);
	JUCE_DECLARE_WEAK_REFERENCEABLE(DrumsData);
};

#endif 

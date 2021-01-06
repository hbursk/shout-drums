//
//  SampleMaps.hpp
//  DrumTest - AU
//
//  Created by Hayden Bursk on 9/20/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#pragma once

#include "JuceHeader.h"

#include "Property.h"

#include <vector>
#include <string>

class SampleMaps
{
public:
    SampleMaps(hise::MainController* mc);
    ~SampleMaps() = default;
    
    Property<std::vector<std::string>> sampleMaps;
    Property<std::vector<std::string>> kickMaps;
    Property<std::vector<std::string>> snareMaps;
    Property<std::vector<std::string>> clapMaps;
    Property<std::vector<std::string>> hatMaps;
    Property<std::vector<std::string>> cymbalMaps;
    Property<std::vector<std::string>> percMaps;
    Property<std::vector<std::string>> tomsMaps;
    Property<std::vector<std::string>> instrumentMaps;

private:
    hise::MainController* m_mainController = nullptr;
    
    void filterSampleMaps( const std::vector<std::string>& filter, Property<std::vector<std::string>>& property );
    
};

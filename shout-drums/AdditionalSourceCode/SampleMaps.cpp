//
//  SampleMaps.cpp
//  DrumTest - AU
//
//  Created by Hayden Bursk on 9/20/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#include "SampleMaps.h"


SampleMaps::SampleMaps( hise::MainController* mc )
: m_mainController( mc )
{
    std::vector<std::string> maps;
    auto pool = mc->getCurrentSampleMapPool();
    auto references = pool->getListOfAllReferences(true);

    PoolReference::Comparator comparator;

    references.sort(comparator);

    maps.reserve( references.size() );

    for (auto r : references)
    {
        maps.push_back(r.getReferenceString().toStdString());
    }
    
    sampleMaps( maps );
    
    filterSampleMaps( {"Kick"}, kickMaps );
    filterSampleMaps( {"Snare"}, snareMaps );
    filterSampleMaps( {"Hat"}, hatMaps );
    filterSampleMaps( {"Perc"}, percMaps );
    filterSampleMaps( {"Clap"}, clapMaps );
    filterSampleMaps( {"Cymbal"}, cymbalMaps );
    filterSampleMaps( {"Tom"}, tomsMaps );
    
    // TODO: Change filter when I have the proper instruments
    filterSampleMaps( {"FX", "Strings", "Synth", "Bass", "Vox"}, instrumentMaps );
}

void SampleMaps::filterSampleMaps( const std::vector<std::string>& filter, Property<std::vector<std::string>>& property )
{
    auto maps = sampleMaps();
    
    std::vector<std::string> filtered;
    
    for ( const auto& map : maps )
    {
        for ( const auto& filt : filter )
        {
            if ( map.find(filt) != std::string::npos )
            {
                filtered.push_back( map );
                break;
            }
        }
    }
    
    property( filtered );
}

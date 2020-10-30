//
//  Localizations.cpp
//  DrumTest - Shared Code
//
//  Created by Hayden Bursk on 10/23/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#include "Localizations.h"

#include "Spanish.h"

using namespace shout;

Localizations::Localizations()
{
    if( SystemStats::getUserLanguage() == "es" )
    {
        juce::LocalisedStrings *currentMappings = new             juce::LocalisedStrings(String::createStringFromData(Spanish_txt, Spanish_txtSize), false);
        juce::LocalisedStrings::setCurrentMappings(currentMappings);
    }
}

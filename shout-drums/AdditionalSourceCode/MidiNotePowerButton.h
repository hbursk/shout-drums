//
//  MidiNotePowerButton.h
//  Snackage - App
//
//  Created by Hayden Bursk on 1/6/21.
//  Copyright © 2021 Shout Audio. All rights reserved.
//

#pragma once

#include "PowerButton.h"

class MidiNotePowerButton : public PowerButton<raw::Data<bool>::InvertedBoolAttribute<MuteAllScriptProcessor::Parameters::IgnoreNotes>>
{
public:
    MidiNotePowerButton(MainController* mc, const String& name, const String& processorId):
                        PowerButton(mc, name, processorId){}
                        
    virtual ~MidiNotePowerButton() = default;
                        
};

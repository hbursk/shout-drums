//
//  TargetKey.hpp
//  Snackage
//
//  Created by Hayden Bursk on 1/18/21.
//  Copyright © 2021 Shout Audio. All rights reserved.
//

#pragma once

#include "JuceHeader.h"

#include "Property.h"
#include "Presets.h"

class TargetKey
{
public:
    TargetKey( MainController* mc, Presets& presets);
    
    Property<TonalKey> targetKey{TonalKey::None};
    Property<bool> hasTonalKey{false};
    
    void setTargetKey( TonalKey key );
    void nextKey();
    void prevKey();
    
private:
    
    
    MainController *m_mainController = nullptr;
    
};

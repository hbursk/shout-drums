//
//  TargetKey.cpp
//  Snackage
//
//  Created by Hayden Bursk on 1/18/21.
//  Copyright © 2021 Shout Audio. All rights reserved.
//

#include "TargetKey.h"

TargetKey::TargetKey( MainController* mc, Presets& presets)
: m_mainController( mc )
{
    presets.presetSelection.onChangedAndNow([this](const auto& selection){
        auto target = m_mainController->getTargetKey();
        auto source = m_mainController->getSourceKey();
        
        if ( target == TonalKey::None && source != TonalKey::None )
        {
            targetKey( source );
        }
        else if ( target != TonalKey::None && source != TonalKey::None )
        {
            targetKey( target );
        }
        
        hasTonalKey( m_mainController->getSourceKey() != TonalKey::None );
    });
}

void TargetKey::setTargetKey( TonalKey key )
{
    m_mainController->setTargetKey(key);
    targetKey( key );
}

void TargetKey::nextKey()
{
    auto key = targetKey();
    
    if ( key == TonalKey::None )
    {
        return;
    }
    
    key = static_cast<TonalKey>(static_cast<int>(key) + 1);
    if ( key >= TonalKey::NumKeys )
    {
        key = static_cast<TonalKey>(0);
    }
    
    setTargetKey( key );
}

void TargetKey::prevKey()
{
    auto key = targetKey();
    
    if ( key == TonalKey::None )
    {
        return;
    }

    if ( key == 0 )
    {
        key = TonalKey::NumKeys;
    }
    
    key = static_cast<TonalKey>(static_cast<int>(key) - 1);

    setTargetKey( key );
}

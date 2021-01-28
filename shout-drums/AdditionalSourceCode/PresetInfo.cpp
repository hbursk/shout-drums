//
//  PresetInfo.cpp
//  Snackage
//
//  Created by Hayden Bursk on 1/25/21.
//  Copyright © 2021 Shout Audio. All rights reserved.
//

#include "PresetInfo.h"
#include "PresetInfo-en.h"

using namespace shout;

PresetInfo::PresetInfo(Presets& presets)
{
    parseJson();

    presets.presetNameOnly.onChangedAndNow([this](const auto& name){
        if ( m_map.find(name) != m_map.end())
        {
            info( m_map.at( name ) );
        }
    });
}

void PresetInfo::openUrl() const
{
    if ( info().author.url.empty() )
    {
        return;
    }
    
    juce::URL( info().author.url ).launchInDefaultBrowser();
}

void PresetInfo::parseJson()
{
    auto json = String( PresetInfoen_json, PresetInfoen_jsonSize).toStdString();
    const auto j = json::parse( json );
    
    auto authors = j.at("authors").get<nlohmann::json>();
    
    std::unordered_map<std::string, Author> authorMap;
    for (auto it = authors.begin(); it != authors.end(); ++it )
    {
        authorMap[it.key()] = Author(it.value());
    }
    
    auto presets = j.at("presets").get<nlohmann::json>();
    
    for (json::iterator it = presets.begin(); it != presets.end(); ++it)
    {
        auto authorKey = it.value().at("author").get<std::string>();
        auto auth = Author();
        if (!authorKey.empty())
        {
            auth = authorMap.at(authorKey);
        }
        
        auto info = Info(it.value(), it.key(), auth);
        m_map[it.key()] = info;
    }
}

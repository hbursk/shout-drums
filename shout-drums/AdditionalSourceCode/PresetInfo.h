//
//  PresetInfo.h
//  Snackage
//
//  Created by Hayden Bursk on 1/25/21.
//  Copyright © 2021 Shout Audio. All rights reserved.
//

#pragma once

#include "Presets.h"
#include "Property.h"

#include "nlohmann/json.hpp"

#include <string>
#include <unordered_map>

using nlohmann::json;

namespace shout
{

struct Author
{
    std::string name;
    std::string url;
    
    Author() = default;
    Author(const json& j)
    {
        name = j.at("name").get<std::string>();
        url = j.at("url").get<std::string>();
    }
    
    inline bool operator==(const Author& other ) const
    {
        return name == other.name &&
        url == other.url;
    }
    
    inline bool operator!=(const Author& other) const
    {
        return name != other.name ||
            url != other.url;
    }

};

struct Info
{
    Author author;
    std::string description;
    std::string title;
    
    inline bool operator==(const Info& other ) const
    {
        return author == other.author &&
               description == other.description &&
               title == other.title;
    }
    
    inline bool operator!=(const Info& other) const
    {
        return author != other.author ||
               description != other.description ||
               title != other.title;
    }

    Info() = default;
    Info(const json& j, const std::string& _title, Author _author)
    : author( std::move(_author) )
    , title( _title )
    {
        if ( j.find("description") != j.end())
        {
            description = j.at("description").get<std::string>();
        }
    }
};

class PresetInfo
{
public:
    using Map = std::unordered_map<std::string, Info>;
    PresetInfo(Presets& presets);
    ~PresetInfo() = default;
    
    Property<Info> info;
    
    void openUrl() const;
    
private:
    void parseJson();
    
    Map m_map;
    
};
}

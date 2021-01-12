
#include "Presets.h"
#include "Colors.h"

#include <algorithm>

const char category_drums[] = "Drums";
const char category_fx[] = "FX";
const char category_lead[] = "Keys";
const char category_bass[] = "Bass";
const char category_vox[] = "Vox";

Presets::Presets(hise::MainController* _mc)
: m_mainController( _mc )
{
    assert( m_mainController );
    m_mainController->getUserPresetHandler().addListener( this );

    buildPresets();

    updateSelection();
}

Presets::~Presets()
{
    m_mainController->getUserPresetHandler().removeListener( this );
}

const std::vector<Bank>& Presets::banks() const
{
    return m_banks;
}

const std::string Presets::presetNameForIndex(size_t index) const
{
    auto preset = presetForIndex(index);
    return preset.name;
}

size_t Presets::numPresets() const
{
    size_t count = 0;
    for (const auto& bank : m_banks)
    {
        for (const auto& category : bank.categories)
        {
            count += category.presets.size();
        }
    }
    
    return count;
}

void Presets::presetChanged(const File& newPreset)
{
    updateSelection();
}

void Presets::presetListUpdated()
{
    buildPresets();
}

void Presets::loadPreset( PresetSelection selection )
{
    auto preset = m_banks[selection.bank]
                  .categories[selection.category]
                  .presets[selection.preset];
    
    m_mainController->getUserPresetHandler().loadUserPreset(preset.file);
}

void Presets::loadPreset( size_t index )
{
    auto preset = presetForIndex(index);
    m_mainController->getUserPresetHandler().loadUserPreset(preset.file);
}

void Presets::nextPreset()
{
    m_mainController->getUserPresetHandler().incPreset( true, false );
}

void Presets::prevPreset()
{
    m_mainController->getUserPresetHandler().incPreset( false, false );
}

void Presets::buildPresets()
{
    m_banks.clear();
    
    Array<File> allPresets;

    auto userDirectory = FrontendHandler::getUserPresetDirectory();

    userDirectory.findChildFiles(allPresets, File::findFiles, true, "*.preset");
    PresetBrowser::DataBaseHelpers::cleanFileList(m_mainController, allPresets);
    allPresets.sort();
    
    Bank currentBank;
    Category currentCategory;
    
    m_banks.push_back( currentBank );
    size_t bankIndex = 0;
    size_t catIndex = 0;
    for ( const auto& preset : allPresets )
    {
        auto name = lowercase( preset.getFileNameWithoutExtension().toStdString() );
        auto category = preset.getParentDirectory();
        auto categoryName = category.getFileNameWithoutExtension().toStdString();
        auto categoryType = categoryStringToType(categoryName);
        auto categoryColor = categoryTypeToColor(categoryType);
        auto bankName = category.getParentDirectory().getFileNameWithoutExtension().toStdString();
        
        Preset p;
        p.name = name;
        p.file = preset;
        p.category = CategoryTypeAndColor(categoryType, categoryColor);
        
        auto& b = m_banks[bankIndex];
        if ( b.name.empty() )
        {
            // first entry
            b.name = bankName;
            Category c;
            c.name = categoryName;
            c.type = categoryType;
            c.color = categoryColor;
            c.presets.push_back( p );
            b.categories.push_back( c );
            continue;
        }
        
        auto& c = b.categories[catIndex];

        if ( b.name == bankName)
        {
            // still on the same bank
            if ( c.name != categoryName )
            {
                // next category
                catIndex++;
                Category nextC;
                nextC.name = categoryName;
                nextC.type = categoryType;
                nextC.color = categoryColor;
                nextC.presets.push_back( p );
                b.categories.push_back( nextC );
            }
            else
            {
                // same category
                c.presets.push_back( p );
            }
            
        }
        else if ( b.name != bankName )
        {
            // need new bank
            bankIndex++;
            
            Bank nextBank;
            nextBank.name = bankName;
            
            Category nextCategory;
            nextCategory.name = categoryName;
            nextCategory.type = categoryType;
            nextCategory.color = categoryColor;
            nextCategory.presets.push_back( p );
            
            nextBank.categories.push_back( nextCategory );
            m_banks.push_back( nextBank );
            
            catIndex = 0;
        }
    }
}

void Presets::updateSelection()
{
    auto file = m_mainController->getUserPresetHandler().getCurrentlyLoadedFile();
    auto fileName = file.getFileNameWithoutExtension();
    
    if ( fileName.isEmpty() )
    {
        presetName( TRANS("load a preset").toStdString() );
        presetBank( "Factory" );
        presetCategory( CategoryTypeAndColor(CategoryType::Drums, categoryTypeToColor(CategoryType::Drums) ) );
        presetSelection( PresetSelection() );
        return;
    }
    
    auto catDir = file.getParentDirectory();
    auto bankDir = catDir.getParentDirectory();
    auto presetStr = lowercase( fileName.toStdString() );
    
    int bank = 0;
    int cat = 0;
    int preset = 0;
    for ( bank=0; bank < m_banks.size(); bank++ )
    {
        if ( m_banks[bank].name == bankDir.getFileNameWithoutExtension() )
        {
            break;
        }
    }
    
    for ( cat=0; cat < m_banks[bank].categories.size(); cat++ )
    {
        if ( m_banks[bank].categories[cat].name == catDir.getFileNameWithoutExtension() )
        {
            break;
        }
    }
    
    for ( preset=0; preset < m_banks[bank].categories[cat].presets.size(); preset++ )
    {
        if ( m_banks[bank].categories[cat].presets[preset].name == presetStr )
        {
            break;
        }
    }
    
    presetBank( m_banks[bank].name );
    presetCategory( CategoryTypeAndColor(m_banks[bank].categories[cat].type,  m_banks[bank].categories[cat].color) );
    presetName( lowercase(m_banks[bank].categories[cat].name + " || " + presetStr) );
    supportsArpeggiator( m_banks[bank].categories[cat].type != CategoryType::Drums );

    PresetSelection sel;
    sel.bank = bank;
    sel.category = cat;
    sel.preset = preset;
    sel.linearIndex = indexForPreset(bank, cat, preset);
    presetSelection( sel );
}

std::string Presets::lowercase(const std::string& str)
{
    auto copy = str;
    std::transform(copy.begin(), copy.end(), copy.begin(),
    [](unsigned char c){ return std::tolower(c); });
    
    return copy;
}

Preset Presets::presetForIndex(size_t index) const
{
    for (const auto& bank : m_banks )
    {
        for (const auto& category : bank.categories )
        {
            if ( category.presets.size() <= index )
            {
                index = index - category.presets.size();
            }
            else
            {
                return category.presets[index];
            }
        }
    }

    return Preset();
}

int Presets::indexForPreset(int bank, int category, int preset) const
{
    int linearIndex = 0;
    int bankIndex = 0;
    while (bankIndex != bank)
    {
        const auto& categories = m_banks[bankIndex].categories;
        for (const auto& cat : categories)
        {
            linearIndex += cat.presets.size();
        }
        
        bankIndex++;
    }
    
    const auto& categories = m_banks[bankIndex].categories;
    
    int categoryIndex = 0;
    while (categoryIndex != category)
    {
        linearIndex += categories[categoryIndex].presets.size();
        categoryIndex++;
    }
    
    linearIndex += preset;
    
    return linearIndex;
}

CategoryType Presets::categoryStringToType(const std::string& category) const
{
    if ( category == category_drums)
    {
        return CategoryType::Drums;
    }
    else if ( category == category_fx )
    {
        return CategoryType::FX;
    }
    else if (category == category_lead)
    {
        return CategoryType::Lead;
    }
    else if (category == category_vox)
    {
        return CategoryType::Vox;
    }
    else if ( category == category_bass)
    {
        return CategoryType::Bass;
    }
    else if ( category == "User Presets")
    {
        return CategoryType::Drums;
    }
    
    throw std::runtime_error("Uknown category string");
}

std::string Presets::categoryTypeToString(const CategoryType& type) const
{
    switch (type)
    {
        case CategoryType::Drums:
            return category_drums;
            
        case CategoryType::FX:
            return category_fx;
            
        case CategoryType::Lead:
            return category_lead;
            
        case CategoryType::Bass:
            return category_bass;
            
        case CategoryType::Vox:
            return category_vox;
            
        default:
            throw std::runtime_error("Unhandled category type");
    }
}

juce::Colour Presets::categoryTypeToColor(const CategoryType& type) const
{
    switch (type)
    {
        case CategoryType::Drums:
            return shout::spec::color::drums_pink;
            
        case CategoryType::FX:
            return shout::spec::color::fx_blue;
            
        case CategoryType::Lead:
            return shout::spec::color::keys_orange;
            
        case CategoryType::Bass:
            return shout::spec::color::bass_teal;

        case CategoryType::Vox:
            return shout::spec::color::vox_pink;

        default:
            throw std::runtime_error("Unhandled category type");
    }

}




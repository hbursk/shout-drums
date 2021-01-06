#include "MainComponent.h"
#include "Colors.h"
#include "ImageData.h"
#include "Font.h"
#include "WaterFillFlatAnimation.h"
#include "WaterFillFlatAnimationPink.h"
#include "WaterFillFlatAnimationDarkPink.h"

//#define SHOW_KEYBOARD
//#define SHOW_PRESET_EDITOR
//#define USE_OPENGL

#if USE_RAW_FRONTEND
MainComponent::MainComponent(MainController* mc) :
#else
MainComponent::MainComponent(juce::FloatingTile* parent) :
FloatingTileContent(parent)
,
#endif
  m_app( mc )
, m_gainSlider( "", mc, "Simple Gain1", m_app.presets() )
//, m_reverbMixSlider( TRANS("reverb").toStdString(), mc, "Convolution Reverb", m_app.presets() )
, m_reverbMacroSlider( TRANS("reverb").toStdString(), mc, m_app.presets())
, m_saturationMixSlider( TRANS("drive").toStdString(), mc, "Shape FX1", m_app.presets() )
, m_widthSlider( TRANS("width").toStdString(), mc, "Simple Gain1", m_app.presets() )
, m_delayMixSlider( TRANS("delay").toStdString(), mc, "Delay1", m_app.presets() )
, m_attackSlider( TRANS("attack").toStdString(), mc, "AHDSR Envelope1", m_app.presets() )
, m_releaseSlider( TRANS("release").toStdString(), mc, "AHDSR Envelope1", m_app.presets() )
, m_attackReleaseContainer( "attack/release" )
, m_backgroundImage()
, m_presetEditorComponent( mc, m_app )
, m_presetBarContainer( mc, m_app.presets(), m_app.midiListener())
, m_editButton( TRANS("edit") )
, m_mainController( mc )
{
#ifdef USE_OPENGL
    m_openGLContext.attachTo(*this);
#endif
    setLookAndFeel(&m_shoutLookAndFeel);
    
    assert( mc );
    
    auto slaf = dynamic_cast<hise::ScriptingObjects::ScriptedLookAndFeel*>(mc->getCurrentScriptLookAndFeel());
    if (slaf)
    {
        slaf->f = shout::Font::labelFont(16.0);
    }
    
    addAndMakeVisible( &m_backgroundImage );
    addAndMakeVisible( &m_backgroundClick );
    
#ifdef SHOW_KEYBOARD
    
    // Get the data model that handles MIDI messages from our main controller
    auto& state = mc->getKeyboardState();

    // Add a stock JUCE MIDI keyboard and connect it to the main controller's MIDI state
    addAndMakeVisible(m_stockKeyboard = new juce::MidiKeyboardComponent(state, MidiKeyboardComponent::horizontalKeyboard));
    m_stockKeyboard->setKeyWidth(40);
#endif

    addAndMakeVisible( &m_infoView );
        
    const float animationStart = 0.0099f;
    const float animationEnd = 0.9703f;

            
    addAndMakeVisible( &m_gainSlider );
    m_gainSlider.rangeAndSkewPoint( -100.f, 0.f, -30.f );
    m_gainSlider.setInfoText(TRANS("output").toStdString(), TRANS("Click and drag up and down to change the main volume").toStdString());
    m_gainSlider.updateDoubleClickValue();

//    addAndMakeVisible( &m_reverbMixSlider );
//    m_reverbMixSlider.rangeAndSkewPoint( -100.f, -20.f, -30.f );
//    m_reverbMixSlider.setInfoText(TRANS("reverb").toStdString(), TRANS("Click and drag up and down to add more space").toStdString());
//    m_reverbMixSlider.setIconAnimation(waterfillpink_json, waterfillpink_jsonSize, animationStart, animationEnd);
//    m_reverbMixSlider.updateDoubleClickValue();
    
    addAndMakeVisible( &m_reverbMacroSlider );
    m_reverbMacroSlider.setInfoText(TRANS("reverb").toStdString(), TRANS("Click and drag up and down to add more space").toStdString());
    m_reverbMacroSlider.setIconAnimation(waterfillpink_json, waterfillpink_jsonSize, animationStart, animationEnd);
    m_reverbMacroSlider.updateDoubleClickValue();
    
    addAndMakeVisible( &m_saturationMixSlider );
    m_saturationMixSlider.rangeAndSkewPoint(0.0, 0.75, 0.37);
    m_saturationMixSlider.setInfoText(TRANS("drive").toStdString(), TRANS("Click and drag up and down to add more grit and dirt").toStdString());
    m_saturationMixSlider.setIconAnimation(waterfillpink_json, waterfillpink_jsonSize, animationStart, animationEnd);
    m_saturationMixSlider.updateDoubleClickValue();

    addAndMakeVisible( &m_delayMixSlider );
    m_delayMixSlider.rangeAndSkewPoint(0.0, 0.5, 0.2);
    m_delayMixSlider.setInfoText(TRANS("delay").toStdString(), TRANS("Click and drag up and down to add more echoes").toStdString());
    m_delayMixSlider.setIconAnimation(waterfillpink_json, waterfillpink_jsonSize, animationStart, animationEnd);
    m_delayMixSlider.updateDoubleClickValue();


    addAndMakeVisible( &m_widthSlider );
    m_widthSlider.rangeAndSkewPoint(0, 200, 100);
    m_widthSlider.setInfoText(TRANS("width").toStdString(), TRANS("Click and drag up and down to make your sound more narrow (mono) or more wide (stereo)").toStdString());
    m_widthSlider.setIconAnimation(waterfillpink_json, waterfillpink_jsonSize, animationStart, animationEnd);
    m_widthSlider.updateDoubleClickValue();

    addChildComponent( &m_attackReleaseContainer );
    m_attackReleaseContainer.addAndMakeVisible( &m_attackSlider );
    m_attackSlider.slider().setRange(juce::Range<double>(0, 20000), 1);
    m_attackSlider.setInfoText(TRANS("attack").toStdString(), TRANS("Click and drag up and down to control how your sounds fade in").toStdString());
    m_attackSlider.setIconAnimation(waterfillpink_json, waterfillpink_jsonSize, animationStart, animationEnd);
    m_attackSlider.updateDoubleClickValue();

    
    m_attackReleaseContainer.addAndMakeVisible( &m_releaseSlider );
    m_releaseSlider.slider().setRange(juce::Range<double>(80,20000), 1);
    m_releaseSlider.setInfoText(TRANS("release").toStdString(), TRANS("Click and drag up and down to control how your sounds fade out").toStdString());
    m_releaseSlider.setIconAnimation(waterfillpink_json, waterfillpink_jsonSize, animationStart, animationEnd);
    m_releaseSlider.updateDoubleClickValue();

    
    addAndMakeVisible( &m_presetBarContainer );
    
    m_backgroundClick.onClick = [this](){
        m_presetBarContainer.closePresetBar();
    };
    
    m_editButton.onClick = [this](){
        m_presetEditorComponent.setVisible( !m_presetEditorComponent.isVisible() );
    };
    
    m_app.presets().presetCategory.onChangedAndNow([this, animationStart, animationEnd](const auto& category)
    {
        juce::Image bgImage;
        switch (category)
        {
            case CategoryType::Drums:
        {
            bgImage = juce::ImageFileFormat::loadFrom( Drums_png, Drums_pngSize );
            m_attackReleaseContainer.setVisible( false );
            getLookAndFeel().setColour( Slider::rotarySliderFillColourId, shout::spec::color::drums_pink );
            updateAllKnobIconAnimation(waterfillpink_json, waterfillpink_jsonSize);
        }
                break;
                
            case CategoryType::FX:
        {
            bgImage = juce::ImageFileFormat::loadFrom( Eyes_png, Eyes_pngSize );
            m_attackReleaseContainer.setVisible( true );
            getLookAndFeel().setColour( Slider::rotarySliderFillColourId, Colour( 0xffe84393 ) );
            updateAllKnobIconAnimation(water_fill_curves_json, water_fill_curves_jsonSize);
        }
                break;
                
            case CategoryType::Vox:
            {
            bgImage = juce::ImageFileFormat::loadFrom( Vox_png, Vox_pngSize );
            m_attackReleaseContainer.setVisible( true );
            getLookAndFeel().setColour( Slider::rotarySliderFillColourId, shout::spec::color::vox_pink );
            updateAllKnobIconAnimation(waterfill_darkpink_json, waterfill_darkpink_jsonSize);
            }
                break;

            case CategoryType::Lead:
                break;
                
            case CategoryType::Bass:
                break;
                
            default:
                break;
        }
                
        m_backgroundImage.setImage( bgImage, RectanglePlacement::stretchToFit );
        m_infoView.clear();
    });
    
#ifdef SHOW_PRESET_EDITOR
    addChildComponent( &m_presetEditorComponent );
    addAndMakeVisible( &m_editButton );
#endif
}

MainComponent::~MainComponent()
{
    m_stockKeyboard = nullptr;
#ifdef USE_OPENGL
    m_openGLContext.detach();
#endif
}

void MainComponent::resized()
{
    // Position the elements
    const int total_width = 800;
    const int total_height = 600;
    
    if ( m_stockKeyboard )
    {
        m_stockKeyboard->setBounds( 0, 0, total_width, 200 );
    }
    
    const auto area = juce::Rectangle<int>(0, 0, total_width, total_height);
    
    m_backgroundImage.setBounds( 0, 0, total_width, total_height);
    m_backgroundClick.setBounds( 0, 0, total_width, total_height);
    
    const int width = 120;
    const int height = 160;
    const int gainWidth = 50;
    m_gainSlider.setBounds( total_width - gainWidth, -3, gainWidth, gainWidth );

    // layout knobs
    auto fb = juce::FlexBox();
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignContent = juce::FlexBox::AlignContent::center;

    fb.items.add (juce::FlexItem (m_saturationMixSlider).withMinWidth (width).withMinHeight (height));
    fb.items.add (juce::FlexItem (m_delayMixSlider).withMinWidth (width).withMinHeight (height));
//    fb.items.add (juce::FlexItem (m_reverbMixSlider).withMinWidth (width).withMinHeight (height));
    fb.items.add (juce::FlexItem (m_reverbMacroSlider).withMinWidth (width).withMinHeight (height));
    fb.items.add (juce::FlexItem (m_widthSlider).withMinWidth (width).withMinHeight (height));

    fb.performLayout (area.withTrimmedBottom( 80 ).toFloat() );
    
    const int switcherHeight = 60;
    const int midiBarHeight = 8;
    const int presetBarHeight = switcherHeight + midiBarHeight + 128;
    
    m_presetBarContainer.setBounds( 0, total_height - switcherHeight - midiBarHeight, total_width, presetBarHeight );
    m_infoView.setBounds(0, m_presetBarContainer.getY() - 40, total_width, 40);
    
    m_attackReleaseContainer.setBounds(0, total_height/2 - 38, total_width, total_height/2 - switcherHeight);
    m_attackSlider.setBounds( total_width/2 - width/2 - width/2, switcherHeight, width, height );
    m_releaseSlider.setBounds( total_width/2 - width/2 + width/2, switcherHeight, width, height );
    
    m_editButton.setBounds( area.getWidth() - 120, 6, 60, 30 );
    
    m_presetEditorComponent.setBounds( 0, 50, area.getWidth(), area.getHeight() - 50 );
}

void MainComponent::paint(Graphics& g)
{
    g.fillAll(juce::Colour(0xff000000));
}

void MainComponent::updateAllKnobIconAnimation(const char * animation, size_t animationSize)
{
    const float animationStart = 0.0099f;
    const float animationEnd = 0.9703f;

    m_reverbMacroSlider.setIconAnimation(animation, animationSize, animationStart, animationEnd);
//    m_reverbMixSlider.setIconAnimation(animation, animationSize, animationStart, animationEnd);
    m_saturationMixSlider.setIconAnimation(animation, animationSize, animationStart, animationEnd);
    m_delayMixSlider.setIconAnimation(animation, animationSize, animationStart, animationEnd);
    m_widthSlider.setIconAnimation(animation, animationSize, animationStart, animationEnd);
    m_attackSlider.setIconAnimation(animation, animationSize, animationStart, animationEnd);
    m_releaseSlider.setIconAnimation(animation, animationSize, animationStart, animationEnd);
}

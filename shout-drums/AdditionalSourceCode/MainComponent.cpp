#include "MainComponent.h"
#include "ImageData.h"
#include "Font.h"

//#define SHOW_KEYBOARD
#define SHOW_PRESET_EDITOR

#if USE_RAW_FRONTEND
MainComponent::MainComponent(MainController* mc) :
#else
MainComponent::MainComponent(juce::FloatingTile* parent) :
FloatingTileContent(parent)
,
#endif
  m_app( mc )
, m_gainSlider( "", mc, "Simple Gain1" )
, m_reverbMixSlider( TRANS("reverb").toStdString(), mc, "Convolution Reverb" )
, m_saturationMixSlider( TRANS("drive").toStdString(), mc, "Shape FX1" )
, m_widthSlider( TRANS("width").toStdString(), mc, "Simple Gain1" )
, m_delayMixSlider( TRANS("delay").toStdString(), mc, "Delay1" )
, m_attackSlider( TRANS("attack").toStdString(), mc, "AHDSR Envelope1" )
, m_releaseSlider( TRANS("release").toStdString(), mc, "AHDSR Envelope1")
, m_attackReleaseContainer( "attack/release" )
, m_presetSwitcher( m_app.presets() )
, m_backgroundImage()
, m_presetEditorComponent( mc, m_app.sampleMaps() )
, m_editButton( TRANS("edit") )
, m_midiBarComponent( m_app.midiListener() )
, m_mainController( mc )
{
    setLookAndFeel(&m_shoutLookAndFeel);
    
    assert( mc );
    
    auto slaf = dynamic_cast<hise::ScriptingObjects::ScriptedLookAndFeel*>(mc->getCurrentScriptLookAndFeel());
    if (slaf)
    {
        slaf->f = shout::Font::labelFont(16.0);
    }
    
    addAndMakeVisible( &m_backgroundImage );
    
//    // Get the data model that handles MIDI messages from our main controller
//    auto& state = mc->getKeyboardState();
//    state.addListener( &m_app.midiListener() );

    // Add a stock JUCE MIDI keyboard and connect it to the main controller's MIDI state
#ifdef SHOW_KEYBOARD
    addAndMakeVisible(m_stockKeyboard = new juce::MidiKeyboardComponent(state, MidiKeyboardComponent::horizontalKeyboard));
    m_stockKeyboard->setKeyWidth(40);
#endif

    addAndMakeVisible( &m_presetSwitcher );
    addAndMakeVisible( &m_midiBarComponent );
    addAndMakeVisible( &m_infoView );
    
    addChildComponent( &m_presetEditorComponent );
    
#ifdef SHOW_PRESET_EDITOR
    addAndMakeVisible( &m_editButton );
#endif
    
    m_editButton.onClick = [this](){
        m_presetEditorComponent.setVisible( !m_presetEditorComponent.isVisible() );
    };
    
    m_app.presets().presetCategory.onChangedAndNow([this](const auto& category)
    {
        juce::Image bgImage;
        if ( category == "Drums" )
        {
            bgImage = juce::ImageFileFormat::loadFrom( GoodVibes_png, GoodVibes_pngSize );
            m_attackReleaseContainer.setVisible( false );
            getLookAndFeel().setColour( Slider::rotarySliderFillColourId, Colour( 0xff00cec9 ) );

        }
        else if ( category == "FX" )
        {
            bgImage = juce::ImageFileFormat::loadFrom( Eyes_png, Eyes_pngSize );
            m_attackReleaseContainer.setVisible( true );
            getLookAndFeel().setColour( Slider::rotarySliderFillColourId, Colour( 0xffe84393 ) );
        }
        else if ( category == "Vox" )
        {
            bgImage = juce::ImageFileFormat::loadFrom( GeoShapes_png, GeoShapes_pngSize );
            m_attackReleaseContainer.setVisible( true );
            getLookAndFeel().setColour( Slider::rotarySliderFillColourId, Colour( 0xff00cec9 ) );
        }
        
        m_backgroundImage.setImage( bgImage, RectanglePlacement::stretchToFit );
    });
            
    addAndMakeVisible( &m_gainSlider );
    m_gainSlider.rangeAndSkewPoint( -100.f, 0.f, -30.f );
    m_gainSlider.setInfoText(TRANS("output").toStdString(), TRANS("Click and drag up and down to change the main volume").toStdString());

    addAndMakeVisible( &m_reverbMixSlider );
    m_reverbMixSlider.rangeAndSkewPoint( -100.f, 0.f, -30.f );
    m_reverbMixSlider.setInfoText(TRANS("reverb").toStdString(), TRANS("Click and drag up and down to add more space").toStdString());
    
    addAndMakeVisible( &m_saturationMixSlider );
    m_saturationMixSlider.setInfoText(TRANS("drive").toStdString(), TRANS("Click and drag up and down to add more grit and dirt").toStdString());
    
    addAndMakeVisible( &m_delayMixSlider );
    m_delayMixSlider.rangeAndSkewPoint(0.0, 0.5, 0.2);
    m_delayMixSlider.setInfoText(TRANS("delay").toStdString(), TRANS("Click and drag up and down to add more echoes").toStdString());

    addAndMakeVisible( &m_widthSlider );
    m_widthSlider.rangeAndSkewPoint(0, 200, 100);
    m_widthSlider.setInfoText(TRANS("width").toStdString(), TRANS("Click and drag up and down to make your sound more narrow (mono) or more wide (stereo)").toStdString());
    
    addChildComponent( &m_attackReleaseContainer );
    m_attackReleaseContainer.addAndMakeVisible( &m_attackSlider );
    m_attackSlider.slider().setRange(juce::Range<double>(0, 20000), 1);
    m_attackSlider.setInfoText(TRANS("attack").toStdString(), TRANS("Click and drag up and down to control how your sounds fade in").toStdString());
    
    m_attackReleaseContainer.addAndMakeVisible( &m_releaseSlider );
    m_releaseSlider.slider().setRange(juce::Range<double>(80,20000), 1);
    m_releaseSlider.setInfoText(TRANS("release").toStdString(), TRANS("Click and drag up and down to control how your sounds fade out").toStdString());
}

MainComponent::~MainComponent()
{
    m_stockKeyboard = nullptr;    
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
    fb.items.add (juce::FlexItem (m_reverbMixSlider).withMinWidth (width).withMinHeight (height));
    fb.items.add (juce::FlexItem (m_widthSlider).withMinWidth (width).withMinHeight (height));

    fb.performLayout (area.withTrimmedBottom( 80 ).toFloat() );
    
    const int switcherHeight = 60;
    m_presetSwitcher.setBounds((total_width - 300)/2, total_height - switcherHeight, 300, switcherHeight );
    m_midiBarComponent.setBounds( 0, m_presetSwitcher.getY() - 4, total_width, 4 );
    m_infoView.setBounds(0, m_midiBarComponent.getY() - 40, total_width, 40);
    
    m_attackReleaseContainer.setBounds(0, total_height/2, total_width, total_height/2 - switcherHeight);
    m_attackSlider.setBounds( total_width/2 - width/2 - width/2, switcherHeight, width, height );
    m_releaseSlider.setBounds( total_width/2 - width/2 + width/2, switcherHeight, width, height );
    
    m_editButton.setBounds( area.getWidth() - 120, 6, 60, 30 );
    
    m_presetEditorComponent.setBounds( 0, 50, area.getWidth(), area.getHeight() - 50 );
}

void MainComponent::paint(Graphics& g)
{
    g.fillAll(juce::Colour(0xfff0f0f0));
}

//
//  ShoutLookAndFeel.cpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 8/15/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#include "ShoutLookAndFeel.h"

#include "FontMontserrat.h"
#include "Font.h"

ShoutLookAndFeel::ShoutLookAndFeel()
: LookAndFeel_V4()
{
    setColour( Slider::rotarySliderOutlineColourId, Colour( 0xffffffff ) );
    setColour( Slider::rotarySliderFillColourId, Colour( 0xff00cec9 ) );
    
    // custom fonts
    Typeface::Ptr tface = Typeface::createSystemTypefaceFor(MontserratRegular_ttf, MontserratRegular_ttfSize);
    setDefaultSansSerifTypeface (tface);
}

void ShoutLookAndFeel::drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
{
    auto outline = slider.findColour (Slider::rotarySliderOutlineColourId);
    auto fill    = slider.findColour (Slider::rotarySliderFillColourId);

    auto bounds = Rectangle<int> (x, y, width, height).toFloat().reduced (10);

    auto radius = jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = jmin (3.0f, radius * 0.5f);
    auto arcRadius = radius - lineW * 0.5f;

    Path backgroundArc;
    backgroundArc.addCentredArc (bounds.getCentreX(),
                                 bounds.getCentreY(),
                                 arcRadius,
                                 arcRadius,
                                 0.0f,
                                 rotaryStartAngle,
                                 rotaryEndAngle,
                                 true);

    g.setColour (outline);
    g.strokePath (backgroundArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));

    if (slider.isEnabled())
    {
        Path valueArc;
        valueArc.addCentredArc (bounds.getCentreX(),
                                bounds.getCentreY(),
                                arcRadius,
                                arcRadius,
                                0.0f,
                                rotaryStartAngle,
                                toAngle,
                                true);

        g.setColour (fill);
        g.strokePath (valueArc, PathStrokeType (lineW, PathStrokeType::curved, PathStrokeType::rounded));
    }
}

Font ShoutLookAndFeel::getAlertWindowMessageFont ()
{
    return shout::Font::labelFont(16.0);
}

Font ShoutLookAndFeel::getAlertWindowTitleFont()
{
    return shout::Font::mainFont(18.0);
}

Font ShoutLookAndFeel::getTextButtonFont (TextButton &, int /*buttonHeight*/)
{
    return shout::Font::mainFont(16.0);
}

Font ShoutLookAndFeel::getComboBoxFont(ComboBox&)
{
    return shout::Font::labelFont(14.0);
}

Font ShoutLookAndFeel::getPopupMenuFont()
{
    return shout::Font::mainFont(14.0);
};

void ShoutLookAndFeel::drawPopupMenuBackground(Graphics& g, int width, int height)
{
    g.setColour((findColour(PopupMenu::backgroundColourId)));
    g.fillRect(0.0f, 0.0f, (float)width, (float)height);
}

void ShoutLookAndFeel::drawButtonText (Graphics &g, TextButton &button, bool /*isMouseOverButton*/, bool /*isButtonDown*/)
{
    Font font (getTextButtonFont (button, button.getHeight()));
    g.setFont (font);
    g.setColour (Colours::white.withMultipliedAlpha (button.isEnabled() ? 1.0f : 0.5f));

    const int yIndent = jmin (4, button.proportionOfHeight (0.3f));
    const int cornerSize = jmin (button.getHeight(), button.getWidth()) / 2;

    const int fontHeight = roundToInt (font.getHeight() * 0.6f);
    const int leftIndent  = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnLeft() ? 4 : 2));
    const int rightIndent = jmin (fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));

    g.drawFittedText (button.getButtonText().toUpperCase(),
                      leftIndent,
                      yIndent,
                      button.getWidth() - leftIndent - rightIndent,
                      button.getHeight() - yIndent * 2,
                      Justification::centred, 2);
}
 

void ShoutLookAndFeel::drawButtonBackground (Graphics& g, Button& button, const Colour& /*backgroundColour*/,
                                       bool isMouseOverButton, bool isButtonDown)
{
    Colour baseColour (Colours::white.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                                       .withMultipliedAlpha (button.isEnabled() ? 0.9f : 0.5f));

    if (isButtonDown || isMouseOverButton)
        baseColour = baseColour.contrasting (isButtonDown ? 0.2f : 0.1f);

    g.setColour(baseColour);

    const float width  = (float)button.getWidth();
    const float height = (float)button.getHeight();

    g.drawRoundedRectangle(2.f, 2.f, width - 4, height - 4, (height-4)/2, 2.f);

}

Font ShoutLookAndFeel::getAlertWindowFont ()
{
    return shout::Font::labelFont(16.0);
};

void ShoutLookAndFeel::setColourIdsForAlertWindow(AlertWindow &window)
{
//    window.setColour(AlertWindow::ColourIds::backgroundColourId, dark);
//    window.setColour(AlertWindow::ColourIds::textColourId, bright);
//    window.setColour(AlertWindow::ColourIds::outlineColourId, bright);
}

void ShoutLookAndFeel::drawProgressBar (Graphics &g, ProgressBar &/*progressBar*/, int width, int height, double progress, const String &textToShow)
{
    const Colour background = Colours::lightgrey;
    const Colour foreground = Colours::darkgrey;

    g.fillAll (foreground);

    if (progress >= 0.0f && progress < 1.0f)
    {
        ColourGradient grad(background, 0.0f, 0.0f, background.withAlpha(0.6f), 0.0f, (float)height, false);

        g.setColour(background);

        g.drawRect(0, 0, width, height);

        int x = 2;
        int y = 2;
        int w = (int)((width - 4) * progress);
        int h = height - 4;

        g.setGradientFill(grad);

        g.fillRect(x,y,w,h);
    }
    else
    {
        
        
    }

    if (textToShow.isNotEmpty())
    {
        g.setColour (Colour::contrasting (background, foreground));
        g.setFont (GLOBAL_FONT());

        g.drawText (textToShow, 0, 0, width, height, Justification::centred, false);
    }

}

void ShoutLookAndFeel::drawAlertBox(Graphics &g, AlertWindow &alert, const Rectangle< int > &textArea, juce::TextLayout &textLayout)
{
    ColourGradient grad(juce::Colours::grey.withMultipliedBrightness(1.4f), 0.0f, 0.0f,
        juce::Colours::darkgrey, 0.0f, (float)alert.getHeight(), false);

    g.setGradientFill(grad);
    g.fillAll();

    g.setColour(Colours::white.withAlpha(0.1f));

    g.fillRect(0, 0, alert.getWidth(), 37);

    g.setColour(Colours::lightgrey);

    for (int i = 0; i < textLayout.getNumLines(); i++)
    {
        textLayout.getLine(i).runs.getUnchecked(0)->colour = Colours::lightgrey;
    }

    textLayout.draw(g, Rectangle<int>(textArea.getX(),
        textArea.getY(),
        textArea.getWidth(),
        textArea.getHeight()).toFloat());

    g.setColour(Colours::lightgrey);
    g.drawRect(0, 0, alert.getWidth(), alert.getHeight());
}


#if HISE_USE_CUSTOM_ALERTWINDOW_LOOKANDFEEL
LookAndFeel* HiseColourScheme::createAlertWindowLookAndFeel(void* mainController)
{
    return new ShoutLookAndFeel();
}
#endif

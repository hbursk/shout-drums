//
//  ShoutLookAndFeel.h
//  DrumTest - App
//
//  Created by Hayden Bursk on 8/15/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#pragma once

#include "JuceHeader.h"

class ShoutLookAndFeel : public LookAndFeel_V4
{
public:
    ShoutLookAndFeel();
    ~ShoutLookAndFeel() = default;
    
    void drawRotarySlider (Graphics&, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
                           Slider& s) override;
    
    void drawScrollbar (Graphics&, ScrollBar&, int x, int y, int width, int height, bool isScrollbarVertical,
                        int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown) override;

    
    Font getAlertWindowMessageFont () override;
    
    virtual Font     getAlertWindowTitleFont() override;
    
    Font getTextButtonFont (TextButton &, int /*buttonHeight*/) override;

    Font getComboBoxFont(ComboBox&) override;

    Font getPopupMenuFont() override;

    void drawPopupMenuBackground(Graphics& g, int width, int height) override;
 
    void drawButtonText (Graphics &g, TextButton &button, bool /*isMouseOverButton*/, bool /*isButtonDown*/) override;

    void drawButtonBackground (Graphics& g, Button& button, const Colour& /*backgroundColour*/,
                               bool isMouseOverButton, bool isButtonDown) override;
 
    Font getAlertWindowFont () override;

    void setColourIdsForAlertWindow(AlertWindow &window);

    void drawProgressBar (Graphics &g, ProgressBar &/*progressBar*/, int width, int height, double progress, const String &textToShow) override;

    void drawAlertBox (Graphics &g, AlertWindow &alert, const Rectangle< int > &textArea, juce::TextLayout &textLayout) override;


};


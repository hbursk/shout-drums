//
//  Knob.cpp
//  DrumTest - App
//
//  Created by Hayden Bursk on 8/18/20.
//  Copyright © 2020 Shout Audio. All rights reserved.
//

#include "Font.h"

#include "FontMontserrat.h"
#include "FontOpenSans-Light.h"
#include "FontNotoSansJP-Regular.h"


const juce::Font shout::Font::mainFont( float pointSize )
{
    static juce::Font mainFont(
        juce::Font( Typeface::createSystemTypefaceFor( MontserratRegular_ttf, MontserratRegular_ttfSize ) ) );
    return mainFont.withPointHeight( pointSize );
}

const juce::Font shout::Font::labelFont( float pointSize )
{
    static juce::Font labelFont(
        juce::Font( Typeface::createSystemTypefaceFor( OpenSansLight_ttf, OpenSansLight_ttfSize ) ) );
    return labelFont.withPointHeight( pointSize );
}

const juce::Font shout::Font::symbolJPFont( float pointSize )
{
    static juce::Font symbolJPFont(
        juce::Font( Typeface::createSystemTypefaceFor( NotoSansJPRegular_otf, NotoSansJPRegular_otfSize ) ) );
    return symbolJPFont.withPointHeight( pointSize );
}


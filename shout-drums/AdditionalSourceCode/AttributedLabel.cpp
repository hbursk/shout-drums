#include "AttributedLabel.h"

#include <cmath>

void AttributedLabel::setText( juce::AttributedString text )
{
    m_text = std::move( text );
    repaint();
}

void AttributedLabel::paint( juce::Graphics& g )
{
    auto bounds = getLocalBounds().toFloat();
#if JUCE_WINDOWS
    // work around for text getting clipped on windows. reduce width
    constexpr auto workaround_width_ratio = 0.90f;

    const auto oldWidth = bounds.getWidth();
    auto       newWidth = bounds.proportionOfWidth( workaround_width_ratio );
    bounds.setWidth( newWidth );
    if ( m_text.getJustification().testFlags( juce::Justification::centred ) )
    {
        bounds.setX( std::floor( ( oldWidth - newWidth ) / 2.f ) );
    }
#endif

    m_text.draw( g, bounds );
}

void AttributedLabel::resized()
{
    repaint();
}

void AttributedLabel::enablementChanged()
{
    setAlpha( isEnabled() ? 1.0 : 0.8 );
}

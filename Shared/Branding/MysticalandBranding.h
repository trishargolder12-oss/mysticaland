#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../Theme/MysticalandColors.h"

namespace Mysticaland::Branding
{
    // Draws the celestial arc with star & stylized M emblem
    void drawEmblem(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour colour = Theme::ChampagneGold);

    // Draws the spaced serif wordmark "M Y S T I C A L A N D"
    void drawWordmark(juce::Graphics& g, juce::Rectangle<float> bounds, float fontSize = 16.0f, juce::Colour colour = Theme::PrimaryText);

    // Draws subtle marble / dark slate background veining texture
    void drawSubtleMarbleTexture(juce::Graphics& g, juce::Rectangle<float> bounds);
}

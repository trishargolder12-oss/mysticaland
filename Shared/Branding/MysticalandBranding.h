#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../Theme/MysticalandColors.h"

namespace Mysticaland::Branding
{
    // High-resolution image assets manager
    class AssetManager
    {
    public:
        static AssetManager& getInstance();

        juce::Image getBackgroundImage();
        juce::Image getEmblemImage();
        juce::Image getEmblemFullImage();

    private:
        AssetManager();
        juce::Image backgroundImage;
        juce::Image emblemImage;
        juce::Image emblemFullImage;
    };

    // Drawing functions
    void drawEmblem(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour colour = Theme::ChampagneGold);
    void drawWordmark(juce::Graphics& g, juce::Rectangle<float> bounds, float fontSize = 16.0f, juce::Colour colour = Theme::PrimaryText);
    void drawSubtleMarbleTexture(juce::Graphics& g, juce::Rectangle<float> bounds);
}

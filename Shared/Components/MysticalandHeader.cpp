#include "MysticalandHeader.h"

namespace Mysticaland::UI
{
    MysticalandHeader::MysticalandHeader() {}

    void MysticalandHeader::paint(juce::Graphics& g)
    {
        auto bounds = getLocalBounds().toFloat();

        // Background
        g.setColour(Theme::MainBackground);
        g.fillRect(bounds);

        // Minimal bottom divider line
        g.setColour(Theme::BorderColor);
        g.drawHorizontalLine(getHeight() - 1, bounds.getX(), bounds.getRight());

        // Header Branding Area (Left side)
        float leftMargin = 22.0f;
        auto emblemBounds = juce::Rectangle<float>(leftMargin, (getHeight() - 32.0f) * 0.5f, 32.0f, 32.0f);
        Branding::drawEmblem(g, emblemBounds, Theme::ChampagneGold);

        // Subtle vertical separator bar between emblem and wordmark
        float sepX = emblemBounds.getRight() + 14.0f;
        float sepY = (getHeight() - 16.0f) * 0.5f;
        g.setColour(Theme::BorderColor);
        g.drawVerticalLine((int)sepX, sepY, sepY + 16.0f);

        // Wordmark
        auto wordmarkBounds = juce::Rectangle<float>(sepX + 16.0f, 0.0f, 210.0f, (float)getHeight());
        Branding::drawWordmark(g, wordmarkBounds, 14.0f, Theme::PrimaryText);

        // Version indicator (Right side)
        auto versionBounds = juce::Rectangle<float>(bounds.getRight() - 100.0f, 0.0f, 80.0f, (float)getHeight());
        g.setColour(Theme::MutedText);
        g.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifTypeName(), 11.0f, juce::Font::plain)));
        g.drawText("v0.1.0", versionBounds, juce::Justification::centredRight, true);
    }

    void MysticalandHeader::resized() {}
}

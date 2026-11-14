#include "EmptyStateComponent.h"

namespace Mysticaland::UI
{
    EmptyStateComponent::EmptyStateComponent() {}

    void EmptyStateComponent::setCategoryName(const juce::String& name)
    {
        currentCategoryName = name;
        repaint();
    }

    void EmptyStateComponent::paint(juce::Graphics& g)
    {
        auto bounds = getLocalBounds().toFloat();
        float cx = bounds.getCentreX();
        float cy = bounds.getCentreY() - 20.0f;

        // 1. Central Celestial Emblem with Arches and Star
        float emblemSize = 110.0f;
        auto emblemBounds = juce::Rectangle<float>(cx - emblemSize * 0.5f, cy - emblemSize * 0.7f, emblemSize, emblemSize);
        Branding::drawEmblem(g, emblemBounds, Theme::ChampagneGold);

        // 2. Wordmark with Flanking Hairline Rules
        float wordmarkY = cy + 42.0f;
        float wordmarkW = 280.0f;
        float wordmarkH = 28.0f;
        auto wordmarkBounds = juce::Rectangle<float>(cx - wordmarkW * 0.5f, wordmarkY, wordmarkW, wordmarkH);
        Branding::drawWordmark(g, wordmarkBounds, 18.0f, Theme::PrimaryText);

        // Flanking horizontal lines
        g.setColour(Theme::BorderColor);
        float lineLength = 70.0f;
        g.drawHorizontalLine((int)(wordmarkY + wordmarkH * 0.5f), wordmarkBounds.getX() - lineLength - 15.0f, wordmarkBounds.getX() - 15.0f);
        g.drawHorizontalLine((int)(wordmarkY + wordmarkH * 0.5f), wordmarkBounds.getRight() + 15.0f, wordmarkBounds.getRight() + lineLength + 15.0f);

        // 3. Understated Instructional Copy (Two Lines)
        float textY = wordmarkY + 50.0f;
        g.setColour(Theme::SecondaryText);
        g.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifTypeName(), 13.0f, juce::Font::plain)));

        juce::String line1 = "SELECT AN " + currentCategoryName + " OR INSTRUMENT";
        juce::String line2 = "FROM THE LEFT PANEL";

        g.drawText(line1, juce::Rectangle<float>(bounds.getX(), textY, bounds.getWidth(), 20.0f), juce::Justification::centred, false);
        
        g.setColour(Theme::MutedText);
        g.drawText(line2, juce::Rectangle<float>(bounds.getX(), textY + 22.0f, bounds.getWidth(), 20.0f), juce::Justification::centred, false);
    }

    void EmptyStateComponent::resized() {}
}

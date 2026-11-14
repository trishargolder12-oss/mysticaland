#include "NavigationItem.h"

namespace Mysticaland::UI
{
    NavigationItem::NavigationItem(const juce::String& name, IconType icon)
        : juce::Button(name), iconType(icon)
    {
        setClickingTogglesState(false);
    }

    void NavigationItem::paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool /*shouldDrawButtonAsDown*/)
    {
        auto bounds = getLocalBounds().toFloat().reduced(2.0f);
        float corner = 8.0f;

        if (getToggleState())
        {
            // Selected state: subtle warm glow, selected background, gold border
            g.setColour(Theme::SelectedBackground);
            g.fillRoundedRectangle(bounds, corner);

            g.setColour(Theme::ChampagneGold.withAlpha(0.6f));
            g.drawRoundedRectangle(bounds, corner, 1.0f);
        }
        else if (shouldDrawButtonAsHighlighted)
        {
            g.setColour(Theme::HoverBackground);
            g.fillRoundedRectangle(bounds, corner);

            g.setColour(Theme::BorderColor);
            g.drawRoundedRectangle(bounds, corner, 0.8f);
        }

        // Draw Icon
        auto iconBounds = bounds.removeFromLeft(42.0f).reduced(10.0f);
        if (iconType == IconType::Waveform)
            drawWaveformIcon(g, iconBounds);
        else
            drawKeyboardIcon(g, iconBounds);

        // Draw Label
        auto textColour = getToggleState() ? Theme::PrimaryText : (shouldDrawButtonAsHighlighted ? Theme::PrimaryText : Theme::SecondaryText);
        g.setColour(textColour);
        g.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifFontName(), 15.0f, juce::Font::plain)));
        
        auto textBounds = bounds.removeFromLeft(bounds.getWidth() - 30.0f);
        g.drawText(getButtonText(), textBounds, juce::Justification::centredLeft, true);

        // Draw Chevron '>'
        auto chevronBounds = bounds;
        g.setColour(getToggleState() ? Theme::ChampagneGold : Theme::MutedText);
        g.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifFontName(), 14.0f, juce::Font::plain)));
        g.drawText(">", chevronBounds, juce::Justification::centred, true);
    }

    void NavigationItem::drawWaveformIcon(juce::Graphics& g, juce::Rectangle<float> bounds)
    {
        auto iconColour = getToggleState() ? Theme::ChampagneGold : Theme::SecondaryText;
        g.setColour(iconColour);

        float cx = bounds.getCentreX();
        float cy = bounds.getCentreY();
        float h = bounds.getHeight();

        // 5 vertical bars representing an audio waveform
        float barWidth = 2.0f;
        float spacing = 4.0f;
        float heights[] = { 0.35f, 0.75f, 1.0f, 0.65f, 0.30f };

        for (int i = 0; i < 5; ++i)
        {
            float x = (cx - 2 * spacing) + i * spacing;
            float barH = h * heights[i];
            g.fillRoundedRectangle(x - barWidth * 0.5f, cy - barH * 0.5f, barWidth, barH, 1.0f);
        }
    }

    void NavigationItem::drawKeyboardIcon(juce::Graphics& g, juce::Rectangle<float> bounds)
    {
        auto iconColour = getToggleState() ? Theme::ChampagneGold : Theme::SecondaryText;
        g.setColour(iconColour);

        // Minimal piano keys outline
        auto kb = bounds.reduced(1.0f, 3.0f);
        g.drawRoundedRectangle(kb, 2.0f, 1.0f);

        // White keys dividers
        float kw = kb.getWidth() / 4.0f;
        for (int i = 1; i < 4; ++i)
            g.drawVerticalLine((int)(kb.getX() + i * kw), kb.getY(), kb.getBottom());

        // Black keys
        float bkw = kw * 0.55f;
        float bkh = kb.getHeight() * 0.55f;
        g.fillRect(kb.getX() + kw - bkw * 0.5f, kb.getY(), bkw, bkh);
        g.fillRect(kb.getX() + kw * 2.0f - bkw * 0.5f, kb.getY(), bkw, bkh);
    }
}

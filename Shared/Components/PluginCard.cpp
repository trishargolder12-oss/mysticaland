#include "PluginCard.h"

namespace Mysticaland::UI
{
    PluginCard::PluginCard(const Plugin::PluginDescriptor& desc)
        : descriptor(desc)
    {
        addAndMakeVisible(actionBtn);

        if (descriptor.isInstalled)
        {
            actionBtn.setButtonText("OPEN MODULE");
            actionBtn.setColour(juce::TextButton::buttonColourId, Theme::SelectedBackground);
            actionBtn.setColour(juce::TextButton::textColourOnId, Theme::PrimaryText);
        }
        else if (descriptor.isComingSoon)
        {
            actionBtn.setButtonText("COMING SOON");
            actionBtn.setEnabled(false);
            actionBtn.setColour(juce::TextButton::buttonColourId, Theme::MainBackground);
            actionBtn.setColour(juce::TextButton::textColourOffId, Theme::MutedText);
        }
        else
        {
            actionBtn.setButtonText("INSTALL");
            actionBtn.setColour(juce::TextButton::buttonColourId, Theme::HoverBackground);
        }

        actionBtn.onClick = [this]()
        {
            if (onModuleAction)
                onModuleAction(descriptor);
        };
    }

    void PluginCard::mouseEnter(const juce::MouseEvent&)
    {
        isHovered = true;
        repaint();
    }

    void PluginCard::mouseExit(const juce::MouseEvent&)
    {
        isHovered = false;
        repaint();
    }

    void PluginCard::drawModuleVisualizer(juce::Graphics& g, juce::Rectangle<float> bounds)
    {
        g.setColour(Theme::MainBackground);
        g.fillRoundedRectangle(bounds, 6.0f);

        g.setColour(Theme::BorderColor.withAlpha(0.5f));
        g.drawRoundedRectangle(bounds, 6.0f, 0.8f);

        auto cx = bounds.getCentreX();
        auto cy = bounds.getCentreY();

        if (descriptor.id == "nebula_eq")
        {
            // Mini EQ Curve
            juce::Path eqCurve;
            float left = bounds.getX() + 10.0f;
            float right = bounds.getRight() - 10.0f;
            float midY = cy + 4.0f;
            eqCurve.startNewSubPath(left, midY);
            eqCurve.quadraticTo(left + 25.0f, midY - 14.0f, cx - 15.0f, midY);
            eqCurve.quadraticTo(cx + 10.0f, midY + 12.0f, cx + 30.0f, midY - 10.0f);
            eqCurve.lineTo(right, midY);

            g.setColour(Theme::ChampagneGold);
            g.strokePath(eqCurve, juce::PathStrokeType(1.6f));

            // Frequency nodes
            g.setColour(Theme::PrimaryText);
            g.fillEllipse(left + 22.0f, midY - 15.0f, 5.0f, 5.0f);
            g.fillEllipse(cx + 28.0f, midY - 11.0f, 5.0f, 5.0f);
        }
        else if (descriptor.id == "pressor")
        {
            // Mini VU Meter & Compression threshold
            auto meterBounds = bounds.reduced(14.0f, 18.0f);
            g.setColour(Theme::SidebarBackground);
            g.fillRoundedRectangle(meterBounds, 4.0f);

            // Needle
            g.setColour(Theme::ChampagneGold);
            g.drawLine(cx - 15.0f, cy + 10.0f, cx + 10.0f, cy - 8.0f, 1.4f);

            // Ticks
            g.setColour(Theme::MutedText);
            for (int i = 0; i < 5; ++i)
                g.drawVerticalLine((int)(cx - 16.0f + i * 8.0f), cy - 12.0f, cy - 8.0f);
        }
        else if (descriptor.id == "arcane_synth")
        {
            // Wavetable Harmonics
            juce::Path wave;
            float left = bounds.getX() + 12.0f;
            float right = bounds.getRight() - 12.0f;
            wave.startNewSubPath(left, cy);

            for (float x = left; x <= right; x += 2.0f)
            {
                float progress = (x - left) / (right - left);
                float y = cy + std::sin(progress * juce::MathConstants<float>::twoPi * 2.5f) * 14.0f;
                wave.lineTo(x, y);
            }
            g.setColour(Theme::ChampagneGold);
            g.strokePath(wave, juce::PathStrokeType(1.5f));
        }
        else
        {
            // Generic ethereal constellation
            g.setColour(Theme::ChampagneGold.withAlpha(0.4f));
            g.drawEllipse(cx - 12.0f, cy - 12.0f, 24.0f, 24.0f, 1.0f);
            g.fillEllipse(cx - 2.0f, cy - 2.0f, 4.0f, 4.0f);
        }
    }

    void PluginCard::paint(juce::Graphics& g)
    {
        auto bounds = getLocalBounds().toFloat().reduced(4.0f);
        float corner = 8.0f;

        // Card Background
        g.setColour(isHovered ? Theme::HoverBackground : Theme::SecondaryBackground);
        g.fillRoundedRectangle(bounds, corner);

        // Border
        g.setColour(isHovered ? Theme::ChampagneGold.withAlpha(0.6f) : Theme::BorderColor);
        g.drawRoundedRectangle(bounds, corner, 1.0f);

        // Preview Window
        auto previewArea = bounds.removeFromTop(100.0f).reduced(10.0f);
        drawModuleVisualizer(g, previewArea);

        // Module Title
        g.setColour(Theme::PrimaryText);
        g.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSerifFontName(), 15.0f, juce::Font::bold)));
        g.drawText(descriptor.name, bounds.removeFromTop(22.0f).reduced(12.0f, 0.0f), juce::Justification::centredLeft, true);

        // Subtitle / Type
        g.setColour(Theme::ChampagneGold);
        g.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifFontName(), 11.0f, juce::Font::plain)));
        g.drawText(descriptor.subtitle, bounds.removeFromTop(18.0f).reduced(12.0f, 0.0f), juce::Justification::centredLeft, true);

        // Description
        g.setColour(Theme::SecondaryText);
        g.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifFontName(), 11.0f, juce::Font::plain)));
        g.drawFittedText(descriptor.description, bounds.removeFromTop(38.0f).reduced(12.0f, 0.0f).toNearestInt(), juce::Justification::topLeft, 2);

        // Status Tag
        auto statusArea = bounds.removeFromTop(20.0f).reduced(12.0f, 0.0f);
        g.setColour(descriptor.isInstalled ? Theme::ChampagneGold : Theme::MutedText);
        g.drawText(descriptor.isInstalled ? "INSTALLED - READY" : (descriptor.isComingSoon ? "UPCOMING SUITE" : "AVAILABLE"), 
                   statusArea, juce::Justification::centredLeft, true);
    }

    void PluginCard::resized()
    {
        auto bounds = getLocalBounds().reduced(14);
        actionBtn.setBounds(bounds.removeFromBottom(30));
    }
}

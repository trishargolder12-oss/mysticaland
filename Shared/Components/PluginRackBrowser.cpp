#include "PluginRackBrowser.h"

namespace Mysticaland::UI
{
    PluginRackBrowser::PluginRackBrowser()
    {
        populateDescriptors();
        refreshCards();
    }

    void PluginRackBrowser::populateDescriptors()
    {
        allDescriptors = {
            // EFFECTS
            {
                "nebula_eq",
                "Nebula EQ",
                "Parametric Studio Equalizer",
                "3-band precision musical EQ with pristine analog biquad curves.",
                "1.0.0",
                Plugin::PluginCategory::Effect,
                true,   // Installed
                false
            },
            {
                "pressor",
                "Pressor",
                "Analog Dynamics Compressor",
                "Warm VCA analog-modeled compressor with smooth gain reduction.",
                "1.0.0",
                Plugin::PluginCategory::Effect,
                true,   // Installed
                false
            },
            {
                "void_tape",
                "Void Tape",
                "Saturator & Color",
                "Tape reel saturation and vintage warmth harmonic exciter.",
                "0.9.0",
                Plugin::PluginCategory::Effect,
                false,
                true   // Coming Soon
            },
            {
                "lumen_reverb",
                "Lumen Reverb",
                "Atmospheric Reverb",
                "Ethereal algorithmic space simulation and celestial decay engine.",
                "0.9.0",
                Plugin::PluginCategory::Effect,
                false,
                true
            },

            // INSTRUMENTS
            {
                "arcane_synth",
                "ArcaneSynth",
                "Wavetable Synthesizer",
                "Modern wavetable powerhouse with celestial modulation and dual oscillators.",
                "1.0.0",
                Plugin::PluginCategory::Instrument,
                false,
                true
            },
            {
                "nocturne_keys",
                "Nocturne Keys",
                "Cinematic Piano",
                "Intimate felt piano sampled under midnight silence with acoustic depth.",
                "0.9.0",
                Plugin::PluginCategory::Instrument,
                false,
                true
            },
            {
                "aether_pads",
                "Aether Pads",
                "Atmospheric Synth",
                "Lush shifting analog pads and textural cinematic drones.",
                "0.9.0",
                Plugin::PluginCategory::Instrument,
                false,
                true
            },
            {
                "ritual_bass",
                "Ritual Bass",
                "Modern Bass Engine",
                "Sub-heavy 808s and aggressive distorted analog basslines.",
                "0.9.0",
                Plugin::PluginCategory::Instrument,
                false,
                true
            }
        };
    }

    void PluginRackBrowser::setCategoryFilter(Plugin::PluginCategory cat)
    {
        if (activeCategory != cat)
        {
            activeCategory = cat;
            refreshCards();
            resized();
            repaint();
        }
    }

    void PluginRackBrowser::refreshCards()
    {
        visibleCards.clear();

        for (const auto& desc : allDescriptors)
        {
            if (desc.category == activeCategory)
            {
                auto* card = visibleCards.add(new PluginCard(desc));
                card->onModuleAction = [this](const Plugin::PluginDescriptor& d)
                {
                    if (onModuleSelected)
                        onModuleSelected(d);
                };
                addAndMakeVisible(card);
            }
        }
    }

    void PluginRackBrowser::paint(juce::Graphics& g)
    {
        auto bounds = getLocalBounds().toFloat();

        // Section Title
        g.setColour(Theme::PrimaryText);
        g.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSerifFontName(), 20.0f, juce::Font::bold)));

        juce::String title = (activeCategory == Plugin::PluginCategory::Effect) ? "EFFECTS SUITE" : "INSTRUMENTS RACK";
        g.drawText(title, juce::Rectangle<float>(28.0f, 18.0f, 300.0f, 26.0f), juce::Justification::centredLeft, true);

        // Subtitle
        g.setColour(Theme::SecondaryText);
        g.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifFontName(), 12.0f, juce::Font::plain)));
        juce::String sub = (activeCategory == Plugin::PluginCategory::Effect) 
            ? "Precision audio processors to shape, dynamics-control and color your master tracks." 
            : "Virtual instruments for modern composition, synthesis and cinematic performance.";
        g.drawText(sub, juce::Rectangle<float>(28.0f, 44.0f, 600.0f, 18.0f), juce::Justification::centredLeft, true);

        // Divider
        g.setColour(Theme::BorderColor);
        g.drawHorizontalLine(68, 28.0f, bounds.getRight() - 28.0f);
    }

    void PluginRackBrowser::resized()
    {
        int startX = 28;
        int startY = 82;
        int cardW = 205;
        int cardH = 265;
        int gapX = 16;
        int gapY = 16;

        int availableWidth = getWidth() - startX * 2;
        int columns = juce::jmax(1, (availableWidth + gapX) / (cardW + gapX));

        for (int i = 0; i < visibleCards.size(); ++i)
        {
            int col = i % columns;
            int row = i / columns;
            int x = startX + col * (cardW + gapX);
            int y = startY + row * (cardH + gapY);

            visibleCards[i]->setBounds(x, y, cardW, cardH);
        }
    }
}

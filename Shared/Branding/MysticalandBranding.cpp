#include "MysticalandBranding.h"

namespace Mysticaland::Branding
{
    void drawEmblem(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour colour)
    {
        g.setColour(colour);

        auto cx = bounds.getCentreX();
        auto cy = bounds.getCentreY();
        auto s = juce::jmin(bounds.getWidth(), bounds.getHeight());

        // 1. Celestial Arches
        juce::Path outerArc;
        outerArc.addCentredArc(cx, cy + s * 0.15f, s * 0.42f, s * 0.38f, 0.0f, -juce::MathConstants<float>::pi * 0.55f, juce::MathConstants<float>::pi * 0.55f, true);
        g.strokePath(outerArc, juce::PathStrokeType(1.0f));

        juce::Path innerArc;
        innerArc.addCentredArc(cx, cy + s * 0.18f, s * 0.35f, s * 0.32f, 0.0f, -juce::MathConstants<float>::pi * 0.45f, juce::MathConstants<float>::pi * 0.45f, true);
        g.strokePath(innerArc, juce::PathStrokeType(0.6f));

        // 2. Four-Point Star at the apex
        float starY = cy - s * 0.24f;
        float starR = s * 0.09f;
        juce::Path star;
        star.startNewSubPath(cx, starY - starR);
        star.quadraticTo(cx + starR * 0.15f, starY - starR * 0.15f, cx + starR, starY);
        star.quadraticTo(cx + starR * 0.15f, starY + starR * 0.15f, cx, starY + starR);
        star.quadraticTo(cx - starR * 0.15f, starY + starR * 0.15f, cx - starR, starY);
        star.quadraticTo(cx - starR * 0.15f, starY - starR * 0.15f, cx, starY - starR);
        star.closeSubPath();
        g.fillPath(star);

        // 3. Stylized Serif 'M'
        juce::Path mPath;
        float mw = s * 0.38f;
        float mh = s * 0.36f;
        float mx = cx - mw * 0.5f;
        float my = cy - s * 0.05f;

        // Left stroke
        mPath.startNewSubPath(mx, my + mh);
        mPath.lineTo(mx + mw * 0.12f, my);
        // Center dip
        mPath.lineTo(cx, my + mh * 0.72f);
        // Right peak
        mPath.lineTo(mx + mw * 0.88f, my);
        // Right stroke
        mPath.lineTo(mx + mw, my + mh);

        g.strokePath(mPath, juce::PathStrokeType(1.6f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    }

    void drawWordmark(juce::Graphics& g, juce::Rectangle<float> bounds, float fontSize, juce::Colour colour)
    {
        g.setColour(colour);
        // Serif font for wordmark as mandated by design philosophy
        g.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSerifFontName(), fontSize, juce::Font::plain)));
        
        // Spaced wordmark: "M Y S T I C A L A N D"
        g.drawText("M Y S T I C A L A N D", bounds, juce::Justification::centred, true);
    }

    void drawSubtleMarbleTexture(juce::Graphics& g, juce::Rectangle<float> bounds)
    {
        // Procedural ultra-subtle golden veining lines mimicking marble
        g.saveState();
        g.reduceClipRegion(bounds.toNearestInt());

        juce::Random rng(1337); // Deterministic seed for reproducible elegance
        g.setColour(Theme::ChampagneGold.withAlpha(0.025f));

        for (int i = 0; i < 7; ++i)
        {
            juce::Path vein;
            float startX = bounds.getX() + rng.nextFloat() * bounds.getWidth();
            float startY = bounds.getY() + rng.nextFloat() * bounds.getHeight();
            vein.startNewSubPath(startX, startY);

            for (int seg = 0; seg < 4; ++seg)
            {
                float nx = startX + (rng.nextFloat() - 0.4f) * 180.0f;
                float ny = startY + rng.nextFloat() * 120.0f;
                vein.quadraticTo((startX + nx) * 0.5f + (rng.nextFloat() - 0.5f) * 40.0f,
                                 (startY + ny) * 0.5f, nx, ny);
                startX = nx;
                startY = ny;
            }

            g.strokePath(vein, juce::PathStrokeType(0.8f));
        }

        g.restoreState();
    }
}

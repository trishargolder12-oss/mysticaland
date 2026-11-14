#include "MysticalandBranding.h"

namespace Mysticaland::Branding
{
    AssetManager& AssetManager::getInstance()
    {
        static AssetManager instance;
        return instance;
    }

    AssetManager::AssetManager()
    {
        // Try multiple standard asset locations (relative to binary, workspace, or common install)
        auto exeDir = juce::File::getSpecialLocation(juce::File::currentExecutableFile).getParentDirectory();
        
        juce::Array<juce::File> candidateDirs = {
            exeDir.getChildFile("Assets"),
            exeDir.getParentDirectory().getChildFile("Assets"),
            juce::File("c:/Users/msix/Desktop/Bizzy Bizzy/Mysticaland/Shared/Assets"),
            juce::File("C:/Program Files/Common Files/VST3/Mysticaland/Assets"),
            juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory).getChildFile("Mysticaland/Assets")
        };

        for (const auto& dir : candidateDirs)
        {
            if (dir.exists())
            {
                auto bgFile = dir.getChildFile("background.jpg");
                auto embFile = dir.getChildFile("emblem.jpg");
                auto embFullFile = dir.getChildFile("emblem_full.jpg");

                if (bgFile.exists() && !backgroundImage.isValid())
                    backgroundImage = juce::ImageFileFormat::loadFrom(bgFile);

                if (embFile.exists() && !emblemImage.isValid())
                    emblemImage = juce::ImageFileFormat::loadFrom(embFile);

                if (embFullFile.exists() && !emblemFullImage.isValid())
                    emblemFullImage = juce::ImageFileFormat::loadFrom(embFullFile);
            }
        }
    }

    juce::Image AssetManager::getBackgroundImage() { return backgroundImage; }
    juce::Image AssetManager::getEmblemImage() { return emblemImage; }
    juce::Image AssetManager::getEmblemFullImage() { return emblemFullImage; }

    void drawEmblem(juce::Graphics& g, juce::Rectangle<float> bounds, juce::Colour colour)
    {
        auto embImg = AssetManager::getInstance().getEmblemImage();
        if (embImg.isValid())
        {
            g.drawImage(embImg, bounds, juce::RectanglePlacement::centred);
            return;
        }

        // Vector fallback if image not loaded
        g.setColour(colour);
        auto cx = bounds.getCentreX();
        auto cy = bounds.getCentreY();
        auto s = juce::jmin(bounds.getWidth(), bounds.getHeight());

        juce::Path outerArc;
        outerArc.addCentredArc(cx, cy + s * 0.15f, s * 0.42f, s * 0.38f, 0.0f, -juce::MathConstants<float>::pi * 0.55f, juce::MathConstants<float>::pi * 0.55f, true);
        g.strokePath(outerArc, juce::PathStrokeType(1.2f));

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

        juce::Path mPath;
        float mw = s * 0.38f;
        float mh = s * 0.36f;
        float mx = cx - mw * 0.5f;
        float my = cy - s * 0.05f;

        mPath.startNewSubPath(mx, my + mh);
        mPath.lineTo(mx + mw * 0.12f, my);
        mPath.lineTo(cx, my + mh * 0.72f);
        mPath.lineTo(mx + mw * 0.88f, my);
        mPath.lineTo(mx + mw, my + mh);
        g.strokePath(mPath, juce::PathStrokeType(1.8f));
    }

    void drawWordmark(juce::Graphics& g, juce::Rectangle<float> bounds, float fontSize, juce::Colour colour)
    {
        g.setColour(colour);
        g.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSerifFontName(), fontSize, juce::Font::plain)));
        g.drawText("M Y S T I C A L A N D", bounds, juce::Justification::centred, true);
    }

    void drawSubtleMarbleTexture(juce::Graphics& g, juce::Rectangle<float> bounds)
    {
        auto bg = AssetManager::getInstance().getBackgroundImage();
        if (bg.isValid())
        {
            g.drawImage(bg, bounds, juce::RectanglePlacement::fillDestination);
            return;
        }

        // Procedural fallback
        g.setColour(Theme::ChampagneGold.withAlpha(0.03f));
        g.drawRect(bounds, 1.0f);
    }
}

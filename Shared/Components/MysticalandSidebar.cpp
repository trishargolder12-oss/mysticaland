#include "MysticalandSidebar.h"

namespace Mysticaland::UI
{
    MysticalandSidebar::MysticalandSidebar()
        : effectsBtn("Effects", NavigationItem::IconType::Waveform),
          instrumentsBtn("Instruments", NavigationItem::IconType::Keyboard)
    {
        addAndMakeVisible(effectsBtn);
        addAndMakeVisible(instrumentsBtn);

        effectsBtn.setToggleState(true, juce::dontSendNotification);

        effectsBtn.onClick = [this]() { setSelectedCategory(Category::Effects); };
        instrumentsBtn.onClick = [this]() { setSelectedCategory(Category::Instruments); };
    }

    void MysticalandSidebar::setSelectedCategory(Category cat)
    {
        currentCategory = cat;
        effectsBtn.setToggleState(cat == Category::Effects, juce::dontSendNotification);
        instrumentsBtn.setToggleState(cat == Category::Instruments, juce::dontSendNotification);

        if (onCategoryChanged)
            onCategoryChanged(cat);

        repaint();
    }

    void MysticalandSidebar::paint(juce::Graphics& g)
    {
        auto bounds = getLocalBounds().toFloat();

        // Background
        g.setColour(Theme::SidebarBackground);
        g.fillRect(bounds);

        // Right vertical border
        g.setColour(Theme::BorderColor);
        g.drawVerticalLine(getWidth() - 1, bounds.getY(), bounds.getBottom());

        // Decorative small 4-point star divider below navigation items
        float starY = 160.0f;
        float starX = bounds.getCentreX();
        float starR = 4.0f;

        g.setColour(Theme::ChampagneGold.withAlpha(0.35f));
        juce::Path star;
        star.startNewSubPath(starX, starY - starR);
        star.quadraticTo(starX + 1.0f, starY - 1.0f, starX + starR, starY);
        star.quadraticTo(starX + 1.0f, starY + 1.0f, starX, starY + starR);
        star.quadraticTo(starX - 1.0f, starY + 1.0f, starX - starR, starY);
        star.quadraticTo(starX - 1.0f, starY - 1.0f, starX, starY - starR);
        star.closeSubPath();
        g.fillPath(star);

        // Thin flanking lines for the star divider
        g.setColour(Theme::BorderColor.withAlpha(0.5f));
        g.drawHorizontalLine((int)starY, starX - 40.0f, starX - 10.0f);
        g.drawHorizontalLine((int)starY, starX + 10.0f, starX + 40.0f);

        // Subtle mountain relief in the bottom corner (as seen in the reference)
        auto bottomArea = bounds.removeFromBottom(160.0f);
        drawSubtleMountainRelief(g, bottomArea);
    }

    void MysticalandSidebar::drawSubtleMountainRelief(juce::Graphics& g, juce::Rectangle<float> bounds)
    {
        g.saveState();
        g.reduceClipRegion(bounds.toNearestInt());

        // Deep shadow mountain ridge silhouette
        juce::Path mountain;
        float w = bounds.getWidth();
        float h = bounds.getHeight();
        float by = bounds.getBottom();

        mountain.startNewSubPath(bounds.getX(), by);
        mountain.lineTo(bounds.getX(), bounds.getY() + h * 0.45f);
        mountain.lineTo(bounds.getX() + w * 0.35f, bounds.getY() + h * 0.15f); // Peak 1
        mountain.lineTo(bounds.getX() + w * 0.55f, bounds.getY() + h * 0.42f);
        mountain.lineTo(bounds.getX() + w * 0.85f, bounds.getY() + h * 0.28f); // Peak 2
        mountain.lineTo(bounds.getRight(), bounds.getY() + h * 0.50f);
        mountain.lineTo(bounds.getRight(), by);
        mountain.closeSubPath();

        // Dark layered gradient
        juce::ColourGradient grad(Theme::MainBackground.withAlpha(0.2f), bounds.getCentreX(), bounds.getY(),
                                  Theme::MainBackground.withAlpha(0.85f), bounds.getCentreX(), by, false);
        g.setGradientFill(grad);
        g.fillPath(mountain);

        // Ridge edge highlight (champagne gold accent, very faint)
        g.setColour(Theme::ChampagneGold.withAlpha(0.12f));
        g.strokePath(mountain, juce::PathStrokeType(1.0f));

        g.restoreState();
    }

    void MysticalandSidebar::resized()
    {
        int itemH = 46;
        int itemMargin = 16;
        int itemW = getWidth() - (itemMargin * 2);

        effectsBtn.setBounds(itemMargin, 24, itemW, itemH);
        instrumentsBtn.setBounds(itemMargin, 24 + itemH + 10, itemW, itemH);
    }
}

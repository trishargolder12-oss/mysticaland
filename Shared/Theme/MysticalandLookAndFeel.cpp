#include "MysticalandLookAndFeel.h"

namespace Mysticaland::Theme
{
    MysticalandLookAndFeel::MysticalandLookAndFeel()
    {
        setColour(juce::ResizableWindow::backgroundColourId, MainBackground);
    }

    void MysticalandLookAndFeel::drawButtonBackground(juce::Graphics& g, juce::Button& button, 
                                                      const juce::Colour& /*backgroundColour*/, 
                                                      bool shouldDrawButtonAsHighlighted, 
                                                      bool shouldDrawButtonAsDown)
    {
        auto bounds = button.getLocalBounds().toFloat().reduced(0.5f);
        auto cornerSize = 6.0f;

        if (button.getToggleState())
        {
            g.setColour(SelectedBackground);
            g.fillRoundedRectangle(bounds, cornerSize);
            
            // Subtle champagne gold accent border
            g.setColour(ChampagneGold);
            g.drawRoundedRectangle(bounds, cornerSize, 1.0f);
        }
        else if (shouldDrawButtonAsHighlighted || shouldDrawButtonAsDown)
        {
            g.setColour(HoverBackground);
            g.fillRoundedRectangle(bounds, cornerSize);
            
            g.setColour(BorderColor.brighter(0.2f));
            g.drawRoundedRectangle(bounds, cornerSize, 0.8f);
        }
        else
        {
            g.setColour(juce::Colours::transparentBlack);
            g.fillRoundedRectangle(bounds, cornerSize);
        }
    }

    void MysticalandLookAndFeel::drawButtonText(juce::Graphics& g, juce::TextButton& button, 
                                                bool /*shouldDrawButtonAsHighlighted*/, 
                                                bool /*shouldDrawButtonAsDown*/)
    {
        auto font = getTextButtonFont(button, button.getHeight());
        g.setFont(font);
        
        juce::Colour textColour = button.getToggleState() ? PrimaryText : SecondaryText;
        g.setColour(textColour);
        
        g.drawText(button.getButtonText(), button.getLocalBounds(), juce::Justification::centred, true);
    }

    juce::Font MysticalandLookAndFeel::getTextButtonFont(juce::TextButton&, int buttonHeight)
    {
        return juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifFontName(), (float)buttonHeight * 0.42f, juce::Font::plain));
    }
}

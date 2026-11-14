#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "MysticalandColors.h"

namespace Mysticaland::Theme
{
    class MysticalandLookAndFeel : public juce::LookAndFeel_V4
    {
    public:
        MysticalandLookAndFeel();
        ~MysticalandLookAndFeel() override = default;

        void drawButtonBackground(juce::Graphics& g, juce::Button& button, 
                                  const juce::Colour& backgroundColour, 
                                  bool shouldDrawButtonAsHighlighted, 
                                  bool shouldDrawButtonAsDown) override;

        void drawButtonText(juce::Graphics& g, juce::TextButton& button, 
                            bool shouldDrawButtonAsHighlighted, 
                            bool shouldDrawButtonAsDown) override;

        juce::Font getTextButtonFont(juce::TextButton&, int buttonHeight) override;

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MysticalandLookAndFeel)
    };
}

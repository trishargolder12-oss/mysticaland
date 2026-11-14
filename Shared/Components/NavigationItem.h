#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../Theme/MysticalandColors.h"

namespace Mysticaland::UI
{
    class NavigationItem : public juce::Button
    {
    public:
        enum class IconType { Waveform, Keyboard };

        NavigationItem(const juce::String& name, IconType icon);
        ~NavigationItem() override = default;

        void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    private:
        IconType iconType;

        void drawWaveformIcon(juce::Graphics& g, juce::Rectangle<float> bounds);
        void drawKeyboardIcon(juce::Graphics& g, juce::Rectangle<float> bounds);

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NavigationItem)
    };
}

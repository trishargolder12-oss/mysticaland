#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../Theme/MysticalandColors.h"
#include "../Branding/MysticalandBranding.h"

namespace Mysticaland::UI
{
    class MysticalandHeader : public juce::Component
    {
    public:
        MysticalandHeader();
        ~MysticalandHeader() override = default;

        void paint(juce::Graphics& g) override;
        void resized() override;

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MysticalandHeader)
    };
}

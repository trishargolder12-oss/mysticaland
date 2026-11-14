#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../Theme/MysticalandColors.h"
#include "../Branding/MysticalandBranding.h"

namespace Mysticaland::UI
{
    class EmptyStateComponent : public juce::Component
    {
    public:
        EmptyStateComponent();
        ~EmptyStateComponent() override = default;

        void paint(juce::Graphics& g) override;
        void resized() override;

        void setCategoryName(const juce::String& name);

    private:
        juce::String currentCategoryName = "EFFECT";

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EmptyStateComponent)
    };
}

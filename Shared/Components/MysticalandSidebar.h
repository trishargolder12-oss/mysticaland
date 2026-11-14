#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include "../Theme/MysticalandColors.h"
#include "NavigationItem.h"

namespace Mysticaland::UI
{
    class MysticalandSidebar : public juce::Component
    {
    public:
        enum class Category { Effects, Instruments };

        std::function<void(Category)> onCategoryChanged;

        MysticalandSidebar();
        ~MysticalandSidebar() override = default;

        void paint(juce::Graphics& g) override;
        void resized() override;

        void setSelectedCategory(Category cat);
        Category getSelectedCategory() const { return currentCategory; }

    private:
        Category currentCategory = Category::Effects;
        NavigationItem effectsBtn;
        NavigationItem instrumentsBtn;

        void drawSubtleMountainRelief(juce::Graphics& g, juce::Rectangle<float> bounds);

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MysticalandSidebar)
    };
}

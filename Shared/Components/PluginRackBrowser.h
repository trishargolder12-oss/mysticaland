#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <Theme/MysticalandColors.h>
#include <PluginCore/PluginDescriptor.h>
#include "PluginCard.h"

namespace Mysticaland::UI
{
    class PluginRackBrowser : public juce::Component
    {
    public:
        std::function<void(const Plugin::PluginDescriptor&)> onModuleSelected;

        PluginRackBrowser();
        ~PluginRackBrowser() override = default;

        void paint(juce::Graphics& g) override;
        void resized() override;

        void setCategoryFilter(Plugin::PluginCategory cat);

    private:
        Plugin::PluginCategory activeCategory = Plugin::PluginCategory::Effect;
        std::vector<Plugin::PluginDescriptor> allDescriptors;
        juce::OwnedArray<PluginCard> visibleCards;

        void populateDescriptors();
        void refreshCards();

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginRackBrowser)
    };
}

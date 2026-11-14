#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <Theme/MysticalandColors.h>
#include <PluginCore/PluginDescriptor.h>

namespace Mysticaland::UI
{
    class PluginCard : public juce::Component
    {
    public:
        std::function<void(const Plugin::PluginDescriptor&)> onModuleAction;

        PluginCard(const Plugin::PluginDescriptor& desc);
        ~PluginCard() override = default;

        void paint(juce::Graphics& g) override;
        void resized() override;
        void mouseEnter(const juce::MouseEvent&) override;
        void mouseExit(const juce::MouseEvent&) override;

        const Plugin::PluginDescriptor& getDescriptor() const { return descriptor; }

    private:
        Plugin::PluginDescriptor descriptor;
        bool isHovered = false;
        juce::TextButton actionBtn;

        void drawModuleVisualizer(juce::Graphics& g, juce::Rectangle<float> bounds);

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginCard)
    };
}

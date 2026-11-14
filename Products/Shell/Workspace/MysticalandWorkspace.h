#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <Theme/MysticalandColors.h>
#include <Branding/MysticalandBranding.h>
#include <Components/EmptyStateComponent.h>

namespace Mysticaland::Shell
{
    class MysticalandWorkspace : public juce::Component
    {
    public:
        enum class Mode { EmptyEffects, EmptyInstruments, PluginLoaded };

        MysticalandWorkspace();
        ~MysticalandWorkspace() override = default;

        void paint(juce::Graphics& g) override;
        void resized() override;

        void setMode(Mode newMode);
        void mountPluginEditor(std::unique_ptr<juce::Component> pluginUI);
        void clearMountedPlugin();

    private:
        Mode currentMode = Mode::EmptyEffects;
        UI::EmptyStateComponent emptyState;
        std::unique_ptr<juce::Component> activePluginUI;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MysticalandWorkspace)
    };
}

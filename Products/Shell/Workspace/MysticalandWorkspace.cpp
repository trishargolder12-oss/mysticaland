#include "MysticalandWorkspace.h"

namespace Mysticaland::Shell
{
    MysticalandWorkspace::MysticalandWorkspace()
    {
        addAndMakeVisible(emptyState);
    }

    void MysticalandWorkspace::setMode(Mode newMode)
    {
        currentMode = newMode;
        if (currentMode == Mode::EmptyEffects)
        {
            clearMountedPlugin();
            emptyState.setVisible(true);
            emptyState.setCategoryName("EFFECT");
        }
        else if (currentMode == Mode::EmptyInstruments)
        {
            clearMountedPlugin();
            emptyState.setVisible(true);
            emptyState.setCategoryName("INSTRUMENT");
        }
        else if (currentMode == Mode::PluginLoaded)
        {
            emptyState.setVisible(false);
        }
        repaint();
    }

    void MysticalandWorkspace::mountPluginEditor(std::unique_ptr<juce::Component> pluginUI)
    {
        clearMountedPlugin();
        activePluginUI = std::move(pluginUI);
        if (activePluginUI != nullptr)
        {
            addAndMakeVisible(*activePluginUI);
            setMode(Mode::PluginLoaded);
            resized();
        }
    }

    void MysticalandWorkspace::clearMountedPlugin()
    {
        if (activePluginUI != nullptr)
        {
            removeChildComponent(activePluginUI.get());
            activePluginUI.reset();
        }
    }

    void MysticalandWorkspace::paint(juce::Graphics& g)
    {
        auto bounds = getLocalBounds().toFloat();

        // 1. Workspace Background
        g.setColour(Theme::WorkspaceBackground);
        g.fillRect(bounds);

        // 2. Subtle Dark Stone / Marble Veining
        Branding::drawSubtleMarbleTexture(g, bounds);

        // 3. Inner border framing
        g.setColour(Theme::BorderColor.withAlpha(0.6f));
        g.drawRect(bounds, 1.0f);
    }

    void MysticalandWorkspace::resized()
    {
        auto bounds = getLocalBounds();
        emptyState.setBounds(bounds);

        if (activePluginUI != nullptr)
            activePluginUI->setBounds(bounds);
    }
}

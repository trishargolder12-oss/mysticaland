#include "MysticalandShellAudioProcessorEditor.h"

MysticalandShellAudioProcessorEditor::MysticalandShellAudioProcessorEditor(MysticalandShellAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setLookAndFeel(&customLookAndFeel);

    addAndMakeVisible(header);
    addAndMakeVisible(sidebar);
    addAndMakeVisible(workspace);

    // Wire Category switching to Workspace mode
    sidebar.onCategoryChanged = [this](Mysticaland::UI::MysticalandSidebar::Category cat)
    {
        if (cat == Mysticaland::UI::MysticalandSidebar::Category::Effects)
            workspace.setMode(Mysticaland::Shell::MysticalandWorkspace::Mode::EmptyEffects);
        else
            workspace.setMode(Mysticaland::Shell::MysticalandWorkspace::Mode::EmptyInstruments);
    };

    // Reference size: 1200 x 720, minimum: 850 x 550
    setResizable(true, true);
    setResizeLimits(850, 550, 2560, 1440);
    setSize(1200, 720);
}

MysticalandShellAudioProcessorEditor::~MysticalandShellAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

void MysticalandShellAudioProcessorEditor::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    // 1. Overall outer background
    g.setColour(Mysticaland::Theme::MainBackground);
    g.fillRoundedRectangle(bounds, 8.0f);

    // 2. High-end outer chassis frame with subtle champagne-gold border
    g.setColour(Mysticaland::Theme::BorderColor);
    g.drawRoundedRectangle(bounds.reduced(0.5f), 8.0f, 1.0f);

    // Subtle top-edge champagne-gold sheen
    g.setColour(Mysticaland::Theme::ChampagneGold.withAlpha(0.2f));
    g.drawRoundedRectangle(bounds.reduced(1.5f), 7.0f, 0.6f);
}

void MysticalandShellAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds().reduced(2); // Inset slightly for rounded chassis frame

    // Top Header: 68px
    int headerHeight = 68;
    header.setBounds(bounds.removeFromTop(headerHeight));

    // Left Navigation Sidebar: 240px wide
    int sidebarWidth = 240;
    sidebar.setBounds(bounds.removeFromLeft(sidebarWidth));

    // Main Workspace: fills remaining area
    workspace.setBounds(bounds);
}

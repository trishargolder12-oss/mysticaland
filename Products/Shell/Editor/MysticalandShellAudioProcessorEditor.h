#pragma once
#include <juce_audio_processors/juce_audio_processors.h>
#include "MysticalandShellAudioProcessor.h"
#include <Theme/MysticalandLookAndFeel.h>
#include <Theme/MysticalandColors.h>
#include <Components/MysticalandHeader.h>
#include <Components/MysticalandSidebar.h>
#include "../Workspace/MysticalandWorkspace.h"

class MysticalandShellAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    explicit MysticalandShellAudioProcessorEditor(MysticalandShellAudioProcessor&);
    ~MysticalandShellAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    MysticalandShellAudioProcessor& audioProcessor;
    
    // Custom Look & Feel
    Mysticaland::Theme::MysticalandLookAndFeel customLookAndFeel;

    // UI Structural Components
    Mysticaland::UI::MysticalandHeader header;
    Mysticaland::UI::MysticalandSidebar sidebar;
    Mysticaland::Shell::MysticalandWorkspace workspace;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MysticalandShellAudioProcessorEditor)
};

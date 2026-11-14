#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_processors/juce_audio_processors.h>

namespace Mysticaland::Plugin
{
    enum class PluginCategory
    {
        Effect,
        Instrument
    };

    struct PluginDescriptor
    {
        juce::String id;
        juce::String name;
        juce::String subtitle;
        juce::String description;
        juce::String version;
        PluginCategory category;
        bool isInstalled;
        bool isComingSoon;
    };

    // Forward declaration of interface that all Mysticaland pluggable DSP modules implement
    class IMysticalandModule
    {
    public:
        virtual ~IMysticalandModule() = default;

        virtual const PluginDescriptor& getDescriptor() const = 0;
        virtual void prepare(double sampleRate, int samplesPerBlock) = 0;
        virtual void reset() = 0;
        virtual void process(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi) = 0;
        virtual std::unique_ptr<juce::Component> createEditor() = 0;
        virtual void getState(juce::MemoryBlock& dest) = 0;
        virtual void setState(const void* data, int size) = 0;
    };
}

#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_dsp/juce_dsp.h>
#include <PluginCore/PluginDescriptor.h>
#include <Theme/MysticalandColors.h>

namespace Mysticaland::Modules
{
    class PressorModule : public Plugin::IMysticalandModule
    {
    public:
        PressorModule();
        ~PressorModule() override = default;

        const Plugin::PluginDescriptor& getDescriptor() const override { return descriptor; }
        void prepare(double sampleRate, int samplesPerBlock) override;
        void reset() override;
        void process(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi) override;
        std::unique_ptr<juce::Component> createEditor() override;
        void getState(juce::MemoryBlock& dest) override;
        void setState(const void* data, int size) override;

        float thresholdDB = -18.0f;
        float ratio = 4.0f;
        float attackMs = 20.0f;
        float releaseMs = 150.0f;
        float makeupGainDB = 3.0f;
        float currentGainReductionDB = 0.0f;

    private:
        Plugin::PluginDescriptor descriptor;
        juce::dsp::Compressor<float> compressor;
    };

    class PressorEditor : public juce::Component, private juce::Timer
    {
    public:
        std::function<void()> onBackToCatalog;

        PressorEditor(PressorModule& module);
        ~PressorEditor() override;

        void paint(juce::Graphics& g) override;
        void resized() override;

    private:
        PressorModule& pressorModule;
        juce::Slider thresholdSlider, ratioSlider, attackSlider, releaseSlider, makeupSlider;
        juce::TextButton backBtn;
        float animatedGR = 0.0f;

        void timerCallback() override;
        void drawVUMeter(juce::Graphics& g, juce::Rectangle<float> bounds);

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PressorEditor)
    };
}

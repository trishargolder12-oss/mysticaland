#pragma once
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_dsp/juce_dsp.h>
#include <PluginCore/PluginDescriptor.h>
#include <Theme/MysticalandColors.h>

namespace Mysticaland::Modules
{
    class NebulaEQModule : public Plugin::IMysticalandModule
    {
    public:
        NebulaEQModule();
        ~NebulaEQModule() override = default;

        const Plugin::PluginDescriptor& getDescriptor() const override { return descriptor; }
        void prepare(double sampleRate, int samplesPerBlock) override;
        void reset() override;
        void process(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi) override;
        std::unique_ptr<juce::Component> createEditor() override;
        void getState(juce::MemoryBlock& dest) override;
        void setState(const void* data, int size) override;

        // DSP Parameters
        float lowGainDB = 0.0f;
        float midGainDB = 0.0f;
        float highGainDB = 0.0f;
        float lowFreqHz = 120.0f;
        float midFreqHz = 1000.0f;
        float highFreqHz = 8000.0f;

    private:
        Plugin::PluginDescriptor descriptor;
        double currentSampleRate = 44100.0;

        // Biquad Filter Coefficients & States (Left and Right channels)
        using IIRFilter = juce::dsp::IIR::Filter<float>;
        using Coefficients = juce::dsp::IIR::Coefficients<float>;

        IIRFilter lowShelfL, lowShelfR;
        IIRFilter peakL, peakR;
        IIRFilter highShelfL, highShelfR;

        void updateFilters();
    };

    class NebulaEQEditor : public juce::Component
    {
    public:
        std::function<void()> onBackToCatalog;

        NebulaEQEditor(NebulaEQModule& module);
        ~NebulaEQEditor() override = default;

        void paint(juce::Graphics& g) override;
        void resized() override;

    private:
        NebulaEQModule& eqModule;
        juce::Slider lowGainSlider, midGainSlider, highGainSlider;
        juce::Slider lowFreqSlider, midFreqSlider, highFreqSlider;
        juce::TextButton backBtn;

        void drawSpectrumCurve(juce::Graphics& g, juce::Rectangle<float> bounds);

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NebulaEQEditor)
    };
}

#include "PressorModule.h"

namespace Mysticaland::Modules
{
    PressorModule::PressorModule()
    {
        descriptor = {
            "pressor",
            "Pressor",
            "Analog Dynamics Compressor",
            "Warm VCA analog-modeled compressor with smooth gain reduction.",
            "1.0.0",
            Plugin::PluginCategory::Effect,
            true,  // isInstalled
            false  // isComingSoon
        };
    }

    void PressorModule::prepare(double sampleRate, int samplesPerBlock)
    {
        juce::dsp::ProcessSpec spec;
        spec.sampleRate = sampleRate > 0 ? sampleRate : 44100.0;
        spec.maximumBlockSize = (juce::uint32)samplesPerBlock;
        spec.numChannels = 2;
        compressor.prepare(spec);
        reset();
    }

    void PressorModule::reset()
    {
        compressor.reset();
        currentGainReductionDB = 0.0f;
    }

    void PressorModule::process(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midi*/)
    {
        compressor.setThreshold(thresholdDB);
        compressor.setRatio(ratio);
        compressor.setAttack(attackMs);
        compressor.setRelease(releaseMs);

        // Track input RMS for meter animation
        float inRms = buffer.getRMSLevel(0, 0, buffer.getNumSamples());

        juce::dsp::AudioBlock<float> block(buffer);
        juce::dsp::ProcessContextReplacing<float> context(block);
        compressor.process(context);

        // Apply makeup gain
        float makeup = juce::Decibels::decibelsToGain(makeupGainDB);
        buffer.applyGain(makeup);

        float outRms = buffer.getRMSLevel(0, 0, buffer.getNumSamples());
        float gr = (inRms > 0.0001f && outRms > 0.0001f) ? (juce::Decibels::gainToDecibels(outRms / inRms) - makeupGainDB) : 0.0f;
        currentGainReductionDB = juce::jmin(0.0f, gr);
    }

    std::unique_ptr<juce::Component> PressorModule::createEditor()
    {
        return std::make_unique<PressorEditor>(*this);
    }

    void PressorModule::getState(juce::MemoryBlock& dest)
    {
        juce::MemoryOutputStream stream(dest, false);
        stream.writeFloat(thresholdDB);
        stream.writeFloat(ratio);
        stream.writeFloat(attackMs);
        stream.writeFloat(releaseMs);
        stream.writeFloat(makeupGainDB);
    }

    void PressorModule::setState(const void* data, int size)
    {
        if (size >= (int)(sizeof(float) * 5))
        {
            juce::MemoryInputStream stream(data, size, false);
            thresholdDB = stream.readFloat();
            ratio = stream.readFloat();
            attackMs = stream.readFloat();
            releaseMs = stream.readFloat();
            makeupGainDB = stream.readFloat();
        }
    }

    // ==========================================
    // Pressor Editor Component
    // ==========================================

    PressorEditor::PressorEditor(PressorModule& module)
        : pressorModule(module), backBtn("< RACK BROWSER")
    {
        addAndMakeVisible(backBtn);
        backBtn.onClick = [this]()
        {
            if (onBackToCatalog)
                onBackToCatalog();
        };

        auto setupRotary = [this](juce::Slider& s, const juce::String& suffix, double minVal, double maxVal, double defaultVal)
        {
            s.setSliderStyle(juce::Slider::RotaryVerticalDrag);
            s.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
            s.setTextValueSuffix(suffix);
            s.setRange(minVal, maxVal, 0.1);
            s.setValue(defaultVal);
            s.setColour(juce::Slider::rotarySliderFillColourId, Theme::ChampagneGold);
            s.setColour(juce::Slider::rotarySliderOutlineColourId, Theme::BorderColor);
            s.setColour(juce::Slider::textBoxTextColourId, Theme::PrimaryText);
            s.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
            addAndMakeVisible(s);
        };

        setupRotary(thresholdSlider, " dB", -60.0, 0.0, pressorModule.thresholdDB);
        setupRotary(ratioSlider, ":1", 1.0, 20.0, pressorModule.ratio);
        setupRotary(attackSlider, " ms", 0.5, 100.0, pressorModule.attackMs);
        setupRotary(releaseSlider, " ms", 10.0, 1000.0, pressorModule.releaseMs);
        setupRotary(makeupSlider, " dB", 0.0, 24.0, pressorModule.makeupGainDB);

        thresholdSlider.onValueChange = [this]() { pressorModule.thresholdDB = (float)thresholdSlider.getValue(); };
        ratioSlider.onValueChange = [this]() { pressorModule.ratio = (float)ratioSlider.getValue(); };
        attackSlider.onValueChange = [this]() { pressorModule.attackMs = (float)attackSlider.getValue(); };
        releaseSlider.onValueChange = [this]() { pressorModule.releaseMs = (float)releaseSlider.getValue(); };
        makeupSlider.onValueChange = [this]() { pressorModule.makeupGainDB = (float)makeupSlider.getValue(); };

        startTimerHz(30);
    }

    PressorEditor::~PressorEditor()
    {
        stopTimer();
    }

    void PressorEditor::timerCallback()
    {
        animatedGR = animatedGR * 0.7f + pressorModule.currentGainReductionDB * 0.3f;
        repaint();
    }

    void PressorEditor::drawVUMeter(juce::Graphics& g, juce::Rectangle<float> bounds)
    {
        g.setColour(Theme::MainBackground);
        g.fillRoundedRectangle(bounds, 8.0f);

        g.setColour(Theme::BorderColor);
        g.drawRoundedRectangle(bounds, 8.0f, 1.0f);

        float cx = bounds.getCentreX();
        float cy = bounds.getBottom() + 15.0f;
        float radius = bounds.getHeight() * 1.15f;

        // Needle Pivot
        float angle = juce::jmap(animatedGR, -24.0f, 0.0f, -0.6f, 0.6f);
        float nx = cx + radius * std::sin(angle);
        float ny = cy - radius * std::cos(angle);

        // Meter Arc Scale
        juce::Path arc;
        arc.addCentredArc(cx, cy, radius, radius, 0.0f, -0.65f, 0.65f, true);
        g.setColour(Theme::BorderColor);
        g.strokePath(arc, juce::PathStrokeType(1.0f));

        // GR Ticks
        for (int db = 0; db >= -20; db -= 4)
        {
            float a = juce::jmap((float)db, -24.0f, 0.0f, -0.6f, 0.6f);
            float x1 = cx + (radius - 8.0f) * std::sin(a);
            float y1 = cy - (radius - 8.0f) * std::cos(a);
            float x2 = cx + (radius + 4.0f) * std::sin(a);
            float y2 = cy - (radius + 4.0f) * std::cos(a);
            g.setColour(db <= -12 ? Theme::ChampagneGold : Theme::MutedText);
            g.drawLine(x1, y1, x2, y2, 1.2f);
        }

        // Active Needle
        g.setColour(Theme::ChampagneGold);
        g.drawLine(cx, cy, nx, ny, 2.0f);

        // Center Cap
        g.setColour(Theme::PrimaryText);
        g.drawText("GAIN REDUCTION (dB)", bounds.removeFromBottom(24.0f), juce::Justification::centred, true);
    }

    void PressorEditor::paint(juce::Graphics& g)
    {
        auto bounds = getLocalBounds().toFloat();

        // Header Title
        g.setColour(Theme::PrimaryText);
        g.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSerifFontName(), 20.0f, juce::Font::bold)));
        g.drawText("PRESSOR", juce::Rectangle<float>(140.0f, 18.0f, 300.0f, 30.0f), juce::Justification::centredLeft, true);

        g.setColour(Theme::ChampagneGold);
        g.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifFontName(), 11.0f, juce::Font::plain)));
        g.drawText("ANALOG DYNAMICS PROCESSOR - PRECISION VCA MODELING", juce::Rectangle<float>(140.0f, 44.0f, 400.0f, 18.0f), juce::Justification::centredLeft, true);

        // VU Meter
        auto meterArea = juce::Rectangle<float>(bounds.getCentreX() - 170.0f, 75.0f, 340.0f, 160.0f);
        drawVUMeter(g, meterArea);
    }

    void PressorEditor::resized()
    {
        backBtn.setBounds(24, 20, 100, 28);

        float w = (float)getWidth() - 48.0f;
        float knobSize = 80.0f;
        float spacing = (w - knobSize * 5.0f) / 6.0f;
        float startY = 270.0f;

        thresholdSlider.setBounds((int)(24.0f + spacing), (int)startY, (int)knobSize, (int)knobSize);
        ratioSlider.setBounds((int)(24.0f + spacing * 2.0f + knobSize), (int)startY, (int)knobSize, (int)knobSize);
        attackSlider.setBounds((int)(24.0f + spacing * 3.0f + knobSize * 2.0f), (int)startY, (int)knobSize, (int)knobSize);
        releaseSlider.setBounds((int)(24.0f + spacing * 4.0f + knobSize * 3.0f), (int)startY, (int)knobSize, (int)knobSize);
        makeupSlider.setBounds((int)(24.0f + spacing * 5.0f + knobSize * 4.0f), (int)startY, (int)knobSize, (int)knobSize);
    }
}

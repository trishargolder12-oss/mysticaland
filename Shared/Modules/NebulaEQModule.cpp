#include "NebulaEQModule.h"

namespace Mysticaland::Modules
{
    NebulaEQModule::NebulaEQModule()
    {
        descriptor = {
            "nebula_eq",
            "Nebula EQ",
            "Parametric Studio Equalizer",
            "3-band precision musical EQ with pristine analog biquad curves.",
            "1.0.0",
            Plugin::PluginCategory::Effect,
            true,  // isInstalled
            false  // isComingSoon
        };
    }

    void NebulaEQModule::prepare(double sampleRate, int /*samplesPerBlock*/)
    {
        currentSampleRate = sampleRate > 0 ? sampleRate : 44100.0;
        reset();
        updateFilters();
    }

    void NebulaEQModule::reset()
    {
        lowShelfL.reset();
        lowShelfR.reset();
        peakL.reset();
        peakR.reset();
        highShelfL.reset();
        highShelfR.reset();
    }

    void NebulaEQModule::updateFilters()
    {
        auto lowCoeffs = Coefficients::makeLowShelf(currentSampleRate, lowFreqHz, 0.707f, juce::Decibels::decibelsToGain(lowGainDB));
        auto midCoeffs = Coefficients::makePeakFilter(currentSampleRate, midFreqHz, 1.0f, juce::Decibels::decibelsToGain(midGainDB));
        auto highCoeffs = Coefficients::makeHighShelf(currentSampleRate, highFreqHz, 0.707f, juce::Decibels::decibelsToGain(highGainDB));

        *lowShelfL.coefficients = *lowCoeffs;
        *lowShelfR.coefficients = *lowCoeffs;
        *peakL.coefficients = *midCoeffs;
        *peakR.coefficients = *midCoeffs;
        *highShelfL.coefficients = *highCoeffs;
        *highShelfR.coefficients = *highCoeffs;
    }

    void NebulaEQModule::process(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midi*/)
    {
        updateFilters();

        auto numSamples = buffer.getNumSamples();
        if (buffer.getNumChannels() >= 2)
        {
            auto* left = buffer.getWritePointer(0);
            auto* right = buffer.getWritePointer(1);

            for (int i = 0; i < numSamples; ++i)
            {
                float sL = left[i];
                float sR = right[i];

                sL = lowShelfL.processSample(sL);
                sR = lowShelfR.processSample(sR);

                sL = peakL.processSample(sL);
                sR = peakR.processSample(sR);

                sL = highShelfL.processSample(sL);
                sR = highShelfR.processSample(sR);

                left[i] = sL;
                right[i] = sR;
            }
        }
        else if (buffer.getNumChannels() == 1)
        {
            auto* mono = buffer.getWritePointer(0);
            for (int i = 0; i < numSamples; ++i)
            {
                float s = mono[i];
                s = lowShelfL.processSample(s);
                s = peakL.processSample(s);
                s = highShelfL.processSample(s);
                mono[i] = s;
            }
        }
    }

    std::unique_ptr<juce::Component> NebulaEQModule::createEditor()
    {
        return std::make_unique<NebulaEQEditor>(*this);
    }

    void NebulaEQModule::getState(juce::MemoryBlock& dest)
    {
        juce::MemoryOutputStream stream(dest, false);
        stream.writeFloat(lowGainDB);
        stream.writeFloat(midGainDB);
        stream.writeFloat(highGainDB);
        stream.writeFloat(lowFreqHz);
        stream.writeFloat(midFreqHz);
        stream.writeFloat(highFreqHz);
    }

    void NebulaEQModule::setState(const void* data, int size)
    {
        if (size >= (int)(sizeof(float) * 6))
        {
            juce::MemoryInputStream stream(data, size, false);
            lowGainDB = stream.readFloat();
            midGainDB = stream.readFloat();
            highGainDB = stream.readFloat();
            lowFreqHz = stream.readFloat();
            midFreqHz = stream.readFloat();
            highFreqHz = stream.readFloat();
            updateFilters();
        }
    }

    // ==========================================
    // Nebula EQ Editor Component
    // ==========================================

    NebulaEQEditor::NebulaEQEditor(NebulaEQModule& module)
        : eqModule(module), backBtn("< RACK BROWSER")
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

        setupRotary(lowGainSlider, " dB", -15.0, 15.0, eqModule.lowGainDB);
        setupRotary(midGainSlider, " dB", -15.0, 15.0, eqModule.midGainDB);
        setupRotary(highGainSlider, " dB", -15.0, 15.0, eqModule.highGainDB);

        setupRotary(lowFreqSlider, " Hz", 30.0, 400.0, eqModule.lowFreqHz);
        setupRotary(midFreqSlider, " Hz", 200.0, 5000.0, eqModule.midFreqHz);
        setupRotary(highFreqSlider, " Hz", 2000.0, 16000.0, eqModule.highFreqHz);

        lowGainSlider.onValueChange = [this]() { eqModule.lowGainDB = (float)lowGainSlider.getValue(); repaint(); };
        midGainSlider.onValueChange = [this]() { eqModule.midGainDB = (float)midGainSlider.getValue(); repaint(); };
        highGainSlider.onValueChange = [this]() { eqModule.highGainDB = (float)highGainSlider.getValue(); repaint(); };

        lowFreqSlider.onValueChange = [this]() { eqModule.lowFreqHz = (float)lowFreqSlider.getValue(); repaint(); };
        midFreqSlider.onValueChange = [this]() { eqModule.midFreqHz = (float)midFreqSlider.getValue(); repaint(); };
        highFreqSlider.onValueChange = [this]() { eqModule.highFreqHz = (float)highFreqSlider.getValue(); repaint(); };
    }

    void NebulaEQEditor::drawSpectrumCurve(juce::Graphics& g, juce::Rectangle<float> bounds)
    {
        g.setColour(Theme::MainBackground);
        g.fillRoundedRectangle(bounds, 8.0f);

        g.setColour(Theme::BorderColor);
        g.drawRoundedRectangle(bounds, 8.0f, 1.0f);

        // Grid lines
        g.setColour(Theme::BorderColor.withAlpha(0.4f));
        g.drawHorizontalLine((int)bounds.getCentreY(), bounds.getX(), bounds.getRight());
        for (int i = 1; i <= 3; ++i)
            g.drawVerticalLine((int)(bounds.getX() + bounds.getWidth() * (i / 4.0f)), bounds.getY(), bounds.getBottom());

        // EQ Real-time Curve
        juce::Path curve;
        float startX = bounds.getX() + 5.0f;
        float endX = bounds.getRight() - 5.0f;
        float midY = bounds.getCentreY();

        curve.startNewSubPath(startX, midY);

        float lowOffset = (eqModule.lowGainDB / 15.0f) * (bounds.getHeight() * 0.35f);
        float midOffset = (eqModule.midGainDB / 15.0f) * (bounds.getHeight() * 0.35f);
        float highOffset = (eqModule.highGainDB / 15.0f) * (bounds.getHeight() * 0.35f);

        float cp1X = bounds.getX() + bounds.getWidth() * 0.2f;
        float cp2X = bounds.getX() + bounds.getWidth() * 0.5f;
        float cp3X = bounds.getX() + bounds.getWidth() * 0.8f;

        curve.cubicTo(cp1X, midY - lowOffset, cp2X - 30.0f, midY - midOffset, cp2X, midY - midOffset);
        curve.cubicTo(cp2X + 30.0f, midY - midOffset, cp3X, midY - highOffset, endX, midY - highOffset * 0.5f);

        // Fill glow
        juce::ColourGradient fillGrad(Theme::ChampagneGold.withAlpha(0.2f), bounds.getCentreX(), bounds.getY(),
                                      Theme::ChampagneGold.withAlpha(0.01f), bounds.getCentreX(), bounds.getBottom(), false);
        g.setGradientFill(fillGrad);
        juce::Path closedPath = curve;
        closedPath.lineTo(endX, bounds.getBottom());
        closedPath.lineTo(startX, bounds.getBottom());
        closedPath.closeSubPath();
        g.fillPath(closedPath);

        // Stroke
        g.setColour(Theme::ChampagneGold);
        g.strokePath(curve, juce::PathStrokeType(2.0f));
    }

    void NebulaEQEditor::paint(juce::Graphics& g)
    {
        auto bounds = getLocalBounds().toFloat();

        // Header Title
        g.setColour(Theme::PrimaryText);
        g.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSerifFontName(), 20.0f, juce::Font::bold)));
        g.drawText("NEBULA EQ", juce::Rectangle<float>(140.0f, 18.0f, 300.0f, 30.0f), juce::Justification::centredLeft, true);

        g.setColour(Theme::ChampagneGold);
        g.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifFontName(), 11.0f, juce::Font::plain)));
        g.drawText("PARAMETRIC STUDIO EQUALIZER - 3-BAND ANALOG BIQUAD", juce::Rectangle<float>(140.0f, 44.0f, 400.0f, 18.0f), juce::Justification::centredLeft, true);

        // Visualizer Curve Area
        auto curveArea = juce::Rectangle<float>(24.0f, 75.0f, bounds.getWidth() - 48.0f, 180.0f);
        drawSpectrumCurve(g, curveArea);

        // Section Labels
        g.setColour(Theme::SecondaryText);
        g.setFont(juce::Font(juce::FontOptions(juce::Font::getDefaultSansSerifFontName(), 13.0f, juce::Font::plain)));

        float sectionW = (bounds.getWidth() - 48.0f) / 3.0f;
        g.drawText("LOW SHELF", 24.0f, 270.0f, sectionW, 20.0f, juce::Justification::centred);
        g.drawText("MID PEAK", 24.0f + sectionW, 270.0f, sectionW, 20.0f, juce::Justification::centred);
        g.drawText("HIGH SHELF", 24.0f + sectionW * 2.0f, 270.0f, sectionW, 20.0f, juce::Justification::centred);
    }

    void NebulaEQEditor::resized()
    {
        backBtn.setBounds(24, 20, 100, 28);

        float w = (float)getWidth() - 48.0f;
        float sectionW = w / 3.0f;
        float startY = 300.0f;
        float knobSize = 85.0f;

        // Low Knobs
        lowGainSlider.setBounds((int)(24.0f + sectionW * 0.5f - knobSize - 5.0f), (int)startY, (int)knobSize, (int)knobSize);
        lowFreqSlider.setBounds((int)(24.0f + sectionW * 0.5f + 5.0f), (int)startY, (int)knobSize, (int)knobSize);

        // Mid Knobs
        midGainSlider.setBounds((int)(24.0f + sectionW * 1.5f - knobSize - 5.0f), (int)startY, (int)knobSize, (int)knobSize);
        midFreqSlider.setBounds((int)(24.0f + sectionW * 1.5f + 5.0f), (int)startY, (int)knobSize, (int)knobSize);

        // High Knobs
        highGainSlider.setBounds((int)(24.0f + sectionW * 2.5f - knobSize - 5.0f), (int)startY, (int)knobSize, (int)knobSize);
        highFreqSlider.setBounds((int)(24.0f + sectionW * 2.5f + 5.0f), (int)startY, (int)knobSize, (int)knobSize);
    }
}

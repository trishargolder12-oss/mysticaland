#include "MysticalandShellAudioProcessor.h"
#include "../Editor/MysticalandShellAudioProcessorEditor.h"

MysticalandShellAudioProcessor::MysticalandShellAudioProcessor()
    : AudioProcessor(BusesProperties()
                     .withInput("Input", juce::AudioChannelSet::stereo(), true)
                     .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      parameters(*this, nullptr, "MYSTICALAND_SHELL_STATE", {})
{
}

MysticalandShellAudioProcessor::~MysticalandShellAudioProcessor() {}

const juce::String MysticalandShellAudioProcessor::getName() const { return "Mysticaland Shell"; }
bool MysticalandShellAudioProcessor::acceptsMidi() const { return true; }
bool MysticalandShellAudioProcessor::producesMidi() const { return false; }
bool MysticalandShellAudioProcessor::isMidiEffect() const { return false; }
double MysticalandShellAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int MysticalandShellAudioProcessor::getNumPrograms() { return 1; }
int MysticalandShellAudioProcessor::getCurrentProgram() { return 0; }
void MysticalandShellAudioProcessor::setCurrentProgram(int) {}
const juce::String MysticalandShellAudioProcessor::getProgramName(int) { return {}; }
void MysticalandShellAudioProcessor::changeProgramName(int, const juce::String&) {}

void MysticalandShellAudioProcessor::prepareToPlay(double /*sampleRate*/, int /*samplesPerBlock*/)
{
}

void MysticalandShellAudioProcessor::releaseResources()
{
}

bool MysticalandShellAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}

void MysticalandShellAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midiMessages*/)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // Strict transparent pass-through
}

bool MysticalandShellAudioProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor* MysticalandShellAudioProcessor::createEditor()
{
    return new MysticalandShellAudioProcessorEditor(*this);
}

void MysticalandShellAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    juce::ValueTree state("MysticalandShellState");
    state.setProperty("version", "0.1.0", nullptr);
    state.setProperty("pluginCode", "Mshl", nullptr);

    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void MysticalandShellAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr && xmlState->hasTagName("MysticalandShellState"))
    {
        auto state = juce::ValueTree::fromXml(*xmlState);
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MysticalandShellAudioProcessor();
}

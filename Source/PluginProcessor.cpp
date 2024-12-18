/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SoundBathOneAudioProcessor::SoundBathOneAudioProcessor()
: AudioProcessor(BusesProperties()
                     .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      randomGenerator(randomDevice()),
      distribution(-1.0f, 1.0f)
{
//    DBG("Noise Generator Initialized");
}

SoundBathOneAudioProcessor::~SoundBathOneAudioProcessor()
{
}

//==============================================================================
const juce::String SoundBathOneAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SoundBathOneAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SoundBathOneAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SoundBathOneAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SoundBathOneAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SoundBathOneAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SoundBathOneAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SoundBathOneAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SoundBathOneAudioProcessor::getProgramName (int index)
{
    return {};
}

void SoundBathOneAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SoundBathOneAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(sampleRate, samplesPerBlock);
    //DBG("prepareToPlay called: sampleRate=" << sampleRate << ", blockSize=" << samplesPerBlock);
}

void SoundBathOneAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SoundBathOneAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SoundBathOneAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    //DBG("processBlock called");
    // Ensure all output channels are filled with a fixed signal for testing
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData[sample] = distribution(randomGenerator) * volume;
        }
    }
}


//==============================================================================
bool SoundBathOneAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SoundBathOneAudioProcessor::createEditor()
{
    return new SoundBathOneAudioProcessorEditor (*this);
}

//==============================================================================
void SoundBathOneAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SoundBathOneAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SoundBathOneAudioProcessor();
}

//CUSTOM========================================================================
//void setVolume(float newVolume) { volume = newVolume; }

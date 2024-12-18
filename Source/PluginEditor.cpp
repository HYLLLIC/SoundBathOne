/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SoundBathOneAudioProcessorEditor::SoundBathOneAudioProcessorEditor (SoundBathOneAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(volumeSlider);
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.onValueChange = [this]()
    {
        audioProcessor.setVolume(volumeSlider.getValue());
    };
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

SoundBathOneAudioProcessorEditor::~SoundBathOneAudioProcessorEditor()
{
}

//==============================================================================
void SoundBathOneAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Ambient Bloom", getLocalBounds(), juce::Justification::centred, 1);
}

void SoundBathOneAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    volumeSlider.setBounds(20, 20, getWidth() - 40, 30);
}

/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif,delaybuffer(2,1)
{
	delaylength = 0.5;
	drymix = 1.0;
	wetmix = 0.5;
	feedback = 0.5;
	delaybufferlength = 1;

	delayreadpostion = 0;
	delaywritepostion = 0;
	
}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
}

//==============================================================================
const String NewProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

int NewProjectAudioProcessor::getNumParameters() {
	return knumparameters;

}
float NewProjectAudioProcessor::getParameter(int index) {
	switch (index) {
	case kdrymixparam: return drymix;
	case kwetmixparam: return wetmix;
	case kfeedbackparam: return feedback;
	case kDelaylengthparam: return delaylength;
	default: return 0.0f;


	}

}
const String NewProjectAudioProcessor::getParameterName(int index) {

	switch (index)
	{
	case kdrymixparam: return"dry mix";
	case kwetmixparam: return"wet mix";
	case kfeedbackparam: return"feedback";
	case kDelaylengthparam: return"delay";
	default:
		break;

	}
	return String::empty;


}
void NewProjectAudioProcessor::setParameter(int index, float newValue) {
	switch (index)		
	{case kdrymixparam: 
		drymix = newValue;
		break;
	case kwetmixparam:
		wetmix = newValue;
		break;
	case kfeedbackparam:
			feedback = newValue;
			break;
	case kDelaylengthparam:
		delaylength = newValue;
		delayreadpostion = (int)(delaywritepostion - delaylength * getSampleRate() + delaybufferlength) % delaybufferlength;
		break;
	default:
		break;
	}
}

bool NewProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NewProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NewProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewProjectAudioProcessor::setCurrentProgram (int index)
{
}

const String NewProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void NewProjectAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void NewProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

	delaybufferlength = (int)(2.0*sampleRate);
	if (delaybufferlength<1)
	{
		delaybufferlength = 1;

	}
	delaybuffer.setSize(2, delaybufferlength);
	delaybuffer.clear();
	delayreadpostion = (int)(delaywritepostion - (delaylength*getSampleRate()) + delaybufferlength) % delaybufferlength;
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void NewProjectAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
	const int numsamples = buffer.getNumSamples();
	int channel, dpr, dpw;
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

		//buffer



		dpr = delayreadpostion;
		dpw = delaywritepostion;
		for (int i = 0; i < numsamples; ++i)
		{
			const float in = channelData[i];
			float out = 0.0;

			out = (drymix*in + wetmix * delaybuffer.getSample(channel, dpr));
			delaybuffer.setSample(channel, dpw, in + (delaybuffer.getSample(channel, dpr)*feedback));
			if (++dpr>=delaybufferlength)
			{
				dpr = 0;
			}
			if (++dpw>=delaybufferlength)
			{
				dpw = 0;
			}
			channelData[i] = out;
		}
        // ..do something to the data...
    }
	delayreadpostion = dpr;
	delaywritepostion = dpw;
}

//==============================================================================
bool NewProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
    return new NewProjectAudioProcessorEditor (*this);
}

//==============================================================================
void NewProjectAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NewProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}

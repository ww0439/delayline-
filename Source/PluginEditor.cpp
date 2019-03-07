/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p),delaylengthlabel("","Delay(second):"),
	feedbacklabel("","feedback:"),drymixlabel("","dry mix level:"),
	wetmixlabel("","delay mix level:")

{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
   
    addAndMakeVisible (delaylengthslider);
    delaylengthslider.setRange (0.01, 2, 0.01);
    delaylengthslider.setSliderStyle (Slider::Rotary);
    delaylengthslider.setTextBoxStyle (Slider::TextBoxLeft, false, 40, 30);
    delaylengthslider.setColour (Slider::thumbColourId, Colours::crimson);
    delaylengthslider.setColour (Slider::trackColourId, Colours::coral);
    delaylengthslider.setColour (Slider::rotarySliderFillColourId, Colours::aliceblue);
    delaylengthslider.setColour (Slider::rotarySliderOutlineColourId, Colours::aliceblue);
    delaylengthslider.setColour (Slider::textBoxTextColourId, Colours::blueviolet);
    delaylengthslider.setColour (Slider::textBoxBackgroundColourId, Colours::crimson);
    delaylengthslider.addListener (this);

 

   
    addAndMakeVisible (feedbackslider);
    feedbackslider.setRange (0, 0.995, 0.005);
    feedbackslider.setSliderStyle (Slider::Rotary);
    feedbackslider.setTextBoxStyle (Slider::TextBoxLeft, false, 40, 30);
    feedbackslider.setColour (Slider::thumbColourId, Colours::crimson);
    feedbackslider.setColour (Slider::trackColourId, Colours::coral);
    feedbackslider.setColour (Slider::rotarySliderFillColourId, Colours::aliceblue);
    feedbackslider.setColour (Slider::rotarySliderOutlineColourId, Colours::aliceblue);
    feedbackslider.setColour (Slider::textBoxTextColourId, Colours::blueviolet);
    feedbackslider.setColour (Slider::textBoxBackgroundColourId, Colours::crimson);
    feedbackslider.addListener (this);

    

   
    addAndMakeVisible (drymixslider);
    drymixslider.setRange (0, 1, 0.01);
    drymixslider.setSliderStyle (Slider::Rotary);
    drymixslider.setTextBoxStyle (Slider::TextBoxLeft, false, 40, 30);
    drymixslider.setColour (Slider::thumbColourId, Colours::crimson);
    drymixslider.setColour (Slider::trackColourId, Colours::coral);
    drymixslider.setColour (Slider::rotarySliderFillColourId, Colours::aliceblue);
    drymixslider.setColour (Slider::rotarySliderOutlineColourId, Colours::aliceblue);
    drymixslider.setColour (Slider::textBoxTextColourId, Colours::blueviolet);
    drymixslider.setColour (Slider::textBoxBackgroundColourId, Colours::crimson);
    drymixslider.addListener (this);

    

   
    addAndMakeVisible (wetmixslider);
    wetmixslider.setRange (0, 1, 0.01);
    wetmixslider.setSliderStyle (Slider::Rotary);
    wetmixslider.setTextBoxStyle (Slider::TextBoxLeft, false, 40, 30);
    wetmixslider.setColour (Slider::thumbColourId, Colours::crimson);
    wetmixslider.setColour (Slider::trackColourId, Colours::coral);
    wetmixslider.setColour (Slider::rotarySliderFillColourId, Colours::aliceblue);
    wetmixslider.setColour (Slider::rotarySliderOutlineColourId, Colours::aliceblue);
    wetmixslider.setColour (Slider::textBoxTextColourId, Colours::blueviolet);
    wetmixslider.setColour (Slider::textBoxBackgroundColourId, Colours::crimson);
    wetmixslider.addListener (this);

   

    addAndMakeVisible (delaylengthlabel);
    delaylengthlabel.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Regular"));
    delaylengthlabel.setJustificationType (Justification::centredLeft);
    delaylengthlabel.setEditable (false, false, false);
    delaylengthlabel.setColour (TextEditor::textColourId, Colours::black);
    delaylengthlabel.setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    

   
    addAndMakeVisible (feedbacklabel);
    feedbacklabel.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Regular"));
    feedbacklabel.setJustificationType (Justification::centredLeft);
    feedbacklabel.setEditable (false, false, false);
    feedbacklabel.setColour (TextEditor::textColourId, Colours::black);
    feedbacklabel.setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    

   
    addAndMakeVisible (drymixlabel);
    drymixlabel.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Regular"));
    drymixlabel.setJustificationType (Justification::centredLeft);
    drymixlabel.setEditable (false, false, false);
    drymixlabel.setColour (TextEditor::textColourId, Colours::black);
    drymixlabel.setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    


    addAndMakeVisible (wetmixlabel);
    wetmixlabel.setFont (Font (15.0f, Font::plain).withTypefaceStyle ("Regular"));
    wetmixlabel.setJustificationType (Justification::centredLeft);
    wetmixlabel.setEditable (false, false, false);
    wetmixlabel.setColour (TextEditor::textColourId, Colours::black);
    wetmixlabel.setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}
void NewProjectAudioProcessorEditor::sliderValueChanged(Slider*slider) {
	if (slider==&delaylengthslider)
	{
		processor.setParameterNotifyingHost(processor.kDelaylengthparam,(float)delaylengthslider.getValue());

	}
	else if (slider==&feedbackslider)
	{
		processor.setParameterNotifyingHost(processor.kfeedbackparam, (float)feedbackslider.getValue());

	}
	else if(slider==&drymixslider)
	{
		processor.setParameterNotifyingHost(processor.kdrymixparam, (float)drymixslider.getValue());
	}
	else if (slider==&wetmixslider)
	{
		processor.setParameterNotifyingHost(processor.kwetmixparam, (float)wetmixslider.getValue());
	}
	
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
    //delaylengthslider = nullptr;
    //feedbackslider = nullptr;
    //drymixslider = nullptr;
    //wetmixslider = nullptr;
    //delaylengthlabel = nullptr;
    //feedbacklabel = nullptr;
    //drymixlabel = nullptr;
    //wetmixlabel = nullptr;
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
	delaylengthslider.setBounds(8, 72, 150, 150);
	feedbackslider.setBounds(176, 72, 150, 150);
	wetmixlabel.setBounds(176, 256, 150, 40);
	drymixlabel.setBounds(8, 256, 150, 40);
	feedbacklabel.setBounds(168, 48, 150, 40);
	delaylengthlabel.setBounds(8, 48, 150, 40);
	wetmixslider.setBounds(176, 320, 150, 150);

	drymixslider.setBounds(8, 312, 150, 150);
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

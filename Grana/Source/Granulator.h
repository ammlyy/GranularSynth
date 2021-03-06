/*
  ==============================================================================

    Granulator.h
    Created: 20 Sep 2020 11:16:43am
    Author:  gabri

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Model.h"
#include "Grain.h"
#include "Extractor.h"


class Granulator
{
public:
    Granulator();
    ~Granulator();
    void initialize(int portionLength);
    void process(AudioBuffer<float>& outputBuffer, int numSamples, Extractor* featureExtractor);
    void setModel(Model* model);
    void setProcessorSampleRate(double processorSampleRate);

private:
    Array<Grain*> activeGrains;     // Grains to be played (extracted from the cloud)
    Model* model;
    int nextOnset;      //Tells us when the next grain should play
    int position;       //Position in the audio file
    int portionLength;
    double processorSampleRate;
    dsp::LinkwitzRileyFilter<float> hiPass;
};
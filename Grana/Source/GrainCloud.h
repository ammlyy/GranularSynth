/*
  ==============================================================================

    GrainCloud.h
    Created: 22 Sep 2020 5:20:42pm
    Author:  jacop

  ==============================================================================
*/

#pragma once
#include "Grain.h"
#include "SequenceStrategy.h"

class GrainCloud : juce::SynthesiserSound { // passive class just describes the sound - the rendering happens inside the Voice class

private: 
    Array<Grain*> grains; //juce array class
    SequenceStrategy strategy;

public: 
    GrainCloud();
    ~GrainCloud();
    

    //virtual functions inherited from SynthesiserSound 
    bool appliesToNote(int midiNoteNumber) override;
    bool appliesToChannel(int midiChannel) override;

    //custom functions
    void addGrain(Grain* g); // adds a grain to the stack
    void deleteGrain(Grain* g); // deletes a grain once its lifetime is over

};
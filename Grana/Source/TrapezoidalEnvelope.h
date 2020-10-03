/*
  ==============================================================================

    TrapezoidalEnvelope.h
    Created: 22 Sep 2020 5:27:29pm
    Author:  jacop

  ==============================================================================
*/

#define _USE_MATH_DEFINES
#include <cmath> 
#include "GrainEnvelope.h"
#include <iomanip> 
#include <vector>

#pragma once


class TrapezoidalEnvelope : public GrainEnvelope
{
public:
    
    float currentValue(float time) override;
    virtual float nextValue() override;

    static void reset();
    static void reset(float duration, int sampleRate, float mainLobeWidth);

    static TrapezoidalEnvelope* getInstance();
    static TrapezoidalEnvelope* setSampleRate(int sampleRate);
    static TrapezoidalEnvelope* setMainLobeWidth(int mainLobeWidth);
    static TrapezoidalEnvelope* setDuration(int duration);

    

private:
    TrapezoidalEnvelope();
    TrapezoidalEnvelope(int sampleRate);
    TrapezoidalEnvelope(float duration, int sampleRate);
    TrapezoidalEnvelope(float duration, int sampleRate, float mainLobeWidth);
    ~TrapezoidalEnvelope();

    void filterCreation();

    float duration; //duration in seconds
    int sampleRate;
    float mainLobeWidth;
    std::vector<double> kernel;
    static TrapezoidalEnvelope* instance;
};

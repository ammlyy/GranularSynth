/*
  ==============================================================================

    GaussianEnvelope.cpp
    Created: 22 Sep 2020 5:26:57pm
    Author:  jacop

  ==============================================================================
*/

#include "GaussianEnvelope.h"


GaussianEnvelope* GaussianEnvelope::instance = 0;


GaussianEnvelope::GaussianEnvelope() : sampleRate(0), duration(0), mainLobeWidth(0.95) {
	filterCreation();
}

GaussianEnvelope::GaussianEnvelope(int sampleRate) : duration(0), sampleRate(sampleRate), mainLobeWidth(0.95){
	filterCreation();
}

GaussianEnvelope::GaussianEnvelope(float duration, int sampleRate) : duration(duration), sampleRate (sampleRate), mainLobeWidth(0.95) {
	filterCreation();
}

GaussianEnvelope::GaussianEnvelope(float duration, int sampleRate, float mainLobeWidth) : duration(duration), sampleRate(sampleRate), mainLobeWidth(0.95) {
	filterCreation();
}





float GaussianEnvelope::currentValue(float time)
{
	return GKernel[(int) time* sampleRate];
}

GaussianEnvelope* GaussianEnvelope::getInstance()
{
	if (!instance)
		instance = new GaussianEnvelope();
	return instance;
}


void GaussianEnvelope::reset()
{
	if (instance != nullptr) {
		delete instance; // REM : it works even if the pointer is NULL (does nothing then)
		instance = nullptr; // so GetInstance will still work.
	}
}

GaussianEnvelope* GaussianEnvelope::setSampleRate(int sampleRate)
{
	GaussianEnvelope* instance = GaussianEnvelope::getInstance();
	instance->sampleRate = sampleRate;
	instance->filterCreation();
	return instance;
}

GaussianEnvelope* GaussianEnvelope::setDuration(int duration)
{
	GaussianEnvelope* instance = GaussianEnvelope::getInstance();
	instance->duration = duration;
	instance->filterCreation();
	return instance;
}

GaussianEnvelope* GaussianEnvelope::setMainLobeWidth(int mainLobeWidth)
{
	GaussianEnvelope* instance = GaussianEnvelope::getInstance();
	instance->mainLobeWidth = mainLobeWidth;
	instance->filterCreation();
	return instance;
}

void GaussianEnvelope::reset(float duration, int sampleRate, float mainLobeWidth)
{
	if (instance != nullptr) {
		delete instance; // REM : it works even if the pointer is NULL (does nothing then) so GetInstance will still work.
	}
	instance = new GaussianEnvelope(duration, sampleRate, mainLobeWidth);
}

// C++ prgroam to generate Gaussian filter 
// Function to create Gaussian filter 
void GaussianEnvelope::filterCreation()
{
	if (GKernel.size() > 0) { //clear previous kernel
		GKernel.clear();
	}

	int halfDuration = (int)duration / 2;
	int halfDurationPositive = halfDuration;
	// intialising standard deviation to 1.0 
	double sigma = mainLobeWidth * duration * sampleRate;
	double r, s = 2.0 * sigma * sigma;

	// generating kernel 

	if ((int)duration %2 == 0) { //this is done in order to solve the problem of having an array
								 //1 cell longer than needed when working with a even duration
		halfDurationPositive--;
	}

	for (int x = -halfDuration; x <= halfDurationPositive; x++) {
			GKernel.push_back((exp(-(x * x) / s)) / (M_PI * s));
			GKernel[x + halfDuration] -= GKernel[0];
			GKernel[x + halfDuration] /= 1 - GKernel[0];
	}
}

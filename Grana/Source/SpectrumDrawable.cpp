/*
  ==============================================================================

    SpectrumDrawable.cpp
    Created: 26 Oct 2020 11:33:12pm
    Author:  amere

  ==============================================================================
*/

#include "SpectrumDrawable.h"

SpectrumDrawable::SpectrumDrawable()
{
    setSize(200, 100);
    currentFrame = nullptr;
}

SpectrumDrawable::~SpectrumDrawable()
{
}

void SpectrumDrawable::paint(Graphics& g)
{
    g.fillAll(Colours::black);

    g.setOpacity(1.0f);
    g.setColour(Colours::limegreen);

    if (this->currentFrame != nullptr)
    {
        auto height = getLocalBounds().getHeight();
        auto width = getLocalBounds().getWidth();

        Path myPath;
        myPath.startNewSubPath(0, getHeight());
        int size = 256;
        for (int i = 0; i < size / 2; ++i)
        {
            myPath.quadraticTo(Point<float>((float)jmap(2 * i, 0, size, 0, width),
                jmap(*(currentFrame + 2 * i), 0.0f, 1.0f, (float)height, 0.0f)),
                Point<float>((float)jmap(2 * i + 1, 0, size, 0, width),
                    jmap(*(currentFrame + 2 * i + 1), 0.0f, 1.0f, (float)height, 0.0f)));
        }
        myPath.lineTo(getWidth(), getHeight());
        g.strokePath(myPath, PathStrokeType(3.0f));
        

        ColourGradient* gradient = new ColourGradient(Colours::grey.brighter(0.2), 0, getHeight(), Colours::aliceblue, 0, 0, false);
        gradient->clearColours();
        gradient->addColour(0, Colours::yellow);
        gradient->addColour(0.2, Colours::yellowgreen);
        gradient->addColour(0.4, Colours::greenyellow);
        gradient->addColour(0.7, Colours::limegreen);

        g.setGradientFill(*gradient);

        g.fillPath(myPath);

        delete gradient;
    }
}

void SpectrumDrawable::resized()
{
}

void SpectrumDrawable::drawNextFrame(float* bins)
{
    currentFrame = bins;
    repaint();
}

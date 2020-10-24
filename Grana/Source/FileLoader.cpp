/*
  ==============================================================================

    FileLoader.cpp
    Created: 21 Aug 2020 4:45:05pm
    Author:  daveg

  ==============================================================================
*/

#include "FileLoader.h"



FileLoader* FileLoader::instance = 0;

// Constructor
FileLoader::FileLoader()
{
    formatManager = new juce::AudioFormatManager();
    readerSource = new std::unique_ptr<juce::AudioFormatReaderSource>();
    thumbnailCache = new juce::AudioThumbnailCache(5);
    thumbnail = new juce::AudioThumbnail(512, *formatManager, *thumbnailCache);
    buffer = new juce::AudioBuffer<float>();
    sampleRate = 0;
}

// Destructor
FileLoader::~FileLoader() 
{
    delete formatManager;
    readerSource->reset(nullptr);
    delete thumbnailCache;
    delete thumbnail;
    delete buffer;
    if(hilbertTransform != nullptr)
        free(hilbertTransform);
}

// Get the instance of FileLoader
FileLoader* FileLoader::getInstance()
{
    if (!instance)
        instance = new FileLoader();
    return instance;
}

void FileLoader::resetInstance()
{
    if (instance != nullptr) {
        delete instance; // REM : it works even if the pointer is NULL (does nothing then)
        instance = nullptr; // so GetInstance will still work.
    }
}

// Read the file and loads it in the thumbnail (to display) and in the buffer
void FileLoader::loadWaveform(juce::File file)
{
    auto* reader = formatManager->createReaderFor(file);
    std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));                                                                                                          // [13]
    thumbnail->setSource(new juce::FileInputSource(file));
    readerSource->reset(newSource.release());
    buffer->setSize(reader->numChannels, reader->lengthInSamples);
    reader->read(buffer, 0, reader->lengthInSamples, 0, true, true);
    ceiledLength = pow(2, ceil(log2(buffer->getNumSamples())));
    hilbertTransform = (double*)calloc((size_t)(buffer->getNumChannels() * (size_t)2 * ceiledLength), sizeof(double));
    sampleRate = reader->sampleRate;

    for (int i = 0; i < this->buffer->getNumChannels(); i++) {
        for (int j = 0; j < buffer->getNumSamples(); j++) { //apply envelope
            if (hilbertTransform != NULL) {
                hilbertTransform[i * 2 * ceiledLength + j * 2] = buffer->getSample(i, j);
                hilbertTransform[i * 2 * ceiledLength + j * 2 + 1] = 0; //real signal ----> a value every two set to zero
            }
        }

        if (hilbertTransform != NULL)
            hilbert(&hilbertTransform[i * ceiledLength], ceiledLength); //Transform file
    }
}

// Drag & Drop funztion (calls loadWaveform to load the file)
void FileLoader::loadFile(const juce::String& gpath)
{
    auto file = juce::File(gpath);
    auto* formatReader = formatManager->createReaderFor(file);
    if (formatReader != nullptr) {
        loadWaveform(file);
    }
}

// GETTERS

juce::AudioFormatManager *FileLoader::getFormatManager() const
{
    return formatManager;
}

std::unique_ptr<juce::AudioFormatReaderSource> *FileLoader::getReaderSource() const
{
    return readerSource;
}

juce::AudioThumbnailCache* FileLoader::getThumbnailCache() const
{
    return thumbnailCache;
}

juce::AudioThumbnail* FileLoader::getThumbnail() const
{
    return thumbnail;
}

juce::AudioBuffer<float> *FileLoader::getAudioBuffer() const
{
    return buffer;
}

int FileLoader::getSampleRate()
{
    return this->sampleRate;
}

void FileLoader::setSampleRate(int sampleRate)
{
    this->sampleRate = sampleRate;
}

double* FileLoader::getHilbertTransform()
{
    return this->hilbertTransform;
}

int FileLoader::getCeiledLength()
{
    return this->ceiledLength;
}




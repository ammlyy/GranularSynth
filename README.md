# GranularSynth

This project was developed for the course of Sound Analysis Synthesis and Processing (SASP) held by Professor A. Sarti at the Politecnico of Milan.
Our goal was to achieve sound granulation, starting from a sample, with independent time-stretching  and frequency shifting using the [JUCE framework](https://juce.com/) and an Hilbert transform implementation taken from  [this software](https://www.cfa.harvard.edu/~spaine/am/)  developed by the Harvard-Smithsonian center for astrophysics. 


## Introduction
### Brief history of granular synthesis
The most common definition of sound is related to the concept of wave propagating in space and time. With the emerging developments in the electro-acoustic technologies raised in the XX century, the British physicist Dennis Gabor published in the late 40s three important papers, where he combines theories from quantum theory with practical experiment. 
His idea is that any continuous tone can be decomposed into a family of functions obtained by shifting in time and space a single acoustic grain. This theory was strongly affected by psychoacoustics since human hearing is not continuous and infinite in resolution.
So, from a representation of a signal in time domain, s(t), and from one in frequency domain S(f) derived from Fourier analysis, he created a mathematical abstraction able to map a signal and its energy onto an “effective time and effective spectral width”. Gabor’s analysis can be also thought as a series of localized Fourier transforms.[4]
This technique was born with the publishment by Dr. Ing. D. Gabor of the article "*Theory of communication*" [[1]] in  which, by the use of the [Hilbert Transform](https://en.wikipedia.org/wiki/Hilbert_transform) and its meaning in the Quantum Mechanichal Formalism,  he derived a new two-dimensional representation of signals with time and frequency as coordinates which he called "diagram of information".
Gabor noticed that any analysis requiring signal windowing (such as STFT), entails a strong relationship between time and frequency. High resolution in frequency requires long time windows, at cost of losing track of when exactly some event occurred. Vice versa, having high temporal resolution (short windows), implies losing frequency precision. This strong connection establish a sort of "uncertainty principle", setting the limits of our comprehension of acoustic quantas.

### Some math
Our approach to Gabor's brilliant article and our interpretation of frequency shifting with a parallelism to the quantum mechanical formalism ...
( COSE PAZZE JACO)
## Software implementation
### File controls
The user can upload a sample, and it will be used as a wavetable to be granulized.
Also the starting position and the size of the section can be controlled, so that the granulator will reproduce cyclically through the selected area. 
Also a master gain control is provided.
### Grain parameters 
The choice of grain parameters is fundamental to achieve different sonic behaviour of our grain cloud.

- **Grain density**: represents how many grains are generated each second. This parameter must be treated carefully since a great overlap of grains will result in some unpredictable clippings. Low values of density will create rhythmic patterns since the distance between successive grains becomes greater.
- **Grain size**: typical grain durations are between 5ms and 100ms. Just around 50ms we start hearing some stable pitch-like behaviour, while shorter segmenets will result in impulsive/noise-like sounds. 
Notice that the spectral bandwidth of the grain is inversely proportional its duration.
- **Envelope shape**: we created three different possible envelopes. The envelope width can be adjusted through the width slider.
   - The Gaussian envelope, as originally thought by Gabor to mathematically model its acoustic quantas. 
   - The raised-cosine envelope.
   - Trapezoidal envelope.

An interesting aspect related to grain enveloping is that they contribute to an AM effect [4].
### Grain playback

### Spectral Output

## Time-Frequency plane
This section is a 2-D canvas where the user can draw. Clicking will enable the control and the user can decide when a grain will be played and how much it will be shifted in frequency. 
## References

[[1]] Theory of Communication, D.Gabor, 

[[2]] Generation and Combination of Grains for Music Synthesis,
Douglas L. Jones and Thomas W. Parks

[[3]] Spectral Granular Synthesis, Stefano Fasciani

[4] Microsound, Curtis Roads, MIT Press, 2002

[1]: http://www.granularsynthesis.com/pdf/gabor.pdf 
[2]: https://www.jstor.org/stable/3679939?seq=1
[3]: https://www.researchgate.net/publication/326316857_Spectral_Granular_Synthesis
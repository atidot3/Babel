#ifndef AUDIOHANDLER_H_
#define AUDIOHANDLER_H_

#include "portaudio.h"

#include <iostream>
#include <string>

#define NUM_SECONDS   (4)
#define SAMPLE_RATE   (44100)
#define FRAMES_PER_BUFFER (1024)
#define SAMPLE_TYPE paInt24
#define NUM_CHANNELS    (2)

class AudioHandler
{
public:
	AudioHandler();
	~AudioHandler();

	bool 	initializePa();
	bool 	initStream();
	bool 	stopStream();
	bool	closeStream();
	bool	initChannels();

protected:
	PaStream  				*_stream;
	PaError  				err;
	int 					_readBufferSize;
	PaStreamParameters		_inputChannel;
	PaStreamParameters		_outputChannel;
	unsigned char			*_readBuffer;
};

#endif
#ifndef AUDIOHANDLER_H_
#define AUDIOHANDLER_H_

#include "../portaudio/include/portaudio.h"
#include "EncodeAudio.h"
#include "AudioSettings.h"

#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>

class AudioHandler
{
public:
	AudioHandler();
	~AudioHandler();

	bool 	initializeAudio();
	bool 	initStream();
	bool	closeStream();
	bool 	initInput();
	bool 	initOutput();
	bool	startStream();
	bool 	stopStream();
	bool 	terminatePa();
	bool	writeStream(unsigned char *);
	bool	readStream();
	void 	cleanReadBuffer();
	int 	getReadBufferSize() const;
	unsigned char 	*getReadBuffer() const;
	EncodeAudio 	*getEnc();
	int 			getSizeRec();
	void 			setSizeRec(int);
	int 			getSizePlay();
	void 			setSizePlay(int);
	unsigned char 	*getStaticBufferRec();
	unsigned char 	*getStaticBufferPlay();
	void 			errorAudio();
	bool 			isRunning();
	bool 			checkRun();

protected:
	PaStream  				*_stream;
	PaError  				err;
	int 					_readBufferSize;
	PaStreamParameters		_inputChannel;
	PaStreamParameters		_outputChannel;
	unsigned char			*_readBuffer;
	EncodeAudio 			*_enc;
	int 					_sizeRec;
	int 					_sizePlay;
	unsigned char 			_staticBufferRec[255 * 255];
	unsigned char 			_staticBufferPlay[255 * 255];
	PaStream				*_streamin;
	PaStream				*_streamout;
	bool 					_run;
	bool 					_started;
};

#endif
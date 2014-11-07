#include "../inc/AudioHandler.h"

AudioHandler::AudioHandler()
{
  _stream = NULL;
  _readBufferSize = FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_SIZE;
  _readBuffer= new unsigned char [_readBufferSize];
  this->_enc = new EncodeAudio;
  this->_streamin = NULL;
  this->_streamout = NULL;
  this->_started = false;
  this->_sizeRec = 0;
  this->_sizePlay = 0;
  this->_run = true;
}

AudioHandler::~AudioHandler()
{
	if (this->_enc)
		delete this->_enc;
	if (this->_streamin)
		Pa_CloseStream(this->_streamin);
	if (this->_streamout)
		Pa_CloseStream(this->_streamout);
	Pa_Terminate();
}

bool 	AudioHandler::initializeAudio()
{
	err = Pa_Initialize();
	if(err != paNoError)
	{
		this->errorAudio();
		return (false);
	}
	this->initInput();
	this->initOutput();
	this->initStream();
	return (true);
}

void		AudioHandler::errorAudio()
{
	if (err != paNoError)
	{
		this->_run = false;
		if (_streamin)
		{
			Pa_AbortStream(this->_streamin);
			Pa_CloseStream(this->_streamin);
		}
		if (this->_streamout)
		{
			Pa_AbortStream(this->_streamout);
			Pa_CloseStream(this->_streamout);
		}
		Pa_Terminate();
		std::cerr << "Error !" << std::endl;
		std::cerr << "Error number : " << err << std::endl;
		std::cerr << "Error message : " << Pa_GetErrorText(err) << std::endl;
	}
}

int 		recordCallback(const void *inputBuffer, void *outputBuffer,
    						unsigned long, const PaStreamCallbackTimeInfo* timeInfo,
    						PaStreamCallbackFlags statusFlags, void *userData)
{
	AudioHandler *dis = (AudioHandler*)userData;
    const SAMPLE *in = (const SAMPLE *)inputBuffer;
    int enc(0);

    (void) timeInfo;
    (void) statusFlags;
    (void) outputBuffer;

    unsigned char *tmp = dis->getEnc()->encodeAudio(in, &enc);

    if (dis->getSizeRec() + enc < 255*255)
    {
	    memcpy(dis->getStaticBufferRec() + dis->getSizeRec(), tmp, enc);
    	dis->setSizeRec(dis->getSizeRec() + enc);
    }
	
	return paContinue;
}

int			playCallback(	const void *inputBuffer, void *outputBuffer,
                            unsigned long,
							const PaStreamCallbackTimeInfo* timeInfo,
							PaStreamCallbackFlags statusFlags,
							void *userData)
{
	AudioHandler *dis = (AudioHandler*)userData;
	SAMPLE	*out = (SAMPLE *)outputBuffer;
	(void) timeInfo;
	(void) statusFlags;
	(void) inputBuffer;
    int tmp;

    tmp = dis->getSizePlay();
    dis->setSizePlay(0);

    if (tmp)
        dis->getEnc()->decodeAudio(dis->getStaticBufferPlay(), out, tmp);

	return paContinue;
}

bool 	AudioHandler::initStream()
{
	err = Pa_OpenStream(&this->_streamin, &this->_inputChannel, NULL, SAMPLE_RATE,
		FRAMES_PER_BUFFER, paClipOff, recordCallback, this);
	if(err != paNoError)
	{
		this->errorAudio();
		return (false);
	}
	err = Pa_OpenStream(&this->_streamout, NULL, &this->_outputChannel, SAMPLE_RATE,
		FRAMES_PER_BUFFER, paClipOff, playCallback, this);
	if (err != paNoError)
	{
		this->errorAudio();
		return (false);
	}
	return (true);
}

bool 	AudioHandler::initInput()
{
	if ((_inputChannel.device = Pa_GetDefaultInputDevice()) == paNoDevice)
	{
		this->errorAudio();
		return(false);
	}
	_inputChannel.channelCount = 1;
	_inputChannel.hostApiSpecificStreamInfo = NULL;
	_inputChannel.sampleFormat = SAMPLE_TYPE;
	_inputChannel.suggestedLatency = Pa_GetDeviceInfo(_inputChannel.device)->defaultHighInputLatency;
	return (true);
}

bool 	AudioHandler::initOutput()
{
	if ((_outputChannel.device = Pa_GetDefaultInputDevice()) == paNoDevice)
	{
		this->errorAudio();
		return (false);
	}
	_outputChannel.channelCount = 1;
	_outputChannel.hostApiSpecificStreamInfo = NULL;
	_outputChannel.sampleFormat = SAMPLE_TYPE;
	_outputChannel.suggestedLatency = Pa_GetDeviceInfo(_outputChannel.device)->defaultHighInputLatency;
	return (true);
}

bool 			AudioHandler::startStream()
{
	if ((this->err = Pa_StartStream(this->_streamin)) != paNoError)
	{
		this->errorAudio();
		this->_started = false;
		return (false);
	}
	if ((this->err = Pa_StartStream(this->_streamout)) != paNoError)
	{
		this->errorAudio();
		this->_started = false;
		return (false);
	}
	this->_started = true;
	return (true);
}

bool 			AudioHandler::stopStream()
{
	this->_sizeRec = 0;
	this->_sizePlay = 0;
	if (this->_streamin)
	{
		if ((this->err = Pa_StopStream(this->_streamin)) != paNoError)
		{
			this->errorAudio();
			this->_started = false;
			return (false);
		}
	}
	if (this->_streamout)
	{
		if ((this->err = Pa_StopStream(this->_streamout)) != paNoError)
		{
			this->errorAudio();
			this->_started = false;
			return (false);
		}
	}
	this->_started = false;
	return (true);
}

unsigned char 	*AudioHandler::getStaticBufferRec()
{
	return (unsigned char *)_staticBufferRec;
}

unsigned char 	*AudioHandler::getStaticBufferPlay()
{
	return (unsigned char *)_staticBufferPlay;
}

int 		AudioHandler::getSizeRec()
{
	return (this->_sizeRec);
}

void 		AudioHandler::setSizeRec(int sizeRec)
{
	this->_sizeRec = sizeRec;
}

int 		AudioHandler::getSizePlay()
{
	return (this->_sizePlay);
}

void 		AudioHandler::setSizePlay(int sizePlay)
{
	this->_sizeRec = sizePlay;
}

EncodeAudio 	*AudioHandler::getEnc()
{
	return (this->_enc);
}

bool 			AudioHandler::isRunning()
{
	return (this->_started);
}

bool 			AudioHandler::checkRun()
{
	return (this->_run);
}
#include "AudioHandler.h"

AudioHandler::AudioHandler()
{
  _stream = NULL;
  _readBufferSize = FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_SIZE;
  _readBuffer= new unsigned char [_readBufferSize];
}

AudioHandler::~AudioHandler()
{

}

bool 	AudioHandler::initializePa()
{
	err = Pa_Initialize();
	if(err != paNoError)
		return (false);
	return (true);
}

bool 	AudioHandler::initStream()
{
	if ((Pa_OpenStream(&_stream, &_inputChannel, &_outputChannel, SAMPLE_RATE,
		FRAMES_PER_BUFFER, paClipOff, NULL, NULL)) != paNoError)
		std::cerr << "Unable to open stream" << std::endl;
	err = Pa_StartStream(_stream);
	if(err != paNoError)
		std::cerr << "Unable to start stream" <<std::endl;
	return (true);
}

bool 	AudioHandler::stopStream()
{
	err = Pa_StopStream(_stream);
	if(err != paNoError)
		return (false);
	return (true);
}

bool 	AudioHandler::closeStream()
{
	err = Pa_CloseStream(_stream);
	if(err != paNoError)
		return (false);
	return (true);
}

bool 	AudioHandler::terminatePa()
{
	err = Pa_Terminate();
	if(err != paNoError)
		return (false);
	return (true);
}

bool 	AudioHandler::initChannels()
{
	if ((initializePa()) == false)
		std::cerr << "Unable to initialize PortAudio" << std::endl;
	if ((_inputChannel.device = Pa_GetDefaultInputDevice()) != paNoDevice)
	{
		_inputChannel.channelCount = 2;
		_inputChannel.hostApiSpecificStreamInfo = NULL;
		_inputChannel.sampleFormat = SAMPLE_TYPE;
		_inputChannel.suggestedLatency = Pa_GetDeviceInfo(_inputChannel.device)->defaultLowInputLatency;
	}
	if ((_outputChannel.device = Pa_GetDefaultInputDevice()) != paNoDevice)
	{
		_outputChannel.channelCount = 2;
		_outputChannel.hostApiSpecificStreamInfo = NULL;
		_outputChannel.sampleFormat = SAMPLE_TYPE;
		_outputChannel.suggestedLatency = Pa_GetDeviceInfo(_outputChannel.device)->defaultLowInputLatency;
	}
	return (true);
}

/**********************************************/

bool            AudioHandler::writeStream(unsigned char *buff)
{
	if ((Pa_WriteStream(_stream, buff, FRAMES_PER_BUFFER)) != paNoError)
	{
		std::cout << "Failed to write on stream" <<std::endl;
		return (false);
	}
	return (true);
}

bool            AudioHandler::readStream()
{
	if ((Pa_ReadStream(_stream, _readBuffer, FRAMES_PER_BUFFER)) != paNoError)
		return (false);
	return (true);
}

void            AudioHandler::cleanReadBuffer()
{
	for (int i = 0; i != _readBufferSize; i++)
		_readBuffer[i] = 0;
}

int             AudioHandler::getReadBufferSize() const
{
	return (_readBufferSize);
}

unsigned char*          AudioHandler::getReadBuffer() const
{
	return (_readBuffer);
}
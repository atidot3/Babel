#include "../inc/AudioHandler.h"

int 	main()
{
	AudioHandler *_audio = new AudioHandler();

	_audio->initializeAudio();
	_audio->startStream();
	_audio->stopStream();
	delete _audio;
	return (0);
}

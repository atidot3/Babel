#include "../inc/AudioHandler.h"

int 	main()
{
	AudioHandler *_audio = new AudioHandler();
    int i = 0;

	_audio->initializeAudio();
	_audio->startStream();
	while(_audio->checkRun() == true)
	{
		Pa_Sleep(1000);
		printf("%d\n", i);
		fflush(stdout);
		i++;
	}
	_audio->stopStream();
	delete _audio;
	return (0);
}

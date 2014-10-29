#include "AudioHandler.h"

int 	main()
{
	AudioHandler audio();

	audio.initializePa();
	audio.initStream();
	audio.initChannels();
	audio.writeStream();
	return (0);
}

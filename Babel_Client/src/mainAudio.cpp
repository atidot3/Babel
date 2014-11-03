#include "AudioHandler.h"

int 	main()
{
	AudioHandler audio;

	audio.initializePa();
	audio.initChannels();
	audio.initStream();
	audio.writeStream(audio.getReadBuffer());
	audio.readStream();
	return (0);
}

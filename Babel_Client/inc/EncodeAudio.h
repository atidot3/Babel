#ifndef _ENCODE_AUDIO_H_
# define _ENCODE_AUDIO_H_

#include <cstddef>

#include "AudioSettings.h"
#include "../opus-1.1/include/opus.h"

class EncodeAudio
{
public:
	EncodeAudio();
	~EncodeAudio();

	unsigned char	*encodeAudio(const SAMPLE *frame, int *retenc);
	void			decodeAudio(const unsigned char *data, SAMPLE *out, int retenc);

protected:
	OpusEncoder	*_enc;
	OpusDecoder	*_dec;
	opus_int32	_len;
	int			_err;
    char        *_compressed;
};

#endif
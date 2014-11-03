#include <stdio.h>
#include <math.h>
#include "../portaudio/include/portaudio.h"

    #if 1
    #define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
    #define SAMPLE_SILENCE  (0.0f)
    #define PRINTF_S_FORMAT "%.8f"
    #elif 1
    #define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;
    #define SAMPLE_SILENCE  (0)
    #define PRINTF_S_FORMAT "%d"
    #elif 0
    #define PA_SAMPLE_TYPE  paInt8
typedef char SAMPLE;
    #define SAMPLE_SILENCE  (0)
    #define PRINTF_S_FORMAT "%d"
	#endif

int main(int ac, char **av)
{
	PaStreamParameters inputParameters;
	PaStreamParameters outputParameters;
	double desiredSampleRate = 48000;

	PaError err;

	err = Pa_Initialize();
	if(err != paNoError)
	{
		fprintf(stderr, "Unable to intialize pa");
		return (-1);
	}

	inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
	if (inputParameters.device == paNoDevice)
	{
		fprintf(stderr,"Error: No default input device.\n");
	}
    inputParameters.channelCount = 2;                    /* stereo input */
	inputParameters.sampleFormat = PA_SAMPLE_TYPE;
	inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
	inputParameters.hostApiSpecificStreamInfo = NULL;

    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
	if (outputParameters.device == paNoDevice)
	{
		fprintf(stderr,"Error: No default output device\n");
	}
    outputParameters.channelCount = 2;                     /* stereo output */
	outputParameters.sampleFormat =  PA_SAMPLE_TYPE;
	outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
	outputParameters.hostApiSpecificStreamInfo = NULL;

	err = Pa_IsFormatSupported( &inputParameters, &outputParameters, desiredSampleRate );
	if( err == paFormatIsSupported )
	{
		printf( "Hooray!\n");
	}
	else
	{
		printf("Too Bad.\n");
	}
}
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "../portaudio/include/portaudio.h"

    #define SAMPLE_RATE  (48000)
    #define FRAMES_PER_BUFFER (512)
    #define NUM_CHANNELS    (2)
    #define NUM_SECONDS     (15)
    /*#define DITHER_FLAG     (paDitherOff)*/
    #define DITHER_FLAG     (0) 

    #define CHECK_OVERFLOW  (0)
    #define CHECK_UNDERFLOW  (0)


    #if 0
    #define PA_SAMPLE_TYPE  paFloat32
    #define SAMPLE_SIZE (4)
    #define SAMPLE_SILENCE  (0.0f)
    #define CLEAR(a) memset( (a), 0, FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_SIZE )
    #define PRINTF_S_FORMAT "%.8f"
    #elif 0
    #define PA_SAMPLE_TYPE  paInt16
    #define SAMPLE_SIZE (2)
    #define SAMPLE_SILENCE  (0)
    #define CLEAR(a) memset( (a), 0,  FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_SIZE )
    #define PRINTF_S_FORMAT "%d"
    #elif 1
    #define PA_SAMPLE_TYPE  paInt24
    #define SAMPLE_SIZE (3)
    #define SAMPLE_SILENCE  (0)
    #define CLEAR(a) memset( (a), 0,  FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_SIZE )
    #define PRINTF_S_FORMAT "%d"
    #elif 0
    #define PA_SAMPLE_TYPE  paInt8
    #define SAMPLE_SIZE (1)
    #define SAMPLE_SILENCE  (0)
    #define CLEAR(a) memset( (a), 0,  FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_SIZE )
    #define PRINTF_S_FORMAT "%d"
    #else
    #define PA_SAMPLE_TYPE  paUInt8
    #define SAMPLE_SIZE (1)
    #define SAMPLE_SILENCE  (128)
    #define CLEAR( a )
    {
      int i;
      
      for(i = 0; i < FRAMES_PER_BUFFER*NUM_CHANNELS; i++)
        ((unsigned char *)a)[i] = (SAMPLE_SILENCE);
    }
    #define PRINTF_S_FORMAT "%d"
    #endif


    int main(void)
    {
      PaStreamParameters inputParameters, outputParameters;
      PaStream *stream = NULL;
      PaError err;
      char *sampleBlock;
      int i;
      int numBytes;


      printf("patest_read_write_wire.c\n"); fflush(stdout);

      numBytes = FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_SIZE ;
      sampleBlock = (char *) malloc(numBytes);
      if(sampleBlock == NULL)
      {
        printf("Could not allocate record array.\n");
        exit(1);
      }
      CLEAR(sampleBlock);

      err = Pa_Initialize();
      if(err != paNoError)
        goto error;

      inputParameters.device = Pa_GetDefaultInputDevice();
      printf("Input device # %d.\n", inputParameters.device);
      printf("Input LL: %g s\n", Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency);
      printf("Input HL: %g s\n", Pa_GetDeviceInfo(inputParameters.device)->defaultHighInputLatency);
      inputParameters.channelCount = NUM_CHANNELS;
      inputParameters.sampleFormat = PA_SAMPLE_TYPE;
      inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultHighInputLatency;
      inputParameters.hostApiSpecificStreamInfo = NULL;

      outputParameters.device = Pa_GetDefaultOutputDevice();
      printf("Output device # %d.\n", outputParameters.device);
      printf("Output LL: %g s\n", Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency);
      printf("Output HL: %g s\n", Pa_GetDeviceInfo(outputParameters.device)->defaultHighOutputLatency);
      outputParameters.channelCount = NUM_CHANNELS;
      outputParameters.sampleFormat = PA_SAMPLE_TYPE;
      outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultHighOutputLatency;
      outputParameters.hostApiSpecificStreamInfo = NULL;

      err = Pa_OpenStream(&stream, &inputParameters, &outputParameters, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, NULL, NULL );
      if(err != paNoError)
        goto error;
   
      err = Pa_StartStream(stream);
      if(err != paNoError)
        goto error;
      printf("Wire on. Will run %d seconds.\n", NUM_SECONDS);
      fflush(stdout);
   
      for(i = 0; i < (NUM_SECONDS*SAMPLE_RATE) / FRAMES_PER_BUFFER; ++i)
      {
        err = Pa_WriteStream(stream, sampleBlock, FRAMES_PER_BUFFER);
        if(err && CHECK_UNDERFLOW)
          goto xrun;
        err = Pa_ReadStream(stream, sampleBlock, FRAMES_PER_BUFFER);
        if(err && CHECK_OVERFLOW)
          goto xrun;
      }
      err = Pa_StopStream(stream);
      if(err != paNoError)
        goto error;

      CLEAR(sampleBlock);
      /*
      err = Pa_StartStream(stream);
      if(err != paNoError) goto error;
      printf("Wire on. Interrupt to stop.\n");
      fflush(stdout);
   
      while(1)
      {
        err = Pa_WriteStream(stream, sampleBlock, FRAMES_PER_BUFFER);
        if(err)
          goto xrun;
        err = Pa_ReadStream(stream, sampleBlock, FRAMES_PER_BUFFER);
        if(err)
          goto xrun;
      }
      err = Pa_StopStream(stream);
      if(err != paNoError)
        goto error;
   
      Pa_CloseStream(stream);
      */
      free(sampleBlock);

      Pa_Terminate();
      return 0;

      xrun:
      if(stream)
      {
        Pa_AbortStream(stream);
        Pa_CloseStream(stream);
      }
      free(sampleBlock);
      Pa_Terminate();
      if(err & paInputOverflow)
        fprintf(stderr, "Input Overflow.\n");
      if(err & paOutputUnderflow)
        fprintf(stderr, "Output Underflow.\n");
      return -2;

      error:
      if(stream)
      {
        Pa_AbortStream(stream);
        Pa_CloseStream(stream);
      }
      free(sampleBlock);
      Pa_Terminate();
      fprintf(stderr, "An error occured while using the portaudio stream\n");
      fprintf(stderr, "Error number: %d\n", err);
      fprintf(stderr, "Error message: %s\n", Pa_GetErrorText(err));
      return -1;
    }
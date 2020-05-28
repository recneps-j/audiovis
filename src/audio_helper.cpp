#include "audio_helper.h"

#define SAMPLE_RATE 44100

bool InitPortAudio(void) {
    //Initialise portaudio API
    PaError err;
    err = Pa_Initialize();
    if( err != paNoError ) {
        return false;
    }
    return true;
}

bool StartReadingAudio(void) {
    PaStream *input_stream;
    PaError err;
    DSP_AudioData audio_input_data;
    /* Open an audio I/O stream. */
    err = Pa_OpenDefaultStream( &input_stream,
                                   2,          /* stereo input */
                                   2,          /* stereo output */
                                   paFloat32,  /* 32 bit floating point output */
                                   SAMPLE_RATE,
                                   paFramesPerBufferUnspecified,        /* frames per buffer, i.e. the number
                                                       of sample frames that PortAudio will
                                                       request from the callback. Many apps
                                                       may want to use
                                                       paFramesPerBufferUnspecified, which
                                                       tells PortAudio to pick the best,
                                                       possibly changing, buffer size.*/
                                    paCallback, /* this is your callback function */
                                    &audio_input_data ); /*This is a pointer that will be passed to
                                                       your callback*/
    err = Pa_StartStream( stream );
    while(Pa_IsStreamActive( stream ));
    err = Pa_StopStream( stream );

    /* -- don't forget to cleanup! -- */
    err = Pa_CloseStream( stream );
                                                
}



int paCallback( const void *inputBuffer, void *outputBuffer,
                unsigned long framesPerBuffer,
                const PaStreamCallbackTimeInfo* timeInfo,
                PaStreamCallbackFlags statusFlags,
                void *userData )
{
    /* Cast data passed through stream to our structure. */
    DSP_AudioData *data = (DSP_AudioData*)userData;
    float *out = (float*)outputBuffer;
    float *in = (float*)inputBuffer;
    unsigned int i;

    for( i=0; i<framesPerBuffer; i++ )
    {
        *out++ = *in++
    }
    return 0;
}
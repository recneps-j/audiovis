#include "audio_helper.h"
#include <iostream>
#include <thread>
#include <chrono>

#define SAMPLE_RATE 44100

bool AudioHelper::InitPortAudio( void ) {
    std::cout << "Initialising PortAudio\n";
    //Initialise portaudio API
    PaError err;
    err = Pa_Initialize();
    if( err != paNoError ) {
        return false;
    }
    return true;
}

bool AudioHelper::StopReadingAudio( void ) {
    PaError err;
    err = Pa_StopStream( this->input_stream );
    /* -- don't forget to cleanup! -- */
    err = Pa_CloseStream( this->input_stream );
    return 0;
}

int AudioHelper::paCallback( const void *inputBuffer, void *outputBuffer,
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
        // Left
        *out++ = *in++;
        // Right
        *out++ = *in++;
    }
    return 0;
}

bool AudioHelper::StartReadingAudio( void ) {
    PaError err;
    DSP_AudioData audio_input_data;
    /* Open an audio I/O stream. */
    err = Pa_OpenDefaultStream( &this->input_stream,
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
                                    this->paCallback, /* this is your callback function */
                                    &audio_input_data ); /*This is a pointer that will be passed to
                                                       your callback*/
    err = Pa_StartStream(input_stream);
    return true;                                      
}
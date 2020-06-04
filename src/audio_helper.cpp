#include "audio_helper.h"
#include <iostream>
#include <thread>
#include <chrono>

#define SAMPLE_RATE 44100

void AudioHelper::CheckDataReady(void) {
    if (this->input_stream_data.data_ready) {
        this->input_stream_data.data_ready = false;
        this->_eh->TriggerEvent(EventType::EVENT_AUDIO_DATA_READY);
    }
}

void AudioHelper::CatchEvent(EventType e) {
    switch (e) {
        case EventType::EVENT_STOP_AUDIO:
        case EventType::EVENT_QUIT:
            this->StopReadingAudio();
            break;
        default:
            break;
    }
}

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
    std::cout << "Stopping audio stream and cleaning up." << std::endl;
    PaError err;
    err = Pa_StopStream( this->input_stream );
    /* -- don't forget to cleanup! -- */
    err = Pa_CloseStream( this->input_stream );
    return 0;
}

int AudioHelper::paCallback(const void *input_buffer, void *output_buffer,
                            unsigned long frames_per_buffer,
                            const PaStreamCallbackTimeInfo* time_info,
                            PaStreamCallbackFlags status_flags,
                            void *user_data)
{
    /* Cast data passed through stream to our structure. */
    DSP_AudioData *input_stream_data = (DSP_AudioData*)user_data;
    float *out = (float*)output_buffer;
    float *in = (float*)input_buffer;
    unsigned int i;

    for( i=0; i<frames_per_buffer; i++ )
    {
        input_stream_data->sample_data[0].push_back(*in);
        // Left
        *out++ = *in++;

        input_stream_data->sample_data[1].push_back(*in);
        // Right
        *out++ = *in++;
    }

    // Might need to implement thread-safe access
    input_stream_data->data_ready = true;
    return 0;
}

bool AudioHelper::StartReadingAudio( void ) {
    PaError err;
    /* Open an audio I/O stream. */
    err = Pa_OpenDefaultStream(&this->input_stream,
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
                                    &(this->input_stream_data)); /*This is a pointer that will be passed to
                                                       your callback*/
    
    //Hard-code default setup
    this->input_stream_data.channels = 2;
    this->input_stream_data.sample_rate = SAMPLE_RATE;
    
    err = Pa_StartStream(input_stream);
    return true;                                      
}
#ifndef AUDIO_HELPER_H
#define AUDIO_HELPER_H

#include <portaudio.h>
#include <vector>

struct DSP_AudioData {
    std::vector<float> sample_data,
    float max=0;
    unsigned sample_rate=0
};

// enum InputStreamType {
//     kDefault
// };

bool InitPortAudio( void );
bool StartReadingAudio( void );
int paCallback( const void *inputBuffer, void *outputBuffer,
                                    unsigned long framesPerBuffer,
                                    const PaStreamCallbackTimeInfo* timeInfo,
                                    PaStreamCallbackFlags statusFlags,
                                    void *userData );


#endif // AUDIO_HELPER_H
#ifndef AUDIO_HELPER_H
#define AUDIO_HELPER_H

#include <vector>
#include <portaudio.h>

struct DSP_AudioData {
    std::vector<float> sample_data;
    float max;
    unsigned sample_rate;
};

// enum InputStreamType {
//     kDefault
// };
class AudioHelper {
private:
    PaStream *input_stream;
public:
    AudioHelper(){}
    static bool InitPortAudio( void );
    static int paCallback( const void *inputBuffer, void *outputBuffer,
                                    unsigned long framesPerBuffer,
                                    const PaStreamCallbackTimeInfo* timeInfo,
                                    PaStreamCallbackFlags statusFlags,
                                    void *userData );
    bool StartReadingAudio( void );
    bool StopReadingAudio( void );
    
};




#endif // AUDIO_HELPER_H
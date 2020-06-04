#ifndef AUDIO_HELPER_H
#define AUDIO_HELPER_H

#include <vector>
#include <portaudio.h>
#include "events.h"

struct DSP_AudioData {
    //[0] for left channel, [1] for right channel
    typedef std::map<int, std::vector<float>> SampleData;
    SampleData sample_data;
    unsigned channels;
    float max;
    unsigned sample_rate;
    bool data_ready=false;
};

class AudioHelper : public Observer {
private:
    PaStream *input_stream;
    EventHandler* _eh;
public:
    DSP_AudioData input_stream_data;
    
    AudioHelper(EventHandler* eh){ this->_eh = eh; };
    virtual void CatchEvent(EventType e) override;
    static bool InitPortAudio(void);
    static int paCallback(const void *input_buffer, void *output_buffer,
                                    unsigned long frames_per_buffer,
                                    const PaStreamCallbackTimeInfo* time_info,
                                    PaStreamCallbackFlags status_flags,
                                    void *user_data);
                                    
    bool StartReadingAudio(void);
    bool StopReadingAudio(void);
    void CheckDataReady(void);
};




#endif // AUDIO_HELPER_H
#ifndef VISUAL_H
#define VISUAL_H

#include "events.h"
#include "audio_helper.h"
#include <SDL.h>

class VisualEffectProcessor : public Observer {
public:
    DSP_AudioData* _input_data; 
    virtual void DoProcessing(SDL_Renderer* renderer) = 0;
    virtual void DoProcessingDummy(SDL_Renderer* renderer) = 0;
    virtual void CatchEvent(EventType e) override;
    virtual ~VisualEffectProcessor(){};
    void StopProcessing(void);
};

class OscilloscopeEffect : public VisualEffectProcessor {
private:
    SDL_Rect rect_to_draw;
public:
    OscilloscopeEffect(DSP_AudioData* input_data) { this->_input_data = input_data; 
                                                    this->rect_to_draw.x = 0;
                                                    this->rect_to_draw.y = 0;
                                                    this->rect_to_draw.w = 32;
                                                    this->rect_to_draw.h = 32;}
    virtual void DoProcessing(SDL_Renderer* renderer) override;
    virtual void DoProcessingDummy(SDL_Renderer* renderer) override;
};

class CircleEffect : public VisualEffectProcessor {
private:
public:
    CircleEffect(DSP_AudioData* input_data) { this->_input_data = input_data; }
    virtual void DoProcessing(SDL_Renderer* renderer) override;
    virtual void DoProcessingDummy(SDL_Renderer* renderer) override;

};

#endif // VISUAL_H
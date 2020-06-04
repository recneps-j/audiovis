#include "visual.h"
#include <iostream>

void OscilloscopeEffect::CatchEvent(EventType e) {
    switch (e) {
        case EventType::EVENT_QUIT:
            this->StopProcessing();
            break;
        default:
            break;
    }
}

void OscilloscopeEffect::DoProcessing(SDL_Renderer* renderer) {
    this->_input_data->sample_data[0].clear();
    this->_input_data->sample_data[1].clear();
}
void OscilloscopeEffect::DoProcessingDummy(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &(this->rect_to_draw));
    this->rect_to_draw.x += 1;
    this->rect_to_draw.y += 1;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void OscilloscopeEffect::StopProcessing(void) {
    return;
}

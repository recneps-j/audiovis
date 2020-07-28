#include "visual.h"
#include "window.h"
#include <cmath>
#include <iostream>

void VisualEffectProcessor::CatchEvent(EventType e) {
    switch (e) {
        case EventType::EVENT_QUIT:
            this->StopProcessing();
            break;
        default:
            break;
    }
}

void OscilloscopeEffect::DoProcessing(SDL_Renderer* renderer) {
    // std::cout << "TRYING TO DRAW SAMPLES" << std::endl;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    int buffer_len = this->_input_data->sample_data[0].size();
    float x_step = (float)SCREEN_WIDTH/(float)buffer_len;

    for (int i=0;i<buffer_len;i++) {
        SDL_RenderDrawPoint(renderer, (int)(x_step*i), (int)(SCREEN_HEIGHT/2 + this->_input_data->sample_data[0][i]*SCREEN_HEIGHT));
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

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

void VisualEffectProcessor::StopProcessing(void) {
    return;
}

void CircleEffect::DoProcessing(SDL_Renderer* renderer) {
    // std::cout << "TRYING TO DRAW SAMPLES" << std::endl;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    int buffer_len = this->_input_data->sample_data[0].size();
    int x_offset = SCREEN_WIDTH/2;
    int y_offset = SCREEN_HEIGHT/2;

    float circle_step = 2.0 * M_PI / (float)buffer_len;
    
    for (int i=0;i<buffer_len;i++) {
        float angle = circle_step * (float)i;
        SDL_RenderDrawPoint(renderer, x_offset + (this->_input_data->sample_data[0][i] * y_offset * (float)cos(angle)), y_offset + (this->_input_data->sample_data[0][i] * y_offset * (float)sin(angle)));
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    this->_input_data->sample_data[0].clear();
    this->_input_data->sample_data[1].clear();
}

void CircleEffect::DoProcessingDummy(SDL_Renderer* renderer) {
    return;
}

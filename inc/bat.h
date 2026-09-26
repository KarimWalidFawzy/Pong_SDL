#pragma once

#include <SDL3/SDL.h>

class Bat {
    float x;
    float y;
    float width;
    float height;
    float speed;

public:
    Bat(float x, float y, float width = 14.0f, float height = 90.0f);

    void update(float direction, float deltaTime, float screenHeight);
    void draw(SDL_Renderer* renderer) const;
    SDL_FRect getRect() const;
};
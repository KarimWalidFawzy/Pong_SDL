#include "bat.h"

Bat::Bat(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height), speed(430.0f) {
}

void Bat::update(float direction, float deltaTime, float screenHeight) {
    y += direction * speed * deltaTime;
    if (y < 0.0f) {
        y = 0.0f;
    }
    if (y + height > screenHeight) {
        y = screenHeight - height;
    }
}

void Bat::draw(SDL_Renderer* renderer) const {
    SDL_FRect rect = getRect();
    SDL_RenderFillRect(renderer, &rect);
}

SDL_FRect Bat::getRect() const {
    return {x, y, width, height};
}
#pragma once

#include <SDL3/SDL.h>

class Ball {
	float x;
	float y;
	float velocityX;
	float velocityY;
	float size;

public:
	Ball(float x, float y, float size = 14.0f);

	void reset(float centerX, float centerY, float direction);
	void update(float deltaTime);
	void bounceVertical();
	void bounceHorizontal();
	void draw(SDL_Renderer* renderer) const;
	SDL_FRect getRect() const;
	float getX() const;
	float getY() const;
	float getVelocityX() const;
};

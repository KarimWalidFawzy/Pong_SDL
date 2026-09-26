#include "ball.h"

namespace {
constexpr float initialSpeedX = 330.0f;
constexpr float initialSpeedY = 180.0f;
}

Ball::Ball(float x, float y, float size)
	: x(x), y(y), velocityX(initialSpeedX), velocityY(initialSpeedY), size(size) {
}

void Ball::reset(float centerX, float centerY, float direction) {
	x = centerX - size / 2.0f;
	y = centerY - size / 2.0f;
	velocityX = initialSpeedX * direction;
	velocityY = initialSpeedY;
}

void Ball::update(float deltaTime) {
	x += velocityX * deltaTime;
	y += velocityY * deltaTime;
}

void Ball::bounceVertical() {
	velocityY = -velocityY;
}

void Ball::bounceHorizontal() {
	velocityX = -velocityX;
}

void Ball::draw(SDL_Renderer* renderer) const {
	SDL_FRect rect = getRect();
	SDL_RenderFillRect(renderer, &rect);
}

SDL_FRect Ball::getRect() const {
	return {x, y, size, size};
}

float Ball::getX() const {
	return x;
}

float Ball::getY() const {
	return y;
}

float Ball::getVelocityX() const {
	return velocityX;
}

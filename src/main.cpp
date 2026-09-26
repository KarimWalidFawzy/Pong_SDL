#include <SDL3/SDL.h>
#include <algorithm>
#include <cstdio>

#include "ball.h"
#include "bat.h"

namespace {
constexpr int screenWidth = 960;
constexpr int screenHeight = 640;
constexpr int winningScore = 7;

bool overlaps(const SDL_FRect& first, const SDL_FRect& second) {
    return first.x < second.x + second.w && first.x + first.w > second.x &&
           first.y < second.y + second.h && first.y + first.h > second.y;
}
}

int main(int, char**) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Pong", screenWidth, screenHeight, 0);
    SDL_Renderer* renderer = window == nullptr ? nullptr : SDL_CreateRenderer(window, nullptr);
    if (renderer == nullptr) {
        std::fprintf(stderr, "SDL setup failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Bat player(36.0f, screenHeight / 2.0f - 45.0f);
    Bat opponent(screenWidth - 50.0f, screenHeight / 2.0f - 45.0f);
    Ball ball(screenWidth / 2.0f, screenHeight / 2.0f);
    int playerScore = 0;
    int opponentScore = 0;
    bool isRunning = true;
    Uint64 previousTicks = SDL_GetTicks();

    while (isRunning) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT ||
                (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)) {
                isRunning = false;
            }
        }

        Uint64 currentTicks = SDL_GetTicks();
        float deltaTime = static_cast<float>(currentTicks - previousTicks) / 1000.0f;
        previousTicks = currentTicks;
        deltaTime = std::min(deltaTime, 0.05f);

        const bool* keys = SDL_GetKeyboardState(nullptr);
        float playerDirection = static_cast<float>(keys[SDL_SCANCODE_S]) -
                                static_cast<float>(keys[SDL_SCANCODE_W]);
        player.update(playerDirection, deltaTime, static_cast<float>(screenHeight));

        SDL_FRect opponentRect = opponent.getRect();
        float opponentDirection = 0.0f;
        if (ball.getY() + 7.0f < opponentRect.y + opponentRect.h / 2.0f) {
            opponentDirection = -1.0f;
        } else if (ball.getY() > opponentRect.y + opponentRect.h / 2.0f) {
            opponentDirection = 1.0f;
        }
        opponent.update(opponentDirection, deltaTime, static_cast<float>(screenHeight));

        ball.update(deltaTime);
        SDL_FRect ballRect = ball.getRect();
        if (ballRect.y <= 0.0f || ballRect.y + ballRect.h >= screenHeight) {
            ball.bounceVertical();
        }

        if ((ball.getVelocityX() < 0.0f && overlaps(ballRect, player.getRect())) ||
            (ball.getVelocityX() > 0.0f && overlaps(ballRect, opponent.getRect()))) {
            ball.bounceHorizontal();
        }

        if (ballRect.x + ballRect.w < 0.0f) {
            ++opponentScore;
            ball.reset(screenWidth / 2.0f, screenHeight / 2.0f, 1.0f);
        } else if (ballRect.x > screenWidth) {
            ++playerScore;
            ball.reset(screenWidth / 2.0f, screenHeight / 2.0f, -1.0f);
        }

        char title[64];
        std::snprintf(title, sizeof(title), "Pong  %d - %d", playerScore, opponentScore);
        SDL_SetWindowTitle(window, title);
        if (playerScore >= winningScore || opponentScore >= winningScore) {
            isRunning = false;
        }

        SDL_SetRenderDrawColor(renderer, 14, 18, 28, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 236, 240, 241, 255);
        player.draw(renderer);
        opponent.draw(renderer);
        ball.draw(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
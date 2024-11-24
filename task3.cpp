#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool isRunning;
Uint32 startTime;
Uint32 currentTime;
bool collision = false;

const int movingBallRadius = 50;
int movingBallX = -2 * movingBallRadius;
int movingBallY = SCREEN_HEIGHT / 2;

const int movableBallRadius = 50;
int movableBallX = SCREEN_WIDTH / 2;
int movableBallY = SCREEN_HEIGHT - movableBallRadius;

bool initializeWindow() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Error: SDL initialization failed\nSDL Error: " << SDL_GetError() << endl;
        return false;
    }

    window = SDL_CreateWindow("Collision", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        cout << "Error: Failed to create window\nSDL Error: " << SDL_GetError() << endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cout << "Error: Failed to create renderer\nSDL Error: " << SDL_GetError() << endl;
        return false;
    }

    return true;
}

void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    if (movableBallY > movableBallRadius) movableBallY -= 10;
                    break;
                case SDLK_LEFT:
                    if (movableBallX > movableBallRadius) movableBallX -= 10;
                    break;
                case SDLK_RIGHT:
                    if (movableBallX < SCREEN_WIDTH - movableBallRadius) movableBallX += 10;
                    break;
                case SDLK_DOWN:
                    if (movableBallY < SCREEN_HEIGHT - movableBallRadius) movableBallY += 10;
                    break;
                default:
                    break;
            }
        }
    }
}

bool checkCollision() {
    int distanceSquared = (movingBallX - movableBallX) * (movingBallX - movableBallX) + (movingBallY - movableBallY) * (movingBallY - movableBallY);
    int sumRadiiSquared = (movingBallRadius + movableBallRadius) * (movingBallRadius + movableBallRadius);
    return distanceSquared <= sumRadiiSquared;
}

void incrementMovingBall() {
    movingBallX += 20;
    if (movingBallX >= SCREEN_WIDTH + movingBallRadius) movingBallX = -movingBallRadius;
}

void update() {
    currentTime = SDL_GetTicks();
    Uint32 elapsedTime = currentTime - startTime;
    if (elapsedTime >= 16) {
        incrementMovingBall();
        startTime = currentTime;
        collision = checkCollision();
    }
}

void drawFilledCircle(int cx, int cy, int radius) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, cx + x, cy + y);
            }
        }
    }
}

void render() {
    SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255);
    SDL_RenderClear(renderer);

    if (collision) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    }
    drawFilledCircle(movingBallX, movingBallY, movingBallRadius);

    if (collision) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    }
    drawFilledCircle(movableBallX, movableBallY, movableBallRadius);

    SDL_RenderPresent(renderer);
}

void cleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char** argv) {
    if (!initializeWindow()) {
        return -1;
    }

    isRunning = true;
    startTime = SDL_GetTicks();

    while (isRunning) {
        handleEvents();
        update();
        render();
    }

    cleanup();

    return 0;
}

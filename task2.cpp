#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 450

SDL_Window* mainWindow = NULL;
SDL_Renderer* mainRenderer = NULL;
bool running;
Uint32 startTicks;
Uint32 currentTicks;

const int CIRCLE_INITIAL_RADIUS = 2;
int circleRadius = CIRCLE_INITIAL_RADIUS;
const int CIRCLE_CENTER_X = WINDOW_WIDTH / 2;
const int CIRCLE_CENTER_Y = WINDOW_HEIGHT / 2;

bool initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Error: SDL initialization failed\nSDL Error: " << SDL_GetError() << endl;
        running = false;
        return false;
    }

    mainWindow = SDL_CreateWindow("Blinking Circle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!mainWindow) {
        cout << "Error: Failed to create window\nSDL Error: " << SDL_GetError() << endl;
        running = false;
        return false;
    }

    mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!mainRenderer) {
        cout << "Error: Failed to create renderer\nSDL Error: " << SDL_GetError() << endl;
        running = false;
        return false;
    }

    return true;
}

void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }
}

void setupCircle() {
    circleRadius = CIRCLE_INITIAL_RADIUS;
}

void increaseRadius() {
    circleRadius += 2;
    if (circleRadius >= min(WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2)) {
        circleRadius = CIRCLE_INITIAL_RADIUS;
    }
}

void update() {
    currentTicks = SDL_GetTicks();
    Uint32 elapsed = currentTicks - startTicks;
    if (elapsed >= 16) {
        increaseRadius();
        startTicks = currentTicks;
    }
}

void drawCircle() {
    for (int x = -circleRadius; x <= circleRadius; x++) {
        for (int y = -circleRadius; y <= circleRadius; y++) {
            if (x * x + y * y <= circleRadius * circleRadius) {
                SDL_RenderDrawPoint(mainRenderer, CIRCLE_CENTER_X + x, CIRCLE_CENTER_Y + y);
            }
        }
    }
}

void render() {
    SDL_SetRenderDrawColor(mainRenderer, 0, 128, 128, 255); // Teal for background
    SDL_RenderClear(mainRenderer);

    SDL_SetRenderDrawColor(mainRenderer, 255, 215, 0, 255); // Gold for circle
    drawCircle();

    SDL_RenderPresent(mainRenderer);
}

void cleanup() {
    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
}

int main(int argc, char** argv) {
    running = initialize();
    setupCircle();
    startTicks = SDL_GetTicks();

    while (running) {
        handleEvents();
        update();
        render();
    }

    cleanup();

    return 0;
}

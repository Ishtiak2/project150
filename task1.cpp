#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

SDL_Window* mainWindow = NULL;
SDL_Renderer* mainRenderer = NULL;
bool running;
int colorRed = 0;
Uint32 startTicks;
Uint32 currentTicks;
const int radius=150;
const  int centerX=WINDOW_WIDTH / 2;
const int centerY=WINDOW_HEIGHT / 2;


bool initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Error: SDL initialization failed\nSDL Error: " << SDL_GetError() << endl;
        running = false;
        return false;
    }

    mainWindow = SDL_CreateWindow("Circle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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


void update() {
  
}

void drawCircle() {
    for (int x = -radius; x <= radius; x++) {
        for (int y = -radius; y <= radius; y++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(mainRenderer, centerX + x,centerY + y);
            }
        }
    }
}

void render() {
    SDL_SetRenderDrawColor(mainRenderer, 135, 206, 235, 255); // Light Sky Blue for background
    SDL_RenderClear(mainRenderer);

    SDL_SetRenderDrawColor(mainRenderer, 255, 0, 0, 255); // Red for circle
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
  
    startTicks = SDL_GetTicks();

    while (running) {
        handleEvents();
        update();
        render();
    }

    cleanup();

    return 0;
}

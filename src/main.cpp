#include <iostream>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "assert.h"
#include "Logger.h"

#define CGAME_DEFAULT_WINDOW_WIDTH 1080
#define CGAME_DEFAULT_WINDOW_HEIGHT 720

using namespace handspired;


int main() {
	Logger * const logger = new Logger(LOGGER_DEBUG);
	
	logger->info("Game started");

	int err;

	// Initialize SDL
	err = SDL_Init(SDL_INIT_VIDEO);
	if (err == -1) {
		logger->errorf("Failed trying to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	// Create main game window
	SDL_Window *window = SDL_CreateWindow(
		"handspired",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		CGAME_DEFAULT_WINDOW_WIDTH,
		CGAME_DEFAULT_WINDOW_HEIGHT,
		SDL_WINDOW_OPENGL
	);
	if (window == NULL) {
		logger->errorf("Failed trying to create SDL window: %s", SDL_GetError());
		return 1;
	}
	logger->info("SDL window created");

	// Create renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	if (window == NULL) {
		logger->errorf("Failed trying to create SDL renderer: %s", SDL_GetError());
		return 1;
	}
	SDL_RenderSetLogicalSize(
		renderer,
		CGAME_DEFAULT_WINDOW_WIDTH,
		CGAME_DEFAULT_WINDOW_HEIGHT
	);
	logger->info("SDL renderer created");

	bool running = true;
	uint64_t frame_count = 0;
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				logger->info("Received quit event, exiting now");
				running = false;
			}
		}

		SDL_Delay(16);
		frame_count++;
	}

	return 0;
}

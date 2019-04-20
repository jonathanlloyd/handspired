#include <iostream>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "assert.h"
#include "GameCode.h"
#include "Logger.h"

#define LOG_LEVEL LOGGER_DEBUG
#define CGAME_DEFAULT_WINDOW_WIDTH 1080
#define CGAME_DEFAULT_WINDOW_HEIGHT 720

using namespace handspired;


int main() {
	Logger * const logger = new Logger(LOG_LEVEL);
	
	logger->info("Game started");

	int err;

	// Initialize SDL
	err = SDL_Init(SDL_INIT_VIDEO);
	if (err < 0) {
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

	uint32_t target_ms = ((1.0 / 60.0) * 1000.0);

	bool running = true;
	uint64_t frame_count = 0;
	uint32_t time_last_flipped = 0;
	uint32_t time_last_loop_ended = 0;
	// TODO(@jonathanlloyd): Move state off the stack?
	GameState game_state = {};
	ControllerState controller_state = {};

	while (running) {
		// Process events
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					logger->info("Received quit event, exiting now");
					running = false;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_SPACE) {
						controller_state.action_button_down = true;
					}
					break;
				case SDL_KEYUP:
					if (event.key.keysym.sym == SDLK_SPACE) {
						controller_state.action_button_down = false;
					}
					break;
			}
		}

		// Get input
		SDL_GetMouseState(&controller_state.mouse_x, &controller_state.mouse_y);
		logger->debugf(
			"Mouse: x=%d, y=%d",
			controller_state.mouse_x,
			controller_state.mouse_y
		);
		logger->debugf(
			"Action button down: %s",
			controller_state.action_button_down ? "true" : "false"
		);

		update_and_render(&game_state, &controller_state);

		/**
		 * TODO(jonathan): Look into a better way of doing this that doesn't
		 *                 hammer the CPU.
		 */
		uint32_t target_time = time_last_flipped + target_ms;
		while (true) {
			if (SDL_GetTicks() >= target_time) {
				break;
			}
		}
		time_last_flipped = SDL_GetTicks();

		uint32_t current_time = SDL_GetTicks();
		int32_t loop_time = current_time - time_last_loop_ended;
		logger->debugf("Loop time: %dms", loop_time);
		time_last_loop_ended = current_time;
		frame_count++;
	}

	return 0;
}

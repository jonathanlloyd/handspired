#ifndef GAMECODE_H
#define GAMECODE_H

typedef struct GameState {
	int player_x;
	int player_y;
} GameState;

typedef struct ControllerState {
	int mouse_x;
	int mouse_y;
	bool action_button_down;
} ControllerState;

void update_and_render(
	GameState *game_state,
	ControllerState *controller_state
);

#endif

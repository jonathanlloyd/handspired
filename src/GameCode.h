#ifndef GAMECODE_H
#define GAMECODE_H

typedef struct GameState {
	int player_x;
	int player_y;
} GameState;

void update_and_render(GameState *game_state);

#endif

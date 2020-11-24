#include "game_utils.h"

void toggleBool(bool& v)
{
	v = !v;
}

void toggleGameState(GameState& state) 
{
	if (state == GameState::PLAYING) 
		state = GameState::PAUSE;

	else if (state == GameState::PAUSE)
		state = GameState::PLAYING;
}
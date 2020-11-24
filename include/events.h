#pragma once

#include <raylib.h>

#include "game_utils.h"

class GameEngine;

#define P1_SHOOT		  KEY_F
#define P1_FORWARD		  KEY_R
#define P1_LEFT			  KEY_D
#define P1_RIGHT		  KEY_G
#define P1_TELEPORT		  KEY_E
#define P1_TELEPORT_BIS   KEY_T

#define P2_SHOOT		  KEY_K
#define P2_FORWARD		  KEY_I
#define P2_LEFT			  KEY_J
#define P2_RIGHT		  KEY_L
#define P2_TELEPORT		  KEY_U
#define P2_TELEPORT_BIS   KEY_O

#define GAME_PAUSE        KEY_SPACE
#define GAME_DEBUG        KEY_C
#define GAME_START_SOLO   KEY_F
#define GAME_START_COOP   KEY_K
#define GAME_OVER_TO_MAIN KEY_ESCAPE

void handleEvents(GameEngine* engine);
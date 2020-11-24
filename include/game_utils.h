#pragma once

#include "math_toolbox.h"
#include "raylib.h"

#define LEFT_BORDER 70
#define RIGHT_BORDER 580
#define TOP_BORDER 70
#define BOT_BORDER 720

enum class GameState
{
    MAIN,
    PLAYING,
    PAUSE,
    GAMEOVER
};

enum class EntitySize
{
    SMALL  = 1,
    MEDIUM = 2,
    BIG    = 3
};

enum class GameType
{
    SINGLEPLAYER = 1,
    COOP = 2
};

enum class EnemyType
{
    FLOATING_MINE,
    MAGNETIC_MINE,
    FIREBALL_MINE,
    MAG_FIRE_MINE,
    MINELAYER
};
struct Sprite2D
{
    //Tile position in the tileset
    int   tileLine;
    int   tileColumn;

    //Origin (dest rect width and height divided per 2)
    float2 origin;
    Color color = RAYWHITE;
};

void toggleBool(bool& v);

void toggleGameState(GameState& state);
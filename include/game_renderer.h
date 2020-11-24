#pragma once

#include <raylib.h>

#include <Vector>
#include "game_utils.h"

class Entity;
class Projectile;
class PlayerController;
class EnemySpawnPoint;

class GameRenderer 
{
    public:
        GameRenderer();
        ~GameRenderer();

        void drawMap();
        void drawBorder();
        void drawEntity(Entity* entity);
        void drawEntityDebug(Entity* entity);
        void drawProjectile(Projectile* projectile);
        void drawPlayerInfo(PlayerController* player, int padding);
        void drawSpawnPoint(EnemySpawnPoint* spawnPoint);
        void drawScore(float2 position, int score);
        void drawGameOver();
        void drawPauseMenu();
        void drawMainMenu();
    private:
        Texture2D m_mapBackground;
        Texture2D m_mapForground;
        Texture2D m_tileset;
};
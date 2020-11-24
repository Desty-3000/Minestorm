
#include "game_renderer.h"

#include "entity.h"
#include "player.h"
#include "projectile.h"
#include "mines.h"

#include <iostream>

GameRenderer::GameRenderer() // Load ressources from files
{
	m_mapBackground = LoadTexture("Assets/minestorm_background.png");
	m_mapForground  = LoadTexture("Assets/minestorm_forground.png");
	m_tileset       = LoadTexture("Assets/minestorm_sprite_atlas_mine_storm.png");
}

GameRenderer::~GameRenderer() // Unload ressources
{
	UnloadTexture(m_mapBackground);
	UnloadTexture(m_mapForground);
	UnloadTexture(m_tileset);
}

void GameRenderer::drawMap() 
{
	DrawTexture(m_mapBackground, 0, 0, WHITE);
}

void GameRenderer::drawBorder() 
{
	DrawTexture(m_mapForground, 0, 0, WHITE);
}


void GameRenderer::drawEntityDebug(Entity* entity)
{
	Collider col = entity->m_collider;
	//Collisions Lines
	for (int i = 0; i < col.m_edges.size(); i++)
	{
		int y = i + 1;
		DrawLine((int)col.m_edges[i].x, (int)col.m_edges[i].y, (int)col.m_edges[y % col.m_edges.size()].x, (int)col.m_edges[y % col.m_edges.size()].y, (col.overlap ? RED : LIME));
		DrawPixel((int)col.m_edges[i].x, (int)col.m_edges[i].y, GREEN);
	}
	//Center
	DrawPixel((int)col.center.x,(int) col.center.y, RED);

	//Direction line
	DrawLine((int)col.center.x, (int)col.center.y, (int)(col.center.x + (20 * entity->getDirection().x)) , (int)(col.center.y + (30 * entity->getDirection().y)), YELLOW);
}

void GameRenderer::drawEntity(Entity* entity)
{
	int size = (int)entity->m_size;
	Rectangle tileRect = { (float)(1 + entity->m_sprite.tileColumn * 256.f),(float)entity->m_sprite.tileLine * 256.f, 256.f, 256.f};
	Rectangle destRect = { entity->getCenter().x, entity->getCenter().y, 50.f * size, 50.f * size };
	Vector2   origin = { 25.f * size, 25.f * size };

	DrawTexturePro(m_tileset, tileRect, destRect, origin, entity->m_rotation, entity->m_sprite.color);
}

void GameRenderer::drawProjectile(Projectile* projectile)
{
	Rectangle tileRect = { (float)projectile->m_sprite.tileColumn * 256.f, (float)projectile->m_sprite.tileLine * 256.f, 256, 256 };
	Rectangle destRect = { projectile->getCenter().x, projectile->getCenter().y, 50.f, 50.f };
	Vector2 origin = { 25.f,  25.f};
	DrawTexturePro(m_tileset, tileRect, destRect, origin, 0, projectile->m_parent->m_spaceShip->m_sprite.color);
}

void GameRenderer::drawPlayerInfo(PlayerController* player, int padding) 
{
	for (int i = 0; i < player->m_spaceShip->getLife(); i++)
	{
		Rectangle tileRect = { 0, 0, 256, 256 };
		Rectangle destRect {};
		if(padding > 0)
			destRect = { 40.f + 30.f * i, 770.f, 60.f, 60.f};
		else
			destRect = { 600.f - 30.f * i, 770.f, 60.f, 60.f };

		//clignotement avec un modulo des familles sur l invicinbilite
		if (player->m_spaceShip->getInvicibilityTime() < 1.f || (int)(player->m_spaceShip->getInvicibilityTime() * 10.f) % 4 == 0)
			DrawTexturePro(m_tileset, tileRect, destRect, {25.f, 25.f}, 0, player->m_spaceShip->m_sprite.color);
		DrawText("Pause/Resume - [Space]", 200, 5, 20, LIME);
	}
}

void GameRenderer::drawSpawnPoint(EnemySpawnPoint* spawnPoint) 
{
	Rectangle tileRect = { 256, 0, 256, 256 };
	Rectangle destRect = {spawnPoint->m_position.x, spawnPoint->m_position.y , 50.f, 50.f};
	Vector2 origin = {25.f, 25.f};
	DrawTexturePro(m_tileset, tileRect, destRect, origin, 0, RED);
}

void GameRenderer::drawScore(float2 position,int score) 
{
	DrawText("Score :", (int) position.x, (int)position.y, 20, LIME);
	std::string scoreS = std::to_string(score);
	DrawText(scoreS.c_str(), (int)position.x + 80, (int)position.y, 20, LIME);
}

void GameRenderer::drawMainMenu() 
{
	DrawText("Start New Game :", 150, 200, 40, RAYWHITE);
	DrawText("Singleplayer - [F]", 180, 300, 30, SKYBLUE);
	DrawText("Cooperation - [K]", 180, 350, 30, RED);

	DrawText("Quit - [Esc]", 255, 635, 20, DARKGRAY);
}

void GameRenderer::drawGameOver()
{
	DrawText("GAME OVER", 190, 200, 40, RED);
	DrawText("Back to Main Menu - [Esc]", 180, 635, 20, DARKGRAY);
}

void GameRenderer::drawPauseMenu() 
{
	drawBorder();
	DrawText("Game Paused", 190, 200, 40, RAYWHITE);
	DrawText("Back to Main Menu - [Esc]", 180, 635, 20, DARKGRAY);

}
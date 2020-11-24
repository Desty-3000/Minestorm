#pragma once

#include "game_utils.h"

#include <Vector>

#include "player.h"

class GameRenderer;
class EnemySpawnPoint;
class MineLayer;

class GameEngine
{
	public:
		//Cstor x Dstor
		GameEngine(GameRenderer* gameRenderer=nullptr);
		~GameEngine();

		void addEnemy(EnemyType type, EntitySize size);
		void addPlayer();
		void addSpawnPoint(float2 position = {0.f, 0.f});

		void startGame(GameType type);
		
		void resetStats();

		GameState m_gameState = GameState::MAIN;
		GameType m_gameType = GameType::SINGLEPLAYER;

		bool m_has_wave_started = false;
		bool m_isDebugOn = false;

		PlayerController* m_playerOnePtr = nullptr;
		PlayerController* m_playerTwoPtr = nullptr;

	private:
		std::vector<Entity*> m_entityList;
		std::vector<EnemySpawnPoint*> m_spawnPointList;

		GameRenderer* m_gameRenderer = nullptr;

		bool m_isEveryoneDead = false;
		bool m_hasMineLayerSpawned = false;
		MineLayer* m_mineLayer = nullptr;

		int  m_score = 0;
		int  m_wave  = 0;
		int  m_enemyCount = 0;

		void startGameLoop();

		float2 getNearestPlayer(Entity* entity);
		
		void updateEntities();
		void drawEntities();

		void updateSpawnPoints();
		void drawSpawnPoints();
		void deleteSpawnPoint(int index);
		void startWave();
		
		void updateScene();
		void drawScene();

		void trySpawnNewMine(EntitySize size);
		void addFireBall(Entity* parent);

		void tryCollisions();
		void emptyLists();

		void spawnMineLayer();

		void startInvincibility();

		void drawPlayerInfos();
};
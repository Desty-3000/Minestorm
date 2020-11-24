
#include "game_engine.h"

#include <raylib.h>
#include <iostream>

#include "game_renderer.h"
#include "events.h"
#include "player.h"
#include "mines.h"
#include "projectile.h"


//MINELAYER
//UPDATE CLEANING
//COLLISION CLEANING
//CODE CLEANING
//README 

void GameEngine::startGameLoop()
{
	while (!WindowShouldClose()) 
	{
		updateScene();

		handleEvents(this);
		
		drawScene();
	}
}

void GameEngine::startWave() 
{
	m_wave++;
	m_hasMineLayerSpawned = false;
	m_has_wave_started = false;
	
	for (int i = 0; i < 7 * m_wave; i++) 
		addSpawnPoint();
	startInvincibility();
}

void GameEngine::spawnMineLayer() 
{
	Entity* mineLayer = new MineLayer();
	m_mineLayer = (MineLayer*) mineLayer;
	m_entityList.push_back(mineLayer);
	m_hasMineLayerSpawned = true;
	m_enemyCount++;
}
//---------------------------------------- [SpawnPoints] ----------------------------------------------

void GameEngine::addSpawnPoint(float2 position)
{
	EnemySpawnPoint* sp = new EnemySpawnPoint(position);
	m_spawnPointList.push_back(sp);
}

void GameEngine::updateSpawnPoints() 
{
	bool isPlacingFinished = true;

	for (auto& spawnPoint : m_spawnPointList) 
	{
		spawnPoint->update();
		if (isPlacingFinished && !spawnPoint->m_isPlaced)
			isPlacingFinished = false;
	}
	if (isPlacingFinished)
	{
		m_has_wave_started = true;

		//Spawn First BiG Mines
		for (int i = 0; i < m_wave; i++)
		{
			int typeInt = 0;
			Math::randomize(typeInt, 0, 3);
			addEnemy((EnemyType)typeInt, EntitySize::BIG);
		}
	}
}

void GameEngine::startInvincibility() 
{
	if (m_playerOnePtr != nullptr) 
	{
		m_playerOnePtr->m_spaceShip->enableInvincibility();
	}
	if (m_playerTwoPtr != nullptr)
	{
		m_playerTwoPtr->m_spaceShip->enableInvincibility();
	}
}
void GameEngine::deleteSpawnPoint(int index) 
{
	delete m_spawnPointList[index];
	m_spawnPointList[index] = m_spawnPointList[m_spawnPointList.size() - 1];
	m_spawnPointList.pop_back();
}

void GameEngine::drawSpawnPoints() 
{
	for (auto& spawnPoint : m_spawnPointList)
	{
		m_gameRenderer->drawSpawnPoint(spawnPoint);
	}
}

//---------------------------------------- [List Management] ----------------------------------------------
void GameEngine::emptyLists() 
{
	delete m_playerOnePtr;
	delete m_playerTwoPtr;
	m_playerOnePtr = nullptr;
	m_playerTwoPtr = nullptr;

	for (int i = 0; i < m_entityList.size(); i++)
		delete m_entityList[i];
	m_entityList.clear();

	for (int i = 0; i < m_spawnPointList.size(); i++)
		delete m_spawnPointList[i];
	m_spawnPointList.clear();
}

//---------------------------------------- [Scene Management] ----------------------------------------------
void GameEngine::drawScene() 
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	m_gameRenderer->drawMap();

	switch (m_gameState)
	{
		case (GameState::MAIN):
		{
			m_gameRenderer->drawMainMenu();
			m_gameRenderer->drawBorder();
			break;
		};
		case (GameState::PLAYING):
		{
			drawSpawnPoints();
			if (m_has_wave_started)
			{
				drawEntities();
				m_gameRenderer->drawBorder();
				m_gameRenderer->drawScore({ 250, 770 }, m_score);
				drawPlayerInfos();
			}
			else
				m_gameRenderer->drawBorder();
			break;
		};
		case (GameState::PAUSE):
		{
			m_gameRenderer->drawPauseMenu();
			m_gameRenderer->drawScore({ 250, 770 }, m_score);
			drawPlayerInfos();
			break;
		};
		case (GameState::GAMEOVER):
		{
			m_gameRenderer->drawBorder();
			m_gameRenderer->drawGameOver();
			m_gameRenderer->drawScore({ 250, 400 }, m_score);
			break;
		};
	};

	EndDrawing();
}


void GameEngine::updateScene()
{
	switch (m_gameState)
	{
	case (GameState::MAIN):
	{
		//Maybe Animations Background
		return;
	};
	case (GameState::PLAYING):
	{
		if (m_has_wave_started)
		{
			tryCollisions();
			updateEntities();

			if (m_enemyCount <= 0)
			{
				if (m_spawnPointList.size() == 0)
				{
					startWave();
					return;
				}
				else 
				{
					for (int i = 0; i < m_spawnPointList.size(); i++) 
					{
						int typeInt = 0;
						Math::randomize(typeInt, 0, 3);
						addEnemy((EnemyType)typeInt, EntitySize::SMALL);
					}
				}
			}
			if (m_spawnPointList.size() == 0 && !m_hasMineLayerSpawned)
			{
				spawnMineLayer();
			}
		}
		else
		{
			updateSpawnPoints();
		}

		return;
	};
	};
}

void GameEngine::drawPlayerInfos() 
{
	if (m_playerOnePtr != nullptr)
		m_gameRenderer->drawPlayerInfo(m_playerOnePtr, 1);
	if (m_playerTwoPtr != nullptr)
		m_gameRenderer->drawPlayerInfo(m_playerTwoPtr, -1);
}
void GameEngine::resetStats() 
{
	m_score = 0;
	m_wave = 0;
	m_has_wave_started = false;
	m_isEveryoneDead = false;
	emptyLists();
}

void GameEngine::startGame(GameType type) 
{
	m_gameType = type;
	addPlayer();
	if (type == GameType::COOP)
		addPlayer();
	m_gameState = GameState::PLAYING;
	startWave();
}

void GameEngine::addPlayer()
{
	if (m_playerOnePtr == nullptr) 
	{
		PlayerController* player = new PlayerController{};
		m_playerOnePtr = player;
		m_entityList.push_back(player->m_spaceShip);
	}
	else if (m_playerTwoPtr == nullptr)
	{
		PlayerController* player = new PlayerController{};
		m_playerTwoPtr = player;
		m_entityList.push_back(player->m_spaceShip);
	}
}

void GameEngine::trySpawnNewMine(EntitySize size) 
{
	if (size == EntitySize::SMALL || m_spawnPointList.size() <= 0)
		return;

	for (int i = 0; i < 2; i++)
	{
		int typeInt = 0;
		Math::randomize(typeInt, 0, 3);
		addEnemy((EnemyType)typeInt, (EntitySize)((int)size - 1));
	}
}

void GameEngine::addFireBall(Entity* parent) 
{
	m_enemyCount++;
	float2 target = getNearestPlayer(parent);
	Entity* fireball = new FireBall(EntitySize::SMALL, parent, target);
	m_entityList.push_back(fireball);
}

float2 GameEngine::getNearestPlayer(Entity* entity) 
{
	if (m_gameType == GameType::SINGLEPLAYER)
		return m_playerOnePtr->m_spaceShip->getCenter();
	else
	{
		if (m_playerOnePtr == nullptr)
			return m_playerTwoPtr->m_spaceShip->getCenter();
		if (m_playerTwoPtr == nullptr)
			return m_playerOnePtr->m_spaceShip->getCenter();

		float2 player1Pos = m_playerOnePtr->m_spaceShip->getCenter();
		float2 player2Pos = m_playerTwoPtr->m_spaceShip->getCenter();

		vector vec1 = Vector::substract(player1Pos, entity->getCenter());
		vector vec2 = Vector::substract(player2Pos, entity->getCenter());

		float lenVec1 = Vector::length(vec1);
		float lenVec2 = Vector::length(vec2);

		return (lenVec1 > lenVec2 ? player2Pos : player1Pos);
	}
}

void GameEngine::tryCollisions() 
{
	for (int x = 0; x < m_entityList.size(); x++)
	{
		for (int i = 0; i < m_playerOnePtr->m_projectileList.size(); i++)
		{
			m_entityList[x]->m_collider.overlap = ColliderOverlaping(m_entityList[x]->m_collider, m_playerOnePtr->m_projectileList[i]->m_collider);
			if (ColliderOverlaping(m_playerOnePtr->m_projectileList[i]->m_collider, m_entityList[x]->m_collider))
			{
				m_playerOnePtr->m_projectileList[i]->takeDamage();
			}
		}
		if (m_playerTwoPtr != nullptr)
		{
			for (int i = 0; i < m_playerTwoPtr->m_projectileList.size(); i++)
			{
				m_entityList[x]->m_collider.overlap = ColliderOverlaping(m_entityList[x]->m_collider, m_playerTwoPtr->m_projectileList[i]->m_collider);
				if (ColliderOverlaping(m_playerTwoPtr->m_projectileList[i]->m_collider, m_entityList[x]->m_collider))
				{
					m_playerTwoPtr->m_projectileList[i]->takeDamage();
				}
			}
		}
	}

	// Trigger spaceship's overlaping if touching mine
	for (int i = 0; i < m_entityList.size(); i++)
	{
		if (m_playerOnePtr != nullptr)
			if (!m_playerOnePtr->m_spaceShip->m_collider.overlap && m_entityList[i] != m_playerOnePtr->m_spaceShip)
				m_playerOnePtr->m_spaceShip->m_collider.overlap = ColliderOverlaping(m_playerOnePtr->m_spaceShip->m_collider, m_entityList[i]->m_collider);

		if (m_playerTwoPtr != nullptr)
			if (!m_playerTwoPtr->m_spaceShip->m_collider.overlap && m_entityList[i] != m_playerTwoPtr->m_spaceShip)
				m_playerTwoPtr->m_spaceShip->m_collider.overlap = ColliderOverlaping(m_playerTwoPtr->m_spaceShip->m_collider, m_entityList[i]->m_collider);
	}

	//Trigger spaceship's overlaping
	if (m_playerOnePtr != nullptr && m_playerTwoPtr != nullptr)
	{
		if (!m_playerOnePtr->m_spaceShip->m_collider.overlap && !m_playerTwoPtr->m_spaceShip->m_collider.overlap)
		{
			m_playerOnePtr->m_spaceShip->m_collider.overlap = ColliderOverlaping(m_playerTwoPtr->m_spaceShip->m_collider, m_playerOnePtr->m_spaceShip->m_collider);
			if (m_playerOnePtr->m_spaceShip->m_collider.overlap || m_playerTwoPtr->m_spaceShip->m_collider.overlap)
			{
				m_playerOnePtr->m_spaceShip->m_collider.overlap = true;
				m_playerTwoPtr->m_spaceShip->m_collider.overlap = true;
			}
		}
	}
}

void GameEngine::updateEntities() 
{
	//Update Entities
	for (auto& entity : m_entityList)
	{
		float2 player = getNearestPlayer(entity);
		entity->update(player);
	}
	if (m_mineLayer != nullptr) 
	{
		if (m_mineLayer->m_pop) 
		{
			addSpawnPoint(m_mineLayer->getCenter());
			m_mineLayer->reset();
		}
	}

	//Kill dead Entities
	for (int i = 0; i < m_entityList.size(); i++)
	{	
		if (!m_entityList[i]->isAlive())
		{
			if (m_playerOnePtr != nullptr)
			{
				if (m_entityList[i] == m_playerOnePtr->m_spaceShip)
				{
					delete m_playerOnePtr;
					m_playerOnePtr = nullptr;
					if (m_gameType == GameType::SINGLEPLAYER || m_playerTwoPtr == nullptr)
					{
						m_gameState = GameState::GAMEOVER;
						return;
					}
				}
			}
			if (m_playerTwoPtr != nullptr)
			{
				if (m_entityList[i] == m_playerTwoPtr->m_spaceShip)
				{
					delete m_playerTwoPtr;
					m_playerTwoPtr = nullptr;
					if (m_playerOnePtr == nullptr)
						m_gameState = GameState::GAMEOVER;
				}
			}
			if (m_mineLayer != nullptr)
			{
				if (m_entityList[i] == m_mineLayer)
				{
					m_mineLayer = nullptr;
				}
			}
			m_score += m_entityList[i]->scoreBySize();
			if (m_entityList[i]->m_spawnMine)
				trySpawnNewMine(m_entityList[i]->m_size);

			if (m_entityList[i]->deathCallback())
					addFireBall(m_entityList[i]);

			delete m_entityList[i];
			m_enemyCount--;
			m_entityList[i] = m_entityList[m_entityList.size() - 1];
			m_entityList.pop_back();
		}
	}
}

void GameEngine::drawEntities()
{
	for (auto& entity : m_entityList)
	{
		m_gameRenderer->drawEntity(entity);
		if (m_isDebugOn)
			m_gameRenderer->drawEntityDebug(entity);
	}
	for (auto& entity : m_playerOnePtr->m_projectileList)
	{
		m_gameRenderer->drawProjectile(entity);
		if (m_isDebugOn)
			m_gameRenderer->drawEntityDebug(entity);
	}
	if (m_playerTwoPtr != nullptr)
	{
		for (auto& entity : m_playerTwoPtr->m_projectileList)
		{
			m_gameRenderer->drawProjectile(entity);
			if (m_isDebugOn)
				m_gameRenderer->drawEntityDebug(entity);
		}
	}	
}

GameEngine::GameEngine(GameRenderer* gameRenderer)
{
	m_gameRenderer = gameRenderer;
	startGameLoop();
}


GameEngine::~GameEngine() // Empty Lists 
{
	emptyLists();

	CloseWindow();
}

void GameEngine::addEnemy(EnemyType type, EntitySize size) 
{
	int spawnPointIndex = 0;
	Math::randomize(spawnPointIndex,0,(int) m_spawnPointList.size()-1);
	m_enemyCount++;
	switch (type)
	{
		case EnemyType::FIREBALL_MINE:
		{
			Entity* mine = new FireballMine(size, m_spawnPointList[spawnPointIndex]->m_position);
			m_entityList.push_back(mine);
			deleteSpawnPoint(spawnPointIndex);
			return;
		}
		case EnemyType::FLOATING_MINE:
		{
			Entity* mine = new FloatingMine(size, m_spawnPointList[spawnPointIndex]->m_position);
			m_entityList.push_back(mine);
			deleteSpawnPoint(spawnPointIndex);
			return;
		}
		case EnemyType::MAGNETIC_MINE:
		{			
			Entity* mine = new MagneticMine(size, m_spawnPointList[spawnPointIndex]->m_position);
			m_entityList.push_back(mine);
			deleteSpawnPoint(spawnPointIndex);
			return;
		}
		case EnemyType::MAG_FIRE_MINE:
		{
			Entity* mine = new MagneticFireballMine(size, m_spawnPointList[spawnPointIndex]->m_position);
			m_entityList.push_back(mine);
			deleteSpawnPoint(spawnPointIndex);
			return;
		}
		case EnemyType::MINELAYER:
		{
			Entity* mine = new FloatingMine();
			m_entityList.push_back(mine);
			deleteSpawnPoint(spawnPointIndex);
			return;
		}
	};
}
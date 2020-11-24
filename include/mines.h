#pragma once

#include "entity.h"

class FloatingMine : public Entity
{
	public:
		FloatingMine(EntitySize size=EntitySize::BIG, float2 position = {});
		~FloatingMine() {};		
		int scoreBySize() override;
};

class MagneticMine : public Entity
{
public:
	MagneticMine(EntitySize size = EntitySize::BIG, float2 position = {});
	~MagneticMine() {};
	
	int scoreBySize() override;
private:
	void updateSpec(float2 player) override;
};

class FireballMine : public Entity
{
public:
	FireballMine(EntitySize size = EntitySize::BIG, float2 position = {});
	~FireballMine() {};
	int scoreBySize() override;
	bool deathCallback() override;
};

class MagneticFireballMine : public Entity
{
public:
	MagneticFireballMine(EntitySize size = EntitySize::BIG, float2 position = {});
	~MagneticFireballMine() {};
	int scoreBySize() override;
	bool deathCallback() override;
	void updateSpec(float2 player) override;
};

class FireBall : public Entity
{
public:
	FireBall(EntitySize size = EntitySize::BIG, Entity* parent = nullptr, float2 target = {});
	~FireBall() {};
	int scoreBySize() override;
};

class EnemySpawnPoint
{
	public:
		EnemySpawnPoint(float2 position = {0.f, 0.f});
		~EnemySpawnPoint();
	
		float2 m_position;
		float2 m_finalPosition;
		void update();


		bool m_isPlaced = false;
	private:

		vector m_vectorDirector{};
};

class MineLayer : public Entity
{
	public:
		MineLayer();
		~MineLayer();
		int scoreBySize() override;
		void updateSpec(float2 player) override;
		bool m_pop = false;
		void reset();
	private:
		
		Timer m_spawnPointTimer {1.5f};
};
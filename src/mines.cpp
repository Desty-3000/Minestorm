
#include "mines.h"

#include <cstdlib>

FloatingMine::FloatingMine(EntitySize size, float2 position) : Entity(20.f * (4 - (int)size))
{
	m_size = size;
	m_rotation = (float) (std::rand() % 180);
	calculateDirection();
	addVelocity(1.f);
	m_sprite.tileLine = 1;
	m_position = position;
	m_spawnMine = true;
	
	m_collider.m_edges.push_back({ 0.f, -30.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ 0.f, -30.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ -10.f / (4 - (int)size), 5.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ -10.f / (4 - (int)size), 5.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ -33.f / (4 - (int)size), 33.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ -33.f / (4 - (int)size), 33.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ 0.f, 26.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ 0.f, 26.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ 33.f / (4 - (int)size), 33.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ 33.f / (4 - (int)size), 33.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ 10.f / (4 - (int)size), 5.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ 10.f / (4 - (int)size), 5.f / (4 - (int)size) });
};

FireballMine::FireballMine(EntitySize size, float2 position) : Entity(20.f * (4 - (int)size))
{
	m_size = size;
	m_rotation = (float)(std::rand() % 180);
	calculateDirection();
	addVelocity(1.f);
	m_sprite.tileLine = 1;
	m_sprite.tileColumn = 3;
	m_position = position;
	m_spawnMine = true;
	
	m_collider.m_edges.push_back({ 0.f, -22.f / (4 - (int) size)});
	m_collider.m_edges_origin.push_back({ 0.f, -22.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ -26.f / (4 - (int)size), -28.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ -26.f / (4 - (int)size), -28.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ -22.f / (4 - (int)size), 0.f });
	m_collider.m_edges_origin.push_back({ -22.f / (4 - (int)size), 0.f });

	m_collider.m_edges.push_back({ -26.f / (4 - (int)size), 30.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ -26.f / (4 - (int)size), 30.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ 0.f, 22.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ 0.f, 22.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ 30.f / (4 - (int)size), 30.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ 30.f / (4 - (int)size), 30.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ 23.f / (4 - (int)size), 0.f });
	m_collider.m_edges_origin.push_back({ 23.f / (4 - (int)size), 0.f });

	m_collider.m_edges.push_back({ 30.f / (4 - (int)size), -30.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ 30.f / (4 - (int)size), -30.f / (4 - (int)size) });
	
};

void MagneticMine::updateSpec(float2 player) 
{
	vector vec = Vector::substract(player, m_position);

	float vecLen = Vector::length(vec);

	// Prevent dividing per 0
	if (vecLen == 0)
		return;
	m_vectorDirector.x = (vec.x / vecLen);
	m_vectorDirector.y = (vec.y / vecLen);
}

void MagneticFireballMine::updateSpec(float2 player)
{
	vector vec = Vector::substract(player, m_position);

	float vecLen = Vector::length(vec);

	// Prevent dividing per 0
	if (vecLen == 0)
		return;
	m_vectorDirector.x = (vec.x / vecLen);
	m_vectorDirector.y = (vec.y / vecLen);
}

MagneticMine::MagneticMine(EntitySize size, float2 position) : Entity(20.f * (4 - (int)size))
{
	m_size = size;
	addVelocity(1.f);
	m_sprite.tileLine = 1;
	m_sprite.tileColumn = 1;
	m_position = position;
	m_spawnMine = true;

	m_collider.m_edges.push_back({ 0.f, -16.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ 0.f, -16.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ -26.f / (4 - (int)size), -28.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ -26.f / (4 - (int)size), -28.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ -15.f / (4 - (int)size), 0.f });
	m_collider.m_edges_origin.push_back({ -15.f / (4 - (int)size), 0.f });

	m_collider.m_edges.push_back({ -26.f / (4 - (int)size), 30.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ -26.f / (4 - (int)size), 30.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ 0.f, 16.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ 0.f, 16.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ 28.f / (4 - (int)size), 29.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ 28.f / (4 - (int)size), 29.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ 15.f / (4 - (int)size), 0.f });
	m_collider.m_edges_origin.push_back({ 15.f / (4 - (int)size), 0.f });

	m_collider.m_edges.push_back({ 28.f / (4 - (int)size), -30.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ 28.f / (4 - (int)size), -30.f / (4 - (int)size) });
};

MagneticFireballMine::MagneticFireballMine(EntitySize size, float2 position) : Entity(20.f * (4 - (int)size))
{
	m_size = size;
	addVelocity(1.f);
	m_sprite.tileLine = 1;
	m_sprite.tileColumn = 2;
	m_position = position;
	m_spawnMine = true;
	
	m_collider.m_edges.push_back({ -16.f / (4 - (int)size), -26.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ -16.f / (4 - (int)size), -26.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ -24.f / (4 - (int)size), -42.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ -24.f / (4 - (int)size), -43.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ -24.f / (4 - (int)size), 18.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ -24.f / (4 - (int)size), 18.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ -42.f / (4 - (int)size), 27.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ -42.f / (4 - (int)size), 27.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ 20.f / (4 - (int)size), 27.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ 20.f / (4 - (int)size), 27.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ 28.f / (4 - (int)size), 44.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ 28.f / (4 - (int)size), 44.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ 28.f / (4 - (int)size), -19.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ 28.f / (4 - (int)size), -19.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ 43.f / (4 - (int)size), -26.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ 43.f / (4 - (int)size), -26.f / (4 - (int)size) });
};

bool MagneticFireballMine::deathCallback()
{
	return true;
}

bool FireballMine::deathCallback()
{
	return true;
}

FireBall::FireBall(EntitySize size, Entity* parent, float2 target) : Entity(60.f)
{
	addVelocity(1.f);
	m_rotation = parent->m_rotation;
	m_position = parent->getCenter();

	vector vec = Vector::substract(target, m_position);
	float vecLen = Vector::length(vec);
	// Prevent dividing per 0
	if (vecLen == 0)
		return;

	m_vectorDirector.x = (vec.x / vecLen);
	m_vectorDirector.y = (vec.y / vecLen);

	m_sprite.tileColumn = 3;
	
	float radius = 7.f;
	float angle = M_PI * 2.f / 12.f;

	for (int i = 0; i < 12; i++)
	{
		m_collider.m_edges.push_back({ radius * cosf(angle * i), radius * sinf(angle * i) });
		m_collider.m_edges_origin.push_back({ radius * cosf(angle * i), radius * sinf(angle * i) });
	}
}

int FireBall::scoreBySize() 
{
	return 110;
}

int FloatingMine::scoreBySize()
{
	switch (m_size)
	{
		case(EntitySize::MEDIUM):
		{
			return 135;
		}
		case(EntitySize::SMALL):
		{
			return 200;
		}
	}
	return 100;
}

int FireballMine::scoreBySize()
{
	switch (m_size)
	{
		case(EntitySize::MEDIUM):
		{
			return 360;
		}
		case(EntitySize::SMALL):
		{
			return 425;
		}
		
	}
	return 325;
}

int MagneticMine::scoreBySize() 
{
	switch (m_size)
	{
	case(EntitySize::MEDIUM):
	{
		return 535;
	}
	case(EntitySize::SMALL):
	{
		return 600;
	}
	
	}
	return 500;
}

int MagneticFireballMine::scoreBySize()
{
	switch (m_size)
	{
	case(EntitySize::MEDIUM):
	{
		return 785;
	}
	case(EntitySize::SMALL):
	{
		return 850;
	}
	}
	return 750;
}

int MineLayer::scoreBySize() 
{
	return 1000;
}
EnemySpawnPoint::EnemySpawnPoint(float2 position) 
{
	if (position.x != 0.f && position.y != 0.f) 
	{
		m_position = position;
		m_finalPosition = position;
	}
	else
	{
		m_position = { 320, 400 };
		m_finalPosition.randomize();
	}

	vector vector = Vector::substract(m_finalPosition, m_position);
	float lenVec = Vector::length(vector);

	m_vectorDirector = Vector::create(vector.x/lenVec, vector.y / lenVec);
}

EnemySpawnPoint::~EnemySpawnPoint()
{

}


void EnemySpawnPoint::update() 
{
	if (!m_isPlaced)
	{
		m_position.x += m_vectorDirector.x * 200.f * GetFrameTime();
		m_position.y += m_vectorDirector.y * 200.f * GetFrameTime();
		if (Vector::compare(m_position, m_finalPosition, 5))
			m_isPlaced = true;
	}
}

MineLayer::MineLayer() : Entity(30.f)
{
	m_size = EntitySize::BIG;
	EntitySize size = m_size;
	m_rotation = (float)(std::rand() % 180);
	calculateDirection();
	m_position.randomize();
	addVelocity(1.f);

	m_sprite.tileColumn = 2;

	m_collider.m_edges.push_back({ -16.f / (4 - (int)size), -26.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ -16.f / (4 - (int)size), -26.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ -24.f / (4 - (int)size), -42.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ -24.f / (4 - (int)size), -43.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ -24.f / (4 - (int)size), 18.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ -24.f / (4 - (int)size), 18.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ -42.f / (4 - (int)size), 27.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ -42.f / (4 - (int)size), 27.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ 20.f / (4 - (int)size), 27.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ 20.f / (4 - (int)size), 27.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ 28.f / (4 - (int)size), 44.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ 28.f / (4 - (int)size), 44.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ 28.f / (4 - (int)size), -19.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ 28.f / (4 - (int)size), -19.f / (4 - (int)size) });

	m_collider.m_edges.push_back({ 43.f / (4 - (int)size), -26.f / (4 - (int)size) });
	m_collider.m_edges_origin.push_back({ 43.f / (4 - (int)size), -26.f / (4 - (int)size) });
}

void MineLayer::reset() 
{
	m_pop = false;
	m_spawnPointTimer.reset();
	Math::randomize(m_rotation, 0, 180);
	calculateDirection();
}

void MineLayer::updateSpec(float2 player)
{
	if (m_spawnPointTimer.isDone())
		m_pop = true;
	else
		m_spawnPointTimer.update(GetFrameTime());

}

MineLayer::~MineLayer()
{

}

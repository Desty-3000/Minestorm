
#include "projectile.h"
#include "player.h"

Projectile::Projectile(PlayerController* parent, float maxLifetime, float speed) : Entity(speed)
{
	m_parent = parent;
	m_rotation = parent->m_spaceShip->m_rotation;
	calculateDirection();
	m_maxLifetime = maxLifetime;
	m_sprite.tileColumn = 3;
	m_position = parent->m_spaceShip->getProjectileSpawn();

	float radius = 3.f;
	float angle = M_PI * 2.f / 12.f;

	for (int i = 0; i < 12; i++) 
	{
		m_collider.m_edges.push_back({ radius * cosf(angle * i), radius * sinf(angle * i) });
		m_collider.m_edges_origin.push_back({ radius * cosf(angle * i), radius * sinf(angle * i) });
	}
}

Projectile::~Projectile() 
{

}

bool Projectile::isDead() 
{
	return m_lifetime >= m_maxLifetime;
}


void Projectile::updateLife() 
{
	m_lifetime += GetFrameTime();
}
#pragma once
#include "entity.h"

class PlayerController;

class Projectile : public Entity
{
	public: 
		Projectile(PlayerController* parent, float maxLifetime = 1.f, float speed = 300.f);
		~Projectile();

		bool isDead();
		void updateLife();
		PlayerController* m_parent;
	private:
		float m_lifetime = 0.f;
		float m_maxLifetime = 1.f;
		
};
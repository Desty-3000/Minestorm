#pragma once

#include <string>
#include <vector>

#include "entity.h"

class Projectile;
class PlayerController;

//Manage the player entity
class PlayerCharacter : public Entity
{
	public:
		PlayerCharacter(PlayerController* parent, Color color = {255,255,255,255});
		~PlayerCharacter();

		void teleport();
		int scoreBySize() override { return -500; }

		void disableInvincibility();
		void enableInvincibility();
		float getInvicibilityTime() const;

		float2 getProjectileSpawn();

	private:

		void updateSpec(float2 player) override;
		void takeDamageSpec() override;

		void updateInvincibility();

		Timer m_invincibilityTimer{ 2.f };
		
		PlayerController* m_parent;
};

//Manage the Player
class PlayerController 
{
	public:
		static int m_playerCount;

		PlayerController();
		~PlayerController();

		void updateProjectiles();
		PlayerCharacter* m_spaceShip{};
		void shoot();

		std::vector<Projectile*> m_projectileList;
	private:	
		//Player Infos
		unsigned int	m_id    = 0;
		
};
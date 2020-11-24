#pragma once

#include "math_toolbox.h"
#include "game_utils.h"
#include "collisions.h"

class PlayerCharacter;

class Entity
{
public:
	//Cstor x Dstor
	Entity(float speed = 0.f, int life = 1);
	virtual ~Entity();

		void update(float2 player);
		virtual void updateSpec(float2 player) {};
		void addVelocity(float velocity);
		void setVelocity(float velocity);
		void calculateDirection();
		void resetVelocity() { m_velocity = 0.f; }
		bool isAlive();
		void takeDamage();
		virtual void takeDamageSpec() {};
		virtual int scoreBySize() { return 0; }
		virtual bool deathCallback() { return false; }
		int getLife() const { return m_life; }
	

		float2   getCenter() const { return m_position; }
		vector   getDirection() const { return m_vectorDirector; }

		Sprite2D m_sprite = { };

		int    m_scoreValue = 0;

		bool   m_spawnMine = false;
		float  m_angle	  = 0.f;
		float  m_rotation = 0.f;

		EntitySize m_size = EntitySize::BIG;
		Collider m_collider{};

		

	private:
		void	 clipBorder();
		void	 focusPlayer(PlayerCharacter* player1);
		
		int		 m_life  		  = 1;

	protected:

		float2   m_position = { 300.f, 300.f };
		vector   m_vectorDirector = { 0.f,  0.f };
		float    m_velocity = 1.f;
		float    m_mass = 4.f;
		float    m_speed = 100.f;
		float    m_rotSpeed = 200.f;
};
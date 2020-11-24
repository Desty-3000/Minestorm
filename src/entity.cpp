
#include "entity.h"

#include <math.h>
#include "math_toolbox.h"
#include "player.h"
#include <iostream>

Entity::Entity(float speed, int life) 
{
	m_speed = speed;
	m_life = life;
}

Entity::~Entity()
{

}

void Entity::calculateDirection() 
{
	m_vectorDirector.x = cosf(Math::degToRadian(m_rotation) - (float)(M_PI / 2.f));
	m_vectorDirector.y = sinf(Math::degToRadian(m_rotation) - (float)(M_PI / 2.f));
}

void Entity::addVelocity(float velocity) 
{
	if(m_velocity < 2.8f)
		m_velocity += velocity;
}

void Entity::setVelocity(float velocity)
{
	m_velocity = velocity;
}

void Entity::update(float2 player)
{
	if (m_collider.overlap)
		takeDamage();
	
	//Rot
	m_rotation = m_angle * m_rotSpeed;

	updateSpec(player);
	//Movement forward
	float vectorMovement = m_speed * m_velocity;
	m_position.x += m_vectorDirector.x * vectorMovement * GetFrameTime();
	m_position.y += m_vectorDirector.y * vectorMovement * GetFrameTime();

	//Collider Updating
	m_collider.center = { m_position.x - 1 ,m_position.y };
	m_collider.angle = Math::degToRadian(m_rotation);
	translateCollider(m_collider);

	//Clip Border
	clipBorder();

}

void Entity::takeDamage() 
{
	m_life--;
	if (isAlive()) 
	{
		m_position.randomize();
	}
	takeDamageSpec();
}

bool Entity::isAlive() 
{
	return m_life > 0;
}

void Entity::focusPlayer(PlayerCharacter* player1)
{
	
	
	

}
void Entity::clipBorder()
{
	if (m_position.x > RIGHT_BORDER)
		m_position.x = LEFT_BORDER;
	if (m_position.y > BOT_BORDER)
		m_position.y = TOP_BORDER;

	if (m_position.x < LEFT_BORDER)
		m_position.x = RIGHT_BORDER;
	if (m_position.y < TOP_BORDER)
		m_position.y = BOT_BORDER;
}

#include "player.h"

#include "raylib.h"
#include "projectile.h"

int PlayerController::m_playerCount = 0;

PlayerCharacter::PlayerCharacter(PlayerController* parent, Color color) : Entity(100.f, 3)
{
	m_parent = parent;
	m_size = EntitySize::MEDIUM;
	m_sprite.color = color;
	m_collider.center = { m_position.x - 5 ,m_position.y };
	m_collider.angle = m_angle;
	m_collider.isActive = false;
	m_position.randomize();
	
	m_collider.m_edges.push_back({-15.f, 28.f});
	m_collider.m_edges_origin.push_back({ -15.f, 28.f });

	m_collider.m_edges.push_back({ 15.f, 28.f });
	m_collider.m_edges_origin.push_back({ 15.f, 28.f });

	m_collider.m_edges.push_back({ 0.f, -30.f });
	m_collider.m_edges_origin.push_back({ 0.f, -30.f });
}

PlayerCharacter::~PlayerCharacter(){}

void PlayerCharacter::takeDamageSpec() 
{
	m_invincibilityTimer.reset();
}
void PlayerController::shoot() 
{
	Projectile* projectile = new Projectile(this);
	m_projectileList.push_back(projectile);
	m_spaceShip->disableInvincibility();
}

void PlayerCharacter::updateInvincibility()
{
	if (m_invincibilityTimer.isDone()) 
	{
		if (m_collider.isActive == false)
			m_collider.isActive = true;
		return;
	}
		m_collider.isActive = false;
	m_invincibilityTimer.update(GetFrameTime());
	if (m_invincibilityTimer.isDone()) 
	{
		m_collider.isActive = true;
	}
}
void PlayerCharacter::disableInvincibility() 
{
	m_invincibilityTimer.end();
}
void PlayerCharacter::enableInvincibility()
{
	m_invincibilityTimer.reset();
}

float PlayerCharacter::getInvicibilityTime() const
{
	return m_invincibilityTimer.get();
}

void PlayerCharacter::teleport()
{
	m_position.randomize();
	resetVelocity();
	Math::randomize(m_angle,0,180);
}

void PlayerCharacter::updateSpec(float2 player) 
{
	//Inertia
	if (m_velocity > 0.f)
		m_velocity -= GetFrameTime() * m_mass;
	else
		m_velocity = 0.f;

	updateInvincibility();
	m_parent->updateProjectiles();
}

float2 PlayerCharacter::getProjectileSpawn() 
{
	return {m_position.x + 50 * cosf(Math::degToRadian(m_rotation) - M_PI / 2),m_position.y + 50 * sinf(Math::degToRadian(m_rotation) - M_PI / 2)};
}

PlayerController::PlayerController() 
{
	m_id = m_playerCount;
	m_playerCount++;

	if (m_id == 0)
		m_spaceShip = new PlayerCharacter(this, SKYBLUE);
	else
		m_spaceShip = new PlayerCharacter(this, RED);
}

void PlayerController::updateProjectiles() 
{
	for (int i = 0; i < m_projectileList.size(); i++)
	{
		if (m_projectileList[i]->isDead() || !m_projectileList[i]->isAlive())
		{
			delete m_projectileList[i];
			m_projectileList[i] = m_projectileList[m_projectileList.size() - 1];
			m_projectileList.pop_back();
			continue;
		}

		m_projectileList[i]->updateLife();
		m_projectileList[i]->update({});
	}
}
PlayerController::~PlayerController() 
{
	m_playerCount--;
	for (auto& projectile : m_projectileList) 
	{
		delete projectile;
	}

	m_projectileList.clear();
}
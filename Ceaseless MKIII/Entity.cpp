#include "Entity.h"
#include "Utility.h"
#include "Assets.h"

// Consts 
const float GRAVITY = 9.81f;
const float PLAYER_SPEED = 190.0f;
const float SPIKE_SPEED = 190.0f;

// Entity stuff here
Entity::Entity(const Vector2& pos, const Vector2& size, const Color& color)
	:m_position(pos), m_size(size), m_color(color)
{
	m_isActive = true;
}

Entity::~Entity()
{}


// Static entity stuff here
StaticEntity::StaticEntity(const Vector2& pos, const Vector2& size, const Color& color)
	:Entity(pos, size, color)
{
	m_tag = "Static";
	
	m_isActive = true;
}

StaticEntity::~StaticEntity()
{}

void StaticEntity::Update()
{
	// Do nothing for static
}

void StaticEntity::Render()
{
	m_bounds = Rectangle{ m_position.x, m_position.y, m_size.x, m_size.y };

	DrawRectangleRec(m_bounds, m_color);
}


// Player stuff here
Player::Player(const Vector2& pos, const Vector2& size, const Color& color)
	:Entity(pos, size, color)
{
	m_isActive = true;

	m_tag = "Player";

	m_velocity = 0.0f;
	m_isMoving = true;
	m_isJumping = false;
	m_isGrounded = false;

	m_collectedItems = 0;
}

Player::~Player()
{}

void Player::Update()
{
	if(m_isMoving)
		Move(PLAYER_SPEED);
}

void Player::Move(const float& speed)
{
	// Accelerating the player
	m_position.y += m_velocity * GetFrameTime();

	// Clamping the velocity so it doesn't go insane 
	m_velocity = utl::Clamp(m_velocity, -speed, speed);

	// Checking for input
	if (IsKeyPressed(KEY_SPACE)) m_isJumping = true;

	// Jumping when space is pressed and the player is allowed to move
	if (m_isJumping && m_isMoving && m_isGrounded)
	{
		m_velocity = -speed;
		m_isJumping = false;
	}
	else m_velocity += GRAVITY;
}

void Player::Render()
{
	// Deleting the player from the vector causes trouble, so it will just disappear when inactive instead
	if (m_isActive)
		m_bounds = Rectangle{ m_position.x, m_position.y, m_size.x, m_size.y };

	DrawRectangleRec(m_bounds, m_color);
}

void Player::CollisionUpdate(std::vector<Entity*>& entities)
{
	// Resolving collisions based on the tag
	for (auto& entity : entities)
	{
		// Player vs. Static
		if (entity->GetTag() == "Static")
		{
			if (CheckCollisionRecs(m_bounds, dynamic_cast<StaticEntity*>(entity)->GetBounds()))
			{
				m_position.y = entity->GetPos().y - m_size.y - 0.5f;
				m_isGrounded = true;
			}
		}
		// Player vs. Spike
		else if (entity->GetTag() == "Spike")
		{
			if (CheckCollisionPointRec(dynamic_cast<Spike*>(entity)->GetPos(), m_bounds))
			{
				PlaySound(Assets::Instance().GetSound("Death"));
				m_isActive = false;
			}
		}
		// Player vs. Coin
		else if (entity->GetTag() == "Coin")
		{
			if (CheckCollisionCircleRec(dynamic_cast<Coin*>(entity)->GetPos(), dynamic_cast<Coin*>(entity)->GetRadius(), m_bounds))
			{
				PlaySound(Assets::Instance().GetSound("Pickup"));
				m_collectedItems++;
				entity->SetActive(false);
			}
		}
	}
}


// Spike stuff here
Spike::Spike(const Vector2& pos, const float&& radius, const int&& points, const Color& color)
	:Entity(pos, Vector2{0.0f, 0.0f}, color)
{
	m_radius = radius;
	m_points = points;

	m_isActive = true;
	
	m_tag = "Spike";
	
	m_velocity = 0.0f;
	m_isMoving = true;
}

Spike::~Spike()
{}

void Spike::Update()
{
	// Deactivating(deleting from the vector) if the entity goes out of bounds
	if (m_position.x < 10.0f)
		m_isActive = false;

	if(m_isMoving)
		Move(SPIKE_SPEED);
}

void Spike::Move(const float& speed)
{
	m_position.x += m_velocity * GetFrameTime();

	m_velocity = -speed;
}

void Spike::Render()
{
	DrawPoly(m_position, (int)m_points, m_radius, 180.0f, m_color);
}


// Coin stuff here
Coin::Coin(const Vector2& pos, const float&& radius, const Color& color)
	:Entity(pos, Vector2{0.0f, 0.0f}, color)
{
	m_radius = radius;

	m_isActive = true;

	m_tag = "Coin";

	m_velocity = 0.0f;
	m_isMoving = true;
}

Coin::~Coin()
{}

void Coin::Update()
{
	// Deactivating(deleting from the vector) if the entity goes out of bounds
	if (m_position.x < 10.0f)
		m_isActive = false;
	
	if (m_isMoving)
		Move(SPIKE_SPEED);
}

void Coin::Move(const float& speed)
{
	m_position.x += m_velocity * GetFrameTime();

	m_velocity = -speed;
}

void Coin::Render()
{
	DrawCircleV(m_position, m_radius, m_color);
}

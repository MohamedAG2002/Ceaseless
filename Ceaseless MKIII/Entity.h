#pragma once

#include <string>
#include <vector>

#include <raylib.h>

#include "MovementComponent.h"

// Main entity class
class Entity
{
public:
	Entity(const Vector2& pos, const Vector2& size, const Color& color);
	~Entity();

protected:
	Vector2 m_position, m_size;
	Color m_color;
	bool m_isActive;
	std::string m_tag;

public:
	virtual void Update() {}
	virtual void Render() {}

	/* Getters and setters */
	// Position
	void SetPos(const Vector2& pos) { m_position = pos; }
	const Vector2& GetPos() const { return m_position; }

	// Size 
	void SetSize(const Vector2& size) { m_size = size; }
	const Vector2& GetSize() const { return m_size; }

	// Color
	void SetColor(const Color& color) { m_color = color; }
	const Color& GetColor() const { return m_color; }

	// Active state
	void SetActive(const bool& active) { m_isActive = active; }
	const bool& IsActive() const { return m_isActive; }

	// Tag
	void SetTag(const std::string&& tag) { m_tag = tag; }
	const std::string& GetTag() const { return m_tag; }
};


// Static entities class
class StaticEntity : public Entity
{
public:
	StaticEntity(const Vector2& pos, const Vector2& size, const Color& color);
	~StaticEntity();

private:
	Rectangle m_bounds;

public:
	void Update() override;
	void Render() override;

	// Bounds getter
	const Rectangle& GetBounds() const { return m_bounds; }
};


// Player class
class Player : public Entity, public MovementComponent
{
public:
	Player(const Vector2& pos, const Vector2& size, const Color& color);
	~Player();

private:
	Rectangle m_bounds;
	bool m_isJumping, m_isGrounded;
	unsigned int m_collectedItems;

public:
	void Update() override;
	void Move(const float& speed) override;
	void Render() override;
	void CollisionUpdate(std::vector<Entity*>& entities);

	// Bounds getter
	const Rectangle& GetBounds() const { return m_bounds; }

	// Collected items
	void SetCollectedItems(const unsigned int&& items) { m_collectedItems = items; }
	const unsigned int& GetCollectedItems() const { return m_collectedItems; }
};


// Spike class
class Spike : public Entity, public MovementComponent
{
public:
	Spike(const Vector2& pos, const float&& radius, const int&& points, const Color& color);
	~Spike();

private:
	float m_radius;
	int m_points;

public:
	void Update() override;
	void Move(const float& speed) override;
	void Render() override;

	/* Getters and setters */
	// Radius 
	void SetRadius(const float&& radius) { m_radius = radius; }
	const float& GetRadius() const { return m_radius; }

	// Points
	void SetPoints(const int&& points) { m_points = points; }
	const int& GetPoints() const { return m_points; }
};


// Coin class
class Coin : public Entity, public MovementComponent
{
public:
	Coin(const Vector2& pos, const float&& radius, const Color& color);
	~Coin();

private:
	float m_radius;

public:
	void Update() override;
	void Move(const float& speed) override;
	void Render() override;

	// Radius getter and setter
	void SetRadius(const float&& radius) { m_radius = radius; }
	const float& GetRadius() const { return m_radius; }
};
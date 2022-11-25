#pragma once

class MovementComponent
{
protected:
	bool m_isMoving;
	float m_velocity;

public:
	virtual void Move(const float& speed) {}

	/* Getters and setters */
	// Moving state
	void SetMoving(const bool& moving) { m_isMoving = moving; }
	const bool& IsMoving() const { return m_isMoving; }

	// Velocity
	void SetVelocity(const float&& velocity) { m_velocity = velocity; }
	const float& GetVelocity() const { return m_velocity; }
};
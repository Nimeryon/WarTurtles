#include "Components/Physic.h"

Turtle::Physic::Physic(GameObject* parent, const std::string& name, Vector2f initialVelocity, Vector2f initialAcceleration, float mass, float friction, float bounciness) :
	Component(parent, name), 
	m_velocity(initialVelocity),
	m_acceleration(initialAcceleration),
	m_mass(mass), 
	m_friction(friction),
	m_bounciness(bounciness),
	m_localGravity(Vector2f::zero)
{
}

void Turtle::Physic::FixedUpdate(const Time& fixedTime)
{
	//update local gravity
}

Turtle::Vector2f Turtle::Physic::GetLocalGravity()
{
	return m_localGravity;
}

Turtle::Vector2f Turtle::Physic::GetAllForces()
{
	return m_localGravity - m_acceleration * m_friction;
}

#include "Components/Physic.h"

Turtle::Physic::Physic(GameObject* parent, const std::string& name) : 
	Component(parent,name), 
	m_velocity(Vector2f::zero), 
	m_acceleration(Vector2f::zero), 
	m_mass(1),
	m_friction(0.2),
	Restitution(0.5)
{
}

Turtle::Physic::Physic(GameObject* parent, const std::string& name, Vector2f initialVelocity, Vector2f initialAcceleration, float mass, float friction, float restitution) :
	Component(parent, name), 
	m_velocity(initialVelocity),
	m_acceleration(initialAcceleration),
	m_mass(mass), 
	m_friction(friction),
	Restitution(restitution),
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
	return m_localGravity ;
}

void Turtle::Physic::InitPhysicParameters(Vector2f initialVelocity, Vector2f initialAcceleration, float mass, float friction, float restitution)
{
	m_velocity = initialVelocity;
	m_acceleration = initialAcceleration;
	m_mass = mass;
	m_friction = friction;
	Restitution = restitution;
}

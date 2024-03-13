#include "Components/Physic.h"

Turtle::Physic::Physic(GameObject* parent, const std::string& name) : 
	Component(parent,name), 
	m_velocity(Vector2f::zero), 
	m_acceleration(Vector2f::zero), 
	m_mass(1.f),
	m_friction(0.2f),
	Restitution(0.5f),
	AngularVelocity(0.f)
{
}

Turtle::Physic::Physic(GameObject* parent, const std::string& name, const Vector2f& initialVelocity, const Vector2f& initialAcceleration, float mass, float friction, float restitution, float angularVelocity) :
	Component(parent, name), 
	m_velocity(initialVelocity),
	m_acceleration(initialAcceleration),
	m_mass(mass), 
	m_friction(friction),
	Restitution(restitution),
	AngularVelocity(angularVelocity),
	m_localGravity(Vector2f::zero)
{
}

void Turtle::Physic::FixedUpdate(const Time& fixedTime)
{
	//update local gravity
}

const Turtle::Vector2f& Turtle::Physic::GetLocalGravity()
{
	return m_localGravity;
}

const Turtle::Vector2f& Turtle::Physic::GetAllForces()
{
	return m_localGravity ;
}

void Turtle::Physic::InitPhysicParameters(const Vector2f& initialVelocity, const Vector2f& initialAcceleration, float mass, float friction, float restitution, float angularVelocity)
{
	m_velocity = initialVelocity;
	m_acceleration = initialAcceleration;
	m_mass = mass;
	m_friction = friction;
	Restitution = restitution;
	AngularVelocity = angularVelocity;
	m_localGravity = Vector2f::zero;
}

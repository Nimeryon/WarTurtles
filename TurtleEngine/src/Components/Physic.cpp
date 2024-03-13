#include "Components/Physic.h"

Turtle::Physic::Physic(GameObject* parent, const std::string& name) : 
	Component(parent,name), 
	Velocity(Vector2f::zero), 
	Acceleration(Vector2f::zero), 
	Mass(1.f),
	StaticFriction(0.2f),
	DynamicFriction(0.5f),
	Restitution(0.5f),
	AngularVelocity(0.f)
{
}

Turtle::Physic::Physic(GameObject* parent, const std::string& name, const Vector2f& initialVelocity, const Vector2f& initialAcceleration, float mass, float staticFriction, float dynamicFriction, float restitution, float angularVelocity) :
	Component(parent, name), 
	Velocity(initialVelocity),
	Acceleration(initialAcceleration),
	Mass(mass), 
	StaticFriction(staticFriction),
	DynamicFriction(dynamicFriction),
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

void Turtle::Physic::AddImpulse(const Vector2f& impulse)
{
	Velocity += impulse / Mass;
}

void Turtle::Physic::InitPhysicParameters(const Vector2f& initialVelocity, const Vector2f& initialAcceleration, float mass, float staticFriction, float dynamicFriction, float restitution, float angularVelocity)
{
	Velocity = initialVelocity;
	Acceleration = initialAcceleration;
	Mass = mass;
	StaticFriction = staticFriction;
	DynamicFriction = dynamicFriction;
	Restitution = restitution;
	AngularVelocity = angularVelocity;
	m_localGravity = Vector2f::zero;
}

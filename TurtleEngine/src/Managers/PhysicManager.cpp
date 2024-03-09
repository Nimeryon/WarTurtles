#include "Managers/PhysicManager.h"
#include "Managers/SceneManager.h"

Turtle::PhysicManager::PhysicManager(Vector2f globalGravity) :
	m_globalGravity(globalGravity)
{}

const Turtle::PhysicManager& Turtle::PhysicManager::Instance()
{
	return SceneManager::Instance().GetCurrentScene()->GetPhysicManager();
}

void Turtle::PhysicManager::ComputeNewPositionFor(Physic& ObjectPhysicComponent, Transform& ObjectTransformComponent, const Turtle::Time& fixedTime) const
{
	Vector2f position = ObjectTransformComponent.GetPosition();

	ObjectPhysicComponent.m_acceleration = ( m_globalGravity + ObjectPhysicComponent.GetAllForces() ) / ObjectPhysicComponent.m_mass;
	position += ObjectPhysicComponent.m_velocity * fixedTime.asSeconds();
	ObjectPhysicComponent.m_velocity += ObjectPhysicComponent.m_acceleration * fixedTime.asSeconds();

	ObjectTransformComponent.SetPosition(position);
}

Turtle::Vector2f Turtle::PhysicManager::GetGlobalGravity() const
{
	return m_globalGravity;
}

void Turtle::PhysicManager::SetGlobalGravity(Vector2f newGravity)
{
	m_globalGravity = newGravity;
}

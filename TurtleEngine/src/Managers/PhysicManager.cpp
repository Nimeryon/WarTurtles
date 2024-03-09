#include "Managers/PhysicManager.h"
#include "Managers/SceneManager.h"

Turtle::PhysicManager::PhysicManager(Vector2f globalGravity) :
	m_globalGravity(globalGravity)
{}

const Turtle::PhysicManager& Turtle::PhysicManager::Instance()
{
	return SceneManager::Instance().GetCurrentScene()->GetPhysicManager();
}

void Turtle::PhysicManager::ComputeNewPositionFor(Physic& ObjectPhysicComponent, Transform& ObjectTransformComponent, const Time& fixedTime) const
{
	ObjectPhysicComponent.m_acceleration = ( m_globalGravity + ObjectPhysicComponent.GetAllForces() ) / ObjectPhysicComponent.m_mass;
	ObjectTransformComponent.Move(ObjectPhysicComponent.m_velocity * fixedTime.asSeconds());
	ObjectPhysicComponent.m_velocity += ObjectPhysicComponent.m_acceleration * fixedTime.asSeconds();
}

void Turtle::PhysicManager::ResolveCollisionFor(Physic& ObjectPhysicComponent, Transform& ObjectTransformComponent, Vector2f& normal, float value)
{
	if (ObjectPhysicComponent.m_bounciness > 0) {
		//Get the out vector ( current velocity reflected with normal ) 
	}
	else {
		ObjectTransformComponent.Move(normal * value);
	}
}

Turtle::Vector2f Turtle::PhysicManager::GetGlobalGravity() const
{
	return m_globalGravity;
}

void Turtle::PhysicManager::SetGlobalGravity(Vector2f newGravity)
{
	m_globalGravity = newGravity;
}

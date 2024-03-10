#include "Managers/PhysicManager.h"
#include "Managers/SceneManager.h"
#include "GameObjects/GameObject.h"

Turtle::PhysicManager::PhysicManager(Vector2f globalGravity) :
	m_globalGravity(globalGravity)
{}

const Turtle::PhysicManager& Turtle::PhysicManager::Instance()
{
	return SceneManager::Instance().GetCurrentScene()->GetPhysicManager();
}

void Turtle::PhysicManager::ComputeNewPositionFor(Physic& ObjectPhysicComponent, Transform& ObjectTransformComponent, const Turtle::Time& fixedTime) const
{
	ObjectPhysicComponent.m_acceleration = ( m_globalGravity + ObjectPhysicComponent.GetAllForces() ) / ObjectPhysicComponent.m_mass;
	ObjectTransformComponent.Move(ObjectPhysicComponent.m_velocity * fixedTime.asSeconds());
	ObjectPhysicComponent.m_velocity += ObjectPhysicComponent.m_acceleration * fixedTime.asSeconds();
}

void Turtle::PhysicManager::ResolveCollisionFor(GameObject& ObjectA, GameObject& ObjectB, Vector2f& normal, float value)
{
	Physic* ObjectAPhysicComponent = ObjectA.GetComponent<Physic>();
	Physic* ObjectBPhysicComponent = ObjectB.GetComponent<Physic>();

	if (ObjectBPhysicComponent) { // ObjectB can be just a wall
		Vector2f relativeVelocity = ObjectBPhysicComponent->m_velocity - ObjectAPhysicComponent->m_velocity;
		float minRestitution = std::min(ObjectAPhysicComponent->Restitution, ObjectBPhysicComponent->Restitution);
		float resultingForce = -(minRestitution + 1.f) * Vector2f::Dot(relativeVelocity, normal);
		resultingForce /= (1.f / ObjectAPhysicComponent->m_mass) + (1.f / ObjectBPhysicComponent->m_mass);

		ObjectAPhysicComponent->m_velocity -= normal * (resultingForce / ObjectAPhysicComponent->m_mass);
		ObjectBPhysicComponent->m_velocity += normal * (resultingForce / ObjectBPhysicComponent->m_mass);
	}
	else {
		Vector2f relativeVelocity = - ObjectAPhysicComponent->m_velocity;
		float minRestitution = ObjectAPhysicComponent->Restitution;
		float resultingForce = -(minRestitution + 1.f) * Vector2f::Dot(relativeVelocity, normal);
		resultingForce /= (1.f / ObjectAPhysicComponent->m_mass);

		ObjectAPhysicComponent->m_velocity -= normal * (resultingForce / ObjectAPhysicComponent->m_mass);
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

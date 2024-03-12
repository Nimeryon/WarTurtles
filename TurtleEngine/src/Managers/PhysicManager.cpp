#include "Managers/PhysicManager.h"
#include "Managers/SceneManager.h"
#include "GameObjects/GameObject.h"
#include "Components/Collisions/CollisionCallBacks.h"
#include "Components/Collisions/ICollisionComponent.h"

Turtle::PhysicManager::PhysicManager(Vector2f globalGravity) :
	m_globalGravity(globalGravity)
{
	// Same shape
	m_collisionDispatcher.add<CircleCollisionComponent, CircleCollisionComponent, collisionBetweenCircles>();
	m_collisionDispatcher.add<PolygonCollisionComponent, PolygonCollisionComponent, collisionBetweenPolygons>();
	m_collisionDispatcher.add<BoxCollisionComponent, BoxCollisionComponent, collisionBetweenBoxes>();

	// Circle / Polygon
	m_collisionDispatcher.add<CircleCollisionComponent, PolygonCollisionComponent, collisionBetweenCircleAndPolygon>();
	m_collisionDispatcher.add<PolygonCollisionComponent, CircleCollisionComponent, collisionBetweenPolygonAndCircle>();

	// Box / Polygon
	m_collisionDispatcher.add<BoxCollisionComponent, PolygonCollisionComponent, collisionBetweenBoxAndPolygon>();
	m_collisionDispatcher.add<PolygonCollisionComponent, BoxCollisionComponent, collisionBetweenPolygonAndBox>();

	// Box / Circle
	m_collisionDispatcher.add<BoxCollisionComponent, CircleCollisionComponent, collisionBetweenBoxAndCircle>();
	m_collisionDispatcher.add<CircleCollisionComponent, BoxCollisionComponent, collisionBetweenCircleAndBox>();
}

const Turtle::PhysicManager& Turtle::PhysicManager::Instance()
{
	return SceneManager::Instance().GetCurrentScene()->GetPhysicManager();
}

void Turtle::PhysicManager::ComputeNewPositionFor(Physic& ObjectPhysicComponent, Transform& ObjectTransformComponent, const Time& fixedTime) const
{
	ObjectPhysicComponent.m_acceleration += ( m_globalGravity + ObjectPhysicComponent.GetAllForces() ) / ObjectPhysicComponent.m_mass;
	ObjectTransformComponent.Move(ObjectPhysicComponent.m_velocity * fixedTime.asSeconds());
	ObjectPhysicComponent.m_velocity += ObjectPhysicComponent.m_acceleration * fixedTime.asSeconds();
}

void Turtle::PhysicManager::ResolveCollisionFor(GameObject& ObjectA, GameObject& ObjectB, Vector2f& normal, float value) const
{
	Physic* ObjectAPhysicComponent = ObjectA.GetComponent<Physic>();
	Physic* ObjectBPhysicComponent = ObjectB.GetComponent<Physic>();
	Transform* ObjectATransformComponent = ObjectA.GetTransform();
	Transform* ObjectBTransformComponent = ObjectB.GetTransform();

	if (ObjectBPhysicComponent) { // ObjectB can be just a wall
		ObjectATransformComponent->Move(-normal * value);
		ObjectBTransformComponent->Move(normal * value);

		Vector2f relativeVelocity = ObjectBPhysicComponent->m_velocity - ObjectAPhysicComponent->m_velocity;
		float minRestitution = std::min(ObjectAPhysicComponent->Restitution, ObjectBPhysicComponent->Restitution);
		float resultingForce = -(minRestitution + 1.f) * Vector2f::Dot(relativeVelocity, normal);
		resultingForce /= (1.f / ObjectAPhysicComponent->m_mass) + (1.f / ObjectBPhysicComponent->m_mass);

		ObjectAPhysicComponent->m_velocity -= normal * (resultingForce / ObjectAPhysicComponent->m_mass);
		ObjectBPhysicComponent->m_velocity += normal * (resultingForce / ObjectBPhysicComponent->m_mass);
	}
	else {
		ObjectATransformComponent->Move(-normal * value);
		Vector2f relativeVelocity = - ObjectAPhysicComponent->m_velocity;
		float minRestitution = ObjectAPhysicComponent->Restitution;
		float resultingForce = -(minRestitution + 1.f) * Vector2f::Dot(relativeVelocity, normal);
		resultingForce /= (1.f / ObjectAPhysicComponent->m_mass);

		ObjectAPhysicComponent->m_velocity -= normal * (resultingForce / ObjectAPhysicComponent->m_mass);
	}
}
void Turtle::PhysicManager::ResolveCollisions(const Time& fixedTime, std::vector<std::unique_ptr<GameObject>>& objects)
{
	for (auto& object : objects)
	{
		if (object->IsActive()) {
			Physic* objectPhysicComponent = object.get()->GetComponent<Physic>();
			ICollisionComponent* objectCollisionComponent = object.get()->GetComponent<ICollisionComponent>();
			if (objectPhysicComponent) {
				ComputeNewPositionFor(*objectPhysicComponent, *object.get()->GetTransform(), fixedTime);
				//TO MODIFY : for now, check all objects for collision
				for (auto& otherObject : objects) {
					if (otherObject != object) {
						Vector2f normal;
						float depth;
						ICollisionComponent* otherObjectCollisionComponent = otherObject.get()->GetComponent<ICollisionComponent>();
						if (otherObjectCollisionComponent && m_collisionDispatcher(*objectCollisionComponent, *otherObjectCollisionComponent, normal, depth))
						{
							ResolveCollisionFor(*object.get(), *otherObject.get(), normal, depth);
						}
					}
				}
			}
		}
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

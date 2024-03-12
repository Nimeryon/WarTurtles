#include "Managers/PhysicManager.h"
#include "Managers/SceneManager.h"
#include "GameObjects/GameObject.h"
#include "Components/Collisions/CollisionCallBacks.h"
#include "Components/Collisions/ContactPointsCollisionCallBacks.h"
#include "Components/Collisions/ICollisionComponent.h"

Turtle::PhysicManager::PhysicManager(Vector2f globalGravity) :
	m_globalGravity(globalGravity)
{
	// Same shape
	m_collisionDispatcher.add<CircleCollisionComponent, CircleCollisionComponent, collisionBetweenCircles>();
	m_contactPointsCollisionDispatcher.add<CircleCollisionComponent, CircleCollisionComponent, GetContactPointsBetweenCircles>();
	m_collisionDispatcher.add<PolygonCollisionComponent, PolygonCollisionComponent, collisionBetweenPolygons>();
	m_contactPointsCollisionDispatcher.add<PolygonCollisionComponent, PolygonCollisionComponent, GetContactPointsBetweenPolygons>();
	m_collisionDispatcher.add<BoxCollisionComponent, BoxCollisionComponent, collisionBetweenBoxes>();
	m_contactPointsCollisionDispatcher.add<BoxCollisionComponent, BoxCollisionComponent, GetContactPointsBetweenBoxes>();

	// Circle / Polygon
	m_collisionDispatcher.add<CircleCollisionComponent, PolygonCollisionComponent, collisionBetweenCircleAndPolygon>();
	m_contactPointsCollisionDispatcher.add<CircleCollisionComponent, PolygonCollisionComponent, GetContactPointsBetweenCircleAndPolygon>();
	m_collisionDispatcher.add<PolygonCollisionComponent, CircleCollisionComponent, collisionBetweenPolygonAndCircle>();
	m_contactPointsCollisionDispatcher.add<PolygonCollisionComponent, CircleCollisionComponent, GetContactPointsBetweenPolygonAndCircle>();

	// Box / Polygon
	m_collisionDispatcher.add<BoxCollisionComponent, PolygonCollisionComponent, collisionBetweenBoxAndPolygon>();
	m_contactPointsCollisionDispatcher.add<BoxCollisionComponent, PolygonCollisionComponent, GetContactPointsBetweenBoxAndPolygon>();
	m_collisionDispatcher.add<PolygonCollisionComponent, BoxCollisionComponent, collisionBetweenPolygonAndBox>();
	m_contactPointsCollisionDispatcher.add<PolygonCollisionComponent, BoxCollisionComponent, GetContactPointsBetweenPolygonAndBox>();

	// Box / Circle
	m_collisionDispatcher.add<BoxCollisionComponent, CircleCollisionComponent, collisionBetweenBoxAndCircle>();
	m_contactPointsCollisionDispatcher.add<BoxCollisionComponent, CircleCollisionComponent, GetContactPointsBetweenBoxAndCircle>();
	m_collisionDispatcher.add<CircleCollisionComponent, BoxCollisionComponent, collisionBetweenCircleAndBox>();
	m_contactPointsCollisionDispatcher.add<CircleCollisionComponent, BoxCollisionComponent, GetContactPointsBetweenCircleAndBox>();
}

const Turtle::PhysicManager& Turtle::PhysicManager::Instance()
{
	return SceneManager::Instance().GetCurrentScene()->GetPhysicManager();
}

void Turtle::PhysicManager::ComputeNewPositionFor(Physic& ObjectPhysicComponent, Transform& ObjectTransformComponent, const Time& fixedTime) const
{
	ObjectPhysicComponent.m_acceleration = m_globalGravity + ObjectPhysicComponent.GetAllForces(); // / ObjectPhysicComponent.Mass
	ObjectTransformComponent.Move(ObjectPhysicComponent.m_velocity * fixedTime.asSeconds());
	ObjectPhysicComponent.m_velocity += ObjectPhysicComponent.m_acceleration * fixedTime.asSeconds();
	ObjectTransformComponent.Rotate(ObjectPhysicComponent.AngularVelocity);
}

void Turtle::PhysicManager::ResolveCollisionFor(GameObject& ObjectA, GameObject& ObjectB, Vector2f& normal, float value)
{
	Physic* ObjectAPhysicComponent = ObjectA.GetComponent<Physic>();
	Physic* ObjectBPhysicComponent = ObjectB.GetComponent<Physic>();
	Transform* ObjectATransformComponent = ObjectA.GetTransform();
	Transform* ObjectBTransformComponent = ObjectB.GetTransform();
	ICollisionComponent* ObjectACollisionComponent = ObjectA.GetComponent<ICollisionComponent>();
	ICollisionComponent* ObjectBCollisionComponent = ObjectB.GetComponent<ICollisionComponent>();

	if (ObjectBPhysicComponent) { // ObjectB can be just a wall
		ObjectATransformComponent->Move(-normal * value);
		ObjectBTransformComponent->Move(normal * value);

		auto contactPoints = m_contactPointsCollisionDispatcher(*ObjectACollisionComponent, *ObjectBCollisionComponent);
		std::vector<Vector2f> impulses;
		std::vector<Vector2f> raList;
		std::vector<Vector2f> rbList;

		Vector2f relativeVelocity;
		float resultingForce;

		for (int i = 0; i < contactPoints.size(); ++i) {
			Vector2f ra = contactPoints[i] - ObjectACollisionComponent->GetCenter();
			raList.emplace_back(ra);
			Vector2f rb = contactPoints[i] - ObjectBCollisionComponent->GetCenter();
			rbList.emplace_back(rb);

			Vector2f raNormal = Vector2f::Perpendicular(ra);
			Vector2f rbNormal = Vector2f::Perpendicular(rb);

			Vector2f angularLinearVelocityA = raNormal * ObjectAPhysicComponent->AngularVelocity;
			Vector2f angularLinearVelocityB = rbNormal * ObjectBPhysicComponent->AngularVelocity;

			relativeVelocity = (ObjectBPhysicComponent->m_velocity + angularLinearVelocityB) -
				(ObjectAPhysicComponent->m_velocity + angularLinearVelocityA);

			float contactVelocityMagnitude = Vector2f::Dot(relativeVelocity, normal);

			if (contactVelocityMagnitude > 0.f)
				continue;

			float raNormalDotN = Vector2f::Dot(raNormal, normal);
			float rbNormalDotN = Vector2f::Dot(rbNormal, normal);

			float denom = 1 / ObjectAPhysicComponent->m_mass + 1 / ObjectBPhysicComponent->m_mass +
				raNormalDotN * raNormalDotN / ObjectACollisionComponent->CalculateRotationalInertia(ObjectAPhysicComponent->m_mass) + 
				rbNormalDotN * rbNormalDotN / ObjectBCollisionComponent->CalculateRotationalInertia(ObjectBPhysicComponent->m_mass);

			float minRestitution = std::min(ObjectAPhysicComponent->Restitution, ObjectBPhysicComponent->Restitution);

			resultingForce = -(minRestitution + 1.f) * contactVelocityMagnitude;
			resultingForce /= denom;
			resultingForce /= contactPoints.size(); //Divide by two if there is two contact points. It cannot more

			Vector2f impulse = normal * resultingForce;
			impulses.emplace_back(impulse);
		}

		for (int i = 0; i < impulses.size(); ++i) {
			Vector2f curImpulse = impulses[i];
			Vector2f ra = raList[i];
			Vector2f rb = rbList[i];
			ObjectAPhysicComponent->m_velocity -= curImpulse / ObjectAPhysicComponent->m_mass;
			ObjectAPhysicComponent->AngularVelocity -= Vector2f::Cross(ra,curImpulse) / ObjectACollisionComponent->CalculateRotationalInertia(ObjectAPhysicComponent->m_mass);
			ObjectBPhysicComponent->m_velocity += curImpulse / ObjectBPhysicComponent->m_mass;
			ObjectBPhysicComponent->AngularVelocity += Vector2f::Cross(rb,curImpulse) / ObjectBCollisionComponent->CalculateRotationalInertia(ObjectBPhysicComponent->m_mass);
		}
		//Code before torque
		/*
		Vector2f relativeVelocity = ObjectBPhysicComponent->m_velocity - ObjectAPhysicComponent->m_velocity;
		float minRestitution = std::min(ObjectAPhysicComponent->Restitution, ObjectBPhysicComponent->Restitution);
		float resultingForce = -(minRestitution + 1.f) * Vector2f::Dot(relativeVelocity, normal);
		resultingForce /= (1.f / ObjectAPhysicComponent->m_mass) + (1.f / ObjectBPhysicComponent->m_mass);

		ObjectAPhysicComponent->m_velocity -= normal * (resultingForce / ObjectAPhysicComponent->m_mass);
		ObjectBPhysicComponent->m_velocity += normal * (resultingForce / ObjectBPhysicComponent->m_mass);
		*/

	}
	else {
		ObjectATransformComponent->Move(-normal * value);

		auto contactPoints = m_contactPointsCollisionDispatcher(*ObjectACollisionComponent, *ObjectBCollisionComponent);
		std::vector<Vector2f> impulses;
		std::vector<Vector2f> raList;
		std::vector<Vector2f> rbList;

		Vector2f relativeVelocity;
		float resultingForce;

		for (int i = 0; i < contactPoints.size(); ++i) {
			Vector2f ra = contactPoints[i] - ObjectACollisionComponent->GetCenter();
			raList.emplace_back(ra);

			Vector2f raNormal = Vector2f::Perpendicular(ra);

			Vector2f angularLinearVelocityA = raNormal * ObjectAPhysicComponent->AngularVelocity;

			relativeVelocity = -(ObjectAPhysicComponent->m_velocity + angularLinearVelocityA);

			float contactVelocityMagnitude = Vector2f::Dot(relativeVelocity, normal);

			if (contactVelocityMagnitude > 0.f)
				continue;

			float raNormalDotN = Vector2f::Dot(raNormal, normal);

			float denom = 1 / ObjectAPhysicComponent->m_mass +
				raNormalDotN * raNormalDotN / ObjectACollisionComponent->CalculateRotationalInertia(ObjectAPhysicComponent->m_mass);

			float minRestitution = ObjectAPhysicComponent->Restitution;

			resultingForce = -(minRestitution + 1.f) * contactVelocityMagnitude;
			resultingForce /= denom;
			resultingForce /= contactPoints.size(); //Divide by two if there is two contact points. It cannot more

			Vector2f impulse = normal * resultingForce;
			impulses.emplace_back(impulse);
		}

		for (int i = 0; i < impulses.size(); ++i) {
			Vector2f curImpulse = impulses[i];
			Vector2f ra = raList[i];
			ObjectAPhysicComponent->m_velocity -= curImpulse / ObjectAPhysicComponent->m_mass;
			ObjectAPhysicComponent->AngularVelocity -= Vector2f::Cross(ra, curImpulse) / ObjectACollisionComponent->CalculateRotationalInertia(ObjectAPhysicComponent->m_mass);
		}
		//Code before torque
		/*
		Vector2f relativeVelocity = - ObjectAPhysicComponent->m_velocity;
		float minRestitution = ObjectAPhysicComponent->Restitution;
		float resultingForce = -(minRestitution + 1.f) * Vector2f::Dot(relativeVelocity, normal);
		resultingForce /= (1.f / ObjectAPhysicComponent->m_mass);

		ObjectAPhysicComponent->m_velocity -= normal * (resultingForce / ObjectAPhysicComponent->m_mass);
		*/
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

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
	ObjectPhysicComponent.Acceleration = m_globalGravity + ObjectPhysicComponent.GetAllForces(); // / ObjectPhysicComponent.Mass
	ObjectTransformComponent.Move(ObjectPhysicComponent.Velocity * fixedTime.asSeconds());
	ObjectPhysicComponent.Velocity += ObjectPhysicComponent.Acceleration * fixedTime.asSeconds();
	ObjectTransformComponent.Rotate(ObjectPhysicComponent.AngularVelocity);
}

void Turtle::PhysicManager::ResolveCollisionFor(GameObject& ObjectA, GameObject& ObjectB, Vector2f& normal, float value)
{
	Transform* ObjectATransformComponent = ObjectA.GetTransform();
	Transform* ObjectBTransformComponent = ObjectB.GetTransform();
	Physic* ObjectBPhysicComponent = ObjectB.GetComponent<Physic>();

	ObjectATransformComponent->Move(-normal * value);
	if(ObjectBPhysicComponent) // if not, B is static
		ObjectBTransformComponent->Move(normal * value);

	std::vector<float> appliedForces;

	CalculateVelocityAndTorqueFor(ObjectA, ObjectB, normal, appliedForces);
	CalculateFriction(ObjectA, ObjectB, normal, appliedForces);

	ObjectA.OnCollide(ObjectB);
	ObjectB.OnCollide(ObjectA);
}
void Turtle::PhysicManager::ResolveCollisions(const Time& fixedTime, std::vector<std::unique_ptr<GameObject>>& objects)
{
	for (auto& object : objects)
	{
		if(!object.get())return;
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

void Turtle::PhysicManager::CalculateVelocityAndTorqueFor(GameObject& ObjectA, GameObject& ObjectB, const Vector2f& normal, std::vector<float>& appliedForces)
{
	appliedForces.clear();
	ICollisionComponent* ObjectACollisionComponent = ObjectA.GetComponent<ICollisionComponent>();
	ICollisionComponent* ObjectBCollisionComponent = ObjectB.GetComponent<ICollisionComponent>();
	Physic* ObjectAPhysicComponent = ObjectA.GetComponent<Physic>();
	Physic* ObjectBPhysicComponent = ObjectB.GetComponent<Physic>();

	auto contactPoints = m_contactPointsCollisionDispatcher(*ObjectACollisionComponent, *ObjectBCollisionComponent);
	appliedForces.assign(contactPoints.size(), 0.f);
	std::vector<Vector2f> impulses;
	std::vector<Vector2f> raList;
	std::vector<Vector2f> rbList;

	for (int i = 0; i < contactPoints.size(); ++i) {
		Vector2f ra = contactPoints[i] - ObjectACollisionComponent->GetCenter();
		raList.emplace_back(ra);
		Vector2f raNormal = Vector2f::Perpendicular(ra);
		Vector2f angularLinearVelocityA = raNormal * ObjectAPhysicComponent->AngularVelocity;
		float raNormalDotN = Vector2f::Dot(raNormal, normal);


		Vector2f relativeVelocity;
		float denom;
		float minRestitution;

		if (ObjectBPhysicComponent) {
			Vector2f rb = contactPoints[i] - ObjectBCollisionComponent->GetCenter();
			rbList.emplace_back(rb);
			Vector2f rbNormal = Vector2f::Perpendicular(rb);
			Vector2f angularLinearVelocityB = rbNormal * ObjectBPhysicComponent->AngularVelocity;
			float rbNormalDotN = Vector2f::Dot(rbNormal, normal);

			relativeVelocity = (ObjectBPhysicComponent->Velocity + angularLinearVelocityB) -
				(ObjectAPhysicComponent->Velocity + angularLinearVelocityA);

			denom = 1 / ObjectAPhysicComponent->Mass + 1 / ObjectBPhysicComponent->Mass +
				raNormalDotN * raNormalDotN / ObjectACollisionComponent->CalculateRotationalInertia(ObjectAPhysicComponent->Mass) +
				rbNormalDotN * rbNormalDotN / ObjectBCollisionComponent->CalculateRotationalInertia(ObjectBPhysicComponent->Mass);

			minRestitution = std::min(ObjectAPhysicComponent->Restitution, ObjectBPhysicComponent->Restitution);
		}
		else {
			relativeVelocity = -(ObjectAPhysicComponent->Velocity + angularLinearVelocityA);
			denom = 1 / ObjectAPhysicComponent->Mass +
				raNormalDotN * raNormalDotN / ObjectACollisionComponent->CalculateRotationalInertia(ObjectAPhysicComponent->Mass);

			minRestitution = ObjectAPhysicComponent->Restitution;
		}

		float contactVelocityMagnitude = Vector2f::Dot(relativeVelocity, normal);

		if (contactVelocityMagnitude > 0.f)
			continue;

		float resultingForce = -(minRestitution + 1.f) * contactVelocityMagnitude;
		resultingForce /= denom;
		resultingForce /= contactPoints.size(); //Divide by two if there is two contact points. It cannot more

		Vector2f impulse = normal * resultingForce;
		impulses.emplace_back(impulse);
		appliedForces[i] = resultingForce;
	}

	for (int i = 0; i < impulses.size(); ++i) {
		Vector2f curImpulse = impulses[i];
		Vector2f ra = raList[i];
		ObjectAPhysicComponent->Velocity -= curImpulse / ObjectAPhysicComponent->Mass;
		ObjectAPhysicComponent->AddAngularVelocity(- Vector2f::Cross(ra, curImpulse) / ObjectACollisionComponent->CalculateRotationalInertia(ObjectAPhysicComponent->Mass));
		if (ObjectBPhysicComponent) {
			Vector2f rb = rbList[i];
			ObjectBPhysicComponent->Velocity += curImpulse / ObjectBPhysicComponent->Mass;
			ObjectBPhysicComponent->AddAngularVelocity(Vector2f::Cross(rb, curImpulse) / ObjectBCollisionComponent->CalculateRotationalInertia(ObjectBPhysicComponent->Mass));
		}
	}
}

void Turtle::PhysicManager::CalculateFriction(GameObject& ObjectA, GameObject& ObjectB, const Vector2f& normal, std::vector<float>& appliedForces)
{
	ICollisionComponent* ObjectACollisionComponent = ObjectA.GetComponent<ICollisionComponent>();
	ICollisionComponent* ObjectBCollisionComponent = ObjectB.GetComponent<ICollisionComponent>();
	Physic* ObjectAPhysicComponent = ObjectA.GetComponent<Physic>();
	Physic* ObjectBPhysicComponent = ObjectB.GetComponent<Physic>();

	auto contactPoints = m_contactPointsCollisionDispatcher(*ObjectACollisionComponent, *ObjectBCollisionComponent);
	std::vector<Vector2f> impulses;
	std::vector<Vector2f> raList;
	std::vector<Vector2f> rbList;
	float sf, df;
	if (ObjectBPhysicComponent) {
		sf = (ObjectAPhysicComponent->StaticFriction + ObjectBPhysicComponent->StaticFriction) * 0.5f;
		df = (ObjectAPhysicComponent->DynamicFriction + ObjectBPhysicComponent->DynamicFriction) * 0.5f;
	}
	else {
		sf = ObjectAPhysicComponent->StaticFriction;
		df = ObjectAPhysicComponent->DynamicFriction;
	}
	

	for (int i = 0; i < contactPoints.size(); ++i) {
		Vector2f ra = contactPoints[i] - ObjectACollisionComponent->GetCenter();
		raList.emplace_back(ra);
		Vector2f raNormal = Vector2f::Perpendicular(ra);
		Vector2f angularLinearVelocityA = raNormal * ObjectAPhysicComponent->AngularVelocity;


		Vector2f relativeVelocity;
		float denom;
		Vector2f rbNormal;

		if (ObjectBPhysicComponent) {
			Vector2f rb = contactPoints[i] - ObjectBCollisionComponent->GetCenter();
			rbList.emplace_back(rb);
			rbNormal = Vector2f::Perpendicular(rb);
			Vector2f angularLinearVelocityB = rbNormal * ObjectBPhysicComponent->AngularVelocity;

			relativeVelocity = (ObjectBPhysicComponent->Velocity + angularLinearVelocityB) -
				(ObjectAPhysicComponent->Velocity + angularLinearVelocityA);

		}
		else {
			relativeVelocity = -(ObjectAPhysicComponent->Velocity + angularLinearVelocityA);
		}

		Vector2f tangent = relativeVelocity - normal * Vector2f::Dot(relativeVelocity, normal);
		if (tangent == Vector2f::zero) {
			continue;
		}
		else {
			tangent.Normalize();
		}

		float raNormalDotT = Vector2f::Dot(raNormal, tangent);
		if (ObjectBPhysicComponent) {
			float rbNormalDotT = Vector2f::Dot(rbNormal, tangent);
			denom = 1 / ObjectAPhysicComponent->Mass + 1 / ObjectBPhysicComponent->Mass +
				raNormalDotT * raNormalDotT / ObjectACollisionComponent->CalculateRotationalInertia(ObjectAPhysicComponent->Mass) +
				rbNormalDotT * rbNormalDotT / ObjectBCollisionComponent->CalculateRotationalInertia(ObjectBPhysicComponent->Mass);
		}
		else {
			denom = 1 / ObjectAPhysicComponent->Mass +
				raNormalDotT * raNormalDotT / ObjectACollisionComponent->CalculateRotationalInertia(ObjectAPhysicComponent->Mass);
		}

		float resultingForce = -Vector2f::Dot(relativeVelocity, tangent);
		resultingForce /= denom;
		resultingForce /= contactPoints.size(); //Divide by two if there is two contact points. It cannot more

		Vector2f impulse;
		float contactVelocityMagnitude = Vector2f::Dot(relativeVelocity, normal);
		if (std::abs(resultingForce) <= appliedForces[i] * sf) {
			impulse = tangent * resultingForce;
		}
		else {
			impulse = tangent * df * -appliedForces[i];
		}
	
		impulses.emplace_back(impulse);
	}

	for (int i = 0; i < impulses.size(); ++i) {
		Vector2f curImpulse = impulses[i];
		Vector2f ra = raList[i];
		ObjectAPhysicComponent->Velocity -= curImpulse / ObjectAPhysicComponent->Mass;
		ObjectAPhysicComponent->AddAngularVelocity(- Vector2f::Cross(ra, curImpulse) / ObjectACollisionComponent->CalculateRotationalInertia(ObjectAPhysicComponent->Mass));
		if (ObjectBPhysicComponent) {
			Vector2f rb = rbList[i];
			ObjectBPhysicComponent->Velocity += curImpulse / ObjectBPhysicComponent->Mass;
			ObjectBPhysicComponent->AddAngularVelocity(Vector2f::Cross(rb, curImpulse) / ObjectBCollisionComponent->CalculateRotationalInertia(ObjectBPhysicComponent->Mass));
		}
	}
}

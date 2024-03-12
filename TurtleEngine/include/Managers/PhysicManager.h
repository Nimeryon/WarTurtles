// Physic.h
#ifndef PHYSICMANAGER_H
#define PHYSICMANAGER_H
#include "Types/Vector2.h"
#include "Utils/Time.h"
#include "Components/Physic.h"
#include "Components/Collisions/CollisionDispatcher.h"

namespace Turtle
{
	class GameObject;
	class Transform;
	class ICollisionComponent;

	class PhysicManager final
	{
	public:
		PhysicManager(Vector2f globalGravity = {0, 9.81f});
		PhysicManager(PhysicManager&) = delete;
		~PhysicManager() = default;

		static const PhysicManager& Instance();

		void ComputeNewPositionFor(Physic& ObjectPhysicComponent, Transform& ObjectTransformComponent, const Time& fixedTime) const;
		void ResolveCollisionFor(GameObject& ObjectA, GameObject& ObjectB, Vector2f& normal, float value) const;
		void ResolveCollisions(const Time& fixedTime, std::vector<std::unique_ptr<GameObject>>& objects);

		Vector2f GetGlobalGravity() const;

		void SetGlobalGravity(Vector2f newGravity);

	private:
		Vector2f m_globalGravity;
		CollisionDispatcher<ICollisionComponent> m_collisionDispatcher;
	};
}
#endif // PHYSICMANAGER_H
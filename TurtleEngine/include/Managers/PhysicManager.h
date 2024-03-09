// Physic.h
#ifndef PHYSICMANAGER_H
#define PHYSICMANAGER_H
#include "Types/Vector2.h"
#include "Utils/Time.h"
#include "Components/Physic.h"

namespace Turtle
{
	class Transform;
	class PhysicManager final
	{
	public:
		
		PhysicManager(PhysicManager&) = delete;
		~PhysicManager() = default;
		explicit PhysicManager(Vector2f globalGravity = {0, -9.81f});

		static const PhysicManager& Instance();
		void ComputeNewPositionFor(Physic& ObjectPhysicComponent, Transform& ObjectTransformComponent, const Time& fixedTime)const;
		void ResolveCollisionFor(Physic& ObjectPhysicComponent, Transform& ObjectTransformComponent, Vector2f& normal, float value);
		Vector2f GetGlobalGravity() const;

		void SetGlobalGravity(Vector2f newGravity);
		
	private:
		Vector2f m_globalGravity;
	};
}
#endif // !PHYSICMANAGER_H
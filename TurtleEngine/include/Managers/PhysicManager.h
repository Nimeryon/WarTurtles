// Physic.h
#ifndef PHYSICMANAGER_H
#define PHYSICMANAGER_H
#include "Types/Vector2.h"
#include "Utils/Time.h"
#include "GameObjects/GameObject.h"
#include "Components/Physic.h"
#include <Components/Transform.h>

namespace Turtle
{
	class PhysicManager final
	{
	public:
		explicit PhysicManager(Vector2f globalGravity);

		void ComputeNewPositionFor(Physic& ObjectPhysicComponent, Transform& ObjectTransformComponent, const Time& fixedTime);
		void ResolveCollisionFor(Physic& ObjectPhysicComponent, Transform& ObjectTransformComponent, Vector2f& normal, float value);
		Vector2f GetGlobalGravity() const;

		void SetGlobalGravity(Vector2f newGravity);
		
	private:
		Vector2f m_globalGravity;
	};
}
#endif // !PHYSICMANAGER_H
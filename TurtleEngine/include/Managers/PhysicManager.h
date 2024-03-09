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
		PhysicManager(Vector2f globalGravity = {0, -9.81f});
		PhysicManager(PhysicManager&) = delete;
		~PhysicManager() = default;

		static const PhysicManager& Instance();

		void ComputeNewPositionFor(Physic& ObjectPhysicComponent, Transform& ObjectTransformComponent, const Time& fixedTime) const;
		Vector2f GetGlobalGravity() const;

		void SetGlobalGravity(Vector2f newGravity);
		
	private:
		Vector2f m_globalGravity;
	};
}
#endif // PHYSICMANAGER_H
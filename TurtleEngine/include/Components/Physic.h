// Physic.h
#ifndef PHYSIC_H
#define PHYSIC_H
#include "Components/Component.h"
#include "Types/Vector2.h"

namespace Turtle
{
	class Physic : public Component
	{
	public:
		Physic() = delete;
		Physic(GameObject* parent, const std::string& name = "Physic Component");
		Physic(GameObject* parent, const std::string& name,const Vector2f initialVelocity, const Vector2f initialAcceleration, float mass = 1, float staticFriction = 0.2, float dynamicFriction = 0.2, float restitution = 0.5, float angularVelocity = 0.f);

		void FixedUpdate(const Time& fixedTime) override;

		const Vector2f& GetLocalGravity();
		const Vector2f& GetAllForces();

		void AddImpulse(const Vector2f& impulse);

		void InitPhysicParameters(const Vector2f initialVelocity, const Vector2f initialAcceleration, float mass, float staticFriction, float dynamicFriction, float restitution, float angularVelocity);

		Vector2f Velocity;
		Vector2f Acceleration;
		float Mass;
		float StaticFriction; // 0 to 1 : 0 = no friction ( like in space ), 1 = will not be able to move
		float DynamicFriction;
		float Restitution;
		float AngularVelocity;
		Vector2f m_localGravity; // local gravity, i.e magnet...
	};
}
#endif // !PHYSIC_H


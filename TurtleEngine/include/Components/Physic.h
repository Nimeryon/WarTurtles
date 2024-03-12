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
		Physic(GameObject* parent, const std::string& name,Vector2f initialVelocity, Vector2f initialAcceleration, float mass = 1, float friction = 0.2, float restitution = 0.5);

		void FixedUpdate(const Time& fixedTime) override;

		Vector2f GetLocalGravity();
		Vector2f GetAllForces();

		void InitPhysicParameters(Vector2f initialVelocity, Vector2f initialAcceleration, float mass, float friction, float restitution);

		Vector2f m_velocity;
		Vector2f m_acceleration;
		float m_mass;
		float m_friction; // 0 to 1 : 0 = no friction ( like in space ), 1 = will not be able to move
		float Restitution;
		float AngularVelocity;
		Vector2f m_localGravity; // local gravity, i.e magnet...
	};
}
#endif // !PHYSIC_H


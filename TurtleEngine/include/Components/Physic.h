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
		Physic(GameObject* parent, const std::string& name,Vector2f initialVelocity, Vector2f initialAcceleration, float mass = 1, float friction = 0.2, float bounciness = 0.1);

		void FixedUpdate(const Time& fixedTime) override;

		Vector2f GetLocalGravity();
		Vector2f GetAllForces();

		Vector2f m_velocity;
		Vector2f m_acceleration;
		float m_mass;
		float m_friction; // 0 to 1 : 0 = no friction ( like in space ), 1 = will not be able to move
		float m_bounciness; // 0 to 1 : 0 = no bounce ( will stop if encounter a wall ), 1 = will bounce at same acceleration
		Vector2f m_localGravity; // local gravity, i.e magnet...
	};
}
#endif // !PHYSIC_H


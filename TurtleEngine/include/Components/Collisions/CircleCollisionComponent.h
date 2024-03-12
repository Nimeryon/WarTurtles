// CircleCollisionComponent.h
#ifndef CIRCLECOLLISIONCOMPONENT_H
#define CIRCLECOLLISIONCOMPONENT_H
#include <SFML/Graphics.hpp>

#include "Components/Collisions/ICollisionComponent.h"
#include "Types/Vector2.h"

namespace Turtle
{
	class CircleCollisionComponent : public ICollisionComponent
	{
	public:
		CircleCollisionComponent() = delete;
		explicit CircleCollisionComponent(GameObject* parent, const std::string& name = "Collision Component (Circle)");

		void InitCollisionParameters(const Vector2f& position, float radius);

		const Vector2f& GetPosition() const;
		Vector2f GetCenter() const override;
		float CalculateRotationalInertia(float mass) override;
		float GetRadius() const;

		void SetPosition(const Vector2f& position);
		void SetRadius(float radius);

		static void ProjectCircle(const CircleCollisionComponent& circle, const Vector2f& axis, float& min, float& max);


		void DebugDraw(Window& window) override;

	private:
		Vector2f m_position;
		float m_radius;

		sf::CircleShape m_debugShape;
		sf::RectangleShape m_debugLineShape;
	};
}
#endif // CIRCLECOLLISIONCOMPONENT_H

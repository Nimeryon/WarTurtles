// CircleCollisionComponent.h
#ifndef CIRCLECOLLISIONCOMPONENT_H
#define CIRCLECOLLISIONCOMPONENT_H
#include "Components/Collisions/ICollisionComponent.h"
#include "Types/Shapes/CircleShape.h"
#include "Types/Vector2.h"

namespace Turtle
{
	class CircleCollisionComponent : public ICollisionComponent
	{
	public:
		CircleCollisionComponent() = delete;
		explicit CircleCollisionComponent(GameObject* parent, const std::string& name = "Collision Component (Circle)");
		CircleCollisionComponent(GameObject* parent, const std::string& name, CircleShape& circleCollision);
		CircleCollisionComponent(GameObject* parent, const std::string& name, Vector2f& center, float radius);

		void UpdateCollisionTransform(Transform& transform) override;
		const CircleShape& GetShape() const override;

		void InitCollisionParameters(Vector2f& center, float radius);
		void InitCollisionParameters(CircleShape& circleCollision);

	private:
		CircleShape CollisionCircle;
	};
}
#endif // !CIRCLECOLLISIONCOMPONENT_H


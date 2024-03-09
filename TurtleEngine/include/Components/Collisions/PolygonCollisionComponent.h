// PolygonCollisionComponent.h
#ifndef POLYGONCOLLISIONCOMPONENT_H
#define POLYGONCOLLISIONCOMPONENT_H
#include "Components/Collisions/ICollisionComponent.h"
#include "Types/Shapes/PolygonShape.h"
#include "Types/Vector2.h"

namespace Turtle
{
	class PolygonCollisionComponent : public ICollisionComponent
	{
	public:
		PolygonCollisionComponent() = delete;
		PolygonCollisionComponent(GameObject* parent, const std::string& name, PolygonShape& polygonCollision);
		PolygonCollisionComponent(GameObject* parent, const std::string& name, Vector2f& location, float rotation, float width, float height);

		void UpdateCollisionTransform(Transform& transform) override;
		const PolygonShape& GetShape() const override;

	private:
		PolygonShape CollisionPolygon;
	};
}
#endif // !POLYGONCOLLISIONCOMPONENT_H


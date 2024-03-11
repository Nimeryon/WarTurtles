// PolygonCollisionComponent.h
#ifndef POLYGONCOLLISIONCOMPONENT_H
#define POLYGONCOLLISIONCOMPONENT_H
#include "Components/Collisions/ICollisionComponent.h"
#include "Types/Vector2.h"

namespace Turtle
{
	class PolygonCollisionComponent : public ICollisionComponent
	{
	public:
		PolygonCollisionComponent() = delete;
		explicit PolygonCollisionComponent(GameObject* parent, const std::string& name = "Collision Component (Polygon)");

		void InitCollisionParameters(const std::vector<Vector2f>& vertice);

		const std::vector<Vector2f>& GetVertice() const;
		Vector2f GetCenter() const override;

		void SetVertice(const std::vector<Vector2f>& vertice);

		std::vector<Vector2f> GetTransformedVertice() const;

		static bool ProjectTransformedVertices(const PolygonCollisionComponent& polygon, const Vector2f& axis, float& min, float& max);
		static bool FindNearestPointTo(const Vector2f& location, const PolygonCollisionComponent& polygon, Vector2f& nearestPoint);

	protected:
		std::vector<Vector2f> m_vertice;
	};
}
#endif // POLYGONCOLLISIONCOMPONENT_H

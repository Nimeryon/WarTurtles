// PolygonShape.h
#ifndef POLYGONSHAPE_H // include guard
#define POLYGONSHAPE_H
#include "Types/Shapes/IShape.h"
#include "Types/Vector2.h"

namespace Turtle
{
class PolygonShape : public IShape {
public:
	PolygonShape() = delete;
	PolygonShape(Vector2f& position, float rotation, std::vector<Vector2f> Vertices);

	void UpdateShapeFromTransform(Transform& transform) override;
	Vector2f GetCenter();

	Vector2f Position;
	float Rotation;
	std::vector<Vector2f> Vertices;
	std::vector<Vector2f> TransformedVertices;
	bool NeedToUpdateTransformedVertices;

	static bool ProjectTransformedVertices(const PolygonShape& polygon, const Vector2f& axis, float& min, float& max);
	static bool FindNearestPointTo(const Vector2f& location, const PolygonShape& polygon, Vector2f& nearestPoint);

private:
	virtual void CreateVertices();
};
}

#endif /* POLYGONSHAPE_H */
// PolygonShape.h
#ifndef POLYGONSHAPE_H // include guard
#define POLYGONSHAPE_H
#include "Types/Shapes/IShape.h"
#include "Types/Vector2.h"

namespace Turtle
{
class PolygonShape : public IShape {
public:
	PolygonShape();
	PolygonShape(Vector2f& position, float rotation, std::vector<Vector2f> Vertices);

	Vector2f GetCenter(const Transform& transform);

	Vector2f Position;
	float Rotation;
	std::vector<Vector2f> Vertices;

	static bool ProjectTransformedVertices(const PolygonShape& polygon, const Vector2f& axis, float& min, float& max);
	static bool FindNearestPointTo(const Vector2f& location, const PolygonShape& polygon, Vector2f& nearestPoint);

	std::vector<Vector2f> GetTransformVertices(const Transform& transform);

private:
	virtual void CreateVertices();
};
}

#endif /* POLYGONSHAPE_H */
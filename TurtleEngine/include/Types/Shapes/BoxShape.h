// BoxShape.h
#ifndef BOXSHAPE_H // include guard
#define BOXSHAPE_H
#include "Types/Shapes/IShape.h"
#include "Types/Vector2.h"

namespace Turtle
{
class BoxShape : public IShape {
public:
	BoxShape() = delete;
	BoxShape(Vector2f& position, float rotation, float width, float height);

	void UpdateShapeFromTransform(Transform& transform) override;
	Vector2f& GetCenter();

	Vector2f Position;
	float Rotation;
	float Width;
	float Height;
	std::vector<Vector2f> Vertices;
	std::vector<Vector2f> TransformedVertices;
	std::vector<int> Triangles;
	bool NeedToUpdateTransformedVertices;

	static bool ProjectTransformedVertices(const BoxShape& box, const Vector2f& axis, float& min, float& max);
	static bool FindNearestPointTo(const Vector2f& location, const BoxShape& box, Vector2f& nearestPoint);

private:
	std::vector<Vector2f>& CreateVertices();
	std::vector<int>& CreateTriangles();
};
}

#endif /* BOXSHAPE_H */
// CircleShape.h
#ifndef CIRCLESHAPE_H // include guard
#define CIRCLESHAPE_H
#include "Types/Shapes/IShape.h"
#include "Types/Vector2.h"

namespace Turtle
{
class CircleShape : public IShape {
public:
	CircleShape();
	CircleShape(Vector2f& center, float radius);

	void UpdateShapeFromTransform(Transform& transform) override;

	Vector2f Center;
	float Radius;

	static void ProjectCircle(const CircleShape& circle, const Vector2f& axis, float& min, float& max);
};
}

#endif /* CIRCLESHAPE_H */
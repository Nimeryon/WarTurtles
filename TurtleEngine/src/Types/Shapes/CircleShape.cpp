#include "Types/Shapes/CircleShape.h"

Turtle::CircleShape::CircleShape(Vector2f& center, float radius) : Center(center), Radius(radius)
{
}

void Turtle::CircleShape::UpdateShapeFromTransform(Transform& transform)
{
	//TO DO
}

void Turtle::CircleShape::ProjectCircle(const CircleShape& circle, const Vector2f& axis, float& min, float& max)
{
	Vector2f direction = Vector2f::Normalize(axis);
	Vector2f point1 = circle.Center + direction * circle.Radius;
	Vector2f point2 = circle.Center - direction * circle.Radius;

	min = Vector2f::Dot(point1, axis);
	max = Vector2f::Dot(point2, axis);
	if (min > max) {
		float temp = min;
		min = max;
		max = temp;
	}
}

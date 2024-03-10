#include "Types/Shapes/BoxShape.h"

Turtle::BoxShape::BoxShape() : Width(0.f), Height(0.f)
{
}

Turtle::BoxShape::BoxShape(Vector2f& position, float rotation, float width, float height) : PolygonShape(position, rotation,std::vector<Vector2f>()), Width(width), Height(height)
{
	CreateVertices();
}

void Turtle::BoxShape::CreateVertices()
{
	Vertices.clear();
	float top = Height / 2.f;
	float bottom = top - Height;
	float left = -Width / 2.f;
	float right = left + Width;

	Vertices.push_back(Vector2f(left, top));
	Vertices.push_back(Vector2f(right, top));
	Vertices.push_back(Vector2f(right, bottom));
	Vertices.push_back(Vector2f(left, bottom));

	TransformedVertices = Vertices;
}

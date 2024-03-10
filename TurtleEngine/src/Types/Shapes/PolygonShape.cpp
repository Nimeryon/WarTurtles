#include "Types/Shapes/PolygonShape.h"

Turtle::PolygonShape::PolygonShape() :
	Position(Vector2f::zero),
	Rotation(0.f)
{
}

Turtle::PolygonShape::PolygonShape(Turtle::Vector2f& position, float rotation, std::vector<Turtle::Vector2f> vertices) :
	Position(position), Rotation(rotation), Vertices(vertices)
{
	
}

Turtle::Vector2f Turtle::PolygonShape::GetCenter(const Transform& transform)
{
	Vector2f center = Vector2f::zero;
	for (auto& vertice : Vertices) {
		center += vertice;
	}
	center /= Vertices.size();
	center = transform.TransformPoint(center);
	return center;
}

bool Turtle::PolygonShape::ProjectTransformedVertices(const PolygonShape& polygon, const Vector2f& axis, float& min, float& max)
{
	if (polygon.TransformedVertices.size() == 0 || axis == Vector2f::zero)
		return false;

	Vector2f curVertice = polygon.TransformedVertices[0];
	float projection = Vector2f::Dot(curVertice, axis);
	min = projection;
	max = projection;

	for (int i = 1; i < polygon.TransformedVertices.size(); ++i) {
		curVertice = polygon.TransformedVertices[i];
		projection = Vector2f::Dot(curVertice, axis);

		if(projection < min)
			min = projection;
		if(projection > max)
			max = projection;
	}

	return true;
}

bool Turtle::PolygonShape::FindNearestPointTo(const Vector2f& location, const PolygonShape& polygon, Vector2f& nearestPoint)
{
	if (polygon.TransformedVertices.size() == 0)
		return false;

	float distance = FLT_MAX;

	for (auto curVertice : polygon.TransformedVertices) {
		float curDistance = Vector2f::Distance(curVertice, location);
		if (curDistance < distance) {
			distance = curDistance;
			nearestPoint = curVertice;
		}
	}

	return true;
}

std::vector<Turtle::Vector2f> Turtle::PolygonShape::GetTransformVertices(const Transform& transform)
{
	std::vector<Vector2f> transformedVertices = Vertices;
	for (auto& vertice : transformedVertices) {
		vertice = transform.TransformPoint(vertice);
	}
	return transformedVertices;
}

void Turtle::PolygonShape::CreateVertices()
{
}

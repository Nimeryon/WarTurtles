#include "Types/Shapes/PolygonShape.h"

Turtle::PolygonShape::PolygonShape(Turtle::Vector2f& position, float rotation, std::vector<Turtle::Vector2f> vertices) : 
	Position(position),Rotation(rotation),Vertices(vertices), NeedToUpdateTransformedVertices(true)
{
	
}

void Turtle::PolygonShape::UpdateShapeFromTransform(Transform& transform)
{
	//TO DO
	NeedToUpdateTransformedVertices = true;
}

Turtle::Vector2f Turtle::PolygonShape::GetCenter()
{
	Vector2f center = Vector2f::zero;

	for (auto curVertice : TransformedVertices)
		center += curVertice;

	center /= TransformedVertices.size();
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

void Turtle::PolygonShape::CreateVertices()
{
}

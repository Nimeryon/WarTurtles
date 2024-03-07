#include "Types/Shapes/BoxShape.h"

Turtle::BoxShape::BoxShape(Vector2f& position, float rotation, float width, float height) : Position(position),Rotation(rotation), Width(width), Height(height), NeedToUpdateTransformedVertices(true)
{
	CreateVertices();
	CreateTriangles();
}

void Turtle::BoxShape::UpdateShapeFromTransform(Transform& transform)
{
	//TO DO
	NeedToUpdateTransformedVertices = true;
}

Turtle::Vector2f& Turtle::BoxShape::GetCenter()
{
	Vector2f center = Vector2f::zero;

	for (auto curVertice : TransformedVertices)
		center += curVertice;

	center /= TransformedVertices.size();
	return center;
}

bool Turtle::BoxShape::ProjectTransformedVertices(const BoxShape& box, const Vector2f& axis, float& min, float& max)
{
	if (box.TransformedVertices.size() == 0 || axis == Vector2f::zero)
		return false;

	Vector2f curVertice = box.TransformedVertices[0];
	float projection = Vector2f::Dot(curVertice, axis);
	min = projection;
	max = projection;

	for (int i = 1; i < box.TransformedVertices.size(); ++i) {
		curVertice = box.TransformedVertices[i];
		projection = Vector2f::Dot(curVertice, axis);

		if(projection < min)
			min = projection;
		if(projection > max)
			max = projection;
	}

	return true;
}

bool Turtle::BoxShape::FindNearestPointTo(const Vector2f& location, const BoxShape& box, Vector2f& nearestPoint)
{
	if (box.TransformedVertices.size() == 0)
		return false;

	float distance = FLT_MAX;

	for (auto curVertice : box.TransformedVertices) {
		float curDistance = Vector2f::Distance(curVertice, location);
		if (curDistance < distance) {
			distance = curDistance;
			nearestPoint = curVertice;
		}
	}

	return true;
}

std::vector<Turtle::Vector2f>& Turtle::BoxShape::CreateVertices()
{
	float top = Height / 2.f;
	float bottom = top - Height;
	float left = -Width / 2.f;
	float right = left + Width;

	std::vector<Turtle::Vector2f> verts;
	verts.push_back(Vector2f(left, top));
	verts.push_back(Vector2f(right, top));
	verts.push_back(Vector2f(right, bottom));
	verts.push_back(Vector2f(left, bottom));

	return verts;
}

std::vector<int>& Turtle::BoxShape::CreateTriangles()
{
	std::vector<int> triangles;
	triangles.push_back(0);
	triangles.push_back(1);
	triangles.push_back(2);
	triangles.push_back(0);
	triangles.push_back(2);
	triangles.push_back(3);

	return triangles;
}

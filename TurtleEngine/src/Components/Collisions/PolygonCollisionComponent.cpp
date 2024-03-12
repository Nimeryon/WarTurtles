#include "Components/Collisions/PolygonCollisionComponent.h"
#include "GameObjects/GameObject.h"

Turtle::PolygonCollisionComponent::PolygonCollisionComponent(GameObject* parent, const std::string& name) :
	ICollisionComponent(parent, name)
{
	SetActive(false);
}

void Turtle::PolygonCollisionComponent::InitCollisionParameters(const std::vector<Vector2f>& vertice)
{
	m_vertice = vertice;

	SetActive(true);
}

const std::vector<Turtle::Vector2f>& Turtle::PolygonCollisionComponent::GetVertice() const { return m_vertice; }

Turtle::Vector2f Turtle::PolygonCollisionComponent::GetCenter() const
{
	Vector2f center;
	for (auto& vertice : m_vertice) {
		center += vertice;
	}

	center /= m_vertice.size();
	return m_parent->GetTransform()->TransformPoint(center);
}

float Turtle::PolygonCollisionComponent::CalculateRotationalInertia(float mass)
{
	return 0.5f;
}

void Turtle::PolygonCollisionComponent::SetVertice(const std::vector<Vector2f>& vertice) { m_vertice = vertice; }

std::vector<Turtle::Vector2f> Turtle::PolygonCollisionComponent::GetTransformedVertice() const
{
	std::vector<Vector2f> transformedVertices = m_vertice;
	for (auto& vertice : transformedVertices) {
		vertice = m_parent->GetTransform()->TransformPoint(vertice);
	}
	return transformedVertices;
}

bool Turtle::PolygonCollisionComponent::ProjectTransformedVertices(const PolygonCollisionComponent& polygon, const Vector2f& axis, float& min, float& max)
{
	const auto& transformedVertice = polygon.GetTransformedVertice();
	if (transformedVertice.size() == 0 || axis == Vector2f::zero)
		return false;

	Vector2f curVertice = transformedVertice[0];
	float projection = Vector2f::Dot(curVertice, axis);
	min = projection;
	max = projection;

	for (int i = 1; i < transformedVertice.size(); ++i) {
		curVertice = transformedVertice[i];
		projection = Vector2f::Dot(curVertice, axis);

		if (projection < min)
			min = projection;
		if (projection > max)
			max = projection;
	}

	return true;
}
bool Turtle::PolygonCollisionComponent::FindNearestPointTo(const Vector2f& location, const PolygonCollisionComponent& polygon, Vector2f& nearestPoint)
{
	const auto& transformedVertice = polygon.GetTransformedVertice();
	if (transformedVertice.size() == 0)
		return false;

	float distance = FLT_MAX;

	for (auto& curVertice : transformedVertice) {
		float curDistance = Vector2f::Distance(curVertice, location);
		if (curDistance < distance) {
			distance = curDistance;
			nearestPoint = curVertice;
		}
	}

	return true;
}

void Turtle::PolygonCollisionComponent::ProjectPointToEdge(const Vector2f& pointToProject, const Vector2f& edgeStart, const Vector2f& edgeEnd, float& squaredDistance, Vector2f& projectedPoint)
{
	Vector2f edge = edgeEnd - edgeStart;
	Vector2f vertexAToCenter = pointToProject - edgeStart;

	float proj = Vector2f::Dot(vertexAToCenter, edge);
	float distance = proj / edge.Magnitude();

	Vector2f curContactPoint;
	if (distance <= 0.f) {
		curContactPoint = edgeStart;
	}
	else if (distance >= 1.f) {
		curContactPoint = edgeEnd;
	}
	else {
		curContactPoint = edgeStart + edge * distance;
	}

	float SquareDistance = std::pow(Vector2f::Distance(pointToProject, curContactPoint), 2);
}

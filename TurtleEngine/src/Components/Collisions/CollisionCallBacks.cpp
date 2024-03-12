#include "Components/Collisions/CollisionCallBacks.h"

namespace Turtle
{
bool collisionBetweenCircles(CircleCollisionComponent& lhs, CircleCollisionComponent& rhs, Vector2f& normal, float& depth)
{
	float distance = Vector2f::Distance(lhs.GetCenter(), rhs.GetCenter());
	float allRadius = lhs.GetRadius() + rhs.GetRadius();

	if (distance >= allRadius)
		return false;

	normal = Vector2f::Normalize(rhs.GetCenter() - lhs.GetCenter());
	depth = allRadius - distance;
	return true;
}

bool collisionBetweenPolygons(PolygonCollisionComponent& lhs, PolygonCollisionComponent& rhs, Vector2f& normal, float& depth)
{
	depth = FLT_MAX;

	const auto& lhsTransformedVertice = lhs.GetTransformedVertice();
	for (int i = 0; i < lhsTransformedVertice.size(); ++i) {
		Vector2f VerticeA = lhsTransformedVertice[i];
		Vector2f VerticeB = lhsTransformedVertice[(i + 1) % lhsTransformedVertice.size()];

		Vector2f edge = VerticeB - VerticeA;
		Vector2f curNormal = Vector2f::Perpendicular(edge);
		curNormal.Normalize();

		float minLhs, maxLhs, minRhs, maxRhs;
		PolygonCollisionComponent::ProjectTransformedVertices(lhs, curNormal, minLhs, maxLhs);
		PolygonCollisionComponent::ProjectTransformedVertices(rhs, curNormal, minRhs, maxRhs);

		if (minLhs >= maxRhs || minRhs >= maxLhs)
			return false;

		float curDepth = std::min(maxRhs - minLhs, maxLhs - minRhs);
		if (curDepth < depth) {
			depth = curDepth;
			normal = curNormal;
		}
	}

	const auto& rhsTransformedVertice = rhs.GetTransformedVertice();
	for (int i = 0; i < rhsTransformedVertice.size(); ++i) {
		Vector2f VerticeA = rhsTransformedVertice[i];
		Vector2f VerticeB = rhsTransformedVertice[(i + 1) % rhsTransformedVertice.size()];

		Vector2f edge = VerticeB - VerticeA;
		Vector2f curNormal = Vector2f::Perpendicular(edge);
		curNormal.Normalize();

		float minLhs, maxLhs, minRhs, maxRhs;
		PolygonCollisionComponent::ProjectTransformedVertices(lhs, curNormal, minLhs, maxLhs);
		PolygonCollisionComponent::ProjectTransformedVertices(rhs, curNormal, minRhs, maxRhs);

		if (minLhs >= maxRhs || minRhs >= maxLhs)
			return false;

		float curDepth = std::min(maxRhs - minLhs, maxLhs - minRhs);
		if (curDepth < depth) {
			depth = curDepth;
			normal = curNormal;
		}
	}

	Vector2f direction = rhs.GetCenter() - lhs.GetCenter();

	if (Vector2f::Dot(direction, normal) < 0)
		normal = -normal;

	return true;
}

bool collisionBetweenBoxes(BoxCollisionComponent& lhs, BoxCollisionComponent& rhs, Vector2f& normal, float& depth)
{
	return collisionBetweenPolygons(lhs, rhs, normal, depth);
}

bool collisionBetweenCircleAndPolygon(CircleCollisionComponent& circleComp, PolygonCollisionComponent& boxComp, Vector2f& normal, float& depth)
{
	depth = FLT_MAX;

	const auto& boxTransformedVertice = boxComp.GetTransformedVertice();
	for (int i = 0; i < boxTransformedVertice.size(); ++i) {
		Vector2f VerticeA = boxTransformedVertice[i];
		Vector2f VerticeB = boxTransformedVertice[(i + 1) % boxTransformedVertice.size()];

		Vector2f edge = VerticeB - VerticeA;
		Vector2f curNormal = Vector2f::Perpendicular(edge);
		curNormal.Normalize();

		float minCircle, maxCircle, minBox, maxBox;
		PolygonCollisionComponent::ProjectTransformedVertices(boxComp, curNormal, minBox, maxBox);
		CircleCollisionComponent::ProjectCircle(circleComp, curNormal, minCircle, maxCircle);

		if (minCircle >= maxBox || minBox >= maxCircle)
		{
			return false;
		}

		float curDepth = std::min(maxBox - minCircle, maxCircle - minBox);
		if (curDepth < depth) {
			depth = curDepth;
			normal = curNormal;
		}
	}

	Vector2f nearestPoint;
	PolygonCollisionComponent::FindNearestPointTo(circleComp.GetCenter(), boxComp, nearestPoint);
	Vector2f axis = nearestPoint - circleComp.GetCenter();
	axis.Normalize();

	float minCircle, maxCircle, minBox, maxBox;
	PolygonCollisionComponent::ProjectTransformedVertices(boxComp, axis, minBox, maxBox);
	CircleCollisionComponent::ProjectCircle(circleComp, axis, minCircle, maxCircle);

	if (minCircle >= maxBox || minBox >= maxCircle)
		return false;

	float curDepth = std::min(maxBox - minCircle, maxCircle - minBox);
	if (curDepth < depth) {
		depth = curDepth;
		normal = axis;
	}

	Vector2f direction = boxComp.GetCenter() - circleComp.GetCenter();

	if (Vector2f::Dot(direction, normal) < 0)
		normal = -normal;

	return true;
}

bool collisionBetweenPolygonAndCircle(PolygonCollisionComponent& boxComp, CircleCollisionComponent& circleComp, Vector2f& normal, float& depth) {

	bool collide = collisionBetweenCircleAndPolygon(circleComp, boxComp, normal, depth);
	normal = -normal;
	return collide;
}

bool collisionBetweenBoxAndPolygon(BoxCollisionComponent& boxComp, PolygonCollisionComponent& polygonComp, Vector2f& normal, float& depth)
{
	return collisionBetweenPolygons(boxComp, polygonComp, normal, depth);
}

bool collisionBetweenPolygonAndBox(PolygonCollisionComponent& polygonComp, BoxCollisionComponent& boxComp, Vector2f& normal, float& depth)
{
	return collisionBetweenPolygons(polygonComp, boxComp, normal, depth);
}

bool collisionBetweenBoxAndCircle(BoxCollisionComponent& boxComp, CircleCollisionComponent& circleComp, Vector2f& normal, float& depth)
{
	return collisionBetweenPolygonAndCircle(boxComp, circleComp, normal, depth);
}

bool collisionBetweenCircleAndBox(CircleCollisionComponent& circleComp, BoxCollisionComponent& boxComp, Vector2f& normal, float& depth)
{
	return collisionBetweenCircleAndPolygon(circleComp, boxComp, normal, depth);
}
}
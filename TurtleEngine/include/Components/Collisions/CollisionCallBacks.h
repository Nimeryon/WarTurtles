// CollisionCallBacks.h
#ifndef COLLISIONCALLBACKS_H
#define COLLISIONCALLBACKS_H
#include <type_traits>
#include <functional>
#include <map>
#include "Components/Collisions/ICollisionComponent.h"
#include "Components/Collisions/PolygonCollisionComponent.h"
#include "Components/Collisions/CircleCollisionComponent.h"
#include "Components/Collisions/BoxCollisionComponent.h"

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

//To call after collision resolution to calculate torque

template<typename CollisionComponentA, typename CollisionComponentB>
std::vector<Vector2f> GetContactPoints(CollisionComponentA& objectA, CollisionComponentB& objectB) {
	//static_assert(false, "Unkown collision component");
	return std::vector<Vector2f>();
}

template<>
std::vector<Vector2f> GetContactPoints<CircleCollisionComponent, CircleCollisionComponent>(CircleCollisionComponent& circleA, CircleCollisionComponent& circleB) {

	std::vector<Vector2f> contactPoints;
	Vector2f centerA = circleA.GetCenter();
	Vector2f centerB = circleB.GetCenter();
	contactPoints.emplace_back(centerA + Vector2f::Normalize(centerB - centerA) * circleA.GetRadius());
	return contactPoints;

}

template<>
std::vector<Vector2f> GetContactPoints<CircleCollisionComponent, PolygonCollisionComponent>(CircleCollisionComponent& circle, PolygonCollisionComponent& polygon) {
	std::vector<Vector2f> contactPoints;
	Vector2f contactPoint;
	auto transformedVertice = polygon.GetTransformedVertice();

	float minDistSquared = FLT_MAX;

	for (int i = 0; i < transformedVertice.size(); ++i) {
		Vector2f vertexA = transformedVertice[i];
		Vector2f vertexB = transformedVertice[(i + 1) % transformedVertice.size()];

		float squaredDistance;
		Vector2f curContactPoint;
		PolygonCollisionComponent::ProjectPointToEdge(circle.GetCenter(), vertexA, vertexB, squaredDistance, curContactPoint);

		if (squaredDistance < minDistSquared) {
			minDistSquared = squaredDistance;
			contactPoint = curContactPoint;
		}
	}
	contactPoints.emplace_back(contactPoint);
	return contactPoints;
}

template<>
std::vector<Vector2f> GetContactPoints<PolygonCollisionComponent, CircleCollisionComponent>(PolygonCollisionComponent& polygon, CircleCollisionComponent& circle) {
	return GetContactPoints(circle, polygon);
}

template<>
std::vector<Vector2f> GetContactPoints<PolygonCollisionComponent, PolygonCollisionComponent>(PolygonCollisionComponent& polygonA, PolygonCollisionComponent& polygonB) {
	auto polygonAVertice = polygonA.GetTransformedVertice();
	auto polygonBVertice = polygonA.GetTransformedVertice();

	std::vector<Vector2f> contactPoints;
	Vector2f contactPoint1 = Vector2f::zero;
	Vector2f contactPoint2 = Vector2f::zero;

	float minDistSquared = FLT_MAX;

	for (int i = 0; i < polygonAVertice.size(); ++i) {
		Vector2f vertexA = polygonAVertice[i];

		for (int j = 0; j < polygonBVertice.size(); ++j) {
			Vector2f vertexB1 = polygonBVertice[j];
			Vector2f vertexB2 = polygonBVertice[(j + 1) % polygonBVertice.size()];

			Vector2f curContactPoint;
			float squaredDistance;
			PolygonCollisionComponent::ProjectPointToEdge(vertexA, vertexB1, vertexB2, squaredDistance, curContactPoint);

			if (squaredDistance == minDistSquared) {
				if (curContactPoint != contactPoint1) {
					contactPoint2 = curContactPoint;
				}
			}
			else if (squaredDistance < minDistSquared) {
				minDistSquared = squaredDistance;
				contactPoint1 = curContactPoint;
			}
		}
	}

	for (int i = 0; i < polygonBVertice.size(); ++i) {
		Vector2f vertexB = polygonBVertice[i];

		for (int j = 0; j < polygonAVertice.size(); ++j) {
			Vector2f vertexA1 = polygonAVertice[j];
			Vector2f vertexA2 = polygonAVertice[(j + 1) % polygonAVertice.size()];

			Vector2f curContactPoint;
			float squaredDistance;
			PolygonCollisionComponent::ProjectPointToEdge(vertexB, vertexA1, vertexA2, squaredDistance, curContactPoint);

			if (squaredDistance == minDistSquared) {
				if (curContactPoint != contactPoint1) {
					contactPoint2 = curContactPoint;
				}
			}
			else if (squaredDistance < minDistSquared) {
				minDistSquared = squaredDistance;
				contactPoint1 = curContactPoint;
			}
		}
	}

	contactPoints.emplace_back(contactPoint1);
	if (contactPoint2 != Vector2f::zero) {
		contactPoints.emplace_back(contactPoint2);
	}

	return contactPoints;
}

template<>
std::vector<Vector2f> GetContactPoints<BoxCollisionComponent, BoxCollisionComponent>(BoxCollisionComponent& boxA, BoxCollisionComponent& boxB) {
	return GetContactPoints<PolygonCollisionComponent, PolygonCollisionComponent>(boxA, boxB);
}

template<>
std::vector<Vector2f> GetContactPoints<BoxCollisionComponent, PolygonCollisionComponent>(BoxCollisionComponent& box, PolygonCollisionComponent& polygon) {
	return GetContactPoints<PolygonCollisionComponent, PolygonCollisionComponent>(box, polygon);
}

template<>
std::vector<Vector2f> GetContactPoints<PolygonCollisionComponent, BoxCollisionComponent>(PolygonCollisionComponent& polygon, BoxCollisionComponent& box) {
	return GetContactPoints<PolygonCollisionComponent, PolygonCollisionComponent>(polygon, box);
}

template<>
std::vector<Vector2f> GetContactPoints<CircleCollisionComponent, BoxCollisionComponent>(CircleCollisionComponent& circle, BoxCollisionComponent& box) {
	return GetContactPoints<CircleCollisionComponent, PolygonCollisionComponent>(circle, box);
}

template<>
std::vector<Vector2f> GetContactPoints<BoxCollisionComponent, CircleCollisionComponent>(BoxCollisionComponent& box, CircleCollisionComponent& circle) {
	return GetContactPoints<PolygonCollisionComponent, CircleCollisionComponent>(box, circle);
}
}
#endif // COLLISIONCALLBACKS_H
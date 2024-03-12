#include "Components/Collisions/ContactPointsCollisionCallBacks.h"

namespace Turtle
{
std::vector<Vector2f> GetContactPointsBetweenCircles(CircleCollisionComponent& circleA, CircleCollisionComponent& circleB) {

	std::vector<Vector2f> contactPoints;
	Vector2f centerA = circleA.GetCenter();
	Vector2f centerB = circleB.GetCenter();
	contactPoints.emplace_back(centerA + Vector2f::Normalize(centerB - centerA) * circleA.GetRadius());
	return contactPoints;

}

std::vector<Vector2f> GetContactPointsBetweenCircleAndPolygon(CircleCollisionComponent& circle, PolygonCollisionComponent& polygon) {
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

std::vector<Vector2f> GetContactPointsBetweenPolygonAndCircle(PolygonCollisionComponent& polygon, CircleCollisionComponent& circle) {
	return GetContactPointsBetweenCircleAndPolygon(circle, polygon);
}

std::vector<Vector2f> GetContactPointsBetweenPolygons(PolygonCollisionComponent& polygonA, PolygonCollisionComponent& polygonB) {
	auto polygonAVertice = polygonA.GetTransformedVertice();
	auto polygonBVertice = polygonB.GetTransformedVertice();

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

std::vector<Vector2f> GetContactPointsBetweenBoxes(BoxCollisionComponent& boxA, BoxCollisionComponent& boxB) {
	return GetContactPointsBetweenPolygons(boxA, boxB);
}

std::vector<Vector2f> GetContactPointsBetweenBoxAndPolygon(BoxCollisionComponent& box, PolygonCollisionComponent& polygon) {
	return GetContactPointsBetweenPolygons(box, polygon);
}

std::vector<Vector2f> GetContactPointsBetweenPolygonAndBox(PolygonCollisionComponent& polygon, BoxCollisionComponent& box) {
	return GetContactPointsBetweenPolygons(polygon, box);
}

std::vector<Vector2f> GetContactPointsBetweenCircleAndBox(CircleCollisionComponent& circle, BoxCollisionComponent& box) {
	return GetContactPointsBetweenCircleAndPolygon(circle, box);
}

std::vector<Vector2f> GetContactPointsBetweenBoxAndCircle(BoxCollisionComponent& box, CircleCollisionComponent& circle) {
	return GetContactPointsBetweenPolygonAndCircle(box, circle);
}
}
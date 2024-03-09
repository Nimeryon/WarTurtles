// CollisionDispatcher.h
#ifndef COLLISIONDISPATCHER_H
#define COLLISIONDISPATCHER_H
#include <type_traits>
#include <functional>
#include <map>
#include "Components/Collisions/ICollisionComponent.h"
#include "Components/Collisions/PolygonCollisionComponent.h"
#include "Components/Collisions/CircleCollisionComponent.h"


namespace Turtle
{
bool collisionBetweenCircles(CircleCollisionComponent& lhs, CircleCollisionComponent& rhs, Vector2f& normal, float& depth) {
	CircleShape lhsCircle = lhs.GetShape();
	CircleShape rhsCircle = lhs.GetShape();
	
	float distance = Vector2f::Distance(lhsCircle.Center, rhsCircle.Center);
	float allRadius = lhsCircle.Radius + rhsCircle.Radius;

	if (distance >= allRadius)
		return false;

	normal = Vector2f::Normalize(rhsCircle.Center - lhsCircle.Center);
	depth = allRadius - distance;
	return true;
}

bool collisionBetweenBoxes(PolygonCollisionComponent& lhs, PolygonCollisionComponent& rhs, Vector2f& normal, float& depth) {
	PolygonShape lhsBox = lhs.GetShape();
	PolygonShape rhsBox = lhs.GetShape();
	depth = FLT_MAX;

	for (int i = 0; i < lhsBox.TransformedVertices.size(); ++i) {
		Vector2f VerticeA = lhsBox.TransformedVertices[i];
		Vector2f VerticeB = lhsBox.TransformedVertices[(i + 1) % lhsBox.TransformedVertices.size()];

		Vector2f edge = VerticeB - VerticeA;
		Vector2f curNormal = Vector2f::Perpendicular(edge);

		float minLhs, maxLhs, minRhs, maxRhs;
		if (!PolygonShape::ProjectTransformedVertices(lhsBox, curNormal, minLhs, maxLhs)
			|| !PolygonShape::ProjectTransformedVertices(rhsBox, curNormal, minRhs, maxRhs)) {
			return false;
		}

		if (minLhs >= maxRhs || minRhs >= maxLhs)
			return false;

		float curDepth = std::min(maxRhs - minLhs, maxLhs - minRhs);
		if (curDepth < depth) {
			depth = curDepth;
			normal = curNormal;
		}
	}

	for (int i = 0; i < rhsBox.TransformedVertices.size(); ++i) {
		Vector2f VerticeA = rhsBox.TransformedVertices[i];
		Vector2f VerticeB = rhsBox.TransformedVertices[(i + 1) % rhsBox.TransformedVertices.size()];

		Vector2f edge = VerticeB - VerticeA;
		Vector2f curNormal = Vector2f::Perpendicular(edge);

		float minLhs, maxLhs, minRhs, maxRhs;
		if (!PolygonShape::ProjectTransformedVertices(lhsBox, curNormal, minLhs, maxLhs)
			|| !PolygonShape::ProjectTransformedVertices(rhsBox, curNormal, minRhs, maxRhs)) {
			return false;
		}

		if (minLhs >= maxRhs || minRhs >= maxLhs)
			return false;

		float curDepth = std::min(maxRhs - minLhs, maxLhs - minRhs);
		if (curDepth < depth) {
			depth = curDepth;
			normal = curNormal;
		}
	}

	//normalize depth and normal here to avoid normalizing in loop
	depth /= normal.Magnitude();
	normal.Normalize();

	Vector2f direction = rhsBox.GetCenter() - lhsBox.GetCenter();

	if (Vector2f::Dot(direction, normal) < 0)
		normal = -normal;

	return true;
}

bool collisionBetweenCircleAndBox(CircleCollisionComponent& circleComp, PolygonCollisionComponent& boxComp, Vector2f& normal, float& depth) {
	PolygonShape box = boxComp.GetShape();
	CircleShape circle = circleComp.GetShape();
	depth = FLT_MAX;

	for (int i = 0; i < box.TransformedVertices.size(); ++i) {
		Vector2f VerticeA = box.TransformedVertices[i];
		Vector2f VerticeB = box.TransformedVertices[(i + 1) % box.TransformedVertices.size()];

		Vector2f edge = VerticeB - VerticeA;
		Vector2f curNormal = Vector2f::Perpendicular(edge);

		float minCircle, maxCircle, minBox, maxBox;
		if (!PolygonShape::ProjectTransformedVertices(box, curNormal, minBox, maxBox))
			return false;
		
		CircleShape::ProjectCircle(circle, curNormal, minCircle, maxCircle);

		if (minCircle >= maxBox || minBox >= maxCircle)
			return false;

		float curDepth = std::min(maxBox - minCircle, maxCircle - minBox);
		if (curDepth < depth) {
			depth = curDepth;
			normal = curNormal;
		}
	}

	Vector2f nearestPoint;
	PolygonShape::FindNearestPointTo(circle.Center, box, nearestPoint);
	Vector2f axis = nearestPoint - circle.Center;
	float minCircle, maxCircle, minBox, maxBox;
	if (!PolygonShape::ProjectTransformedVertices(box, axis, minBox, maxBox))
		return false;

	CircleShape::ProjectCircle(circle, axis, minCircle, maxCircle);

	if (minCircle >= maxBox || minBox >= maxCircle)
		return false;

	float curDepth = std::min(maxBox - minCircle, maxCircle - minBox);
	if (curDepth < depth) {
		depth = curDepth;
		normal = axis;
	}

	depth /= normal.Magnitude();
	normal.Normalize();
	Vector2f direction = box.GetCenter() - circle.Center;;

	if (Vector2f::Dot(direction, normal) < 0)
		normal = -normal;

	return true;
}

bool collisionBetweenBoxAndCircle(PolygonCollisionComponent& boxComp, CircleCollisionComponent& circleComp, Vector2f& normal, float& depth) {

	bool collide = collisionBetweenCircleAndBox(circleComp, boxComp, normal, depth);
	normal = -normal;
	return collide;
}

template<typename LeftICollision, typename RightICollision = LeftICollision>
class CollisionDispatcher {
public:
	using callable = std::function<bool(LeftICollision&, RightICollision&, Vector2f&, float&)>;
	using key_t = std::pair<std::string, std::string>;

	template<typename LCollision, typename RCollision, 
			bool (*Func)(LCollision&, RCollision&, Vector2f&, float&)>
	void add() {

		struct trampoline_s {
			static bool trampoline(LeftICollision& lhs, RightICollision& rhs, Vector2f& normal, float& depth)
			{
				return std::invoke(Func, static_cast<LCollision&>(lhs), static_cast<RCollision&>(rhs), normal, depth);
			}
		};

		key_t key(typeid(LCollision).name(), typeid(RCollision).name());
		key_t inverseKey(typeid(RCollision).name(), typeid(LCollision).name());
		if (m_map.contains(key) || m_map.contains(inverseKey))
			throw std::runtime_error("This collision callback is already in the map");

		m_map.insert({ key, &trampoline_s::trampoline });
	}

	bool operator()(LeftICollision& lhs, RightICollision& rhs, Vector2f& normal, float& depth)
	{
		auto iterator = std::find_if(m_map.begin(), m_map.end(), [&lhs, &rhs](const auto& element) {
			return (typeid(lhs).name() == element.first.first) && (typeid(rhs).name() == element.first.second);
		});
		if(iterator == m_map.end())
			throw std::runtime_error("This collision callback is not implemented");
		return iterator->second(lhs, rhs, normal, depth);
	}

private:
	std::map<key_t, callable> m_map;
};
}
#endif // !COLLISIONDISPATCHER_H


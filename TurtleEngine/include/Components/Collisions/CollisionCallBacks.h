// CollisionCallBacks.h
#ifndef COLLISIONCALLBACKS_H
#define COLLISIONCALLBACKS_H
#include "Types/Vector2.h"
#include "Components/Collisions/PolygonCollisionComponent.h"
#include "Components/Collisions/CircleCollisionComponent.h"
#include "Components/Collisions/BoxCollisionComponent.h"

namespace Turtle
{
bool collisionBetweenCircles(CircleCollisionComponent& lhs, CircleCollisionComponent& rhs, Vector2f& normal, float& depth);

bool collisionBetweenPolygons(PolygonCollisionComponent& lhs, PolygonCollisionComponent& rhs, Vector2f& normal, float& depth);

bool collisionBetweenBoxes(BoxCollisionComponent& lhs, BoxCollisionComponent& rhs, Vector2f& normal, float& depth);

bool collisionBetweenCircleAndPolygon(CircleCollisionComponent& circleComp, PolygonCollisionComponent& boxComp, Vector2f& normal, float& depth);

bool collisionBetweenPolygonAndCircle(PolygonCollisionComponent& boxComp, CircleCollisionComponent& circleComp, Vector2f& normal, float& depth);

bool collisionBetweenBoxAndPolygon(BoxCollisionComponent& boxComp, PolygonCollisionComponent& polygonComp, Vector2f& normal, float& depth);

bool collisionBetweenPolygonAndBox(PolygonCollisionComponent& polygonComp, BoxCollisionComponent& boxComp, Vector2f& normal, float& depth);

bool collisionBetweenBoxAndCircle(BoxCollisionComponent& boxComp, CircleCollisionComponent& circleComp, Vector2f& normal, float& depth);

bool collisionBetweenCircleAndBox(CircleCollisionComponent& circleComp, BoxCollisionComponent& boxComp, Vector2f& normal, float& depth);
}
#endif // COLLISIONCALLBACKS_H
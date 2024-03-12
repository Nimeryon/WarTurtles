// ContactPointsCollisionCallBacks.h
#ifndef CONTACTPOINTSCOLLISIONCALLBACKS_H
#define CONTACTPOINTSCOLLISIONCALLBACKS_H
#include <vector>
#include "Types/Vector2.h"
#include "Components/Collisions/PolygonCollisionComponent.h"
#include "Components/Collisions/CircleCollisionComponent.h"
#include "Components/Collisions/BoxCollisionComponent.h"

namespace Turtle
{
std::vector<Vector2f> GetContactPointsBetweenCircles(CircleCollisionComponent& circleA, CircleCollisionComponent& circleB);

std::vector<Vector2f> GetContactPointsBetweenCircleAndPolygon(CircleCollisionComponent& circle, PolygonCollisionComponent& polygon);

std::vector<Vector2f> GetContactPointsBetweenPolygonAndCircle(PolygonCollisionComponent& polygon, CircleCollisionComponent& circle);

std::vector<Vector2f> GetContactPointsBetweenPolygons(PolygonCollisionComponent& polygonA, PolygonCollisionComponent& polygonB);

std::vector<Vector2f> GetContactPointsBetweenBoxes(BoxCollisionComponent& boxA, BoxCollisionComponent& boxB);

std::vector<Vector2f> GetContactPointsBetweenBoxAndPolygon(BoxCollisionComponent& box, PolygonCollisionComponent& polygon);

std::vector<Vector2f> GetContactPointsBetweenPolygonAndBox(PolygonCollisionComponent& polygon, BoxCollisionComponent& box);

std::vector<Vector2f> GetContactPointsBetweenCircleAndBox(CircleCollisionComponent& circle, BoxCollisionComponent& box);

std::vector<Vector2f> GetContactPointsBetweenBoxAndCircle(BoxCollisionComponent& box, CircleCollisionComponent& circle);
}
#endif // CONTACTPOINTSCOLLISIONCALLBACKS_H
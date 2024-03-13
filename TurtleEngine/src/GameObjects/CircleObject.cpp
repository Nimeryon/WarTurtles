#include "GameObjects/CircleObject.h"
#include "Components/Physic.h"
#include "Components/Collisions/CircleCollisionComponent.h"
#include "Components/Renderer/ShapeRenderer.h"

Turtle::CircleObject::CircleObject(const std::string& name, GameObject* parent) :
	GameObject(name, parent),
	m_isStatic(true)
{
	m_physicComponent = AddComponent<Turtle::Physic>();
	m_physicComponent->SetActive(false);

	m_colliderComponent = AddComponent<Turtle::CircleCollisionComponent>();
	m_shapeComponent = AddComponent<Turtle::ShapeRenderer<sf::CircleShape>>();

	InitParameters();
}

void Turtle::CircleObject::InitParameters(float radius, const Vector2f& center, const sf::Color& color)
{
	m_colliderComponent->InitCollisionParameters(center, radius);
	m_shapeComponent->GetShape().setFillColor(color);
	SetRadius(radius);
	SetCenter(center);
}

void Turtle::CircleObject::InitPhysicsParameters(const Vector2f& initialVelocity, const Vector2f& initialAcceleration, float mass, float friction, float restitution, float angularVelocity)
{
	m_physicComponent->InitPhysicParameters(initialVelocity, initialAcceleration, mass, friction, restitution, angularVelocity);
	m_physicComponent->SetActive(true);
	m_isStatic = false;
}

bool Turtle::CircleObject::IsStatic() const { return m_isStatic; }
void Turtle::CircleObject::SetStatic(bool isStatic)
{
	m_isStatic = isStatic;
	m_physicComponent->SetActive(m_isStatic);
}

float Turtle::CircleObject::GetRadius() const { return m_shapeComponent->GetShape().getRadius(); }
const Turtle::Vector2f& Turtle::CircleObject::GetCenter() const
{
	const auto& center = m_shapeComponent->GetShape().getPosition();
	return { center.x, center.y };
}

void Turtle::CircleObject::SetRadius(float radius)
{
	m_colliderComponent->InitCollisionParameters(GetCenter(), radius);
	m_shapeComponent->GetShape().setRadius(radius);
	m_shapeComponent->SetOrigin({ radius, radius });
}
void Turtle::CircleObject::SetCenter(const Vector2f& center)
{
	m_colliderComponent->InitCollisionParameters(center, GetRadius());
	m_shapeComponent->GetShape().setPosition(center.x, center.y);
}

Turtle::Physic* Turtle::CircleObject::GetPhysicComponent() const { return m_physicComponent; }
Turtle::CircleCollisionComponent* Turtle::CircleObject::GetColliderComponent() const { return m_colliderComponent; }
Turtle::ShapeRenderer<sf::CircleShape>* Turtle::CircleObject::GetShapeRendererComponent() const { return m_shapeComponent; }
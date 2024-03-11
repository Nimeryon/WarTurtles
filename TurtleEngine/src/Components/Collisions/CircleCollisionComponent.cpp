#include "Components/Collisions/CircleCollisionComponent.h"
#include "GameObjects/GameObject.h"

Turtle::CircleCollisionComponent::CircleCollisionComponent(GameObject* parent, const std::string& name) : 
	ICollisionComponent(parent, name),
	m_position({0, 0}),
	m_radius(0)
{
	m_debugShape.setFillColor(sf::Color::Transparent);
	m_debugShape.setOutlineColor(sf::Color::Red);
	m_debugShape.setOutlineThickness(1);
	SetActive(false);
}

void Turtle::CircleCollisionComponent::InitCollisionParameters(const Vector2f& center, float radius)
{
	m_position = center;
	m_radius = radius;

	m_debugShape.setPosition({ m_position.x, m_position.y });
	m_debugShape.setRadius(m_radius);

	SetActive(true);
}

const Turtle::Vector2f& Turtle::CircleCollisionComponent::GetPosition() const { return m_position; }
Turtle::Vector2f Turtle::CircleCollisionComponent::GetCenter() const
{
	return m_parent->GetTransform()->TransformPoint(GetPosition());
}
float Turtle::CircleCollisionComponent::GetRadius() const { return 0.0f; }

void Turtle::CircleCollisionComponent::SetPosition(const Vector2f& position) 
{ 
	m_position = position;
	m_debugShape.setPosition({ m_position.x, m_position.y });
}
void Turtle::CircleCollisionComponent::SetRadius(float radius) 
{ 
	m_radius = radius;
	m_debugShape.setRadius(m_radius);
}

void Turtle::CircleCollisionComponent::ProjectCircle(const CircleCollisionComponent& circle, const Vector2f& axis, float& min, float& max)
{
	Vector2f direction = Vector2f::Normalize(axis);
	Vector2f point1 = circle.GetCenter() + direction * circle.GetRadius();
	Vector2f point2 = circle.GetCenter() - direction * circle.GetRadius();

	min = Vector2f::Dot(point1, axis);
	max = Vector2f::Dot(point2, axis);
	if (min > max) {
		float temp = min;
		min = max;
		max = temp;
	}
}

void Turtle::CircleCollisionComponent::DebugDraw(Window& window)
{
	window.draw(m_debugShape, m_parent->GetTransform()->GetTransformMatrix());
}

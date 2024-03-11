#include "Components/Collisions/BoxCollisionComponent.h"
#include "GameObjects/GameObject.h"

Turtle::BoxCollisionComponent::BoxCollisionComponent(GameObject* parent, const std::string& name) :
	PolygonCollisionComponent(parent, name),
	m_width(0),
	m_height(0)
{
	m_debugShape.setFillColor(sf::Color::Transparent);
	m_debugShape.setOutlineColor(sf::Color::Red);
	m_debugShape.setOutlineThickness(1);
	m_vertice.assign(4, { 0, 0 });
}

void Turtle::BoxCollisionComponent::InitCollisionParameters(float width, float height)
{
	m_width = width;
	m_height = height;

	m_debugShape.setSize({ m_width, m_height });

	_UpdateVertice();
	SetActive(true);
}

float Turtle::BoxCollisionComponent::GetWidth() const { return m_width; }
float Turtle::BoxCollisionComponent::GetHeight() const { return m_height; }

void Turtle::BoxCollisionComponent::SetWidth(float width) 
{
	m_width = width;
	m_debugShape.setSize({ m_width, m_height });
	_UpdateVertice();
}
void Turtle::BoxCollisionComponent::SetHeight(float height) 
{ 
	m_height = height;
	m_debugShape.setSize({ m_width, m_height });
	_UpdateVertice();
}

void Turtle::BoxCollisionComponent::DebugDraw(Window& window)
{
	window.draw(m_debugShape, m_parent->GetTransform()->GetTransformMatrix());
	
}

void Turtle::BoxCollisionComponent::_UpdateVertice()
{
	float left = -m_width / 2.f;
	float right = left + m_width;
	float bottom = -m_height / 2.f;
	float top = bottom + m_height;

	m_vertice[0] = (Vector2f(left, top));
	m_vertice[1] = (Vector2f(right, top));
	m_vertice[2] = (Vector2f(right, bottom));
	m_vertice[3] = (Vector2f(left, bottom));
}

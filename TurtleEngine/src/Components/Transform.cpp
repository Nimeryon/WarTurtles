// Transform.cpp
#include "Components/Transform.h"

#include "GameObjects/GameObject.h"

Turtle::Transform::Transform(GameObject* parent) :
	Component(parent, "Transform"),
    m_position(Vector2f(0, 0)),
    m_rotation(0.0f),
    m_scale(Vector2f(1, 1)),
    m_globalPosition(Vector2f(0, 0)),
    m_globalRotation(0.0f),
    m_globalScale(Vector2f(1, 1))
{}

void Turtle::Transform::TransformUpdate()
{
    if (!m_parent->GetParent())
    {
        m_globalPosition = m_position;
        m_globalRotation = m_rotation;
        m_globalScale = m_scale;
    }
    else
    {
        m_globalPosition = m_position + m_parent->GetParent()->GetTransform()->GetPosition();
        m_globalRotation = m_rotation + m_parent->GetParent()->GetTransform()->GetRotation();
        m_globalScale = m_scale * m_parent->GetParent()->GetTransform()->GetScale();
    }

}

void Turtle::Transform::SetActive(bool active) { return; }

Turtle::Vector2f Turtle::Transform::GetGlobalPosition() const { return m_globalPosition; }
float Turtle::Transform::GetGlobalRotation() const { return m_globalRotation; }
Turtle::Vector2f Turtle::Transform::GetGlobalScale() const { return m_globalScale; }

Turtle::Vector2f Turtle::Transform::GetPosition() const { return m_position; }
float Turtle::Transform::GetRotation() const { return m_rotation; }
Turtle::Vector2f Turtle::Transform::GetScale() const { return m_scale; }

void Turtle::Transform::SetPosition(const Vector2f& position)
{
	m_position = position;
    m_parent->NeedTransformUpdate();
}
void Turtle::Transform::SetRotation(float rotation)
{
	m_rotation = rotation;
    m_parent->NeedTransformUpdate();
}
void Turtle::Transform::SetScale(const Vector2f& scale)
{
	m_scale = scale;
    m_parent->NeedTransformUpdate();
}

void Turtle::Transform::Move(const Vector2f& offset)
{
	m_position += offset;
    m_parent->NeedTransformUpdate();
}
void Turtle::Transform::Rotate(float angle)
{
	m_rotation += angle;
    m_parent->NeedTransformUpdate();
}
void Turtle::Transform::Scale(const Vector2f& factors)
{
	m_scale *= factors;
    m_parent->NeedTransformUpdate();
}

Turtle::Vector2f Turtle::Transform::Right() const
{
    // Calculate the right vector based on the rotation angle
    const auto angleInRadians = static_cast<float>(m_rotation * (M_PI / 180.0f)); // Convert degrees to radians
    const float cosTheta = std::cos(angleInRadians);
    const float sinTheta = std::sin(angleInRadians);

    return { cosTheta, sinTheta };
}
Turtle::Vector2f Turtle::Transform::Up() const
{
    return Vector2f::Perpendicular(Right());
}

Turtle::Vector2f Turtle::Transform::TransformPoint(const Vector2f& point) const
{
    const auto transformedPoint = GetTransformMatrix().transformPoint({ point.x, point.y });
    return { transformedPoint.x,  transformedPoint.y };
}
Turtle::Vector2f Turtle::Transform::InverseTransformPoint(const Vector2f& point) const
{
    const auto transformedPoint = GetInverseTransformMatrix().transformPoint({ point.x, point.y });
    return { transformedPoint.x,  transformedPoint.y };
}

Turtle::TransformMatrix Turtle::Transform::GetTransformMatrix() const {
    TransformMatrix transformMatrix;
    transformMatrix.translate({ m_globalPosition.x, m_globalPosition.y });
    transformMatrix.rotate(m_globalRotation);
    transformMatrix.scale({ m_globalScale.x, m_globalScale.y });

    return transformMatrix;
}
Turtle::TransformMatrix Turtle::Transform::GetInverseTransformMatrix() const
{
    return GetTransformMatrix().getInverse();
}

void Turtle::Transform::Compose(const Transform& other, bool inWorldSpace) {
    if (inWorldSpace)
    {
        // If in world space, transform the other object to world space
        // and then combine it with this object's transformation
        *this *= other;
    }
    else
    {
        // If in relative space, combine the other object's transformation
        // with this object's transformation directly
        m_position += other.GetPosition();
        m_rotation += other.GetRotation();
        m_scale    *= other.GetScale();
    }
}

bool Turtle::Transform::operator==(const Transform& other) const
{
    return (m_position == other.GetPosition() &&
            m_rotation == other.GetRotation() &&
            m_scale    == other.GetScale());
}

bool Turtle::Transform::operator!=(const Transform& other) const
{
    return !(*this == other);
}

Turtle::Transform& Turtle::Transform::operator*=(const Transform& other)
{
    m_position += other.TransformPoint(m_position);
    m_rotation += other.GetRotation();
    m_scale *= other.GetScale();

    m_parent->NeedTransformUpdate();
    return *this;
}

Turtle::Transform Turtle::Transform::operator*(const Transform& other) const
{
    Transform result = *this;
    result *= other;

    return result;
}
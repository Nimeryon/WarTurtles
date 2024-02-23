// Transform.cpp
#include "Components/Transform.h"

Turtle::Transform::Transform(GameObject* parent) :
	Component(parent, "Transform"), m_position(Vector2f(0, 0)), m_rotation(0.0f), m_scale(Vector2f(1, 1))
{}

Turtle::Vector2f Turtle::Transform::GetGlobalPosition() const
{
    return GetPosition();
}
float Turtle::Transform::GetGlobalRotation() const
{
    return GetRotation();
}
Turtle::Vector2f Turtle::Transform::GetGlobalScale() const
{
    return GetScale();
}

Turtle::Vector2f Turtle::Transform::GetPosition() const { return m_position; }
float Turtle::Transform::GetRotation() const { return m_rotation; }
Turtle::Vector2f Turtle::Transform::GetScale() const { return m_scale; }

void Turtle::Transform::SetPosition(const Vector2f& position) {	m_position = position; }
void Turtle::Transform::SetRotation(float rotation) { m_rotation = rotation; }
void Turtle::Transform::SetScale(const Vector2f& scale) { m_scale = scale; }

void Turtle::Transform::Move(const Vector2f& offset) { m_position += offset; }
void Turtle::Transform::Rotate(float angle) { m_rotation += angle; }
void Turtle::Transform::Scale(const Vector2f& factors) { m_scale *= factors; }

void Turtle::Transform::RotateAround(const Vector2f& point, float angle)
{
    // Translate the point to the origin
    const Vector2f translatedPoint = point - m_position;

    // Rotate the translated point
    const float angleInRadians = angle * (M_PI / 180.0f); // Convert degrees to radians
    const float cosTheta = std::cos(angleInRadians);
	const float sinTheta = std::sin(angleInRadians);

    const float newX = cosTheta * translatedPoint.x - sinTheta * translatedPoint.y;
    const float newY = sinTheta * translatedPoint.x + cosTheta * translatedPoint.y;

    // Translate the rotated point back to the original position
    m_position.x += newX;
    m_position.y += newY;

    // Update the rotation of the Transform
    m_rotation += angle;
}

Turtle::Vector2f Turtle::Transform::Right() const
{
    // Calculate the right vector based on the rotation angle
    const float angleInRadians = m_rotation * (M_PI / 180.0f); // Convert degrees to radians
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
    transformMatrix.translate({ m_position.x, m_position.y });
    transformMatrix.rotate(m_rotation);
    transformMatrix.scale({ m_scale.x, m_scale.y });

    return transformMatrix;
}
Turtle::TransformMatrix Turtle::Transform::GetInverseTransformMatrix() const
{
    return GetTransformMatrix().getInverse();
}

void Turtle::Transform::Compose(const Transform& other, bool inWorldSpace) {
    if (inWorldSpace) {
        // If in world space, transform the other object to world space
        // and then combine it with this object's transformation
        *this *= other;
    }
    else {
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

    return *this;
}

Turtle::Transform Turtle::Transform::operator*(const Transform& other) const
{
    Transform result = *this;
    result *= other;

    return result;
}
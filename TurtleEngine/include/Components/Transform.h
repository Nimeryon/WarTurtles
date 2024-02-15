// Transform.h
#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "Component.h"
#include "Types/Vector2.h"
#include "Types/TransformMatrix.h"

namespace Turtle
{
class Transform : public Component
{
public:
    Transform(GameObject* parent);

    // Global getters
    Vector2f GetGlobalPosition() const;
    float GetGlobalRotation() const;
    Vector2f GetGlobalScale() const;

    // Getters
    Vector2f GetPosition() const;
    float GetRotation() const;
    Vector2f GetScale() const;

    // Setters
    void SetPosition(const Vector2f& position);
    void SetRotation(float rotation);
    void SetScale(const Vector2f& scale);

    void Move(const Vector2f& offset);
    void Rotate(float angle);
    void Scale(const Vector2f& factors);

    void RotateAround(const Vector2f& point, float angle);

    Vector2f Up() const; // Return up vector of this transform
    Vector2f Right() const; // Return right vector of this transform

    Vector2f TransformPoint(const Vector2f& point) const;
    Vector2f InverseTransformPoint(const Vector2f& point) const;

    TransformMatrix GetTransformMatrix() const;
    TransformMatrix GetInverseTransformMatrix() const;
    void Compose(const Transform& other, bool inWorldSpace = true);

    bool operator==(const Transform& other) const;
    bool operator!=(const Transform& other) const;
    Transform& operator*=(const Transform& other);
    Transform operator*(const Transform& other) const;

protected:
    Vector2f m_position;
    float m_rotation;
    Vector2f m_scale;
};
} // namespace Turtle

#endif /* TRANSFORM_H */
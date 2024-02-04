#include <iostream>
#include <algorithm>

#include "Vector2.h"
#include "../Utils/Math.h" // Include any necessary math utilities

namespace Turtle
{
template<typename Type>
Vector2<Type>::Vector2() : x(0), y(0) {}

template<typename Type>
Vector2<Type>::Vector2(Type _x, Type _y) : x(_x), y(_y) {}

template<typename Type>
const Vector2<Type> Vector2<Type>::zero = Vector2(0, 0);

template<typename Type>
const Vector2<Type> Vector2<Type>::one = Vector2(1, 1);

template<typename Type>
const Vector2<Type> Vector2<Type>::left = Vector2(-1, 0);

template<typename Type>
const Vector2<Type> Vector2<Type>::right = Vector2(1, 0);

template<typename Type>
const Vector2<Type> Vector2<Type>::up = Vector2(0, -1);

template<typename Type>
const Vector2<Type> Vector2<Type>::down = Vector2(0, 1);

template<typename Type>
Type Vector2<Type>::Angle(const Vector2& v1, const Vector2& v2)
{
    return std::acos(Dot(v1, v2) / (Magnitude(v1) * Magnitude(v2))) * (180.0 / M_PI);
}

template<typename Type>
Vector2<Type> Vector2<Type>::ClampMagnitude(const Vector2& vector, Type maxLength)
{
    Type magnitude = Magnitude(vector);
    return (magnitude > maxLength) ? Normalize(vector) * maxLength : vector;
}

template<typename Type>
Type Vector2<Type>::Distance(const Vector2& v1, const Vector2& v2)
{
    return Magnitude(v1 - v2);
}

template<typename Type>
Type Vector2<Type>::Dot(const Vector2& v1, const Vector2& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

template<typename Type>
Vector2<Type> Vector2<Type>::Lerp(const Vector2& from, const Vector2& to, Type t)
{
    t = std::clamp(t, static_cast<Type>(0.0), static_cast<Type>(1.0));
    return from + t * (to - from);
}

template<typename Type>
Vector2<Type> Vector2<Type>::LerpUnclamped(const Vector2& from, const Vector2& to, Type t)
{
    return from + t * (to - from);
}

template<typename Type>
Vector2<Type> Vector2<Type>::Max(const Vector2& v1, const Vector2& v2)
{
    return { std::max(v1.x, v2.x), std::max(v1.y, v2.y) };
}

template<typename Type>
Vector2<Type> Vector2<Type>::Min(const Vector2& v1, const Vector2& v2)
{
    return { std::min(v1.x, v2.x), std::min(v1.y, v2.y) };
}

template<typename Type>
Vector2<Type> Vector2<Type>::MoveTowards(const Vector2& current, const Vector2& target, Type maxDistanceDelta)
{
    Vector2<Type> toTarget = target - current;
    Type distance = Magnitude(toTarget);
    return (distance <= maxDistanceDelta || distance == static_cast<Type>(0.0)) ? target : current + toTarget / distance * maxDistanceDelta;
}

template<typename Type>
Vector2<Type> Vector2<Type>::Perpendicular(const Vector2& vector)
{
    return { -vector.y, vector.x };
}

template<typename Type>
Vector2<Type> Vector2<Type>::Reflect(const Vector2& inDirection, const Vector2& normal)
{
    return inDirection - 2 * Dot(inDirection, normal) * normal;
}

template<typename Type>
Vector2<Type> Vector2<Type>::Scale(const Vector2& vector, Type scalar)
{
    return { vector.x * scalar, vector.y * scalar };
}

template<typename Type>
Type Vector2<Type>::SignedAngle(const Vector2& from, const Vector2& to)
{
    Type angle = Angle(from, to);
    Type sign = (from.x * to.y - from.y * to.x < static_cast<Type>(0)) ? static_cast<Type>(-1) : static_cast<Type>(1);
    return sign * angle;
}

template<typename Type>
Vector2<Type> Vector2<Type>::SmoothDamp(const Vector2& current, const Vector2& target, Vector2& currentVelocity, Type smoothTime, Type maxSpeed, Type deltaTime)
{
    smoothTime = std::max(static_cast<Type>(0.0001), smoothTime);
    Type omega = static_cast<Type>(2.0) / smoothTime;

    Type x = omega * deltaTime;
    Type expTerm = static_cast<Type>(1.0) / (static_cast<Type>(1.0) + x + static_cast<Type>(0.48) * x * x + static_cast<Type>(0.235) * x * x * x);
    Vector2<Type> change = (current - target) * (static_cast<Type>(1.0) - expTerm);
    Vector2<Type> result = target + (currentVelocity + omega * change) * deltaTime;
    currentVelocity = (currentVelocity - omega * change) * expTerm;

    if (Magnitude(result - current) > maxSpeed) {
        result = current + Normalize(result - current) * maxSpeed;
    }

    return result;
}

template<typename Type>
Type Vector2<Type>::Magnitude(const Vector2& vector)
{
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

template<typename Type>
Vector2<Type> Vector2<Type>::Normalize(const Vector2& vector)
{
    Type magnitude = Magnitude(vector);
    return (magnitude > static_cast<Type>(0.0)) ? vector / magnitude : vector;
}

template<typename Type>
Type Vector2<Type>::SqrMagnitude() const
{
    return x * x + y * y;
}

template<typename Type>
Type Vector2<Type>::Magnitude() const
{
    return std::sqrt(SqrMagnitude());
}

template<typename Type>
Vector2<Type> Vector2<Type>::Normalized() const
{
    Type magnitude = Magnitude();
    return (magnitude > static_cast<Type>(0.0)) ? *this / magnitude : *this;
}

template<typename Type>
void Vector2<Type>::Normalize()
{
    Type magnitude = Magnitude();
    if (magnitude > static_cast<Type>(0.0))
    {
        x /= magnitude;
        y /= magnitude;
    }
}

template<typename Type>
std::string Vector2<Type>::ToString() const
{
    std::ostringstream oss;
    oss << "(" << x << ", " << y << ")";
    return oss.str();
}

template<typename Type>
Vector2<Type> Vector2<Type>::operator-() const
{
    return Vector2(-x, -y);
}

template<typename Type>
Vector2<Type> Vector2<Type>::operator+(const Vector2& other) const
{
    return Vector2(x + other.x, y + other.y);
}

template<typename Type>
Vector2<Type> Vector2<Type>::operator-(const Vector2& other) const
{
    return Vector2(x - other.x, y - other.y);
}

template<typename Type>
Vector2<Type> Vector2<Type>::operator*(Type scalar) const
{
    return Vector2(x * scalar, y * scalar);
}

template<typename Type>
Vector2<Type> Vector2<Type>::operator*(const Vector2& other) const
{
    return Vector2(x * other.x, y * other.y);
}

template<typename Type>
Vector2<Type> Vector2<Type>::operator/(Type scalar) const
{
    if (scalar != static_cast<Type>(0.0))
    {
        return Vector2(x / scalar, y / scalar);
    }

    throw std::invalid_argument("Division by zero");
}

template<typename Type>
Vector2<Type> Vector2<Type>::operator/(const Vector2& other) const
{
    if (other.x != static_cast<Type>(0.0) && other.y != static_cast<Type>(0.0))
    {
        return Vector2(x / other.x, y / other.y);
    }

    throw std::invalid_argument("Division by zero");
}

template<typename Type>
bool Vector2<Type>::operator==(const Vector2& other) const
{
    return x == other.x && y == other.y;
}

template<typename Type>
bool Vector2<Type>::operator!=(const Vector2& other) const
{
    return !(*this == other);
}

template<typename Type>
Vector2<Type>& Vector2<Type>::operator+=(const Vector2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

template<typename Type>
Vector2<Type>& Vector2<Type>::operator-=(const Vector2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

template<typename Type>
Vector2<Type>& Vector2<Type>::operator*=(Type scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

template<typename Type>
Vector2<Type>& Vector2<Type>::operator*=(const Vector2& other)
{
    x *= other.x;
    y *= other.y;
    return *this;
}

template<typename Type>
Vector2<Type>& Vector2<Type>::operator/=(Type scalar)
{
    if (scalar != static_cast<Type>(0.0))
    {
        x /= scalar;
        y /= scalar;
    }
    else
    {
        throw std::invalid_argument("Division by zero");
    }
    return *this;
}

template<typename Type>
Vector2<Type>& Vector2<Type>::operator/=(const Vector2& other)
{
    if (other.x != static_cast<Type>(0.0) && other.y != static_cast<Type>(0.0))
    {
        x /= other.x;
        y /= other.y;
    }
    else
    {
        throw std::invalid_argument("Division by zero");
    }
    return *this;
}

template <typename Type>
std::ostream& operator<<(std::ostream& os, const Vector2<Type>& vector)
{
    os << vector.ToString();
    return os;
}
}
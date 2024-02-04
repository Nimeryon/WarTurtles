// Vector2.h
#ifndef VECTOR2_H // include guard
#define VECTOR2_H

namespace Turtle
{
template<typename Type>
struct Vector2
{
    Type x;
    Type y;

    Vector2();
    Vector2(Type _x, Type _y);

    // =====================
    // Statics
    // =====================

	// Zero vector x: 0, y: 0
    static const Vector2 zero;
    // One vector x: 1, y: 1
    static const Vector2 one;
    // Left vector x: -1, y: 0
    static const Vector2 left;
    // Right vector x: 1, y: 0
    static const Vector2 right;
    // Up vector x: 0, y: -1
    static const Vector2 up;
    // Down vector x: 0, y: 1
    static const Vector2 down;

    // Function to calculate the angle between two vectors in degrees
    static Type Angle(const Vector2& v1, const Vector2& v2);

    // Function to clamp the magnitude of a vector to a specified range
    static Vector2 ClampMagnitude(const Vector2& vector, Type maxLength);

    // Function to calculate the distance between two vectors
    static Type Distance(const Vector2& v1, const Vector2& v2);

    // Function to calculate the dot product of two vectors
    static Type Dot(const Vector2& v1, const Vector2& v2);

    // Function to linearly interpolate between two vectors
    static Vector2 Lerp(const Vector2& from, const Vector2& to, Type t);

    // Function to linearly interpolate between two vectors without clamping t
    static Vector2 LerpUnclamped(const Vector2& from, const Vector2& to, Type t);

    // Function to get the maximum component of a vector
    static Vector2 Max(const Vector2& v1, const Vector2& v2);

    // Function to get the minimum component of a vector
    static Vector2 Min(const Vector2& v1, const Vector2& v2);

    // Function to move a vector towards a target vector
    static Vector2 MoveTowards(const Vector2& current, const Vector2& target, Type maxDistanceDelta);

    // Function to get a vector perpendicular to the input vector
    static Vector2 Perpendicular(const Vector2& vector);

    // Function to reflect a vector off a surface with a specified normal
    static Vector2 Reflect(const Vector2& inDirection, const Vector2& normal);

    // Function to scale a vector by a scalar factor
    static Vector2 Scale(const Vector2& vector, Type scalar);

    // Function to get the signed angle between two vectors in degrees
    static Type SignedAngle(const Vector2& from, const Vector2& to);

    // Function for smooth damping between two vectors
    static Vector2 SmoothDamp(const Vector2& current, const Vector2& target, Vector2& currentVelocity, Type smoothTime, Type maxSpeed, Type deltaTime);

    // Function to calculate the magnitude of a vector
    static Type Magnitude(const Vector2& vector);

    // Function to normalize a vector
    static Vector2 Normalize(const Vector2& vector);

    // =====================
    // Properties
	// =====================

    // Function to calculate the squared magnitude of a vector
    Type SqrMagnitude() const;

    // Function to calculate the magnitude of a vector
    Type Magnitude() const;

    // Function to normalize a vector
    Vector2 Normalized() const;

    // Function to normalize the vector
    void Normalize();

    // Function to convert the vector to a string
    std::string ToString() const;

    // Function to parse a string and set the vector's components
    void FromString(const std::string& str);

    // =====================
    // Operators
	// =====================

    // Unary minus operator
    Vector2 operator-() const;

    // Binary addition operator
    Vector2 operator+(const Vector2& other) const;

    // Binary subtraction operator
    Vector2 operator-(const Vector2& other) const;

    // Binary multiplication by scalar operator
    Vector2 operator*(Type scalar) const;

    // Binary multiplication by another vector
    Vector2 operator*(const Vector2& other) const;

    // Binary division by scalar operator
    Vector2 operator/(Type scalar) const;

    // Binary division by another vector
    Vector2 operator/(const Vector2& other) const;

    // Equality operator
    bool operator==(const Vector2& other) const;

    // Inequality operator
    bool operator!=(const Vector2& other) const;

    // Compound assignment operators
    Vector2& operator+=(const Vector2& other);

    // Compound assignment operators
    Vector2& operator-=(const Vector2& other);

    // Compound assignment operators
    Vector2& operator*=(Type scalar);

    // Compound assignment operators
    Vector2& operator*=(const Vector2& other);

    // Compound division by scalar
    Vector2& operator/=(Type scalar);

    // Compound division by another vector
    Vector2& operator/=(const Vector2& other);
};

// Overloading the << operator for Vector2
template <typename Type>
std::ostream& operator<<(std::ostream& os, const Vector2<Type>& vector);

using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;
using Vector2i = Vector2<int>;
}

#include "Vector2.hxx"
#endif /* VECTOR2_H */
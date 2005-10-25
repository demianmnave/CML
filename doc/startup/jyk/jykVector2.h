// --------------------------------------------------------------------------------------
// FILE: jykVector2.h
// AUTHOR: Jesse Krebs
// --------------------------------------------------------------------------------------

#ifndef JYKVECTOR2_H
#define JYKVECTOR2_H

#include "jykMath.h"
#include <iostream>

/* --------------------------------------------------------------------------------------

Throughout the code (not just in this class but in all of the math classes), I haven't
been consistent with numbered arguments, i.e.:

    friend Vector2<T> operator+<>(const Vector2<T>& v1, const Vector2<T>& v2);
    
Sometimes I've used 1 and 2, and sometimes 0 and 1. Obviously in the final code we'll
choose a convention and stick with it.

-------------------------------------------------------------------------------------- */

namespace jyk {

template <class T = float>
class Vector2
{
public:

    Vector2();
    Vector2(T m0, T m1);
    
    T GetX() const;
    T GetY() const;
    
    void SetX(T x);
    void SetY(T y);
    void Set(T x, T y);
    
    void Zero();

    void Minimize(const Vector2<T>& v);
    void Maximize(const Vector2<T>& v);
    
    // NormalizeSelf() returns the length. Not sure about this.
    T NormalizeSelf(T epsilon = Math<T>::EPSILON);
    T Length() const;
    T LengthSquared() const;
    T Dot(const Vector2<T>& v) const;
    T PerpDot(const Vector2<T>& v) const; // Support for (y, -x) as well as (-y, x)?
    Vector2<T> Perp() const;
    Vector2<T> UnitPerp(T epsilon = Math<T>::EPSILON) const;

    Vector2<T> Absolute() const;
    Vector2<T> Reflect(const Vector2<T>& v) const;
    Vector2<T> GetRotated(T a) const; // Choice of rotation handedness?
    void RotateSelf(T a);
    
    Vector2<T> GetNormalized(T epsilon = Math<T>::EPSILON) const;

    void Random(T min, T max);
    
    T            operator[](unsigned int i) const;    
    bool        operator==(const Vector2<T>& v) const; // No epsilon
    bool        operator!=(const Vector2<T>& v) const; // No epsilon
    Vector2<T>& operator+=(const Vector2<T>& v);
    Vector2<T>& operator-=(const Vector2<T>& v);
    Vector2<T>& operator*=(T s);
    Vector2<T>& operator/=(T s);
    Vector2<T>  operator-() const;

    // I've always made binary operators friend functions, but I'm aware that they don't have to be.
    friend Vector2<T> operator+<>(const Vector2<T>& v1, const Vector2<T>& v2);
    friend Vector2<T> operator-<>(const Vector2<T>& v1, const Vector2<T>& v2);
    friend Vector2<T> operator*<>(T s, const Vector2<T>& v);
    friend Vector2<T> operator*<>(const Vector2<T>& v, T s);
    friend Vector2<T> operator/<>(const Vector2<T>& v, T s);
    
    friend std::ostream& operator<< <>(std::ostream& os, const Vector2<T>& v);
    
    // Overloaded * for dot product, for math-ops like v*M*v
    friend T operator*<>(const Vector2<T>& v0, const Vector2<T>& v1);
  
    static Vector2<T> Perp(const Vector2<T>& v);
    static T Dot(const Vector2<T>& v1, const Vector2<T>& v2);
    static T PerpDot(const Vector2<T>& v0, const Vector2<T>& v1);
    static T LengthSquared(const Vector2<T>& v);
    
    static Vector2<T> Normalize(const Vector2<T>& v, T epsilon = Math<T>::EPSILON);
    
    static T AngleBetween(const Vector2<T>& v1, const Vector2<T>& v2);    
    static T SignedAngleBetween(const Vector2<T>& v1, const Vector2<T>& v2);
    
    static Vector2<T> Lerp(const Vector2<T>& v1, const Vector2<T>& v2, T t);
    static Vector2<T> Slerp(const Vector2<T>& v1, const Vector2<T>& v2, T t, T epsilon = Math<>::EPSILON);

    static const Vector2 ZERO;
    static const Vector2 X_AXIS;
    static const Vector2 Y_AXIS;
    
private:
    
    T m_[2];
};
// --------------------------------------------------------------------------------------
template <class T> const Vector2<T> Vector2<T>::ZERO((T)0.0, (T)0.0);
template <class T> const Vector2<T> Vector2<T>::X_AXIS((T)1.0, (T)0.0);
template <class T> const Vector2<T> Vector2<T>::Y_AXIS((T)0.0, (T)1.0);
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T>::Vector2() {}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T>::Vector2(T m0, T m1)
{
    m_[0] = m0;
    m_[1] = m1;
}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector2<T>::GetX() const
{
    return m_[0];
}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector2<T>::GetY() const
{
    return m_[1];
}
// --------------------------------------------------------------------------------------
template <class T> inline void Vector2<T>::SetX(T x)
{
    m_[0] = x;
}
// --------------------------------------------------------------------------------------
template <class T> inline void Vector2<T>::SetY(T y)
{
    m_[1] = y;
}
// --------------------------------------------------------------------------------------
template <class T> inline void Vector2<T>::Set(T x, T y)
{
    m_[0] = x;
    m_[1] = y;
}
// --------------------------------------------------------------------------------------
template <class T> inline void Vector2<T>::Zero()
{
    m_[0] = (T)0.0;
    m_[1] = (T)0.0;
}
// --------------------------------------------------------------------------------------
template <class T> void Vector2<T>::Minimize(const Vector2& v)
{
    Set(Math::Min(m_[0], v.m_[0]), Math::Min(m_[1], v.m_[1]));
}
// --------------------------------------------------------------------------------------
template <class T> void Vector2<T>::Maximize(const Vector2& v)
{
    Set(Math::Max(m_[0], v.m_[0]), Math::Max(m_[1], v.m_[1]));
}
// --------------------------------------------------------------------------------------
// Maybe don't return length? Or return boolean for success?
template <class T> inline T Vector2<T>::NormalizeSelf(T epsilon)
{
    T l = Length();
    if (l < epsilon)
        Zero();
    else
        *this /= l;
    return l;
}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector2<T>::Length() const
{
    return Math<T>::Sqrt(LengthSquared());
}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector2<T>::LengthSquared() const
{
    return m_[0] * m_[0] + m_[1] * m_[1];
}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector2<T>::Dot(const Vector2& v) const
{
    return m_[0] * v.m_[0] + m_[1] * v.m_[1];
}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector2<T>::PerpDot(const Vector2& v) const
{
        return -m_[1] * v.m_[0] + m_[0] * v.m_[1];
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T> Vector2<T>::Perp() const
{
    return Vector2(-m_[1], m_[0]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T> Vector2<T>::UnitPerp(T epsilon) const
{
    return Normalize(Perp(), epsilon);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T> Vector2<T>::Absolute() const
{
    return Vector2(Math::Fabs(m_[0]), Math::Fabs(m_[1]));
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T> Vector2<T>::Reflect(const Vector2& v) const
{
    return v - (T)2.0 * Dot(v) * *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T> Vector2<T>::GetRotated(T a) const
{
    float s = Math<T>::Sin(a);
    float c = Math<T>::Cos(a);
    return Vector2<T>(c * m_[0] - s * m_[1], s * m_[0] + c * m_[1]);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Vector2<T>::RotateSelf(T a)
{
    float s = Math<T>::Sin(a);
    float c = Math<T>::Cos(a);
    float x = m_[0];
    m_[0] = c * x - s * m_[1];
    m_[1] = s * x + c * m_[1];
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T> Vector2<T>::GetNormalized(T epsilon) const
{
    T l = Length();
    if (l < epsilon)
        return ZERO;
    return *this / l;
}
// --------------------------------------------------------------------------------------
template <class T> inline void Vector2<T>::Random(T min, T max)
{
    m_[0] = Math<T>::Random(min, max);
    m_[1] = Math<T>::Random(min, max);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector2<T>::operator[](unsigned int i) const
{
    assert(i < 2);
    return m_[i];
}
// --------------------------------------------------------------------------------------
template <class T> inline bool Vector2<T>::operator==(const Vector2& v) const
{
    return m_[0] == v.m_[0] && m_[1] == v.m_[1];
}
// --------------------------------------------------------------------------------------
template <class T> inline bool Vector2<T>::operator!=(const Vector2& v) const
{
    return m_[0] != v.m_[0] || m_[1] != v.m_[1];
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T>& Vector2<T>::operator+=(const Vector2& v)
{
    m_[0] += v.m_[0];
    m_[1] += v.m_[1];
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T>& Vector2<T>::operator-=(const Vector2& v)
{
    m_[0] -= v.m_[0];
    m_[1] -= v.m_[1];
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T>& Vector2<T>::operator*=(T s)
{
    m_[0] *= s;
    m_[1] *= s;
    return *this;
}
// --------------------------------------------------------------------------------------
// Not sure whether (or how) to check for unstable division (|s| < some small number).
template <class T> inline Vector2<T>& Vector2<T>::operator/=(T s)
{
    assert(Math<T>::Fabs(s) > Math<T>::EPSILON);
    T inv = (T)1.0 / s;
    m_[0] *= inv;
    m_[1] *= inv;
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T> Vector2<T>::operator-() const
{
    return Vector2<T>(-m_[0], -m_[1]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T> Vector2<T>::Perp(const Vector2<T>& v)
{
    return v.Perp();
}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector2<T>::Dot(const Vector2<T>& v1, const Vector2<T>& v2)
{
    return v1.Dot(v2);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector2<T>::PerpDot(const Vector2<T>& v0, const Vector2<T>& v1)
{
    return v0.PerpDot(v1);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector2<T>::LengthSquared(const Vector2<T>& v)
{
    return v.LengthSquared();
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T> Vector2<T>::Normalize(const Vector2<T>& v, T epsilon)
{
    return v.GetNormalized(epsilon);
}
// --------------------------------------------------------------------------------------
// Below is some documentation. My eventual goal is that all non-trivial functions
// be documented, either in comment blocks in the code files themselves, or in separate
// accompanying documents.
// --------------------------------------------------------------------------------------
// Vector2<T>::AngleBetween()
// Vector2<T>::SingedAngleBetween()
//
// Recall that a.b = cos(theta)|a||b|, where theta is the angle between the vectors.
// Furthermore, aT.b = sin(theta)|a||b|, where aT = a-perp. Note that the scale factor,
// |a||b|, is the same in either case. This means that we can submit aT.b and a.b to
// atan2() as arguments and get the correct signed angle between the two vectors.
//
// Another way to look at it is that b' = [a.b, aT.b], where b' is b rotated into the
// local space of a where a is parallel to the x axis in local space. Then, as expected,
// atan2() can be used to find the angle to the x axis.
//
// Using the atan2() method handles vectors of (almost) any length uniformly. The only
// failure case is when one or both of the input vectors is (near) the zero vector.
// --------------------------------------------------------------------------------------
template <class T> inline T Vector2<T>::AngleBetween(const Vector2<T>& v1, const Vector2<T>& v2)
{
    return Math<T>::Fabs(SignedAngleBetween(v1, v2));
}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector2<T>::SignedAngleBetween(const Vector2<T>& v1, const Vector2<T>& v2)
{
    return Math<T>::ATan2(v1.PerpDot(v2), v1.Dot(v2));
}
// --------------------------------------------------------------------------------------    
template <class T> Vector2<T> Vector2<T>::Lerp(const Vector2<T>& v1, const Vector2<T>& v2, T t)
{
    if (t <= (T)0.0)
        return v1;
    if (t >= (T)1.0)
        return v2;
    return v1 + t * (v2 - v1);
}
// --------------------------------------------------------------------------------------
template <class T> Vector2<T> Vector2<T>::Slerp(const Vector2<T>& v1, const Vector2<T>& v2, T t, T epsilon)
{
    if (t <= (T)0.0)
        return v1;
    if (t >= (T)1.0)
        return v2;
        
    T c = v1.Dot(v2);

    if (c < (T)-1.0 + epsilon)
        return v1; // Undefined. What's the best way to handle this?
    if (c > (T)+1.0 - epsilon)
        return Normalize(Lerp(v1, v2, t)); // Need an NLerp() function.
    
    T a = Math<T>::ACos(c); // No ACosSafe() required
    return (Math<T>::Sin(((T)1.0 - t) * a) * v1 + Math<T>::Sin(t * a) * v2) / Math<T>::Sin(a);
    
    // The only thing I'm not sure about (and this applies to Vector3 and Quaternion as well)
    // is what the best way to find the angle is. We could also write:
    
//  T s = Math<T>::Sqrt((T)1.0 - c * c);
//  T a = Math<T>::ATan2(s, c);
//  return (Math<T>::Sin(((T)1.0 - t) * a) * v1 + Math<T>::Sin(t * a) * v2) / s;
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T> operator+(const Vector2<T>& v1, const Vector2<T>& v2)
{
    return Vector2<T>(v1.m_[0] + v2.m_[0], v1.m_[1] + v2.m_[1]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T> operator-(const Vector2<T>& v1, const Vector2<T>& v2)
{
    return Vector2<T>(v1.m_[0] - v2.m_[0], v1.m_[1] - v2.m_[1]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T> operator*(T s, const Vector2<T>& v)
{
    return Vector2<T>(s * v.m_[0], s * v.m_[1]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T> operator*(const Vector2<T>& v, T s)
{
    return Vector2<T>(v.m_[0] * s, v.m_[1] * s);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T> operator/(const Vector2<T>& v, T s)
{
    assert(Math<T>::Fabs(s) > Math<T>::EPSILON);
    T inv = (T)1.0 / s;
    return Vector2<T>(v.m_[0] * inv, v.m_[1] * inv);
}
// --------------------------------------------------------------------------------------
// No preconceived idea of how this should be implemented, or what format the data should
// be displayed in. I just know that the basic math classes should overload << in some
// form.
template <class T> inline std::ostream& operator<<(std::ostream& os, const Vector2<T>& v)
{
    return os << "[" << v.m_[0] << " " << v.m_[1] << "]";
}
// --------------------------------------------------------------------------------------
template <class T> inline T operator*(const Vector2<T>& v0, const Vector2<T>& v1)
{
    return v0.Dot(v1);
}
// --------------------------------------------------------------------------------------

} // namespace jyk

#endif

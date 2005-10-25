// --------------------------------------------------------------------------------------
// FILE: Vector3.h
// AUTHOR: Jesse Krebs
// --------------------------------------------------------------------------------------

#ifndef JYKVECTOR3_H
#define JYKVECTOR3_H

#include "jykMath.h"
#include <ostream>

/* --------------------------------------------------------------------------------------

I'm just sort of making notes when they occur to me, so things I mention here probably
apply to Vector2 and other classes as well.

I've seen commercial code that has a 'divide by a vector' function, like this:

x /= v.x;
y /= v.y;
z /= v.z;

This can come in handy, but I don't know whether it's mathematically 'acceptable'. So
I'm not sure whether or not to include it here.

I've also seen const used for arguments of trivial types, like this:

Vector3& operator*=(const float s);

Is this important? Does it gain anything?

-------------------------------------------------------------------------------------- */ 

namespace jyk {

template <class T = float>
class Vector3
{
public:

    Vector3();
    Vector3(T x, T y, T z);
    Vector3(T v[]);
    
    // We can discuss the issue of component access. I know GetX() is awkward - it's just
    // left over from a previous version of the class.
    T GetX() const;
    T GetY() const;
    T GetZ() const;

    void SetX(T x);
    void SetY(T y);
    void SetZ(T z);
    void Set(T x, T y, T z);
    void Set(T v[]);

    void Zero() {Set(0.0f, 0.0f, 0.0f);}

    void Random(T min, T max);
    
    // I've done a little research on 'random unit length' algorithms with uniform
    // distribution, but haven't settled on anything yet.
    void RandomUnitLength();
    
    // What these do isn't really clear from the names. They're intended to be used for
    // things like AABB construction, but maybe they shouldn't be included.
    void Minimize(const Vector3& v);
    void Maximize(const Vector3& v);

    T NormalizeSelf(T epsilon = Math<T>::EPSILON);
    T Length() const;
    T LengthSquared() const;
    T Dot(const Vector3& v) const;
    
    Vector3<T> Cross(const Vector3<T>& v) const;    
    Vector3<T> UnitCross(const Vector3<T>& v, T epsilon = Math<T>::EPSILON) const;
    Vector3<T> GetAbsolute() const;
    Vector3<T> Reflect(const Vector3<T>& v) const;
    
    void AbsoluteSelf();
    
    Vector3<T> GetNormalized(T epsilon = Math<T>::EPSILON) const;

    // These functions are awkwardly named and kind of silly, but I need at least one of them
    // in some form or another. They're used for finding robust solutions to various
    // geometric problems.
    unsigned int GetLargestAbsoluteComponent() const;
    unsigned int GetSmallestAbsoluteComponent() const;    
    unsigned int GetMostAlignedCardinalAxis() const;
    unsigned int GetLeastAlignedCardinalAxis() const;
    unsigned int GetMostAlignedCardinalPlane() const;
    
    // Awkward name, but useful function.
    Vector3<T> GetAnyPerpendicularUnitVector() const;

    void MakeOrthonormalBasis(Vector3<T>& x, Vector3<T>& y, Vector3<T>& z, unsigned int i = 2, bool normalize = true) const;
    void MakeOrthonormalBasis(Vector3& u, Vector3& v, bool normalize = false) const;
    void ProjectOntoPlane(const Vector3& normal);
    void PushOntoPlane(const Vector3& normal); // 'Push' vector onto plane without changing its length
    bool Compare(const Vector3& v, T epsilon = Math<T>::EPSILON) const; // Compare using epsilon

    T        operator[](unsigned int i) const;
    bool     operator==(const Vector3<T>& v) const; // No epsilon
    bool     operator!=(const Vector3<T>& v) const; // No epsilon
    Vector3& operator+=(const Vector3<T>& v);
    Vector3& operator-=(const Vector3<T>& v);
    Vector3& operator*=(T s);
    Vector3& operator/=(T s);
    Vector3  operator-() const;
    
    friend Vector3<T> operator+<>(const Vector3<T>& v1, const Vector3<T>& v2);
    friend Vector3<T> operator-<>(const Vector3<T>& v1, const Vector3<T>& v2);
    friend Vector3<T> operator*<>(T s, const Vector3<T>& v);
    friend Vector3<T> operator*<>(const Vector3<T>& v, T s);
    friend Vector3<T> operator/<>(const Vector3<T>& v, T s);

    friend std::ostream& operator<< <>(std::ostream& os, const Vector3<T>& v);

    static T Length(const Vector3<T>& v);
    static T LengthSquared(const Vector3<T>& v);
    static T Dot(const Vector3<T>& v1, const Vector3<T>& v2);
    static Vector3<T> Cross(const Vector3<T>& v1, const Vector3<T>& v2);
    static Vector3<T> UnitCross(const Vector3<T>& v1, const Vector3<T>& v2);
    static Vector3<T> Normalize(const Vector3<T>& v, T epsilon = Math<T>::EPSILON);

    static T TripleProduct(const Vector3& v1, const Vector3& v2, const Vector3& v3);   
    static T AngleBetween(const Vector3<T>& v1, const Vector3<T>& v2);
    
    // Haven't added it yet, but there will also be a SignedAngleBetween() function
    // that takes an 'up' vector to determine the sign.

    static Vector3<T> Lerp(const Vector3<T>& v1, const Vector3<T>& v2, T t);
    static Vector3<T> Slerp(const Vector3<T>& v1, const Vector3<T>& v2, T t, T epsilon = Math<>::EPSILON);
    
    static const Vector3<T> ZERO;
    static const Vector3<T> X_AXIS;
    static const Vector3<T> Y_AXIS;
    static const Vector3<T> Z_AXIS;
    static const int STRIDE;
    
private:

    // Don't know about this. We'll probably be changing the access syntax anyway.
    enum {X, Y, Z};
    
    T m_[3];
};
// --------------------------------------------------------------------------------------
template <class T> const Vector3<T> Vector3<T>::ZERO((T)0.0, (T)0.0, (T)0.0);
template <class T> const Vector3<T> Vector3<T>::X_AXIS((T)1.0, (T)0.0, (T)0.0);
template <class T> const Vector3<T> Vector3<T>::Y_AXIS((T)0.0, (T)1.0, (T)0.0);
template <class T> const Vector3<T> Vector3<T>::Z_AXIS((T)0.0, (T)0.0, (T)1.0);
// --------------------------------------------------------------------------------------
// I had this in here for compatibility with OpenGL vertex arrays. Not sure if
// anything like this is useful or necessary.
template <class T> const int Vector3<T>::STRIDE(sizeof(Vector3<T>) == 3 * sizeof(T) ? 0 : sizeof(Vector3<T>));
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T>::Vector3() {}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T>::Vector3(T x, T y, T z) {Set(x, y, z);}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T>::Vector3(T v[]) {Set(v);}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector3<T>::GetX() const {return m_[X];}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector3<T>::GetY() const {return m_[Y];}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector3<T>::GetZ() const {return m_[Z];}
// --------------------------------------------------------------------------------------
template <class T> inline void Vector3<T>::SetX(T x) {m_[X] = x;}
// --------------------------------------------------------------------------------------
template <class T> inline void Vector3<T>::SetY(T y) {m_[Y] = y;}
// --------------------------------------------------------------------------------------
template <class T> inline void Vector3<T>::SetZ(T z) {m_[Z] = z;}
// --------------------------------------------------------------------------------------
template <class T> inline void Vector3<T>::Set(T x, T y, T z)
{
    m_[X] = x;
    m_[Y] = y;
    m_[Z] = z;
}
// --------------------------------------------------------------------------------------
template <class T> inline void Vector3<T>::Set(T v[])
{
    assert(v);
    m_[X] = v[0];
    m_[Y] = v[1];
    m_[Z] = v[2];
}
// --------------------------------------------------------------------------------------
template <class T> void Vector3<T>::Minimize(const Vector3& v)
{
    Set(Math<T>::Min(m_[X], v.m_[X]), Math<T>::Min(m_[Y], v.m_[Y]), Math<T>::Min(m_[Z], v.m_[Z]));
}
// --------------------------------------------------------------------------------------
template <class T> void Vector3<T>::Maximize(const Vector3& v)
{
    Set(Math<T>::Max(m_[X], v.m_[X]), Math<T>::Max(m_[Y], v.m_[Y]), Math<T>::Max(m_[Z], v.m_[Z]));
}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector3<T>::NormalizeSelf(T epsilon)
{
    T l = Length();
    if (l < epsilon)
        Zero();
    else
        *this /= l;
    return l;
}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector3<T>::Length() const
{
    return Math<T>::Sqrt(LengthSquared());
}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector3<T>::LengthSquared() const
{
    // Could be (perhaps should be) implemented as this->Dot(*this).
    return m_[X] * m_[X] + m_[Y] * m_[Y] + m_[Z] * m_[Z];
}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector3<T>::Dot(const Vector3& v) const
{
    return m_[X] * v.m_[X] + m_[Y] * v.m_[Y] + m_[Z] * v.m_[Z];
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> Vector3<T>::Cross(const Vector3& v) const
{
    return Vector3<T>(m_[Y] * v.m_[Z] - m_[Z] * v.m_[Y],
                      m_[Z] * v.m_[X] - m_[X] * v.m_[Z],
                      m_[X] * v.m_[Y] - m_[Y] * v.m_[X]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> Vector3<T>::UnitCross(const Vector3& v, T epsilon) const
{
    return Normalize(Cross(v), epsilon);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> Vector3<T>::GetAbsolute() const
{
    return Vector3(Math<T>::Fabs(m_[X]), Math<T>::Fabs(m_[Y]), Math<T>::Fabs(m_[Z]));
}
// --------------------------------------------------------------------------------------
// It isn't really clear from the function name whether 'this' or 'v' is getting
// reflected. Need to fix that.
template <class T> inline Vector3<T> Vector3<T>::Reflect(const Vector3& v) const
{
    return v - (T)2.0 * this->Dot(v) * *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline void Vector3<T>::AbsoluteSelf()
{
    Set(Math<T>::Fabs(m_[X]), Math<T>::Fabs(m_[Y]), Math<T>::Fabs(m_[Z]));
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> Vector3<T>::GetNormalized(T epsilon) const
{
    T l = Length();
    return l < epsilon ? ZERO : *this / l;
    
    // I have mixed feelings about the ?: operator. On the one hand, I like compact
    // code, and being able to reduce four lines to one is nice. On the other hand, it's
    // sort of obfuscated and hard to read. So I'm open to opinions on the subject.
}
// --------------------------------------------------------------------------------------
// How these are set up is actually important, as it ensures that 'orthonormal basis'
// functions return a basis with positive determinant.
template <class T> inline unsigned int Vector3<T>::GetLargestAbsoluteComponent() const
{
    T x = Math<T>::Fabs(m_[X]);
    T y = Math<T>::Fabs(m_[Y]);
    T z = Math<T>::Fabs(m_[Z]);
    
    // Ah, '?:' abuse. Gotta love it.
    return x > y ? (z > x ? 2 : 0) : (y > z ? 1 : 2);
}
// --------------------------------------------------------------------------------------
template <class T> inline unsigned int Vector3<T>::GetSmallestAbsoluteComponent() const
{
    T x = Math<T>::Fabs(m_[X]);
    T y = Math<T>::Fabs(m_[Y]);
    T z = Math<T>::Fabs(m_[Z]);
    
    return x < y ? (z < x ? 2 : 0) : (y < z ? 1 : 2);
}
// --------------------------------------------------------------------------------------    
template <class T> inline unsigned int Vector3<T>::GetMostAlignedCardinalAxis() const
{
    return GetLargestAbsoluteComponent();
}
// --------------------------------------------------------------------------------------
template <class T> inline unsigned int Vector3<T>::GetLeastAlignedCardinalAxis() const
{
    return GetSmallestAbsoluteComponent();
}
// --------------------------------------------------------------------------------------
template <class T> inline unsigned int Vector3<T>::GetMostAlignedCardinalPlane() const
{
    return GetLeastAlignedCardinalAxis();
}
// --------------------------------------------------------------------------------------
// Doesn't check for length < epsilon.
template <class T> inline Vector3<T> Vector3<T>::GetAnyPerpendicularUnitVector() const
{
    int i = GetLeastAlignedCardinalAxis();
    int j = (i + 1) % 3;
    int k = (j + 1) % 3; // (i + 2) % 3? Math::Next()? CyclicPermutation()?

    T v[3];
    v[i] = (T)0.0;
    v[j] = -m_[k];
    v[k] = +m_[j];
    
    T l = Math<T>::Sqrt(v[j] * v[j] + v[k] * v[k]);
    
    T invl = (T)1.0 / l;
    v[j] *= invl;
    v[k] *= invl;
    
    return Vector3<T>(v);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Vector3<T>::Random(T min, T max)
{
    m_[X] = Math<T>::Random(min, max);
    m_[Y] = Math<T>::Random(min, max);
    m_[Z] = Math<T>::Random(min, max);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Vector3<T>::RandomUnitLength()
{
    Random(-(T)1.0, (T)1.0);
    if (LengthSquared() < Math<T>::EPSILON) // Hack...
        *this = X_AXIS;
    NormalizeSelf();
}
// --------------------------------------------------------------------------------------
template <class T>
void Vector3<T>::MakeOrthonormalBasis(Vector3& x, Vector3& y, Vector3& z, unsigned int i, bool normalize) const
{
    // The code for this is in Matrix3. I'd like a vector version also. It'll either be
    // the same code (more or less), or perhaps just create the basis via a 3x3 matrix
    // and then extract the basis vectors.
}
// --------------------------------------------------------------------------------------
// For when you only need u and v.
template <class T>
void Vector3<T>::MakeOrthonormalBasis(Vector3& u, Vector3& v, bool normalize) const
{
    Vector3<T> w = *this;
    MakeOrthonormalBasis(u, v, w, 2, normalize);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector3<T>::operator[](unsigned int i) const
{
    assert(i < 3);
    return m_[i];
}
// --------------------------------------------------------------------------------------
template <class T> inline bool Vector3<T>::operator==(const Vector3& v) const
{
    return m_[X] == v.m_[X] && m_[Y] == v.m_[Y] && m_[Z] == v.m_[Z];
}
// --------------------------------------------------------------------------------------
template <class T> inline bool Vector3<T>::operator!=(const Vector3& v) const
{
    return m_[X] != v.m_[X] || m_[Y] != v.m_[Y] || m_[Z] != v.m_[Z];
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T>& Vector3<T>::operator+=(const Vector3& v)
{
    m_[X] += v.m_[X];
    m_[Y] += v.m_[Y];
    m_[Z] += v.m_[Z];
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T>& Vector3<T>::operator-=(const Vector3& v)
{
    m_[X] -= v.m_[X];
    m_[Y] -= v.m_[Y];
    m_[Z] -= v.m_[Z];
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T>& Vector3<T>::operator*=(T s)
{
    m_[X] *= s;
    m_[Y] *= s;
    m_[Z] *= s;
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T>& Vector3<T>::operator/=(T s)
{
    assert(Math<T>::Fabs(s) > Math<T>::EPSILON);
    T inv = (T)1.0 / s;
    m_[X] *= inv;
    m_[Y] *= inv;
    m_[Z] *= inv;
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> Vector3<T>::operator-() const
{
    return Vector3(-m_[X], -m_[Y], -m_[Z]);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector3<T>::Length(const Vector3<T>& v)
{
    return v.Length();
}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector3<T>::LengthSquared(const Vector3<T>& v)
{
    return v.LengthSquared();
}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector3<T>::Dot(const Vector3<T>& v1, const Vector3<T>& v2)
{
    return v1.Dot(v2);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> Vector3<T>::Cross(const Vector3<T>& v1, const Vector3<T>& v2)
{
    return v1.Cross(v2);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> Vector3<T>::UnitCross(const Vector3<T>& v1, const Vector3<T>& v2)
{
    return v1.UnitCross(v2);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> Vector3<T>::Normalize(const Vector3<T>& v, T epsilon)
{
    return v.GetNormalized(epsilon);
}
// --------------------------------------------------------------------------------------
// Some more notes for eventual documentation. I'll just leave this in wherever they
// occur.
// --------------------------------------------------------------------------------------
// The triple product of three vectors a, b and c is a.(bxc). An interesting property
// of the triple product is that it is invariant under cyclic permutation, that is,
// a.(bxc) = b.(cxa) = c.(axb). Due to the cross product, reversing any two terms will
// reverse the sign of the result.
//
// The determinant of a 3x3 matrix is also the triple product of the vectors that make
// up the matrix. The determinant can also be expressed in a number of different
// permutations, which corresponds with the cyclic invariance of the triple product.
// --------------------------------------------------------------------------------------
template <class T> T Vector3<T>::TripleProduct(const Vector3& v1, const Vector3& v2, const Vector3& v3)
{
    return v1.Dot(v2.Cross(v3));
}
// --------------------------------------------------------------------------------------
template <class T> inline T Vector3<T>::AngleBetween(const Vector3<T>& v1, const Vector3<T>& v2)
{
    return Math<T>::ATan2(Length(Cross(v1, v2)), Dot(v1, v2));
}
// --------------------------------------------------------------------------------------
// Lerp() and Slerp() are exactly the same for 2d and 3d, so it'd be nice if there were
// a way to factor out this code.
// --------------------------------------------------------------------------------------
template <class T> Vector3<T> Vector3<T>::Lerp(const Vector3<T>& v1, const Vector3<T>& v2, T t)
{
    if (t <= (T)0.0)
        return v1;
    if (t >= (T)1.0)
        return v2;
    return v1 + t * (v2 - v1);
}
// --------------------------------------------------------------------------------------
// There are some notes on this in Vector2.
template <class T> Vector3<T> Vector3<T>::Slerp(const Vector3<T>& v1, const Vector3<T>& v2, T t, T epsilon)
{
    if (t <= (T)0.0)
        return v1;
    if (t >= (T)1.0)
        return v2;
        
    T c = v1.Dot(v2);

    if (c < (T)-1.0 + epsilon)
        return v1;
    if (c > (T)+1.0 - epsilon)
        return Normalize(Lerp(v1, v2, t));
    
    T a = Math<T>::ACos(c);
    return (Math<T>::Sin(((T)1.0 - t) * a) * v1 + Math<T>::Sin(t * a) * v2) / Math<T>::Sin(a);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> operator+(const Vector3<T>& v1, const Vector3<T>& v2)
{
    return Vector3<T>(v1.m_[0] + v2.m_[0], v1.m_[1] + v2.m_[1], v1.m_[2] + v2.m_[2]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> operator-(const Vector3<T>& v1, const Vector3<T>& v2)
{
    return Vector3<T>(v1.m_[0] - v2.m_[0], v1.m_[1] - v2.m_[1], v1.m_[2] - v2.m_[2]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> operator*(T s, const Vector3<T>& v)
{
    return Vector3<T>(s * v.m_[0], s * v.m_[1], s * v.m_[2]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> operator*(const Vector3<T>& v, T s)
{
    return Vector3<T>(v.m_[0] * s, v.m_[1] * s, v.m_[2] * s);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> operator/(const Vector3<T>& v, T s)
{
    assert(Math<T>::Fabs(s) > Math<T>::EPSILON);
    T inv = (T)1.0 / s;
    return Vector3<T>(v.m_[0] * inv, v.m_[1] * inv, v.m_[2] * inv);
}
// --------------------------------------------------------------------------------------
template <class T> inline std::ostream& operator<<(std::ostream& os, const Vector3<T>& v)
{
    return os << "[" << v.m_[0] << " " << v.m_[1] << " " << v.m_[2] << "]";
}
// --------------------------------------------------------------------------------------

} // jyk

#endif

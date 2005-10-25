// --------------------------------------------------------------------------------------
// FILE: Quaternion.h
// AUTHOR: Jesse Krebs
// --------------------------------------------------------------------------------------

#ifndef JYKQUATERNION_H
#define JYKQUATERNION_H

// I was going to have an AxisAngle class at one point, but I don't know that it's necessary.
#include "jykAxisAngle.h"
#include <ostream>

namespace jyk {

/* --------------------------------------------------------------------------------------

May also offer a compressed quaternion class.

There's quite a bit of stuff that hasn't been added to this class yet, but nothing that
will be a problem.

-------------------------------------------------------------------------------------- */

template <class T = float>
class Quaternion
{
public:

    Quaternion();
    Quaternion(T x, T y, T z, T w);
    Quaternion(T q[]);
    Quaternion(const Vector3<T>& v);
    Quaternion(const AxisAngle<T>& a);
    Quaternion(const Vector3<T>& axis, T angle);
    // Maybe not...
    Quaternion(const Vector3<T>& v1,
               const Vector3<T>& v2,
               bool unit = true,
               T epsilon = (T)0.001);
               
    // I've also seen constructors that perform a slerp, but that seems a little unclear.
    // For example, should it be slerp, lerp, or nlerp?

    void Set(T x, T y, T z, T w);
    void Set(T q[]);
    void Set(const Vector3<T>& v, T w);

    void Identity();

    void FromVector(const Vector3<T>& v);
    void FromAxisAngle(const AxisAngle<T>& a);
    void FromAxisAngle(const Vector3<T>& axis, T angle, bool normalize = false, T epsilon = Math<T>::EPSILON);
    
    void ToAxisAngle(AxisAngle<T>& a, T epsilon = Math<T>::EPSILON) const;
    void ToAxisAngle(Vector3<T>& axis, T& angle, T epsilon = Math<T>::EPSILON) const;

    Vector3<T> GetXAxis() const;
    Vector3<T> GetYAxis() const;
    Vector3<T> GetZAxis() const;
    Vector3<T> GetLocalAxis(unsigned int i) const;

    Quaternion GetConjugate() const;
   
    void RotateAboutLocalX(T a);
    void RotateAboutLocalY(T a);
    void RotateAboutLocalZ(T a);
    void RotateAboutLocalAxis(unsigned int i, T a);

    // Better name for this function?
    void RotateBetweenVectors(const Vector3<T>& v1, const Vector3<T>& v2, bool unit = true, T epsilon = Math<T>::EPSILON);

    // 'Length' could also be 'Magnitude'.
    T Length() const;
    T LengthSquared() const;
    T Norm() const;
    
    void Random(T min, T max);    
    void RandomUnitLength();

    Vector3<T> RotateVector(const Vector3<T>& v) const;
 
    // Maybe not.
    bool Invariant(T epsilon = Math<T>::EPSILON) const;
   
    void Normalize();
    
    Quaternion<T> GetNormalized() const;
    
    T Dot(const Quaternion& q) const;

    Quaternion<T> Pow(T t, T epsilon = Math<T>::EPSILON) const;

    T              operator[](unsigned int i) const;
    Quaternion<T>& operator+=(const Quaternion<T>& q);
    Quaternion<T>& operator-=(const Quaternion<T>& q);
    Quaternion<T>& operator*=(T s);
    Quaternion<T>& operator/=(T s);
    Quaternion<T>  operator-() const;

    static Quaternion<T> Normalize(const Quaternion<T>& q);

    static Quaternion<T> Lerp(const Quaternion<T>& q1, const Quaternion<T>& q2, T t);
    static Quaternion<T> NLerp(const Quaternion<T>& q1, const Quaternion<T>& q2, T t);
    static Quaternion<T> Slerp(const Quaternion<T>& q1, const Quaternion<T>& q2, T t, T epsilon = Math<>::EPSILON);
    
    static Quaternion<T> Pow(const Quaternion<T>& q, T t, T epsilon = Math<T>::EPSILON);
    
    friend Quaternion<T> operator*<>(const Quaternion<T>& q1, const Quaternion<T>& q2);
    friend Quaternion<T> operator+<>(const Quaternion<T>& q1, const Quaternion<T>& q2);
    friend Quaternion<T> operator-<>(const Quaternion<T>& q1, const Quaternion<T>& q2);
    friend Quaternion<T> operator*<>(T s, const Quaternion<T>& q);
    friend Quaternion<T> operator*<>(const Quaternion<T>& q, T s);
    friend Quaternion<T> operator/<>(const Quaternion<T>& q, T s);

    friend std::ostream& operator<< <>(std::ostream& os, const Quaternion<T>& q);
    
    static const Quaternion ZERO;
    static const Quaternion IDENTITY;

private:

    // xyzw, or wxyz? Make that a configurable option? (I know that's not in the bid.)
    // In any case, I'm open to suggestions.
    
    // There's a lot of commonality between quaternions and 4d vectors - arithmatic
    // operations, length, normalization - so it seems like there should be a way to
    // factor some of that out.

    enum {X, Y, Z, W};

    T m_[4]; // xyzw for now
};
// --------------------------------------------------------------------------------------
template <class T> const Quaternion<T> Quaternion<T>::ZERO((T)0.0, (T)0.0, (T)0.0, (T)0.0);
template <class T> const Quaternion<T> Quaternion<T>::IDENTITY((T)0.0, (T)0.0, (T)0.0, (T)1.0);
// --------------------------------------------------------------------------------------
template <class T> inline Quaternion<T>::Quaternion() {}
// --------------------------------------------------------------------------------------
template <class T> inline Quaternion<T>::Quaternion(T x, T y, T z, T w)
{
    Set(x, y, z, w);
}
// --------------------------------------------------------------------------------------
template <class T> inline Quaternion<T>::Quaternion(T q[])
{
    Set(q);
}
// --------------------------------------------------------------------------------------
template <class T> inline Quaternion<T>::Quaternion(const Vector3<T>& v)
{
    FromVector(v);
}
// --------------------------------------------------------------------------------------
template <class T> inline Quaternion<T>::Quaternion(const AxisAngle<T>& a)
{
    FromAxisAngle(a);
}
// --------------------------------------------------------------------------------------
template <class T> inline Quaternion<T>::Quaternion(const Vector3<T>& axis, T angle)
{
    FromAxisAngle(axis, angle);
}
// --------------------------------------------------------------------------------------
template <class T> inline Quaternion<T>::Quaternion(const Vector3<T>& v1,
                                                    const Vector3<T>& v2,
                                                    bool unit,
                                                    T epsilon)
{
    RotateBetweenVectors(v1, v2, unit, epsilon);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Quaternion<T>::Set(T x, T y, T z, T w)
{
    m_[X] = x;
    m_[Y] = y;
    m_[Z] = z;
    m_[W] = w;
}
// --------------------------------------------------------------------------------------
template <class T> inline void Quaternion<T>::Set(T q[])
{
    assert(q);
    m_[X] = q[0];
    m_[Y] = q[1];
    m_[Z] = q[2];
    m_[W] = q[3];
}
// --------------------------------------------------------------------------------------
template <class T> inline void Quaternion<T>::Set(const Vector3<T>& v, T w)
{
    Set(v[0], v[1], v[2], w);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Quaternion<T>::Identity()
{
    Set((T)0.0, (T)0.0, (T)0.0, (T)1.0);
}
// --------------------------------------------------------------------------------------
// Quaternion<T>::GetConjugate()
//
// Returns the conjugate of *this. The conjugate of a quaternion [v, w] is [-v, w]. When
// representing rotations with quaternions, this has the effect of reversing the rotation.
// This could also be accomplished by negating w, but here we still stick with the
// correct mathematical definition.
// --------------------------------------------------------------------------------------
template <class T> inline Quaternion<T> Quaternion<T>::GetConjugate() const
{
    return Quaternion<T>(-m_[X], -m_[Y], -m_[Z], m_[W]);
}
// --------------------------------------------------------------------------------------
// Make consistent with vector version.
template <class T> inline void Quaternion<T>::Normalize()
{
    *this /= Length();
}
// --------------------------------------------------------------------------------------
template <class T> inline Quaternion<T> Quaternion<T>::GetNormalized() const
{
    T l = Length();
    if (l < Math<T>::EPSILON) // Epsilon should be an argument.
        return ZERO;
    return *this / l;
}
// --------------------------------------------------------------------------------------
template <class T> inline T Quaternion<T>::Dot(const Quaternion& q) const
{
    return m_[X] * q.m_[X] + m_[Y] * q.m_[Y] + m_[Z] * q.m_[Z] + m_[W] * q.m_[W];
}
// --------------------------------------------------------------------------------------
template <class T> inline T Quaternion<T>::Length() const
{
    return Math<T>::Sqrt(LengthSquared());
}
// --------------------------------------------------------------------------------------
// LengthSquared() and Norm() do the same thing. Not sure whether to have just one, or
// both. If both, Norm() will probably just be inlined and call LengthSquared().
template <class T> inline T Quaternion<T>::LengthSquared() const
{
    // Also, as with vectors, could be implemented as this->Dot(*this).
    return m_[X] * m_[X] + m_[Y] * m_[Y] + m_[Z] * m_[Z] + m_[W] * m_[W];
}
// --------------------------------------------------------------------------------------
template <class T> inline T Quaternion<T>::Norm() const
{
    return m_[X] * m_[X] + m_[Y] * m_[Y] + m_[Z] * m_[Z] + m_[W] * m_[W];
}
// --------------------------------------------------------------------------------------
template <class T> inline void Quaternion<T>::Random(T min, T max)
{
    Set(Math<T>::Random(min, max),
        Math<T>::Random(min, max),
        Math<T>::Random(min, max),
        Math<T>::Random(min, max));
}
// --------------------------------------------------------------------------------------
template <class T> inline void Quaternion<T>::RandomUnitLength()
{
    Random(-(T)1.0, (T)1.0);
    if (LengthSquared() < Math<T>::EPSILON) // Hack.
        *this = IDENTITY;
    Normalize();
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> Quaternion<T>::RotateVector(const Vector3<T>& v) const
{
    // Basically, this just amounts to converting the quaternion to a matrix and performing
    // a matrix-vector mult. The only reason I can think of to do it in place instead is
    // to avoid creating a temporary matrix object.

    T x2 = m_[X] + m_[X];
    T y2 = m_[Y] + m_[Y];
    T z2 = m_[Z] + m_[Z];    

    T xx2 = m_[X] * x2;
    T xy2 = m_[X] * y2;
    T xz2 = m_[X] * z2;
    T xw2 = m_[W] * x2;
    T yy2 = m_[Y] * y2;
    T yz2 = m_[Y] * z2;
    T yw2 = m_[W] * y2;
    T zz2 = m_[Z] * z2;
    T zw2 = m_[W] * z2;

    return Vector3<T>(((T)1.0 - yy2 - zz2) * v[0] + (xy2 - zw2) * v[1] + (xz2 + yw2) * v[2],
                      (xy2 + zw2) * v[0] + ((T)1.0 - xx2 - zz2) * v[1] + (yz2 - xw2) * v[2],
                      (xz2 - yw2) * v[0] + (yz2 + xw2) * v[1] + ((T)1.0 - xx2 - yy2) * v[2]);
}
// --------------------------------------------------------------------------------------
// I haven't done much work with non-unit quats, but I've read that they are useful in
// some cases. The following function however is based on the assumption that the quat
// should be unit-length, and checks for that.
template <class T> inline bool Quaternion<T>::Invariant(T epsilon) const
{
    return Math<T>::Compare(Length(), (T)1.0, epsilon);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Quaternion<T>::FromVector(const Vector3<T>& v)
{
    Set(v, (T)0.0);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Quaternion<T>::FromAxisAngle(const AxisAngle<T>& a)
{
    FromAxisAngle(a.GetAxis(), a.GetAngle());
}
// --------------------------------------------------------------------------------------
template <class T> inline void Quaternion<T>::FromAxisAngle(const Vector3<T>& axis, T angle, bool normalize, T epsilon)
{
    T s, c;
    Math<T>::SinCos(angle * (T)0.5, s, c);

    if (normalize)
    {
        T l = axis.Length();
        if (l < epsilon)
        {
            Identity();
            return;
        }
        s /= l;
    }

    Set(axis * s, c);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Quaternion<T>::ToAxisAngle(AxisAngle<T>& a, T epsilon) const
{
    Vector3<T> axis;
    T angle;
    ToAxisAngle(axis, angle);
    a.Set(axis, angle);
}
// --------------------------------------------------------------------------------------
template <class T> void Quaternion<T>::ToAxisAngle(Vector3<T>& axis, T& angle, T epsilon) const
{
    T l = Math<T>::SqrtSafe((T)1.0 - m_[W] * m_[W]);
    if (l < epsilon)
    {
        axis.Zero();
        angle = (T)0.0;
    }
    else
    {
        T invl = (T)1.0 / l;
        axis.Set(m_[X] * invl, m_[Y] * invl, m_[Z] * invl);
        angle = (T)2.0 * Math<T>::ACosSafe(m_[W]);
    }
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> Quaternion<T>::GetXAxis() const
{
    return GetLocalAxis(0);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> Quaternion<T>::GetYAxis() const
{
    return GetLocalAxis(1);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> Quaternion<T>::GetZAxis() const
{
    return GetLocalAxis(2);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> Quaternion<T>::GetLocalAxis(unsigned int i) const
{
    assert(i < 3);

    unsigned int j, k;
    Math<>::GetCyclicPermutation(i, j, k);
    
    T j2 = m_[j] + m_[j];
    T k2 = m_[k] + m_[k];
    
    T axis[3];
    
    axis[i] = (T)1.0 - m_[j] * j2 - m_[k] * k2;
    axis[j] = m_[i] * j2 + m_[W] * k2;
    axis[k] = m_[i] * k2 - m_[W] * j2;
    
    return Vector3<T>(axis);
}    
// --------------------------------------------------------------------------------------
template <class T> inline void Quaternion<T>::RotateAboutLocalX(T a)
{
    RotateAboutLocalAxis(0, a);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Quaternion<T>::RotateAboutLocalY(T a)
{
    RotateAboutLocalAxis(1, a);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Quaternion<T>::RotateAboutLocalZ(T a)
{
    RotateAboutLocalAxis(2, a);
}
// --------------------------------------------------------------------------------------
template <class T> void Quaternion<T>::RotateAboutLocalAxis(unsigned int i, T a)
{
    assert(i < 3);
    
    a *= (T)0.5;
    T s = Math<T>::Sin(a);
    T c = Math<T>::Cos(a);

    unsigned int j, k;
    Math<>::GetCyclicPermutation(i, j, k);    
    
    T q[4];
    
    q[i] = c * m_[i] + s * m_[W];
    q[j] = c * m_[j] + s * m_[k];
    q[k] = c * m_[k] - s * m_[j];
    q[W] = c * m_[W] - s * m_[i];
    
    Set(q);
}
// --------------------------------------------------------------------------------------
// Quaternion<T>::RotateBetweenVectors()
//
// This function sets 'this' to a quaternion that will rotate v1 onto v2, where v1 and v2
// are vectors with length != 0.
//
// There are a couple of ways to find q for unit-length vectors v1 and v2. One is to set
// q as [v1Xb, v1.b], where b is Normalize(v1+v2). Another method is Stan Melax's function
// from GPG1.
//
// Credit for the method used here, which works with input vectors of non-unit length and is
// gauranteed to produce a unit-length quaternion (within numerical limits), goes as far
// as I know to an online poster with the alias 'minorlogic'. My google search found
// the site minorlogic.com and the name Michael Norel, who I am pretty sure is the same
// person. A derivation of the algorithm, and a link to a thread discussing it, can be found
// at http://www.martinb.com/maths/algebra/vectors/angleBetween/index.htm.
//
// Here is a brief summary of the derivation. We want a quaternion q in the form
// [sin(a/2)n, cos(a/2)]. We have the following easy-to-compute values:
//
// c = v1Xv2
// d = v1.v2
// l = |v1||v2|
//
// So it would be convenient if we could somehow express q using only those terms.
//
// Recall that |v1Xv2| = sin(a)|v1||v2|. We can then express n as follows:
//
// n = Normalize(c) = c/Length(c) = c/(sin(a)l)
//
// So we can now express q as:
//
// [sin(a/2)(c/(sin(a)l), cos(a/2)]
//
// Although we want a unit-length quaternion for our result, we can as an intermediate step
// scale q by a constant and then normalize as our final step. If we scale q by 2cos(a/2)l,
// and substitute where appropriate using the trig identities sin(a/2) = .5(sin(a)/cos(a/2))
// and cos(a/2) = sqrt(.5(1+cos(a))), working through the math yields:
//
// [c, l + d]
//
// If we know a priori that v1 and v2 are unit-length, then we have:
//
// [c, 1 + d]
//
// Whichever version we use, normalizing as our final step gives us our unit-length result.
//
// All of the methods mentioned fail when the angle between v1 and v2 is near pi.
// This is at it should be, since in this case there is an infinite number of axes to
// choose from.
//
// With our chosen algorithm, when a is near pi, q will be near zero length and cannot be normalized.
// In this case we simply choose a unit-length vector n known to be perpendicular to v1
// and v2, and set q to [n, 0]. Since a is pi, [sin(a/2)n, cos(a/2)] = [n, 0].
// --------------------------------------------------------------------------------------
template <class T> void Quaternion<T>::RotateBetweenVectors(const Vector3<T>& v1,
                                                            const Vector3<T>& v2,
                                                            bool unit,
                                                            T epsilon)
{
    if (unit)
        Set(v1.Cross(v2), (T)1.0 + v1.Dot(v2));
    else
        Set(v1.Cross(v2), Math<T>::Sqrt(v1.LengthSquared() * v2.LengthSquared()) + v1.Dot(v2));
        
    T l = Length();
    if (l > epsilon)
        *this /= l;
    else
        Set(v1.GetAnyPerpendicularUnitVector(), (T)0.0);
}
// --------------------------------------------------------------------------------------
template <class T>
inline T Quaternion<T>::operator[](unsigned int i) const
{
    assert(i < 4);
    return m_[i];
}
// --------------------------------------------------------------------------------------
template <class T> inline Quaternion<T>& Quaternion<T>::operator+=(const Quaternion<T>& q)
{
    m_[X] += q.m_[X];
    m_[Y] += q.m_[Y];
    m_[Z] += q.m_[Z];
    m_[W] += q.m_[W];
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Quaternion<T>& Quaternion<T>::operator-=(const Quaternion<T>& q)
{
    m_[X] -= q.m_[X];
    m_[Y] -= q.m_[Y];
    m_[Z] -= q.m_[Z];
    m_[W] -= q.m_[W];
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Quaternion<T>& Quaternion<T>::operator*=(T s)
{
    m_[X] *= s;
    m_[Y] *= s;
    m_[Z] *= s;
    m_[W] *= s;
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Quaternion<T>& Quaternion<T>::operator/=(T s)
{
    assert(Math<T>::Fabs(s) > Math<T>::EPSILON);
    T inv = (T)1.0 / s;
    m_[X] *= inv;
    m_[Y] *= inv;
    m_[Z] *= inv;
    m_[W] *= inv;
    return *this;
}
// --------------------------------------------------------------------------------------
// Quaternion<T>::operator-()
//
// Negates all components. A unit quaternion and its negative represent the same rotation.
// --------------------------------------------------------------------------------------
template <class T> inline Quaternion<T> Quaternion<T>::operator-() const
{
    return Quaternion<T>(-m_[X], -m_[Y], -m_[Z], -m_[W]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Quaternion<T> Quaternion<T>::Normalize(const Quaternion<T>& q)
{
    return q.GetNormalized();
}
// --------------------------------------------------------------------------------------
template <class T> Quaternion<T> Quaternion<T>::Lerp(const Quaternion<T>& q1, const Quaternion<T>& q2, T t)
{
    if (t <= (T)0.0)
        return q1;
    if (t >= (T)1.0)
        return q2;
    return q1 + t * (q2 - q1);
}
// --------------------------------------------------------------------------------------
template <class T> Quaternion<T> Quaternion<T>::NLerp(const Quaternion<T>& q1, const Quaternion<T>& q2, T t)
{
    if (t <= (T)0.0)
        return q1;
    if (t >= (T)1.0)
        return q2;
        
    Quaternion<T> q3 = q2;

    if (q1.Dot(q3) < (T)0.0)
        q3 = -q3; // NegateSelf() function?
    
    return Normalize(Lerp(q1, q3, t));
}
// --------------------------------------------------------------------------------------
template <class T> Quaternion<T> Quaternion<T>::Slerp(const Quaternion<T>& q1, const Quaternion<T>& q2, T t, T epsilon)
{
    if (t <= (T)0.0)
        return q1;
    if (t >= (T)1.0)
        return q2;
        
    Quaternion<T> q3 = q2;
    T c = q1.Dot(q3);

    if (c < (T)0.0)
    {
        q3 = -q3;
        c = -c;
    }
    
    if (c > (T)1.0 - epsilon)
        return Normalize(Lerp(q1, q3, t));
        
    T a = Math<T>::ACos(c);
    return (Math<T>::Sin(((T)1.0 - t) * a) * q1 + Math<T>::Sin(t * a) * q3) / Math<T>::Sin(a);
    
    // You could also leave out the division by sin(a) and instead normalize. Then, length < epsilon
    // would indicate the degenerate case. I'll probably make this change at some point.
}
// --------------------------------------------------------------------------------------
template <class T> Quaternion<T> Quaternion<T>::Pow(const Quaternion<T>& q, T t, T epsilon)
{
    // I think I changed this and never tested it, so I'm not sure whether it's right.
    
    if (Math<T>::Fabs(q.m_[W]) > (T)1.0 - epsilon)
        return Normalize(Quaternion<T>(t * q.m_[X], t * q.m_[Y], t * q.m_[Z], (T)1.0 + t * (q.m_[W] - (T)1.0)));

    T a = Math<T>::ACosSafe(q.m_[W]);
    T s = Math<T>::Sin(t * a);
    return Quaternion<T>(s * q.m_[X], s * q.m_[Y], s * q.m_[Z], Math<T>::Sin(((T)1.0 - t) * a) + s * q.m_[W]) / Math<T>::Sin(a);
}
// --------------------------------------------------------------------------------------
// Here's where 'standard' and 'reverse' multiplication will come into play.
template <class T> inline Quaternion<T> operator*(const Quaternion<T>& q1, const Quaternion<T>& q2)
{
    return Quaternion<T>(
        q1.m_[3] * q2.m_[0] + q1.m_[0] * q2.m_[3] + q1.m_[1] * q2.m_[2] - q1.m_[2] * q2.m_[1],
        q1.m_[3] * q2.m_[1] + q1.m_[1] * q2.m_[3] + q1.m_[2] * q2.m_[0] - q1.m_[0] * q2.m_[2],
        q1.m_[3] * q2.m_[2] + q1.m_[2] * q2.m_[3] + q1.m_[0] * q2.m_[1] - q1.m_[1] * q2.m_[0],
        q1.m_[3] * q2.m_[3] - q1.m_[0] * q2.m_[0] - q1.m_[1] * q2.m_[1] - q1.m_[2] * q2.m_[2]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Quaternion<T> operator+(const Quaternion<T>& q1, const Quaternion<T>& q2)
{
    return Quaternion<T>(q1.m_[0] + q2.m_[0], q1.m_[1] + q2.m_[1], q1.m_[2] + q2.m_[2], q1.m_[3] + q2.m_[3]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Quaternion<T> operator-(const Quaternion<T>& q1, const Quaternion<T>& q2)
{
    return Quaternion<T>(q1.m_[0] - q2.m_[0], q1.m_[1] - q2.m_[1], q1.m_[2] - q2.m_[2], q1.m_[3] - q2.m_[3]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Quaternion<T> operator*(T s, const Quaternion<T>& q)
{
    return Quaternion<T>(s * q.m_[0], s * q.m_[1], s * q.m_[2], s * q.m_[3]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Quaternion<T> operator*(const Quaternion<T>& q, T s)
{
    return Quaternion<T>(q.m_[0] * s, q.m_[1] * s, q.m_[2] * s, q.m_[3] * s);
}
// --------------------------------------------------------------------------------------
template <class T> inline Quaternion<T> operator/(const Quaternion<T>& q, T s)
{
    assert(Math<T>::Fabs(s) > Math<T>::EPSILON); // ?
    T inv = (T)1.0 / s;
    return Quaternion<T>(q.m_[0] * inv, q.m_[1] * inv, q.m_[2] * inv, q.m_[3] * inv);
}
// --------------------------------------------------------------------------------------
template <class T> inline std::ostream& operator<<(std::ostream& os, const Quaternion<T>& q)
{
    return os << "[" << q.m_[0] << " " << q.m_[1] << " " << q.m_[2] << " " << q.m_[3] << "]";
}
// --------------------------------------------------------------------------------------

} // namespace jyk

#endif

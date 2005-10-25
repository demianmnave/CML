// --------------------------------------------------------------------------------------
// FILE: Matrix3.h
// AUTHOR: Jesse Krebs
// --------------------------------------------------------------------------------------

#ifndef JYKMATRIX3_H
#define JYKMATRIX3_H

#include "jykVector3.h"
#include "jykQuaternion.h"
#include "jykMatrix2.h"

namespace jyk {

template <class T = float>
class Matrix3
{
public:

    Matrix3();
    Matrix3(T m00, T m01, T m02,
            T m10, T m11, T m12,
            T m20, T m21, T m22);
    Matrix3(const Vector3<T>& axis, T angle);
    Matrix3(const Quaternion<T> q);
    Matrix3(const Vector3<T>& v1,
            const Vector3<T>& v2,
            bool unit = true,
            T epsilon = (T)0.001);
            
    T Get(unsigned int i, unsigned int j) const;

    void Zero();
    void Identity();

    void Set(T m00, T m01, T m02,
             T m10, T m11, T m12,
             T m20, T m21, T m22);
    
    Matrix3<T> TransposeMult(const Matrix3<T>& m) const;
    Matrix3<T> MultTranspose(const Matrix3<T>& m) const;

    Vector3<T> TransposeMult(const Vector3<T>& v) const;
    
    Vector3<T> GetXAxis() const;
    Vector3<T> GetYAxis() const;
    Vector3<T> GetZAxis() const;

    Vector3<T> GetAxis(unsigned int i) const;
    void GetBasisVectors(Vector3<T>& x, Vector3<T>& y, Vector3<T>& z) const;
 
    void FromBasisVectors(const Vector3<T>& x, const Vector3<T>& y, const Vector3<T>& z);

    void FromAxisAngle(const AxisAngle<T>& axisangle);
    void FromAxisAngle(const Vector3<T>& axis, T angle);
    void FromAxisAngle(T ax, T ay, T az, T angle);
    void FromQuaternion(const Quaternion<T>& q);
    void FromNonUnitQuaternion(const Quaternion<T>& q);

    void ToAxisAngle(AxisAngle<T>& axisangle, T epsilon = Math<T>::EPSILON) const;
    void ToAxisAngle(Vector3<T>& axis, T& angle, T epsilon = Math<T>::EPSILON) const;
    void ToQuaternion(Quaternion<T>& q) const;

    // Technically these should probably be 'parent', not 'world'.
    void SetRotateWorldX(T a);
    void SetRotateWorldY(T a);
    void SetRotateWorldZ(T a);
    void SetRotateWorldAxis(unsigned int i, T a);
    
    void RotateAboutLocalX(T a);
    void RotateAboutLocalY(T a);
    void RotateAboutLocalZ(T a);
    void RotateAboutLocalAxis(unsigned int i, T a);

    void SetUniformScale(T s);
    void SetScale(const Vector3<T>& s);
    void SetScale(T sx, T sy, T sz);
    void SetScaleAlongAxis(const Vector3<T>& n, T s);

    void SetOrthographicProjectionYZ();
    void SetOrthographicProjectionXZ();
    void SetOrthographicProjectionXY();
    void SetOrthographicProjection(unsigned int i);
    void SetOrthographicProjection(const Vector3<T>& n);

    T Trace() const;
    T Determinant() const;

    Matrix3<T> GetTranspose() const;
    void TransposeSelf();
    
    Matrix3<T> GetInverse(T epsilon = Math<T>::EPSILON) const;
    bool InvertSelf(T epsilon = Math<T>::EPSILON);
    
    void SkewSymmetric(const Vector3<T>& v);
    void TensorProduct(const Vector3<T>& v);
    void TensorProduct(const Vector3<T>& v1, const Vector3<T>& v2);
    
    void Random(T min, T max);
    
    void MakeOrthonormalBasis(const Vector3<T>& vec, unsigned int u = 2, bool normalize = true);

    void Orthogonalize(unsigned int u = 2, unsigned int n = 0, T k = (T)0.25);

    void ScaleAngle(T t);

    void RotateBetweenVectors(const Vector3<T>& v1, const Vector3<T>& v2, bool unit = true, T epsilon = Math<T>::EPSILON);
    
    static Matrix3<T> Slerp(const Matrix3<T>& m1, const Matrix3<T>& m2, T t);

    static Matrix3<T> ScaleAngle(const Matrix3<T>& m, T t);

    static T Determinant(const Matrix3<T>& m);
    static Matrix3<T> Transpose(const Matrix3<T>& m);
    static Matrix3<T> Inverse(const Matrix3<T>& m);
    
    Matrix3<T>& operator+=(const Matrix3<T>& m);
    Matrix3<T>& operator-=(const Matrix3<T>& m);
    Matrix3<T>& operator*=(const Matrix3<T>& m);
    Matrix3<T>& operator*=(T s);
    Matrix3<T>& operator/=(T s);
    Matrix3<T>  operator-() const;

    friend Matrix3<T> operator+<>(const Matrix3<T>& m1, const Matrix3<T>& m2);
    friend Matrix3<T> operator-<>(const Matrix3<T>& m1, const Matrix3<T>& m2);
    friend Matrix3<T> operator*<>(const Matrix3<T>& m1, const Matrix3<T>& m2);
    friend Matrix3<T> operator*<>(const Matrix3<T>& m, T s);
    friend Matrix3<T> operator*<>(T s, const Matrix3<T>& m);
    friend Matrix3<T> operator/<>(const Matrix3<T>& m, T s);
    friend Vector3<T> operator*<>(const Matrix3<T>& m, const Vector3<T>& v); // Column vectors for now
    
    friend std::ostream& operator<< <>(std::ostream& os, const Matrix3<T>& m);

    static const Matrix3<T> ZERO;
    static const Matrix3<T> IDENTITY;

private:

    unsigned int LargestDiagonalElementIndex() const; // Awkward name.
    bool IndexIsValid(unsigned int i) const; // Won't need this.
    void NormalizeAxis(unsigned int i, T epsilon = Math<T>::EPSILON);

    T m_[3][3];
};
// --------------------------------------------------------------------------------------
template <class T> const Matrix3<T> Matrix3<T>::ZERO((T)0.0, (T)0.0, (T)0.0,
                                                     (T)0.0, (T)0.0, (T)0.0,
                                                     (T)0.0, (T)0.0, (T)0.0);
template <class T> const Matrix3<T> Matrix3<T>::IDENTITY((T)1.0, (T)0.0, (T)0.0,
                                                         (T)0.0, (T)1.0, (T)0.0,
                                                         (T)0.0, (T)0.0, (T)1.0);
// --------------------------------------------------------------------------------------
template <class T> inline Matrix3<T>::Matrix3() {}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix3<T>::Matrix3(T m00, T m01, T m02,
                                              T m10, T m11, T m12,
                                              T m20, T m21, T m22)
{
    Set(m00, m01, m02,
        m10, m11, m12,
        m20, m21, m22);
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix3<T>::Matrix3(const Vector3<T>& axis, T angle)
{
    FromAxisAngle(axis, angle);
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix3<T>::Matrix3(const Quaternion<T> q)
{
    FromQuaternion(q);
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix3<T>::Matrix3(const Vector3<T>& v1,
                                              const Vector3<T>& v2,
                                              bool unit,
                                              T epsilon)
{
    RotateBetweenVectors(v1, v2, unit, epsilon);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Matrix3<T>::Get(unsigned int i, unsigned int j) const
{
    assert (i < 3 && j < 3);
    return m_[i][j];
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::Zero()
{
    Set((T)0.0, (T)0.0, (T)0.0,
        (T)0.0, (T)0.0, (T)0.0,
        (T)0.0, (T)0.0, (T)0.0);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::Identity()
{
    Set((T)1.0, (T)0.0, (T)0.0,
        (T)0.0, (T)1.0, (T)0.0,
        (T)0.0, (T)0.0, (T)1.0);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::Set(T m00, T m01, T m02,
                                               T m10, T m11, T m12,
                                               T m20, T m21, T m22)
{
    m_[0][0] = m00;
    m_[0][1] = m01;
    m_[0][2] = m02;
    
    m_[1][0] = m10;
    m_[1][1] = m11;
    m_[1][2] = m12;
    
    m_[2][0] = m20;
    m_[2][1] = m21;
    m_[2][2] = m22;
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix3<T> Matrix3<T>::TransposeMult(const Matrix3<T>& m) const
{
    return Matrix3<T>(m_[0][0] * m.m_[0][0] + m_[1][0] * m.m_[1][0] + m_[2][0] * m.m_[2][0],
                      m_[0][0] * m.m_[0][1] + m_[1][0] * m.m_[1][1] + m_[2][0] * m.m_[2][1],
                      m_[0][0] * m.m_[0][2] + m_[1][0] * m.m_[1][2] + m_[2][0] * m.m_[2][2],
                      m_[0][1] * m.m_[0][0] + m_[1][1] * m.m_[1][0] + m_[2][1] * m.m_[2][0],
                      m_[0][1] * m.m_[0][1] + m_[1][1] * m.m_[1][1] + m_[2][1] * m.m_[2][1],
                      m_[0][1] * m.m_[0][2] + m_[1][1] * m.m_[1][2] + m_[2][1] * m.m_[2][2],
                      m_[0][2] * m.m_[0][0] + m_[1][2] * m.m_[1][0] + m_[2][2] * m.m_[2][0],
                      m_[0][2] * m.m_[0][1] + m_[1][2] * m.m_[1][1] + m_[2][2] * m.m_[2][1],
                      m_[0][2] * m.m_[0][2] + m_[1][2] * m.m_[1][2] + m_[2][2] * m.m_[2][2]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix3<T> Matrix3<T>::MultTranspose(const Matrix3<T>& m) const
{
    return Matrix3<T>(m_[0][0] * m.m_[0][0] + m_[0][1] * m.m_[0][1] + m_[0][2] * m.m_[0][2],
                      m_[0][0] * m.m_[1][0] + m_[0][1] * m.m_[1][1] + m_[0][2] * m.m_[1][2],
                      m_[0][0] * m.m_[2][0] + m_[0][1] * m.m_[2][1] + m_[0][2] * m.m_[2][2],
                      m_[1][0] * m.m_[0][0] + m_[1][1] * m.m_[0][1] + m_[1][2] * m.m_[0][2],
                      m_[1][0] * m.m_[1][0] + m_[1][1] * m.m_[1][1] + m_[1][2] * m.m_[1][2],
                      m_[1][0] * m.m_[2][0] + m_[1][1] * m.m_[2][1] + m_[1][2] * m.m_[2][2],
                      m_[2][0] * m.m_[0][0] + m_[2][1] * m.m_[0][1] + m_[2][2] * m.m_[0][2],
                      m_[2][0] * m.m_[1][0] + m_[2][1] * m.m_[1][1] + m_[2][2] * m.m_[1][2],
                      m_[2][0] * m.m_[2][0] + m_[2][1] * m.m_[2][1] + m_[2][2] * m.m_[2][2]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> Matrix3<T>::TransposeMult(const Vector3<T>& v) const
{
    return Vector3<T>(m.m_[0][0] * v[0] + m.m_[1][0] * v[1] + m.m_[2][0] * v[2],
                      m.m_[0][1] * v[0] + m.m_[1][1] * v[1] + m.m_[2][1] * v[2],
                      m.m_[0][2] * v[0] + m.m_[1][2] * v[1] + m.m_[2][2] * v[2]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> Matrix3<T>::GetXAxis() const
{
    return GetAxis(0);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> Matrix3<T>::GetYAxis() const
{
    return GetAxis(1);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> Matrix3<T>::GetZAxis() const
{
    return GetAxis(2);
}
// --------------------------------------------------------------------------------------
// Column vectors throughout, but will be configurable.
template <class T> inline Vector3<T> Matrix3<T>::GetAxis(unsigned int i) const
{
    assert(i < 3);
    return Vector3<T>(m_[0][i], m_[1][i], m_[2][i]);
}    
// --------------------------------------------------------------------------------------
template <class T>
inline void Matrix3<T>::GetBasisVectors(Vector3<T>& x, Vector3<T>& y, Vector3<T>& z) const
{
    x.Set(m_[0][0], m_[1][0], m_[2][0]);
    y.Set(m_[0][1], m_[1][1], m_[2][1]);
    z.Set(m_[0][2], m_[1][2], m_[2][2]);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::FromBasisVectors(const Vector3<T>& x,
                                                            const Vector3<T>& y,
                                                            const Vector3<T>& z)
{
    Set(x[0], y[0], z[0],
        x[1], y[1], z[1],
        x[2], y[2], z[2]);
}
// --------------------------------------------------------------------------------------
// Matrix3<T>::FromAxisAngle()
//
// A vector v can be rotated around a normalized axis n by decomposing v into components
// parallel and perpendicular to n. The parallel componenent is invariant under rotation,
// so we need simply rotate the perpendicular component and then add the parallel component
// back in to get v'.
//
// v-parallel can be found by (v.n)n. v-perp is then trivially v - (v.n)n.
//
// We now want to rotate v-perp in the plane perpendicular to n. For that we need two
// basis vectors. v-perp will be our 'i' axis. For 'j' we need a vector perpendicular
// to v-perp. This can be found as nxv.
//
// We can now find v'-perp as a simple linear combination of i and j, cos(a)i + sin(a)j.
//
// Expanding and adding back in v-parallel, we get:
//
// v' = (v.n)n + cos(a)(v - (v.n)n) + sin(a)(nxv)
//
// When we rotate an orthonormal basis around an axis, we are in effect rotating each
// of the three basis vectors around that axis. Our reference basis vectors are [1 0 0],
// [0 1 0], and [0 0 1]. The axes of our new basis after rotation can be found by applying
// the above equation to these basis vectors. The matrix can also be derived by expanding
// the above equation, grouping, and expressing in matrix-vector form.
//
// If c and s are the cos and sin of the angle, and x, y and z are the axis components,
// then the rotation matrix is:
//
// [(1 - c)xx + c            (1 - c)xy + sz        (1 - c)xz - sy]
// [(1 - c)xy - sz            (1 - c)yy + c        (1 - c)yz - sx]
// [(1 - c)xz + sy            (1 - c)yz - sx        (1 - c)zz + c]
//
// Exploiting a few common terms yields our implementation.
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::FromAxisAngle(const AxisAngle<T>& a)
{
    FromAxisAngle(a.GetAxis(), a.GetAngle());
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::FromAxisAngle(const Vector3<T>& axis, T angle)
{
    FromAxisAngle(axis[0], axis[1], axis[2], angle);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix3<T>::FromAxisAngle(T ax, T ay, T az, T angle)
{
    T s, c;
    Math<T>::SinCos(angle, s, c);
    T omc = (T)1.0 - c;
    
    T xomc = ax * omc;
    T yomc = ay * omc;
    T zomc = az * omc;
    
    T xxomc = ax * xomc;
    T xyomc = ax * yomc;
    T xzomc = ax * zomc;
    T yyomc = ay * yomc;
    T yzomc = ay * zomc;
    T zzomc = az * zomc;
    
    T xs = ax * s;
    T ys = ay * s;
    T zs = az * s;

    Set(xxomc + c,  xyomc - zs, xzomc + ys,
        xyomc + zs, yyomc + c,  yzomc - xs,
        xzomc - ys, yzomc + xs, zzomc + c);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::FromQuaternion(const Quaternion<T>& q)
{
    T x = q[0];
    T y = q[1];
    T z = q[2];
    T w = q[3];
    
    T x2 = x + x;
    T y2 = y + y;
    T z2 = z + z;    

    T xx2 = x * x2;
    T xy2 = x * y2;
    T xz2 = x * z2;
    T xw2 = w * x2;
    T yy2 = y * y2;
    T yz2 = y * z2;
    T yw2 = w * y2;
    T zz2 = z * z2;
    T zw2 = w * z2;

    Set((T)1.0 - yy2 - zz2, xy2 - zw2,            xz2 + yw2,
        xy2 + zw2,            (T)1.0 - xx2 - zz2, yz2 - xw2,
        xz2 - yw2,            yz2 + xw2,            (T)1.0 - xx2 - yy2);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::FromNonUnitQuaternion(const Quaternion<T>& q)
{
    T x = q[0];
    T y = q[1];
    T z = q[2];
    T w = q[3];

    T s = (T)2.0 / q.Norm();
    
    T xs = x * s;
    T ys = y * s;
    T zs = z * s;    

    T xxs = x * xs;
    T xys = x * ys;
    T xzs = x * zs;
    T xws = w * xs;
    T yys = y * ys;
    T yzs = y * zs;
    T yws = w * ys;
    T zzs = z * zs;
    T zws = w * zs;
    
    Set((T)1.0 - yys - zzs, xys - zws,            xzs + yws,
        xys + zws,            (T)1.0 - xxs - zzs, yzs - xws,
        xzs - yws,            yzs + xws,            (T)1.0 - xxs - yys);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::ToAxisAngle(AxisAngle<T>& axisangle, T epsilon) const
{
    Vector3<T> axis;
    T angle;
    ToAxisAngle(axis, angle, epsilon);
    axisangle.Set(axis, angle);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix3<T>::ToAxisAngle(Vector3<T>& axis, T& angle, T epsilon) const
{
    axis.Set(m_[2][1] - m_[1][2], m_[0][2] - m_[2][0], m_[1][0] - m_[0][1]);
    T l = axis.Length();
    T tmo = Trace() - (T)1.0;
    
    if (l > epsilon)
    {
        axis /= l;
        angle = Math<T>::ACos(tmo * (T)0.5);
    }
    else if (tmo > (T)0.0)
    {
        axis.Zero();
        angle = (T)0.0;
    }
    else
    {
        unsigned int i = LargestDiagonalElementIndex();
        unsigned int j, k;
        Math<>::GetCyclicPermutation(i, j, k);
        
        T n[3];    
        n[i] = Math<T>::Sqrt(m_[i][i] - m_[j][j] - m_[k][k] + (T)1.0) * (T)0.5;
        T inv2 = (T)0.5 / n[i];
        n[j] = m_[j][i] * inv2;
        n[k] = m_[k][i] * inv2;
        
        axis.Set(n);
        angle = Math<T>::PI;
    }
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix3<T>::ToQuaternion(Quaternion<T>& q) const
{
    T r[4];
    T t = Trace();
    if (t >= (T)0.0)
    {
        r[3] = Math<T>::Sqrt(t + (T)1.0) * (T)0.5;
        T s = (T)0.25 / r[3];
        r[0] = (m_[2][1] - m_[1][2]) * s;
        r[1] = (m_[0][2] - m_[2][0]) * s;
        r[2] = (m_[1][0] - m_[0][1]) * s;
    }
    else
    {
        unsigned int i = LargestDiagonalElementIndex();
        unsigned int j, k;
        Math<>::GetCyclicPermutation(i, j, k);
        
        r[i] = Math<T>::Sqrt(m_[i][i] - m_[j][j] - m_[k][k] + (T)1.0) * (T)0.5;
        T s = (T)0.25 / r[i];
        r[j] = (m_[i][j] + m_[j][i]) * s;
        r[k] = (m_[i][k] + m_[k][i]) * s;
        r[3] = (m_[k][j] - m_[j][k]) * s;
    }
    q.Set(r);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::SetRotateWorldX(T a)
{
    SetRotateWorldAxis(0, a);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::SetRotateWorldY(T a)
{
    SetRotateWorldAxis(1, a);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::SetRotateWorldZ(T a)
{
    SetRotateWorldAxis(2, a);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix3<T>::SetRotateWorldAxis(unsigned int i, T a)
{
    if (!IndexIsValid(i))
        return;
        
    T s, c;
    Math<T>::SinCos(a, s, c);

    unsigned int j, k;
    Math<>::GetCyclicPermutation(i, j, k);
    
    m_[i][i] = (T)1.0;
    m_[i][j] = (T)0.0;
    m_[i][k] = (T)0.0;
    
    m_[j][i] = (T)0.0;
    m_[j][j] = +c;
    m_[j][k] = -s;
    
    m_[k][i] = (T)0.0;
    m_[k][j] = +s;
    m_[k][k] = +c;
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::RotateAboutLocalX(T a)
{
    RotateAboutLocalAxis(0, a);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::RotateAboutLocalY(T a)
{
    RotateAboutLocalAxis(1, a);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::RotateAboutLocalZ(T a)
{
    RotateAboutLocalAxis(2, a);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix3<T>::RotateAboutLocalAxis(unsigned int i, T a)
{
    if (!IndexIsValid(i))
        return;
    
    unsigned int j, k;
    Math<>::GetCyclicPermutation(i, j, k);

    T u[3], v[3];
    T s, c;
    Math<T>::SinCos(a, s, c);
    
    u[0] = c * m_[0][j] + s * m_[0][k];
    u[1] = c * m_[1][j] + s * m_[1][k];
    u[2] = c * m_[2][j] + s * m_[2][k];
    
    v[0] = c * m_[0][k] - s * m_[0][j];
    v[1] = c * m_[1][k] - s * m_[1][j];
    v[2] = c * m_[2][k] - s * m_[2][j];
    
    m_[0][j] = u[0];
    m_[1][j] = u[1];
    m_[2][j] = u[2];
    
    m_[0][k] = v[0];
    m_[1][k] = v[1];
    m_[2][k] = v[2];  
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::SetUniformScale(T s)
{
    Set(s,      (T)0.0, (T)0.0,
        (T)0.0, s,      (T)0.0,
        (T)0.0, (T)0.0, s);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::SetScale(const Vector3<T>& s)
{
    Set(s[0],   (T)0.0, (T)0.0,
        (T)0.0, s[1],   (T)0.0,
        (T)0.0, (T)0.0, s[2]);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::SetScale(T sx, T sy, T sz)
{
    Set(sx,     (T)0.0, (T)0.0,
        (T)0.0, sy,     (T)0.0,
        (T)0.0, (T)0.0, sz);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix3<T>::SetScaleAlongAxis(const Vector3<T>& n, T s)
{
    T smo = s - (T)1.0;
    T smoxx = smo * n[0] * n[0];
    T smoxy = smo * n[0] * n[1];
    T smoxz = smo * n[0] * n[2];
    T smoyy = smo * n[1] * n[1];
    T smoyz = smo * n[1] * n[2];    
    T smozz = smo * n[2] * n[2];
    
    Set((T)1.0 + smoxx, smoxy,            smoxz,
        smoxy,            (T)1.0 + smoyy, smoyz,
        smoxz,            smoyz,            (T)1.0 + smozz);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::SetOrthographicProjectionYZ()
{
    SetOrthographicProjection(0);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::SetOrthographicProjectionXZ()
{
    SetOrthographicProjection(1);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::SetOrthographicProjectionXY()
{
    SetOrthographicProjection(2);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix3<T>::SetOrthographicProjection(unsigned int i)
{
    if (!IndexIsValid(i))
        return;

    Identity();
    m_[i][i] = (T)0.0;
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix3<T>::SetOrthographicProjection(const Vector3<T>& n)
{
    T xx = n[0] * n[0];
    T xy = n[0] * n[1];
    T xz = n[0] * n[2];
    T yy = n[1] * n[1];
    T yz = n[1] * n[2];
    T zz = n[2] * n[2];
    
    Set((T)1.0 - xx, -xy,          -xz,
        -xy,         (T)1.0 - yy, -yz,
        -xz,         -yz,          (T)1.0 - zz);
}
// --------------------------------------------------------------------------------------
// Matrix3<T>::Trace()
//
// The trace is the sum of the diagonal elements
// --------------------------------------------------------------------------------------
template <class T> inline T Matrix3<T>::Trace() const
{
    return m_[0][0] + m_[1][1] + m_[2][2];
}
// --------------------------------------------------------------------------------------
template <class T> T Matrix3<T>::Determinant() const
{
    return m_[0][0] * (m_[1][1] * m_[2][2] - m_[1][2] * m_[2][1]) -
           m_[0][1] * (m_[1][0] * m_[2][2] - m_[1][2] * m_[2][0]) +
           m_[0][2] * (m_[1][0] * m_[2][1] - m_[1][1] * m_[2][0]);
}
// --------------------------------------------------------------------------------------
template <class T> Matrix3<T> Matrix3<T>::GetTranspose() const
{
    return Matrix3<T>(m_[0][0], m_[1][0], m_[2][0],
                      m_[0][1], m_[1][1], m_[2][1],
                      m_[0][2], m_[1][2], m_[2][2]);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix3<T>::TransposeSelf()
{
    T m01 = m_[0][1];
    T m02 = m_[0][2];
    T m12 = m_[1][2];
    
    m_[0][1] = m_[1][0];
    m_[0][2] = m_[2][0];
    m_[1][2] = m_[2][1];
    
    m_[1][0] = m01;
    m_[2][0] = m02;
    m_[2][1] = m12;
}
// --------------------------------------------------------------------------------------
// The Doom 3 math library uses another method for inversion that I'm not familiar
// with. At some point I'd like to find out what the method is called so I can
// research it. For larger matrices, this method seems to be considerably more efficient
// than adjoint/determinant.
// --------------------------------------------------------------------------------------
template <class T> bool Matrix3<T>::InvertSelf(T epsilon)
{
    T co[3][3];
    
    co[0][0] = m_[1][1] * m_[2][2] - m_[1][2] * m_[2][1];
    co[0][1] = m_[1][2] * m_[2][0] - m_[1][0] * m_[2][2];
    co[0][2] = m_[1][0] * m_[2][1] - m_[1][1] * m_[2][0];
    
    T det = m_[0][0] * co[0][0] + m_[0][1] * co[0][1] + m_[0][2] * co[0][2];
    
    if (Math<T>::Fabs(det) < epsilon)
        return false;
        
    T invdet = (T)1.0 / det;
    
    co[1][0] = m_[0][2] * m_[2][1] - m_[0][1] * m_[2][2];
    co[1][1] = m_[0][0] * m_[2][2] - m_[0][2] * m_[2][0];
    co[1][2] = m_[0][1] * m_[2][0] - m_[0][0] * m_[2][1];
    co[2][0] = m_[0][1] * m_[1][2] - m_[0][2] * m_[1][1];
    co[2][1] = m_[0][2] * m_[1][0] - m_[0][0] * m_[1][2];
    co[2][2] = m_[0][0] * m_[1][1] - m_[0][1] * m_[1][0];

    m_[0][0] = co[0][0] * invdet;
    m_[0][1] = co[1][0] * invdet;
    m_[0][2] = co[2][0] * invdet;
    
    m_[1][0] = co[0][1] * invdet;
    m_[1][1] = co[1][1] * invdet;
    m_[1][2] = co[2][1] * invdet;
    
    m_[2][0] = co[0][2] * invdet;
    m_[2][1] = co[1][2] * invdet;
    m_[2][2] = co[2][2] * invdet;
    
    return true;
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix3<T>::SkewSymmetric(const Vector3<T>& v)
{
    Set( (T)0.0, -v[2],    v[1],
         v[2],    (T)0.0, -v[0],
        -v[1],    v[0],    (T)0.0);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix3<T>::TensorProduct(const Vector3<T>& v)
{
    T v01 = v[0] * v[1];
    T v02 = v[0] * v[2];
    T v12 = v[1] * v[2];
    
    Set(v[0] * v[0], v01,          v02,
        v01,         v[1] * v[1], v12,
        v02,         v12,          v[2] * v[2]);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix3<T>::TensorProduct(const Vector3<T>& v1, const Vector3<T>& v2)
{
    Set(v1[0] * v2[0], v1[0] * v2[1], v1[0] * v2[2],
        v1[1] * v2[0], v1[1] * v2[1], v1[1] * v2[2],
        v1[2] * v2[0], v1[2] * v2[1], v1[2] * v2[2]);
}
// --------------------------------------------------------------------------------------
template <class T>
void Matrix3<T>::MakeOrthonormalBasis(const Vector3<T>& vec, unsigned int u, bool normalize)
{
    if (!IndexIsValid(u))
        return;

    unsigned int v, w;
    Math<>::GetCyclicPermutation(u, v, w);        

    unsigned int i = vec.GetLeastAlignedCardinalAxis();
    unsigned int j, k;
    Math<>::GetCyclicPermutation(i, j, k);

    Vector3<T> temp = vec;
    if (normalize)
        temp.NormalizeSelf();
    
    m_[0][u] = temp[0];
    m_[1][u] = temp[1];
    m_[2][u] = temp[2];
    
    m_[i][v] = (T)0.0;
    m_[j][v] = -m_[k][u];
    m_[k][v] = +m_[j][u];
    
    T lsqr = m_[j][v] * m_[j][v] + m_[k][v] * m_[k][v];
    T invl = Math<T>::InvSqrt(lsqr);
    
    m_[j][v] *= invl;
    m_[k][v] *= invl;
    
    m_[i][w] = lsqr * invl;
    m_[j][w] = -m_[i][u] * m_[k][v];
    m_[k][w] = +m_[i][u] * m_[j][v];
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix3<T>::Orthogonalize(unsigned int u, unsigned int n, T k)
{
    assert(k > 0.0f);
    
    if (!IndexIsValid(u))
        return;

    for (unsigned int c = 0; c < n; ++c)
    {        
        T dot00 = m_[0][0] * m_[0][0] + m_[1][0] * m_[1][0] + m_[2][0] * m_[2][0];
        T dot01 = m_[0][0] * m_[0][1] + m_[1][0] * m_[1][1] + m_[2][0] * m_[2][1];
        T dot02 = m_[0][0] * m_[0][2] + m_[1][0] * m_[1][2] + m_[2][0] * m_[2][2];
        T dot11 = m_[0][1] * m_[0][1] + m_[1][1] * m_[1][1] + m_[2][1] * m_[2][1];
        T dot12 = m_[0][1] * m_[0][2] + m_[1][1] * m_[1][2] + m_[2][1] * m_[2][2];
        T dot22 = m_[0][2] * m_[0][2] + m_[1][2] * m_[1][2] + m_[2][2] * m_[2][2];
        
        T s01 = k * dot01 / dot11;
        T s02 = k * dot02 / dot22;
        T s10 = k * dot01 / dot00;
        T s12 = k * dot12 / dot22;
        T s20 = k * dot02 / dot00;
        T s21 = k * dot12 / dot11;
        
        T m[3][3];
        
        m[0][0] = m_[0][0] - s01 * m_[0][1] - s02 * m_[0][2];
        m[1][0] = m_[1][0] - s01 * m_[1][1] - s02 * m_[1][2];
        m[2][0] = m_[2][0] - s01 * m_[2][1] - s02 * m_[2][2];
        
        m[0][1] = m_[0][1] - s10 * m_[0][0] - s12 * m_[0][2];
        m[1][1] = m_[1][1] - s10 * m_[1][0] - s12 * m_[1][2];
        m[2][1] = m_[2][1] - s10 * m_[2][0] - s12 * m_[2][2];
        
        m[0][2] = m_[0][2] - s20 * m_[0][0] - s21 * m_[0][1];
        m[1][2] = m_[1][2] - s20 * m_[1][0] - s21 * m_[1][1];
        m[2][2] = m_[2][2] - s20 * m_[2][0] - s21 * m_[2][1];

        m_[0][0] = m[0][0];
        m_[0][1] = m[0][1];
        m_[0][2] = m[0][2];
        m_[1][0] = m[1][0];
        m_[1][1] = m[1][1];
        m_[1][2] = m[1][2];
        m_[2][0] = m[2][0];
        m_[2][1] = m[2][1];
        m_[2][2] = m[2][2];
    }

    unsigned int v, w;
    Math<>::GetCyclicPermutation(u, v, w);

    NormalizeAxis(u);
    m_[0][v] = m_[1][w] * m_[2][u] - m_[2][w] * m_[1][u];
    m_[1][v] = m_[2][w] * m_[0][u] - m_[0][w] * m_[2][u];
    m_[2][v] = m_[0][w] * m_[1][u] - m_[1][w] * m_[0][u];
    NormalizeAxis(v);
    m_[0][w] = m_[1][u] * m_[2][v] - m_[2][u] * m_[1][v];
    m_[1][w] = m_[2][u] * m_[0][v] - m_[0][u] * m_[2][v];
    m_[2][w] = m_[0][u] * m_[1][v] - m_[1][u] * m_[0][v];
    NormalizeAxis(w);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix3<T>::ScaleAngle(T t)
{
    Vector3f n;
    float a;
    ToAxisAngle(n, a);
    FromAxisAngle(n, a * t);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix3<T>::RotateBetweenVectors(const Vector3<T>& v1,
                                                         const Vector3<T>& v2,
                                                         bool unit,
                                                         T epsilon)
{
    // I haven't settled on an implementation yet, but after spending some time with
    // it, it seems the fastest and most stable solution may be to just create a
    // vector-to-vector quaternion and convert it to a matrix.
}
// --------------------------------------------------------------------------------------
template <class T> Matrix3<T> Matrix3<T>::Slerp(const Matrix3<T>& m1, const Matrix3<T>& m2, T t)
{
    if (t <= (T)0.0)
        return m1;
    if (t >= (T)1.0)
        return m2;

    Matrix3<T> R = m1.TransposeMult(m2);
    Vector3<T> axis;
    T angle;
    R.ToAxisAngle(axis, angle);
    angle *= t;
    R.FromAxisAngle(axis, angle); // Any possible shortcuts here?
    
    return m1 * R;

    // I plan to condense this to:
    
//  return m1 * ScaleAngle(Difference(m1, m2));
}
// --------------------------------------------------------------------------------------
template <class T> Matrix3<T> Matrix3<T>::ScaleAngle(const Matrix3<T>& m, T t)
{
    Vector3f n;
    float a;
    m.ToAxisAngle(n, a);
    return Matrix3<T>(n, a * t);
}
// --------------------------------------------------------------------------------------
template <class T> T Matrix3<T>::Determinant(const Matrix3<T>& m)
{
    return m.Determinant();
}
// --------------------------------------------------------------------------------------
template <class T> Matrix3<T> Matrix3<T>::Transpose(const Matrix3<T>& m)
{
    return m.GetTranspose();
}
// --------------------------------------------------------------------------------------
template <class T> Matrix3<T> Matrix3<T>::Inverse(const Matrix3<T>& m)
{
    return m.GetInverse();
}
// --------------------------------------------------------------------------------------
template <class T> inline unsigned int Matrix3<T>::LargestDiagonalElementIndex() const
{
    unsigned int i = 0;
    if (m_[1][1] > m_[i][i])
        i = 1;
    if (m_[2][2] > m_[i][i])
        i = 2;
    return i;
}
// --------------------------------------------------------------------------------------
template <class T> inline bool Matrix3<T>::IndexIsValid(unsigned int i) const
{
    assert(i < 3);
    return i < 3;
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix3<T>::NormalizeAxis(unsigned int i, T epsilon)
{
    T l = Math<T>::Sqrt(m_[0][i] * m_[0][i] + m_[1][i] * m_[1][i] + m_[2][i] * m_[2][i]);
    if (l < epsilon)
        return;
    T invl = (T)1.0 / l;
    m_[0][i] *= invl;
    m_[1][i] *= invl;
    m_[2][i] *= invl;
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix3<T>& Matrix3<T>::operator+=(const Matrix3<T>& m)
{
    m_[0][0] += m.m_[0][0];
    m_[0][1] += m.m_[0][1];
    m_[0][2] += m.m_[0][2];
    
    m_[1][0] += m.m_[1][0];
    m_[1][1] += m.m_[1][1];
    m_[1][2] += m.m_[1][2];
    
    m_[2][0] += m.m_[2][0];
    m_[2][1] += m.m_[2][1];
    m_[2][2] += m.m_[2][2];
    
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix3<T>& Matrix3<T>::operator-=(const Matrix3<T>& m)
{
    m_[0][0] -= m.m_[0][0];
    m_[0][1] -= m.m_[0][1];
    m_[0][2] -= m.m_[0][2];
    
    m_[1][0] -= m.m_[1][0];
    m_[1][1] -= m.m_[1][1];
    m_[1][2] -= m.m_[1][2];
    
    m_[2][0] -= m.m_[2][0];
    m_[2][1] -= m.m_[2][1];
    m_[2][2] -= m.m_[2][2];
    
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix3<T>& Matrix3<T>::operator*=(const Matrix3<T>& m)
{
    T r0, r1, r2;
    
    r0 = m_[0][0];
    r1 = m_[0][1];
    r2 = m_[0][2];
    
    m_[0][0] = r0 * m.m_[0][0] + r1 * m.m_[1][0] + r2 * m.m_[2][0];
    m_[0][1] = r0 * m.m_[0][1] + r1 * m.m_[1][1] + r2 * m.m_[2][1];
    m_[0][2] = r0 * m.m_[0][2] + r1 * m.m_[1][2] + r2 * m.m_[2][2];
    
    r0 = m_[1][0];
    r1 = m_[1][1];
    r2 = m_[1][2];
    
    m_[1][0] = r0 * m.m_[0][0] + r1 * m.m_[1][0] + r2 * m.m_[2][0];
    m_[1][1] = r0 * m.m_[0][1] + r1 * m.m_[1][1] + r2 * m.m_[2][1];
    m_[1][2] = r0 * m.m_[0][2] + r1 * m.m_[1][2] + r2 * m.m_[2][2];
    
    r0 = m_[2][0];
    r1 = m_[2][1];
    r2 = m_[2][2];
    
    m_[2][0] = r0 * m.m_[0][0] + r1 * m.m_[1][0] + r2 * m.m_[2][0];
    m_[2][1] = r0 * m.m_[0][1] + r1 * m.m_[1][1] + r2 * m.m_[2][1];
    m_[2][2] = r0 * m.m_[0][2] + r1 * m.m_[1][2] + r2 * m.m_[2][2];

    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix3<T>& Matrix3<T>::operator*=(T s)
{
    m_[0][0] *= s;
    m_[0][1] *= s;
    m_[0][2] *= s;
    
    m_[1][0] *= s;
    m_[1][1] *= s;
    m_[1][2] *= s;
    
    m_[2][0] *= s;
    m_[2][1] *= s;
    m_[2][2] *= s;
    
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix3<T>& Matrix3<T>::operator/=(T s)
{
    T inv = (T)1.0 / s;

    m_[0][0] *= inv;
    m_[0][1] *= inv;
    m_[0][2] *= inv;
    
    m_[1][0] *= inv;
    m_[1][1] *= inv;
    m_[1][2] *= inv;
    
    m_[2][0] *= inv;
    m_[2][1] *= inv;
    m_[2][2] *= inv;
    
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix3<T> Matrix3<T>::operator-() const
{
    return Matrix3<T>(-m_[0][0], -m_[0][1], -m_[0][2],
                      -m_[1][0], -m_[1][1], -m_[1][2],
                      -m_[2][0], -m_[2][1], -m_[2][2]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix3<T> operator+(const Matrix3<T>& m1, const Matrix3<T>& m2)
{
    return Matrix3<T>(m1.m_[0][0] + m2.m_[0][0], m1.m_[0][1] + m2.m_[0][1], m1.m_[0][2] + m2.m_[0][2],
                      m1.m_[1][0] + m2.m_[1][0], m1.m_[1][1] + m2.m_[1][1], m1.m_[1][2] + m2.m_[1][2],
                      m1.m_[2][0] + m2.m_[2][0], m1.m_[2][1] + m2.m_[2][1], m1.m_[2][2] + m2.m_[2][2]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix3<T> operator-(const Matrix3<T>& m1, const Matrix3<T>& m2)
{
    return Matrix3<T>(m1.m_[0][0] - m2.m_[0][0], m1.m_[0][1] - m2.m_[0][1], m1.m_[0][2] - m2.m_[0][2],
                      m1.m_[1][0] - m2.m_[1][0], m1.m_[1][1] - m2.m_[1][1], m1.m_[1][2] - m2.m_[1][2],
                      m1.m_[2][0] - m2.m_[2][0], m1.m_[2][1] - m2.m_[2][1], m1.m_[2][2] - m2.m_[2][2]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix3<T> operator*(const Matrix3<T>& m1, const Matrix3<T>& m2)
{
    return Matrix3<T>(m1.m_[0][0] * m2.m_[0][0] + m1.m_[0][1] * m2.m_[1][0] + m1.m_[0][2] * m2.m_[2][0],
                      m1.m_[0][0] * m2.m_[0][1] + m1.m_[0][1] * m2.m_[1][1] + m1.m_[0][2] * m2.m_[2][1],
                      m1.m_[0][0] * m2.m_[0][2] + m1.m_[0][1] * m2.m_[1][2] + m1.m_[0][2] * m2.m_[2][2],
                      m1.m_[1][0] * m2.m_[0][0] + m1.m_[1][1] * m2.m_[1][0] + m1.m_[1][2] * m2.m_[2][0],
                      m1.m_[1][0] * m2.m_[0][1] + m1.m_[1][1] * m2.m_[1][1] + m1.m_[1][2] * m2.m_[2][1],
                      m1.m_[1][0] * m2.m_[0][2] + m1.m_[1][1] * m2.m_[1][2] + m1.m_[1][2] * m2.m_[2][2],
                      m1.m_[2][0] * m2.m_[0][0] + m1.m_[2][1] * m2.m_[1][0] + m1.m_[2][2] * m2.m_[2][0],
                      m1.m_[2][0] * m2.m_[0][1] + m1.m_[2][1] * m2.m_[1][1] + m1.m_[2][2] * m2.m_[2][1],
                      m1.m_[2][0] * m2.m_[0][2] + m1.m_[2][1] * m2.m_[1][2] + m1.m_[2][2] * m2.m_[2][2]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix3<T> operator*(T s, const Matrix3<T>& m)
{
    return Matrix3<T>(s * m.m_[0][0], s * m.m_[0][1], s * m.m_[0][2],
                      s * m.m_[1][0], s * m.m_[1][1], s * m.m_[1][2],
                      s * m.m_[2][0], s * m.m_[2][1], s * m.m_[2][2]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix3<T> operator*(const Matrix3<T>& m, T s)
{
    return Matrix3<T>(m.m_[0][0] * s, m.m_[0][1] * s, m.m_[0][2] * s,
                      m.m_[1][0] * s, m.m_[1][1] * s, m.m_[1][2] * s,
                      m.m_[2][0] * s, m.m_[2][1] * s, m.m_[2][2] * s);
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix3<T> operator/(const Matrix3<T>& m, T s)
{
    assert(s != (T)0.0); // Epsilon?
    
    T inv = (T)1.0 / s;
    
    return Matrix3<T>(m.m_[0][0] * inv, m.m_[0][1] * inv, m.m_[0][2] * inv,
                      m.m_[1][0] * inv, m.m_[1][1] * inv, m.m_[1][2] * inv,
                      m.m_[2][0] * inv, m.m_[2][1] * inv, m.m_[2][2] * inv);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector3<T> operator*(const Matrix3<T>& m, const Vector3<T>& v)
{
    return Vector3<T>(m.m_[0][0] * v[0] + m.m_[0][1] * v[1] + m.m_[0][2] * v[2],
                      m.m_[1][0] * v[0] + m.m_[1][1] * v[1] + m.m_[1][2] * v[2],
                      m.m_[2][0] * v[0] + m.m_[2][1] * v[1] + m.m_[2][2] * v[2]);
}
// --------------------------------------------------------------------------------------
template <class T> inline std::ostream& operator<<(std::ostream& os, const Matrix3<T>& m)
{
    for (int i = 0; i < 3; ++i)
    {
        os << "[ ";
        for (int j = 0; j < 3; ++j)
            os << m.m_[i][j] << " ";
        os << "]" << std::endl;
    }
    
    return os;
}
// --------------------------------------------------------------------------------------

} // namespace jyk

#endif

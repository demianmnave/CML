// --------------------------------------------------------------------------------------
// FILE: Matrix2.h
// AUTHOR: Jesse Krebs
// --------------------------------------------------------------------------------------

#ifndef JYKMATRIX2_H
#define JYKMATRIX2_H

#include "jykVector2.h"
#include <assert.h>

namespace jyk {

// Will probably replace 'T' with a more meaningful name throughout the library.
template <class T = float>
class Matrix2
{
public:

    Matrix2();
    Matrix2(T m00, T m01,
            T m10, T m11);
            
    T Get(unsigned int i, unsigned int j) const;

    void Set(T m00, T m01,
             T m10, T m11);

    void Identity();    
        
    void FromBasisVectors(const Vector2<T>& x, const Vector2<T>& y);
    
    void SetUniformScale(T s);
    void SetScale(const Vector2<T>& s);
    void SetScale(T sx, T sy);
    void SetScaleAlongAxis(const Vector2<T>& n, T s);
    
    void SetOrthographicProjectionX();
    void SetOrthographicProjectionY();
    void SetOrthographicProjection(const Vector2<T>& n);
    
    void SkewSymmetric(T s);
    
    T Trace() const;
    T Determinant() const;    
    
    Matrix2<T> GetTranspose() const;
    void TransposeSelf();
    
    Matrix2<T> GetInverse(T epsilon = Math<T>::EPSILON) const;
    bool InvertSelf(T epsilon = Math<T>::EPSILON);
    
    void TensorProduct(const Vector2<T>& v);
    void TensorProduct(const Vector2<T>& v1, const Vector2<T>& v2);
    
    void Random(T min, T max);
    
    Vector2<T> GetXAxis() const;
    Vector2<T> GetYAxis() const;

    Vector2<T> GetAxis(unsigned int i) const;
    void GetBasisVectors(Vector2<T>& x, Vector2<T>& y) const;
    
    void Orthogonalize(unsigned int u = 0, unsigned int n = 0, T k = (T)0.25);
    
    void FromAngle(T a);

    void ToAngle(T& a) const;

    // Needs more clear name.
    void Rotate(T a);

    static T Determinant(const Matrix2<T>& m);
    static Matrix2<T> Transpose(const Matrix2<T>& m);
    static Matrix2<T> Inverse(const Matrix2<T>& m);

    Matrix2<T>  operator-() const;
    Matrix2<T>& operator+=(const Matrix2<T>& m);
    Matrix2<T>& operator-=(const Matrix2<T>& m);
    Matrix2<T>& operator*=(const Matrix2<T>& m);
    Matrix2<T>& operator*=(T s);
    Matrix2<T>& operator/=(T s);

    friend Matrix2<T> operator+<>(const Matrix2<T>& m1, const Matrix2<T>& m2);
    friend Matrix2<T> operator-<>(const Matrix2<T>& m1, const Matrix2<T>& m2);
    friend Matrix2<T> operator*<>(const Matrix2<T>& m1, const Matrix2<T>& m2);
    friend Matrix2<T> operator*<>(const Matrix2<T>& m, T s);
    friend Matrix2<T> operator*<>(T s, const Matrix2<T>& m);
    friend Matrix2<T> operator/<>(const Matrix2<T>& m, T s);
    friend Vector2<T> operator*<>(const Vector2<T>& v, const Matrix2<T>& m);
    friend Vector2<T> operator*<>(const Matrix2<T>& m, const Vector2<T>& v);
    
    friend std::ostream& operator<< <>(std::ostream& os, const Matrix2<T>& m);

    static const Matrix2 ZERO;
    static const Matrix2 IDENTITY;

private:

    bool IndexIsValid(unsigned int i) const;

    T m_[2][2];
};
// --------------------------------------------------------------------------------------
template <class T> const Matrix2<T> Matrix2<T>::ZERO((T)0.0, (T)0.0,
                                                     (T)0.0, (T)0.0);
template <class T> const Matrix2<T> Matrix2<T>::IDENTITY((T)1.0, (T)0.0,
                                                         (T)0.0, (T)1.0);
// --------------------------------------------------------------------------------------
template <class T> inline Matrix2<T>::Matrix2() {}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix2<T>::Matrix2(T m00, T m01,
                                              T m10, T m11)
{
    m_[0][0] = m00;
    m_[0][1] = m01;
    m_[1][0] = m10;
    m_[1][1] = m11;
}
// --------------------------------------------------------------------------------------
template <class T> T Matrix2<T>::Get(unsigned int i, unsigned int j) const
{
    assert (i < 2 && j < 2);
    
    return m_[i][j];
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix2<T>::Set(T m00, T m01,
                                               T m10, T m11)
{
    m_[0][0] = m00;
    m_[0][1] = m01;
    m_[1][0] = m10;
    m_[1][1] = m11;
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix2<T>::Identity()
{
    Set((T)1.0, (T)0.0,
        (T)0.0, (T)1.0);
}
// --------------------------------------------------------------------------------------
// Currently uses column vectors, but will be configurable like everything else.
template <class T> inline void Matrix2<T>::FromBasisVectors(const Vector2<T>& x,
                                                            const Vector2<T>& y)
{
    Set(x[0], y[0],
        x[1], y[1]);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix2<T>::SetUniformScale(T s)
{
    Set(s,      (T)0.0,
        (T)0.0, s);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix2<T>::SetScale(const Vector2<T>& s)
{
    Set(s[0],   (T)0.0
        (T)0.0, s[1]);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix2<T>::SetScale(T sx, T sy)
{
    Set(sx,     (T)0.0,
        (T)0.0, sy);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix2<T>::SetScaleAlongAxis(const Vector2<T>& n, T s)
{
    T smo = s - (T)1.0;
    T smoxx = smo * n[0] * n[0];
    T smoxy = smo * n[0] * n[1];
    T smoyy = smo * n[1] * n[1];
    
    Set((T)1.0 + smoxx, smoxy,
        smoxy,          (T)1.0 + smoyy);    
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix2<T>::SetOrthographicProjectionX()
{
    Set((T)1.0, (T)0.0,
        (T)0.0, (T)0.0);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix2<T>::SetOrthographicProjectionY()
{
    Set((T)0.0, (T)0.0,
        (T)0.0, (T)1.0);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix2<T>::SetOrthographicProjection(const Vector2<T>& n)
{
    T xx = n[0] * n[0];
    T xy = n[0] * n[1];
    T yy = n[1] * n[1];
    
    Set((T)1.0 - xx, -xy,
        -xy,         (T)1.0 - yy);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix2<T>::SkewSymmetric(T s)
{
    Set((T)0.0, -s,
        s,      (T)0.0);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix2<T>::FromAngle(T a)
{    
    T s, c;
    Math<T>::SinCos(a, s, c);

    Set(c, -s, s, c);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix2<T>::ToAngle(T& a) const
{
    a = Math<T>::ATan2(m_[1][0], m_[0][0]);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Matrix2<T>::Trace() const
{
    return m_[0][0] + m_[1][1];
}
// --------------------------------------------------------------------------------------
template <class T> T Matrix2<T>::Determinant() const
{
    return m_[0][0] * m_[1][1] - m_[0][1] * m_[1][0];
}
// --------------------------------------------------------------------------------------
template <class T> Matrix2<T> Matrix2<T>::GetTranspose() const
{
    return Matrix2<T>(m_[0][0], m_[1][0],
                      m_[0][1], m_[1][1]);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix2<T>::TransposeSelf()
{
    T m01 = m_[0][1];
    m_[0][1] = m_[1][0];
    m_[1][0] = m01;
}
// --------------------------------------------------------------------------------------
template <class T> Matrix2<T> Matrix2<T>::GetInverse(T epsilon) const
{
    T det = Determinant();
    if (Math<T>::Fabs(det) < epsilon)
        return ZERO;

    T invdet = (T)1.0 / det;
    return Matrix2<T>( m_[1][1] * invdet, -m_[0][1] * invdet,
                      -m_[1][0] * invdet,  m_[0][0] * invdet);
}
// --------------------------------------------------------------------------------------
template <class T> bool Matrix2<T>::InvertSelf(T epsilon)
{
    T det = Determinant();
    if (Math<T>::Fabs(det) < epsilon)
        return false;
    
    T invdet = (T)1.0 / det;
    T m00 = m_[0][0];
    m_[0][0] = m_[1][1] * invdet;
    m_[0][1] *= -invdet;
    m_[1][0] *= -invdet;
    m_[1][1] = m00 * invdet;
    
    return true;
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix2<T>::TensorProduct(const Vector2<T>& v)
{
    T v01 = v[0] * v[1];
    
    Set(v[0] * v[0], v01,
        v01,         v[1] * v[1]);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix2<T>::TensorProduct(const Vector2<T>& v1, const Vector2<T>& v2)
{
    Set(v1[0] * v2[0], v1[0] * v2[1],
        v1[1] * v2[0], v1[1] * v2[1]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T> Matrix2<T>::GetXAxis() const
{
    return GetAxis(0);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T> Matrix2<T>::GetYAxis() const
{
    return GetAxis(1);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T> Matrix2<T>::GetAxis(unsigned int i) const
{
    assert(i < 2);
    return Vector2<T>(m_[0][i], m_[1][i]);
}    
// --------------------------------------------------------------------------------------
template <class T>
inline void Matrix2<T>::GetBasisVectors(Vector2<T>& x, Vector2<T>& y) const
{
    x.Set(m_[0][0], m_[1][0]);
    y.Set(m_[0][1], m_[1][1]);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix2<T>::Orthogonalize(unsigned int u, unsigned int n, T k)
{
    // This will have an iterative step like the 3x3 version.
    
    Vector2<T> x, y;
    GetBasisVectors(x, y);
    x.NormalizeSelf();
    y = x.Perp();
    FromBasisVectors(x, y);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix2<T>::Rotate(T a)
{
    T u[2], v[2];
    T s, c;
    Math<T>::SinCos(a, s, c);
    
    u[0] = c * m_[0][0] + s * m_[0][1];
    u[1] = c * m_[1][0] + s * m_[1][1];
    
    v[0] = c * m_[0][1] - s * m_[0][0];
    v[1] = c * m_[1][1] - s * m_[1][0];
    
    m_[0][0] = u[0];
    m_[1][0] = u[1];
    
    m_[0][1] = v[0];
    m_[1][1] = v[1];
}
// --------------------------------------------------------------------------------------
template <class T> inline bool Matrix2<T>::IndexIsValid(unsigned int i) const
{
    assert(i < 2);
    return i < 2;
}
// --------------------------------------------------------------------------------------
template <class T> T Matrix2<T>::Determinant(const Matrix2<T>& m)
{
    return m.Determinant();
}
// --------------------------------------------------------------------------------------
template <class T> Matrix2<T> Matrix2<T>::Transpose(const Matrix2<T>& m)
{
    return m.GetTranspose();
}
// --------------------------------------------------------------------------------------
template <class T> Matrix2<T> Matrix2<T>::Inverse(const Matrix2<T>& m)
{
    return m.GetInverse();
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix2<T> Matrix2<T>::operator-() const
{
    return Matrix2<T>(-m_[0][0], -m_[0][1],
                      -m_[1][0], -m_[1][1]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix2<T>& Matrix2<T>::operator+=(const Matrix2<T>& m)
{
    m_[0][0] += m.m_[0][0];
    m_[0][1] += m.m_[0][1];
    
    m_[1][0] += m.m_[1][0];
    m_[1][1] += m.m_[1][1];
    
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix2<T>& Matrix2<T>::operator-=(const Matrix2<T>& m)
{
    m_[0][0] -= m.m_[0][0];
    m_[0][1] -= m.m_[0][1];
    
    m_[1][0] -= m.m_[1][0];
    m_[1][1] -= m.m_[1][1];
    
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix2<T>& Matrix2<T>::operator*=(const Matrix2<T>& m)
{
    T r0, r1;
    
    r0 = m_[0][0];
    r1 = m_[0][1];
    
    m_[0][0] = r0 * m.m_[0][0] + r1 * m.m_[1][0];
    m_[0][1] = r0 * m.m_[0][1] + r1 * m.m_[1][1];
    
    r0 = m_[1][0];
    r1 = m_[1][1];
    
    m_[1][0] = r0 * m.m_[0][0] + r1 * m.m_[1][0];
    m_[1][1] = r0 * m.m_[0][1] + r1 * m.m_[1][1];

    return *this;
    
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix2<T>& Matrix2<T>::operator*=(T s)
{
    m_[0][0] *= s;
    m_[0][1] *= s;
    
    m_[1][0] *= s;
    m_[1][1] *= s;
    
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix2<T>& Matrix2<T>::operator/=(T s)
{
    assert(s != (T)0.0);
    
    T invs = (T)1.0 / s;

    m_[0][0] *= invs;
    m_[0][1] *= invs;
    
    m_[1][0] *= invs;
    m_[1][1] *= invs;
    
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix2<T> operator+(const Matrix2<T>& m1, const Matrix2<T>& m2)
{
    return Matrix2<T>(m1.m_[0][0] + m2.m_[0][0], m1.m_[0][1] + m2.m_[0][1],
                      m1.m_[1][0] + m2.m_[1][0], m1.m_[1][1] + m2.m_[1][1]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix2<T> operator-(const Matrix2<T>& m1, const Matrix2<T>& m2)
{
    return Matrix2<T>(m1.m_[0][0] - m2.m_[0][0], m1.m_[0][1] - m2.m_[0][1],
                      m1.m_[1][0] - m2.m_[1][0], m1.m_[1][1] - m2.m_[1][1]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix2<T> operator*(const Matrix2<T>& m1, const Matrix2<T>& m2)
{
    return Matrix2<T>(m1.m_[0][0] * m2.m_[0][0] + m1.m_[0][1] * m2.m_[1][0],
                      m1.m_[0][0] * m2.m_[0][1] + m1.m_[0][1] * m2.m_[1][1],
                      m1.m_[1][0] * m2.m_[0][0] + m1.m_[1][1] * m2.m_[1][0],
                      m1.m_[1][0] * m2.m_[0][1] + m1.m_[1][1] * m2.m_[1][1]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix2<T> operator*(T s, const Matrix2<T>& m)
{
    return Matrix2<T>(s * m.m_[0][0], s * m.m_[0][1],
                      s * m.m_[1][0], s * m.m_[1][1]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix2<T> operator*(const Matrix2<T>& m, T s)
{
    return Matrix2<T>(m.m_[0][0] * s, m.m_[0][1] * s,
                      m.m_[1][0] * s, m.m_[1][1] * s);
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix2<T> operator/(const Matrix2<T>& m, T s)
{
    assert(s != (T)0.0);
    
    T invs = (T)1.0 / s;
    
    return Matrix2<T>(m.m_[0][0] * invs, m.m_[0][1] * invs,
                      m.m_[1][0] * invs, m.m_[1][1] * invs);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T> operator*(const Vector2<T>& v, const Matrix2<T>& m)
{
    return Vector2<T>(v[0] * m.m_[0][0] + v[1] * m.m_[1][0],
                      v[0] * m.m_[0][1] + v[1] * m.m_[1][1]);
}
// --------------------------------------------------------------------------------------
template <class T> inline Vector2<T> operator*(const Matrix2<T>& m, const Vector2<T>& v)
{
    return Vector2<T>(m.m_[0][0] * v[0] + m.m_[0][1] * v[1],
                      m.m_[1][0] * v[0] + m.m_[1][1] * v[1]);
}
// --------------------------------------------------------------------------------------
template <class T> inline std::ostream& operator<<(std::ostream& os, const Matrix2<T>& m)
{
    for (int i = 0; i < 2; ++i)
    {
        os << "[ ";
        for (int j = 0; j < 2; ++j)
            os << m.m_[i][j] << " ";
        os << "]" << std::endl;
    }
    
    return os;
}
// --------------------------------------------------------------------------------------

} // namespace jyk

#endif

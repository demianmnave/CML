// --------------------------------------------------------------------------------------
// FILE: mlMatrix4.h
// AUTHOR: Jesse Krebs
// --------------------------------------------------------------------------------------

#ifndef MLMATRIX4_H
#define MLMATRIX4_H

/* --------------------------------------------------------------------------------------

I started this class to do some testing with variable conventions. It's done with
placeholder code - some member variables and switch statements - which will be replaced
by the template architecture.

Some of the functions here are copied and pasted from Matrix3 or Matrix4, and don't have
the variable convention placeholder code.

-------------------------------------------------------------------------------------- */ 

#include "jykQuaternion.h"
#include <ostream>

namespace cml {

template <class T = float>
class Matrix4
{
public:

    enum {DEGREES = 0,
          RADIANS = 1,
          ROW = 0,
          COLUMN = 1,
          LEFT = 0,
          RIGHT = 1};

    Matrix4();
    Matrix4(int angleUnit,
            int vectorConvention,
            int coordSysHandedness,
            int rotationHandedness,
            int storage);
    Matrix4(T m00, T m01, T m02, T m03,
            T m10, T m11, T m12, T m13,
            T m20, T m21, T m22, T m23,
            T m30, T m31, T m32, T m33,
            int angleUnit,
            int vectorConvention,
            int coordSysHandedness,
            int rotationHandedness,
            int storage);
    
    // I assume we'll do something else for external access, such as overload ().      
    T Get(unsigned int i, unsigned int j) const;
           
    void Set(T m00, T m01, T m02, T m03,
             T m10, T m11, T m12, T m13,
             T m20, T m21, T m22, T m23,
             T m30, T m31, T m32, T m33);
    
    Vector3<T> GetTranslation() const;
    Vector3<T> GetInverseTranslation() const;
    
    // Miscellaneous functions in no particular order.
    void LoadIdentity();
    void LoadBasisVectors(const Vector3<T>& x, const Vector3<T>& y, const Vector3<T>& z);
    void LoadTransposedBasisVectors(const Vector3<T>& x, const Vector3<T>& y, const Vector3<T>& z);  
    void LoadTranslation(const Vector3<T>& t);
    void LoadTranslation(T x, T y, T z);    
    void LoadScale(const Vector3<T>& s);
    void LoadScale(T sx, T sy, T sz);
    void LoadAxisAngle(const Vector3<T>& axis, T angle);
    void LoadAxisAngle(T x, T y, T z, T angle);
    void LoadQuaternion(const Quaternion<T>& q);
    void ToQuaternion(Quaternion<T>& q) const;
    void RotateAboutLocalAxis(unsigned int i, T angle);
    void MakeOrthonormalBasis(const Vector3<T>& vec, unsigned int u, bool normalize);  
    void Orthogonalize3x3(unsigned int u, unsigned int n, T k);

    // These functions build a transformation matrix from a given sequence of
    // scaling, rotation, and translation. Some of the sequences aren't of much practical
    // use, but the functions were fairly straightforward to write, and I like to be thorough.
    
    void BuildTransformSR(const Vector3<T>& scale, const Vector3<T>& axis, T angle);
    void BuildTransformRS(const Vector3<T>& axis, T angle, const Vector3<T>& scale);
    void BuildTransformST(const Vector3<T>& scale, const Vector3<T>& translation);
    void BuildTransformTS(const Vector3<T>& translation, const Vector3<T>& scale);
    void BuildTransformRT(const Vector3<T>& axis, T angle, const Vector3<T>& translation);
    void BuildTransformTR(const Vector3<T>& translation, const Vector3<T>& axis, T angle);
    
    void BuildTransformSRT(const Vector3<T>& scale, const Vector3<T>& axis, T angle, const Vector3<T>& translation);
    void BuildTransformSTR(const Vector3<T>& scale, const Vector3<T>& translation, const Vector3<T>& axis, T angle);
    void BuildTransformRST(const Vector3<T>& axis, T angle, const Vector3<T>& scale, const Vector3<T>& translation);
    void BuildTransformRTS(const Vector3<T>& axis, T angle, const Vector3<T>& translation, const Vector3<T>& scale);
    void BuildTransformTSR(const Vector3<T>& translation, const Vector3<T>& scale, const Vector3<T>& axis, T angle);
    void BuildTransformTRS(const Vector3<T>& translation, const Vector3<T>& axis, T angle, const Vector3<T>& scale);
    
    // These are the corresponding inverse functions (not completed). The argument for their
    // inclusion is that general 4x4 inversion is expensive and usually unnecessary. For combinations
    // of scaling, rotation, and translation, there is usually a shortcut.
    
    void InvertSelfSOnly();
    void InvertSelfROnly();
    void InvertSelfTOnly();

    void InvertSelfSROnly();
    void InvertSelfRSOnly();
    void InvertSelfRTOnly();
    void InvertSelfTROnly();
    void InvertSelfSTOnly();
    void InvertSelfTSOnly();
    
    void InvertSelfSRTOnly();
    
    // This isn't part of the configurable architecture, but will be a very important feature of
    // the library. These functions allow for creation from or extraction of Euler angle triples
    // in any order, including repeated (XYX) and sequences of two rather than three (XY).
    
    // 'i', 'odd', and 'repeat' will be replaced by encoded named constants.
    void LoadEulerAngles(T a0, T a1, T a2, int i, bool odd, bool repeat);
    void LoadEulerAngles(T a0, T a1, int i, bool odd);  
    void ToEulerAngles(T& a0, T& a1, T& a2, int i, bool odd, bool repeat, T epsilon = Math<T>::EPSILON);
    void ToEulerAngles(T& a0, T& a1, int i, bool odd);
    
    void LookAt(const Vector3<T>& pos, const Vector3<T>& target, const Vector3<T>& up);

    T Determinant() const;
    
    Matrix4<T> GetTranspose() const;
    void TransposeSelf();

    static T Determinant(const Matrix4<T>& m);
    static Matrix4<T> Transpose(const Matrix4<T>& m);
    static Matrix4<T> Inverse(const Matrix4<T>& m);
    
    Matrix4<T>  operator-() const;
    Matrix4<T>& operator+=(const Matrix4<T>& m);
    Matrix4<T>& operator-=(const Matrix4<T>& m);
    Matrix4<T>& operator*=(const Matrix4<T>& m);
    Matrix4<T>& operator*=(T s);
    Matrix4<T>& operator/=(T s);

    friend Matrix4<T> operator+<>(const Matrix4<T>& m0, const Matrix4<T>& m1);
    friend Matrix4<T> operator-<>(const Matrix4<T>& m0, const Matrix4<T>& m1);
    friend Matrix4<T> operator*<>(const Matrix4<T>& m0, const Matrix4<T>& m1);
    friend Matrix4<T> operator*<>(const Matrix4<T>& m, T s);
    friend Matrix4<T> operator*<>(T s, const Matrix4<T>& m);
    friend Matrix4<T> operator/<>(const Matrix4<T>& m, T s);

    static const Matrix4 ZERO;
    static const Matrix4 IDENTITY;

private:

    // These are just my placeholder functions for row- or column-major access.

    T& m_(unsigned int i, unsigned int j)
    {
        assert(i < 4);
        assert(j < 4);
        
        switch (m_storage)
        {
            case ROW:
                return m_data[i * 4 + j];
            case COLUMN:
                return m_data[i + j * 4];
            default:
                return m_data[i + j * 4]; // Silence 'return value expected' error
        }
    }
    
    const T& m_(unsigned int i, unsigned int j) const
    {
        assert(i < 4);
        assert(j < 4);
        
        switch (m_storage)
        {
            case ROW:
                return m_data[i * 4 + j];
            case COLUMN:
                return m_data[i + j * 4];
            default:
                return m_data[i + j * 4]; // Silence 'return value expected' error
        }
    }
    
    T ConvertAngle(T angle) const
    {
        return (m_angleUnit == RADIANS) ? angle : Math<T>::DegToRad(angle);
    }
    
    // These are some support functions, which I just inlined here because I was lazy.
    // Most if not all will become obsolete after the architecture change.
    
    void Set3x3(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22)
    {
        m_(0, 0) = m00;
        m_(0, 1) = m01;
        m_(0, 2) = m02;
        m_(1, 0) = m10;
        m_(1, 1) = m11;
        m_(1, 2) = m12;
        m_(2, 0) = m20;
        m_(2, 1) = m21;
        m_(2, 2) = m22;
    }

    void FillHomogenousRowAndColumn()
    {
        m_(3, 0) = (T)0.0;
        m_(3, 1) = (T)0.0;
        m_(3, 2) = (T)0.0;
        m_(3, 3) = (T)1.0;
        m_(2, 3) = (T)0.0;
        m_(1, 3) = (T)0.0;
        m_(0, 3) = (T)0.0;
    }
    
    void FillHomogenousRowOrColumn()
    {
        switch (m_vectorConvention)
        {
            case ROW:
                m_(0, 3) = (T)0.0;
                m_(1, 3) = (T)0.0;
                m_(2, 3) = (T)0.0;
                m_(3, 3) = (T)1.0;
                break;
            case COLUMN:
                m_(3, 0) = (T)0.0;
                m_(3, 1) = (T)0.0;
                m_(3, 2) = (T)0.0;
                m_(3, 3) = (T)1.0;
                break;
        }
    }

    void ScaleBasisVectors(T sx, T sy, T sz)
    {
        switch (m_vectorConvention)
        {
        case ROW:
            m_(0, 0) *= sx;
            m_(0, 1) *= sx;
            m_(0, 2) *= sx;
            
            m_(1, 0) *= sy;
            m_(1, 1) *= sy;
            m_(1, 2) *= sy;
            
            m_(2, 0) *= sz;
            m_(2, 1) *= sz;
            m_(2, 2) *= sz;
            break;
        case COLUMN:
            m_(0, 0) *= sx;
            m_(1, 0) *= sx;
            m_(2, 0) *= sx;
            
            m_(0, 1) *= sy;
            m_(1, 1) *= sy;
            m_(2, 1) *= sy;
            
            m_(0, 2) *= sz;
            m_(1, 2) *= sz;
            m_(2, 2) *= sz;
            break;
        }
    }
    
    void ScaleBasisVectors(const Vector3<T>& scale)
    {
        ScaleBasisVectors(scale[0], scale[1], scale[2]);
    }
    
    void ScaleTransposedBasisVectors(T sx, T sy, T sz)
    {
        switch (m_vectorConvention)
        {
        case ROW:
            m_(0, 0) *= sx;
            m_(1, 0) *= sx;
            m_(2, 0) *= sx;
            
            m_(0, 1) *= sy;
            m_(1, 1) *= sy;
            m_(2, 1) *= sy;
            
            m_(0, 2) *= sz;
            m_(1, 2) *= sz;
            m_(2, 2) *= sz;
            break;
        case COLUMN:
            m_(0, 0) *= sx;
            m_(0, 1) *= sx;
            m_(0, 2) *= sx;
            
            m_(1, 0) *= sy;
            m_(1, 1) *= sy;
            m_(1, 2) *= sy;
            
            m_(2, 0) *= sz;
            m_(2, 1) *= sz;
            m_(2, 2) *= sz;
            break;
        }
    }
    
    void ScaleTransposedBasisVectors(const Vector3<T>& scale)
    {
        ScaleTransposedBasisVectors(scale[0], scale[1], scale[2]);
    }

    T   m_data[16];
    
    // Placeholder variables
    
    int m_angleUnit;
    int m_vectorConvention;
    int m_coordSysHandedness;
    int m_rotationHandedness;
    int m_storage;
    
    
};
// --------------------------------------------------------------------------------------
template <class T> Matrix4<T>::Matrix4()
{
}
// --------------------------------------------------------------------------------------
template <class T> Matrix4<T>::Matrix4(int angleUnit,
                                       int vectorConvention,
                                       int coordSysHandedness,
                                       int rotationHandedness,
                                       int storage)
{
    m_angleUnit = angleUnit;
    m_vectorConvention = vectorConvention;
    m_coordSysHandedness = coordSysHandedness;
    m_rotationHandedness = rotationHandedness;
    m_storage = storage;
}
// --------------------------------------------------------------------------------------
template <class T> Matrix4<T>::Matrix4(T m00, T m01, T m02, T m03,
                                       T m10, T m11, T m12, T m13,
                                       T m20, T m21, T m22, T m23,
                                       T m30, T m31, T m32, T m33,
                                       int angleUnit,
                                       int vectorConvention,
                                       int coordSysHandedness,
                                       int rotationHandedness,
                                       int storage)
{
    m_angleUnit = angleUnit;
    m_vectorConvention = vectorConvention;
    m_coordSysHandedness = coordSysHandedness;
    m_rotationHandedness = rotationHandedness;
    m_storage = storage;
    
    m_(0, 0) = m00;
    m_(0, 1) = m01;
    m_(0, 2) = m02;
    m_(0, 3) = m03;
    
    m_(1, 0) = m10;
    m_(1, 1) = m11;
    m_(1, 2) = m12;
    m_(1, 3) = m13;
    
    m_(2, 0) = m20;
    m_(2, 1) = m21;
    m_(2, 2) = m22;
    m_(2, 3) = m23;
    
    m_(3, 0) = m30;
    m_(3, 1) = m31;
    m_(3, 2) = m32;
    m_(3, 3) = m33;
}
// --------------------------------------------------------------------------------------
template <class T> T Matrix4<T>::Get(unsigned int i, unsigned int j) const
{
    assert (i < 4 && j < 4);
    return m_(i, j);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix4<T>::Set(T m00, T m01, T m02, T m03,
                                               T m10, T m11, T m12, T m13,
                                               T m20, T m21, T m22, T m23,
                                               T m30, T m31, T m32, T m33)
{
    m_(0, 0) = m00;
    m_(0, 1) = m01;
    m_(0, 2) = m02;
    m_(0, 3) = m03;
    
    m_(1, 0) = m10;
    m_(1, 1) = m11;
    m_(1, 2) = m12;
    m_(1, 3) = m13;
    
    m_(2, 0) = m20;
    m_(2, 1) = m21;
    m_(2, 2) = m22;
    m_(2, 3) = m23;
    
    m_(3, 0) = m30;
    m_(3, 1) = m31;
    m_(3, 2) = m32;
    m_(3, 3) = m33;
}
// --------------------------------------------------------------------------------------
template <class T> Vector3<T> Matrix4<T>::GetTranslation() const
{
    switch (m_vectorConvention)
    {
        case ROW:
            return Vector3<T>(m_(3, 0), m_(3, 1), m_(3, 2));
        case COLUMN:
            return Vector3<T>(m_(0, 3), m_(1, 3), m_(2, 3));
    }
}
// --------------------------------------------------------------------------------------
// For extracting translation from a view matrix. May need to specify that it only works
// for a TR matrix.
template <class T> Vector3<T> Matrix4<T>::GetInverseTranslation() const
{
    switch (m_vectorConvention)
    {
        case ROW:
            return Vector3<T>(-m_(3, 0) * m_(0, 0) - m_(3, 1) * m_(0, 1) - m_(3, 2) * m_(0, 2),
                              -m_(3, 0) * m_(1, 0) - m_(3, 1) * m_(1, 1) - m_(3, 2) * m_(1, 2),
                              -m_(3, 0) * m_(2, 0) - m_(3, 1) * m_(2, 1) - m_(3, 2) * m_(2, 2));
            break;
        case COLUMN:
            return Vector3<T>(-m_(0, 0) * m_(0, 3) - m_(1, 0) * m_(1, 3) - m_(2, 0) * m_(2, 3),
                              -m_(0, 1) * m_(0, 3) - m_(1, 1) * m_(1, 3) - m_(2, 1) * m_(2, 3),
                              -m_(0, 2) * m_(0, 3) - m_(1, 2) * m_(1, 3) - m_(2, 2) * m_(2, 3));
    }
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix4<T>::LoadIdentity()
{
    Set((T)1.0, (T)0.0, (T)0.0, (T)0.0,
        (T)0.0, (T)1.0, (T)0.0, (T)0.0,
        (T)0.0, (T)0.0, (T)1.0, (T)0.0,
        (T)0.0, (T)0.0, (T)0.0, (T)1.0);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::LoadBasisVectors(const Vector3<T>& x, const Vector3<T>& y, const Vector3<T>& z)
{
    switch (m_vectorConvention)
    {
        case ROW:
            Set3x3(x[0], x[1], x[2],
                   y[0], y[1], y[2],
                   z[0], z[1], z[2]);
            break;
        case COLUMN:
            Set3x3(x[0], y[0], z[0],
                   x[1], y[1], z[1],
                   x[2], y[2], z[2]);
            break;
    }
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::LoadTransposedBasisVectors(const Vector3<T>& x, const Vector3<T>& y, const Vector3<T>& z)
{
    switch (m_vectorConvention)
    {
        case ROW:
            Set3x3(x[0], y[0], z[0],
                   x[1], y[1], z[1],
                   x[2], y[2], z[2]);
            break;
        case COLUMN:
            Set3x3(x[0], x[1], x[2],
                   y[0], y[1], y[2],
                   z[0], z[1], z[2]);
            break;
    }
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix4<T>::LoadTranslation(const Vector3<T>& t)
{
    LoadTranslation(t[0], t[1], t[2]);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::LoadTranslation(T x, T y, T z)
{
    switch (m_vectorConvention)
    {
        case ROW:
            m_(3, 0) = x;
            m_(3, 1) = y;
            m_(3, 2) = z;
            break;
        case COLUMN:
            m_(0, 3) = x;
            m_(1, 3) = y;
            m_(2, 3) = z;
            break;
    }
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix4<T>::LoadScale(const Vector3<T>& s)
{
    LoadScale(s[0], s[1], s[2]);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::LoadScale(T sx, T sy, T sz)
{
    Set3x3(sx,     (T)0.0, (T)0.0,
           (T)0.0, sy,     (T)0.0,
           (T)0.0, (T)0.0, sz);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix4<T>::LoadAxisAngle(const Vector3<T>& axis, T angle)
{
    LoadAxisAngle(axis[0], axis[1], axis[2], angle);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::LoadAxisAngle(T x, T y, T z, T angle)
{
    T s, c;
    Math<T>::SinCos(ConvertAngle(angle), s, c);
    T omc = (T)1.0 - c;
    
    T xomc = x * omc;
    T yomc = y * omc;
    T zomc = z * omc;
    
    T xxomc = x * xomc;
    T xyomc = x * yomc;
    T xzomc = x * zomc;
    T yyomc = y * yomc;
    T yzomc = y * zomc;
    T zzomc = z * zomc;
    
    T xs = x * s;
    T ys = y * s;
    T zs = z * s;
    
    bool matched = (m_coordSysHandedness == m_rotationHandedness);
    if ((m_vectorConvention == ROW && matched) || (m_vectorConvention == COLUMN && !matched))
    {
        Set3x3(xxomc + c,  xyomc + zs, xzomc - ys,
               xyomc - zs, yyomc + c,  yzomc + xs,
               xzomc + ys, yzomc - xs, zzomc + c);
    }
    else if ((m_vectorConvention == COLUMN && matched) || (m_vectorConvention == ROW && !matched))
    {
        Set3x3(xxomc + c,  xyomc - zs, xzomc + ys,
               xyomc + zs, yyomc + c,  yzomc - xs,
               xzomc - ys, yzomc + xs, zzomc + c);
    }
    else
        assert(false);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::LoadQuaternion(const Quaternion<T>& q)
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

    bool matched = (m_coordSysHandedness == m_rotationHandedness);
    if ((m_vectorConvention == ROW && matched) || (m_vectorConvention == COLUMN && !matched))
    {
        Set3x3((T)1.0 - yy2 - zz2, xy2 + zw2,          xz2 - yw2,
               xy2 - zw2,          (T)1.0 - xx2 - zz2, yz2 + xw2,
               xz2 + yw2,          yz2 - xw2,          (T)1.0 - xx2 - yy2);
    }
    else if ((m_vectorConvention == COLUMN && matched) || (m_vectorConvention == ROW && !matched))
    {
        Set3x3((T)1.0 - yy2 - zz2,  xy2 - zw2,            xz2 + yw2,
               xy2 + zw2,            (T)1.0 - xx2 - zz2, yz2 - xw2,
               xz2 - yw2,            yz2 + xw2,            (T)1.0 - xx2 - yy2);
    }
    else
        assert(false);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::ToQuaternion(Quaternion<T>& q) const
{
    T result[4];
    T t = Trace();
    if (t >= (T)0.0)
    {
        result[3] = Math<T>::Sqrt(t + (T)1.0) * (T)0.5;
        T s = (T)0.25 / result[3];
        result[0] = (m_(2, 1) - m_(1, 2)) * s;
        result[1] = (m_(0, 2) - m_(2, 0)) * s;
        result[2] = (m_(1, 0) - m_(0, 1)) * s;
    }
    else
    {
        unsigned int i = LargestDiagonalElementIndex();
        unsigned int j, k;
        Math<>::GetCyclicPermutation(i, j, k);
        
        result[i] = Math<T>::Sqrt(m_[i][i] - m_[j][j] - m_[k][k] + (T)1.0) * (T)0.5;
        T s = (T)0.25 / result[i];
        result[j] = (m_[i][j] + m_[j][i]) * s;
        result[k] = (m_[i][k] + m_[k][i]) * s;
        result[3] = (m_[k][j] - m_[j][k]) * s;
    }
    q.Set(result);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::RotateAboutLocalAxis(unsigned int i, T angle)
{
    assert(i < 3);
    
    unsigned int j, k;
    Math<>::GetCyclicPermutation(i, j, k);
    
    T u[3], v[3];
    T s, c;
    Math<T>::SinCos(ConvertAngle(angle), s, c);
    
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
template <class T> void Matrix4<T>::MakeOrthonormalBasis(const Vector3<T>& vec, unsigned int u, bool normalize)
{
    if (!IndexIsValid(u))
        return;

    unsigned int v, w;
    Math<>::GetCyclicPermutation(u, v, w);
        
    unsigned int i = vec.GetSmallestAbsoluteComponent();
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
template <class T> void Matrix4<T>::Orthogonalize3x3(unsigned int u, unsigned int n, T k)
{
    assert(k > 0.0f);
    
    if (!IndexIsValid(u))
        return;

    for (unsigned int c = 0; c < n; ++c)
    {        
        T dot00 = m_(0, 0) * m_(0, 0) + m_(1, 0) * m_(1, 0) + m_(2, 0) * m_(2, 0);
        T dot01 = m_(0, 0) * m_(0, 1) + m_(1, 0) * m_(1, 1) + m_(2, 0) * m_(2, 1);
        T dot02 = m_(0, 0) * m_(0, 2) + m_(1, 0) * m_(1, 2) + m_(2, 0) * m_(2, 2);
        T dot11 = m_(0, 1) * m_(0, 1) + m_(1, 1) * m_(1, 1) + m_(2, 1) * m_(2, 1);
        T dot12 = m_(0, 1) * m_(0, 2) + m_(1, 1) * m_(1, 2) + m_(2, 1) * m_(2, 2);
        T dot22 = m_(0, 2) * m_(0, 2) + m_(1, 2) * m_(1, 2) + m_(2, 2) * m_(2, 2);
        
        T s01 = k * dot01 / dot11;
        T s02 = k * dot02 / dot22;
        T s10 = k * dot01 / dot00;
        T s12 = k * dot12 / dot22;
        T s20 = k * dot02 / dot00;
        T s21 = k * dot12 / dot11;
        
        T m[3][3];
        
        m[0][0] = m_(0, 0) - s01 * m_(0, 1) - s02 * m_(0, 2);
        m[1][0] = m_(1, 0) - s01 * m_(1, 1) - s02 * m_(1, 2);
        m[2][0] = m_(2, 0) - s01 * m_(2, 1) - s02 * m_(2, 2);
        
        m[0][1] = m_(0, 1) - s10 * m_(0, 0) - s12 * m_(0, 2);
        m[1][1] = m_(1, 1) - s10 * m_(1, 0) - s12 * m_(1, 2);
        m[2][1] = m_(2, 1) - s10 * m_(2, 0) - s12 * m_(2, 2);
        
        m[0][2] = m_(0, 2) - s20 * m_(0, 0) - s21 * m_(0, 1);
        m[1][2] = m_(1, 2) - s20 * m_(1, 0) - s21 * m_(1, 1);
        m[2][2] = m_(2, 2) - s20 * m_(2, 0) - s21 * m_(2, 1);

        m_(0, 0) = m[0][0];
        m_(0, 1) = m[0][1];
        m_(0, 2) = m[0][2];
        m_(1, 0) = m[1][0];
        m_(1, 1) = m[1][1];
        m_(1, 2) = m[1][2];
        m_(2, 0) = m[2][0];
        m_(2, 1) = m[2][1];
        m_(2, 2) = m[2][2];
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
template <class T> void Matrix4<T>::BuildTransformSR(const Vector3<T>& scale, const Vector3<T>& axis, T angle)
{
    LoadAxisAngle(axis, angle);
    ScaleBasisVectors(scale);
    FillHomogenousRowAndColumn();
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::BuildTransformRS(const Vector3<T>& axis, T angle,const Vector3<T>& scale)
{
    LoadAxisAngle(axis, angle);
    ScaleTransposedBasisVectors(scale);
    FillHomogenousRowAndColumn();
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::BuildTransformST(const Vector3<T>& scale, const Vector3<T>& translation)
{
    LoadScale(scale);
    LoadTranslation(translation);
    FillHomogenousRowOrColumn();
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::BuildTransformTS(const Vector3<T>& translation, const Vector3<T>& scale)
{
    LoadScale(scale);
    LoadTranslation(translation[0] * m_(0, 0), translation[1] * m_(1, 1), translation[2] * m_(2, 2));
    FillHomogenousRowOrColumn();
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::BuildTransformRT(const Vector3<T>& axis, T angle, const Vector3<T>& translation)
{
    LoadAxisAngle(axis, angle);
    LoadTranslation(translation);
    FillHomogenousRowOrColumn();
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::BuildTransformTR(const Vector3<T>& translation, const Vector3<T>& axis, T angle)
{
    LoadAxisAngle(axis, angle);
    switch (m_vectorConvention)
    {
        case ROW:
            m_(3, 0) = translation[0] * m_(0, 0) + translation[1] * m_(1, 0) + translation[2] * m_(2, 0);
            m_(3, 1) = translation[0] * m_(0, 1) + translation[1] * m_(1, 1) + translation[2] * m_(2, 1);
            m_(3, 2) = translation[0] * m_(0, 2) + translation[1] * m_(1, 2) + translation[2] * m_(2, 2);
            break;
        case COLUMN:
            m_(0, 3) = m_(0, 0) * translation[0] + m_(0, 1) * translation[1] + m_(0, 2) * translation[2];
            m_(1, 3) = m_(1, 0) * translation[0] + m_(1, 1) * translation[1] + m_(1, 2) * translation[2];
            m_(2, 3) = m_(2, 0) * translation[0] + m_(2, 1) * translation[1] + m_(2, 2) * translation[2];
            break;
    }
    FillHomogenousRowOrColumn();
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::BuildTransformSRT(const Vector3<T>& scale,
                                                      const Vector3<T>& axis,
                                                      T angle,
                                                      const Vector3<T>& translation)
{
    BuildTransformSR(scale, axis, angle);
    LoadTranslation(translation);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::BuildTransformSTR(const Vector3<T>& scale,
                                                      const Vector3<T>& translation,
                                                      const Vector3<T>& axis,
                                                      T angle)
{
    BuildTransformTR(translation, axis, angle);
    ScaleBasisVectors(scale);

}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::BuildTransformRST(const Vector3<T>& axis,
                                                      T angle,
                                                      const Vector3<T>& scale,
                                                      const Vector3<T>& translation)
{
    BuildTransformRS(axis, angle, scale);
    LoadTranslation(translation);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::BuildTransformRTS(const Vector3<T>& axis,
                                                      T angle,
                                                      const Vector3<T>& translation,
                                                      const Vector3<T>& scale)
{
    BuildTransformRS(axis, angle, scale);
    LoadTranslation(translation[0] * scale[0], translation[1] * scale[1], translation[2] * scale[2]);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::BuildTransformTSR(const Vector3<T>& translation,
                                                      const Vector3<T>& scale,
                                                      const Vector3<T>& axis,
                                                      T angle)
{
    BuildTransformSR(scale, axis, angle);
    switch (m_vectorConvention)
    {
        case ROW:
            m_(3, 0) = translation[0] * m_(0, 0) + translation[1] * m_(1, 0) + translation[2] * m_(2, 0);
            m_(3, 1) = translation[0] * m_(0, 1) + translation[1] * m_(1, 1) + translation[2] * m_(2, 1);
            m_(3, 2) = translation[0] * m_(0, 2) + translation[1] * m_(1, 2) + translation[2] * m_(2, 2);
            break;
        case COLUMN:
            m_(0, 3) = m_(0, 0) * translation[0] + m_(0, 1) * translation[1] + m_(0, 2) * translation[2];
            m_(1, 3) = m_(1, 0) * translation[0] + m_(1, 1) * translation[1] + m_(1, 2) * translation[2];
            m_(2, 3) = m_(2, 0) * translation[0] + m_(2, 1) * translation[1] + m_(2, 2) * translation[2];
            break;
    }
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::BuildTransformTRS(const Vector3<T>& translation,
                                                      const Vector3<T>& axis,
                                                      T angle,
                                                      const Vector3<T>& scale)
{
    BuildTransformRS(axis, angle, scale);
    switch (m_vectorConvention)
    {
        case ROW:
            m_(3, 0) = translation[0] * m_(0, 0) + translation[1] * m_(1, 0) + translation[2] * m_(2, 0);
            m_(3, 1) = translation[0] * m_(0, 1) + translation[1] * m_(1, 1) + translation[2] * m_(2, 1);
            m_(3, 2) = translation[0] * m_(0, 2) + translation[1] * m_(1, 2) + translation[2] * m_(2, 2);
            break;
        case COLUMN:
            m_(0, 3) = m_(0, 0) * translation[0] + m_(0, 1) * translation[1] + m_(0, 2) * translation[2];
            m_(1, 3) = m_(1, 0) * translation[0] + m_(1, 1) * translation[1] + m_(1, 2) * translation[2];
            m_(2, 3) = m_(2, 0) * translation[0] + m_(2, 1) * translation[1] + m_(2, 2) * translation[2];
            break;
    }
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::InvertSelfSOnly()
{
    m_(0, 0) = (T)1.0 / m_(0, 0);
    m_(1, 1) = (T)1.0 / m_(1, 1);
    m_(2, 2) = (T)1.0 / m_(2, 2);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::InvertSelfROnly()
{
    T m01 = m_(0, 1);
    T m02 = m_(0, 2);
    T m12 = m_(1, 2);
    
    m_(0, 1) = m_(1, 0);
    m_(0, 2) = m_(2, 0);
    m_(1, 2) = m_(2, 1);
    
    m_(1, 0) = m01;
    m_(2, 0) = m02;
    m_(2, 1) = m12;
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::InvertSelfTOnly()
{
    switch (m_vectorConvention)
    {
        case ROW:
            m_(3, 0) = -m_(3, 0);
            m_(3, 1) = -m_(3, 1);
            m_(3, 2) = -m_(3, 2);
            break;
        case COLUMN:
            m_(0, 3) = -m_(0, 3);
            m_(1, 3) = -m_(1, 3);
            m_(2, 3) = -m_(2, 3);
            break;
    }
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::InvertSelfSROnly()
{
    T invsx2, invsy2, invsz2;
    switch (m_vectorConvention)
    {
        case ROW:
        {
            invsx2 = (T)1.0 / (m_(0, 0) * m_(0, 0) + m_(0, 1) * m_(0, 1) + m_(0, 2) * m_(0, 2));
            invsy2 = (T)1.0 / (m_(1, 0) * m_(1, 0) + m_(1, 1) * m_(1, 1) + m_(1, 2) * m_(1, 2));
            invsz2 = (T)1.0 / (m_(2, 0) * m_(2, 0) + m_(2, 1) * m_(2, 1) + m_(2, 2) * m_(2, 2));
            break;
        }
        case COLUMN:
        {
            invsx2 = (T)1.0 / (m_(0, 0) * m_(0, 0) + m_(1, 0) * m_(1, 0) + m_(2, 0) * m_(2, 0));
            invsy2 = (T)1.0 / (m_(0, 1) * m_(0, 1) + m_(1, 1) * m_(1, 1) + m_(2, 1) * m_(2, 1));
            invsz2 = (T)1.0 / (m_(0, 2) * m_(0, 2) + m_(1, 2) * m_(1, 2) + m_(2, 2) * m_(2, 2));
            break;
        }
    }
    ScaleBasisVectors(invsx2, invsy2, invsz2);
    InvertSelfROnly();
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::InvertSelfRSOnly()
{
    T invsx2, invsy2, invsz2;
    switch (m_vectorConvention)
    {
        case ROW:
        {            
            invsx2 = (T)1.0 / (m_(0, 0) * m_(0, 0) + m_(1, 0) * m_(1, 0) + m_(2, 0) * m_(2, 0));
            invsy2 = (T)1.0 / (m_(0, 1) * m_(0, 1) + m_(1, 1) * m_(1, 1) + m_(2, 1) * m_(2, 1));
            invsz2 = (T)1.0 / (m_(0, 2) * m_(0, 2) + m_(1, 2) * m_(1, 2) + m_(2, 2) * m_(2, 2));
            break;
        }
        case COLUMN:
        {
            invsx2 = (T)1.0 / (m_(0, 0) * m_(0, 0) + m_(0, 1) * m_(0, 1) + m_(0, 2) * m_(0, 2));
            invsy2 = (T)1.0 / (m_(1, 0) * m_(1, 0) + m_(1, 1) * m_(1, 1) + m_(1, 2) * m_(1, 2));
            invsz2 = (T)1.0 / (m_(2, 0) * m_(2, 0) + m_(2, 1) * m_(2, 1) + m_(2, 2) * m_(2, 2));
            break;
        }
    }
    ScaleTransposedBasisVectors(invsx2, invsy2, invsz2);
    InvertSelfROnly();
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::InvertSelfRTOnly()
{
    LoadTranslation(GetInverseTranslation());
    InvertSelfROnly();
}
// --------------------------------------------------------------------------------------
template <class T> inline void Matrix4<T>::InvertSelfTROnly()
{
    InvertSelfRTOnly();
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::InvertSelfSTOnly()
{
    InvertSelfSOnly();
    
    switch (m_vectorConvention)
    {
        case ROW:
        {            
            m_(3, 0) = -m_(3, 0) * m_(0, 0);
            m_(3, 1) = -m_(3, 1) * m_(1, 1);
            m_(3, 2) = -m_(3, 2) * m_(2, 2);
            break;
        }
        case COLUMN:
        {
            m_(0, 3) = -m_(0, 3) * m_(0, 0);
            m_(1, 3) = -m_(1, 3) * m_(1, 1);
            m_(2, 3) = -m_(2, 3) * m_(2, 2);
            break;
        }
    }
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::InvertSelfTSOnly()
{
    InvertSelfSTOnly();
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::InvertSelfSRTOnly()
{
    InvertSelfSROnly();
    switch (m_vectorConvention)
    {
        case ROW:
            LoadTranslation(
                -m_(3, 0) * m_(0, 0) + -m_(3, 1) * m_(1, 0) + -m_(3, 2) * m_(2, 0),
                -m_(3, 0) * m_(0, 1) + -m_(3, 1) * m_(1, 1) + -m_(3, 2) * m_(2, 1),
                -m_(3, 0) * m_(0, 2) + -m_(3, 1) * m_(1, 2) + -m_(3, 2) * m_(2, 2));
            break;
        case COLUMN:
            LoadTranslation(
                m_(0, 0) * -m_(0, 3) + m_(0, 1) * -m_(1, 3) + m_(0, 2) * -m_(2, 3),
                m_(1, 0) * -m_(0, 3) + m_(1, 1) * -m_(1, 3) + m_(1, 2) * -m_(2, 3),
                m_(2, 0) * -m_(0, 3) + m_(2, 1) * -m_(1, 3) + m_(2, 2) * -m_(2, 3));
            break;
    }
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::LoadEulerAngles(T angle0, T angle1, T angle2, int i, bool odd, bool repeat)
{
    int j, k;
    if (odd)
    {
        angle0 = -angle0;
        angle1 = -angle1;
        angle2 = -angle2;
        j = (i + 2) % 3;
        k = (i + 1) % 3;
    }
    else
    {
        j = (i + 1) % 3;
        k = (i + 2) % 3;
    }
    
    T s0 = Math<T>::Sin(ConvertAngle(angle0));
    T c0 = Math<T>::Cos(ConvertAngle(angle0));
    T s1 = Math<T>::Sin(ConvertAngle(angle1));
    T c1 = Math<T>::Cos(ConvertAngle(angle1));
    T s2 = Math<T>::Sin(ConvertAngle(angle2));
    T c2 = Math<T>::Cos(ConvertAngle(angle2));
    
    T s0s2 = s0 * s2;
    T s0c2 = s0 * c2;
    T c0s2 = c0 * s2;
    T c0c2 = c0 * c2;
    
    if (repeat)
    {
        m_(i, i) = c1;
        m_(i, j) = s0 * s1;
        m_(i, k) = c0 * s1;
        
        m_(j, i) = s1 * s2;
        m_(j, j) = -c1 * s0s2 + c0c2;
        m_(j, k) = -c1 * c0s2 - s0c2;
        
        m_(k, i) = -s1 * c2;
        m_(k, j) = c1 * s0c2 + c0s2;
        m_(k, k) = c1 * c0c2 - s0s2;
    }
    else
    {
        m_(i, i) = c1 * c2;
        m_(i, j) = s1 * s0c2 - c0s2;
        m_(i, k) = s1 * c0c2 + s0s2;
        
        m_(j, i) = c1 * s2;
        m_(j, j) = s1 * s0s2 + c0c2;
        m_(j, k) = s1 * c0s2 - s0c2;
        
        m_(k, i) = -s1;
        m_(k, j) = s0 * c1;
        m_(k, k) = c0 * c1;
    }
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::LoadEulerAngles(T angle0, T angle1, int i, bool odd)
{
    int j, k;
    if (odd)
    {
        angle0 = -angle0;
        angle1 = -angle1;
        j = (i + 2) % 3;
        k = (i + 1) % 3;
    }
    else
    {
        j = (i + 1) % 3;
        k = (i + 2) % 3;
    }
    
    T s0 = Math<T>::Sin(ConvertAngle(angle0));
    T c0 = Math<T>::Cos(ConvertAngle(angle0));
    T s1 = Math<T>::Sin(ConvertAngle(angle1));
    T c1 = Math<T>::Cos(ConvertAngle(angle1));

    m_(i, i) = c1;
    m_(i, j) = s0 * s1;
    m_(i, k) = c0 * s1;
    
    m_(j, i) = (T)0.0;
    m_(j, j) = c0;
    m_(j, k) = -s0;
    
    m_(k, i) = -s1;
    m_(k, j) = s0 * c1;
    m_(k, k) = c0 * c1;
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::ToEulerAngles(T& a0, T& a1, T& a2, int i, bool odd, bool repeat, T epsilon)
{
    int j, k;
    if (odd)
    {
        j = (i + 2) % 3;
        k = (i + 1) % 3;
    }
    else
    {
        j = (i + 1) % 3;
        k = (i + 2) % 3;
    }

    if (repeat)
    {
        T s1 = Math<T>::Sqrt(m_(i, j) * m_(i, j) + m_(i, k) * m_(i, k));
        T c1 = m_(i, i);
        a1 = Math<T>::ATan2(s1, c1);
        if (s1 > epsilon)
        {
            a0 = Math<T>::ATan2(m_(i, j), m_(i, k));
            a2 = Math<T>::ATan2(m_(j, i), -m_(k, i));
        }
        else // Gimbal lock
        {
            a0 = (T)0.0;
            if (c1 < (T)0.0)
                a2 = -Math<T>::ATan2(-m_(j, k), m_(j, j));
            else
                a2 = Math<T>::ATan2(-m_(j, k), m_(j, j));
        }
    }
    else
    {
        T c1 = Math<T>::Sqrt(m_(i, i) * m_(i, i) + m_(j, i) * m_(j, i));
        a1 = atan2(-m_(k, i), c1);
        if (c1 > epsilon)
        {
            a0 = Math<T>::ATan2(m_(k, j), m_(k, k));
            a2 = Math<T>::ATan2(m_(j, i), m_(i, i));
        }
        else // Gimbal lock
        {
            a0 = (T)0.0;
            if (a1 < (T)0.0)
                a2 = Math<T>::ATan2(-m_(j, k), m_(j, j));
            else
                a2 = -Math<T>::ATan2(-m_(j, k), m_(j, j));
        }
    }
    
    if (odd)
    {
        a0 = -a0;
        a1 = -a1;
        a2 = -a2;
    }

    if (m_angleUnit == DEGREES)
    {
        a0 = Math<T>::RadToDeg(a0);
        a1 = Math<T>::RadToDeg(a1);
        a2 = Math<T>::RadToDeg(a2);
    }
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::ToEulerAngles(T& a0, T& a1, int i, bool odd)
{
    int j, k;
    if (odd)
    {
        j = (i + 2) % 3;
        k = (i + 1) % 3;
    }
    else
    {
        j = (i + 1) % 3;
        k = (i + 2) % 3;
    }

    a0 = Math<T>::ATan2(-m_(j, k), m_(j, j));
    a1 = Math<T>::ATan2(-m_(k, i), m_(i, i));
    
    if (odd)
    {
        a0 = -a0;
        a1 = -a1;
    }

    if (m_angleUnit == DEGREES)
    {
        a0 = Math<T>::RadToDeg(a0);
        a1 = Math<T>::RadToDeg(a1);
    }

}
// --------------------------------------------------------------------------------------
// An important note on the 'lookat' function. People associate LH with +z into the
// screen and RH with -z into the screen so strongly, that they call a +z lookat matrix
// left-handed and a -z lookat matrix right-handed. Although it would be convenient for
// the user to have the choice of handedness dictate the type of lookat matrix, I don't
// think it's technically correct.
//
// So although this code chooses the direction of the z axis based on coordinate system
// handedness, I plan to change that (it will probably be a function argument of some
// sort instead).
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::LookAt(const Vector3<T>& pos, const Vector3<T>& target, const Vector3<T>& up)
{
    Vector3<T> z;
    switch (m_coordSysHandedness)
    {
        case LEFT:
            z = Vector3<T>::Normalize(target - pos);
            break;
        case RIGHT:
            z = Vector3<T>::Normalize(pos - target);
            break;
    }
    Vector3<T> x = Vector3<T>::Normalize(up.Cross(z));
    Vector3<T> y = z.Cross(x);
    
    LoadTransposedBasisVectors(x, y, z);
    LoadTranslation(-pos.Dot(x), -pos.Dot(y), -pos.Dot(z));

    switch (m_vectorConvention)
    {
        case ROW:
            m_(0, 3) = (T)0.0;
            m_(1, 3) = (T)0.0;
            m_(2, 3) = (T)0.0;
            m_(3, 3) = (T)1.0;
            break;
        case COLUMN:
            m_(3, 0) = (T)0.0;
            m_(3, 1) = (T)0.0;
            m_(3, 2) = (T)0.0;
            m_(3, 3) = (T)1.0;
            break;
    }
}
// --------------------------------------------------------------------------------------
template <class T> T Matrix4<T>::Determinant() const
{
    T det2_23_23 = m_(2, 2) * m_(3, 3) - m_(2, 3) * m_(3, 2);
    T det2_23_13 = m_(2, 1) * m_(3, 3) - m_(2, 3) * m_(3, 1);
    T det2_23_12 = m_(2, 1) * m_(3, 2) - m_(2, 2) * m_(3, 1);
    T det2_23_03 = m_(2, 0) * m_(3, 3) - m_(2, 3) * m_(3, 0);
    T det2_23_02 = m_(2, 0) * m_(3, 2) - m_(2, 2) * m_(3, 0);
    T det2_23_01 = m_(2, 0) * m_(3, 1) - m_(2, 1) * m_(3, 0);
    
    T det3_123_123 = m_(1, 1) * det2_23_23 - m_(1, 2) * det2_23_13 + m_(1, 3) * det2_23_12;
    T det3_123_023 = m_(1, 0) * det2_23_23 - m_(1, 2) * det2_23_03 + m_(1, 3) * det2_23_02;
    T det3_123_013 = m_(1, 0) * det2_23_13 - m_(1, 1) * det2_23_03 + m_(1, 3) * det2_23_01;
    T det3_123_012 = m_(1, 0) * det2_23_12 - m_(1, 1) * det2_23_02 + m_(1, 2) * det2_23_01;

    return m_(0, 0) * det3_123_123 - m_(0, 1) * det3_123_023 + m_(0, 2) * det3_123_013 - m_(0, 3) * det3_123_012;
}
// --------------------------------------------------------------------------------------
template <class T> Matrix4<T> Matrix4<T>::GetTranspose() const
{
    return Matrix4<T>(m_(0, 0), m_(1, 0), m_(2, 0), m_(3, 0),
                      m_(0, 1), m_(1, 1), m_(2, 1), m_(3, 1),
                      m_(0, 2), m_(1, 2), m_(2, 2), m_(3, 2),
                      m_(0, 3), m_(1, 3), m_(2, 3), m_(3, 3),
                      m_angleUnit,
                      m_vectorConvention,
                      m_coordSysHandedness,
                      m_rotationHandedness,
                      m_storage);
}
// --------------------------------------------------------------------------------------
template <class T> void Matrix4<T>::TransposeSelf()
{
    T m01 = m_(0, 1);
    T m02 = m_(0, 2);
    T m03 = m_(0, 3);
    T m12 = m_(1, 2);
    T m13 = m_(1, 3);
    T m23 = m_(2, 3);
    
    m_(0, 1) = m_(1, 0);
    m_(0, 2) = m_(2, 0);
    m_(0, 3) = m_(3, 0);
    m_(1, 2) = m_(2, 1);
    m_(1, 3) = m_(3, 1);
    m_(2, 3) = m_(3, 2);
    
    m_(1, 0) = m01;
    m_(2, 0) = m02;
    m_(3, 0) = m03;
    m_(2, 1) = m12;
    m_(3, 1) = m13;
    m_(3, 2) = m23;
}
// --------------------------------------------------------------------------------------
template <class T> T Matrix4<T>::Determinant(const Matrix4<T>& m)
{
    return m.Determinant();
}
// --------------------------------------------------------------------------------------
template <class T> Matrix4<T> Matrix4<T>::Transpose(const Matrix4<T>& m)
{
    return m.GetTranspose();
}
// --------------------------------------------------------------------------------------
template <class T> Matrix4<T> Matrix4<T>::Inverse(const Matrix4<T>& m)
{
    return m.GetInverse();
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix4<T> Matrix4<T>::operator-() const
{
    return Matrix4<T>(-m_(0, 0), -m_(0, 1), -m_(0, 2), -m_(0, 3),
                      -m_(1, 0), -m_(1, 1), -m_(1, 2), -m_(1, 3),
                      -m_(2, 0), -m_(2, 1), -m_(2, 2), -m_(2, 3),
                      -m_(3, 0), -m_(3, 1), -m_(3, 2), -m_(3, 3));
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix4<T>& Matrix4<T>::operator+=(const Matrix4<T>& m)
{
    m_(0, 0) += m.m_(0, 0);
    m_(0, 1) += m.m_(0, 1);
    m_(0, 2) += m.m_(0, 2);
    m_(0, 3) += m.m_(0, 3);
    
    m_(1, 0) += m.m_(1, 0);
    m_(1, 1) += m.m_(1, 1);
    m_(1, 2) += m.m_(1, 2);
    m_(1, 3) += m.m_(1, 3);
    
    m_(2, 0) += m.m_(2, 0);
    m_(2, 1) += m.m_(2, 1);
    m_(2, 2) += m.m_(2, 2);
    m_(2, 3) += m.m_(2, 3);
    
    m_(3, 0) += m.m_(3, 0);
    m_(3, 1) += m.m_(3, 1);
    m_(3, 2) += m.m_(3, 2);
    m_(3, 3) += m.m_(3, 3);
    
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix4<T>& Matrix4<T>::operator-=(const Matrix4<T>& m)
{
    m_(0, 0) -= m.m_(0, 0);
    m_(0, 1) -= m.m_(0, 1);
    m_(0, 2) -= m.m_(0, 2);
    m_(0, 3) -= m.m_(0, 3);
    
    m_(1, 0) -= m.m_(1, 0);
    m_(1, 1) -= m.m_(1, 1);
    m_(1, 2) -= m.m_(1, 2);
    m_(1, 3) -= m.m_(1, 3);
    
    m_(2, 0) -= m.m_(2, 0);
    m_(2, 1) -= m.m_(2, 1);
    m_(2, 2) -= m.m_(2, 2);
    m_(2, 3) -= m.m_(2, 3);
    
    m_(3, 0) -= m.m_(3, 0);
    m_(3, 1) -= m.m_(3, 1);
    m_(3, 2) -= m.m_(3, 2);
    m_(3, 3) -= m.m_(3, 3);
    
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix4<T>& Matrix4<T>::operator*=(const Matrix4<T>& m)
{
    T r0, r1, r2, r3;
    
    r0 = m_(0, 0);
    r1 = m_(0, 1);
    r2 = m_(0, 2);
    r3 = m_(0, 3);
    
    m_(0, 0) = r0 * m.m_(0, 0) + r1 * m.m_(1, 0) + r2 * m.m_(2, 0) + r3 * m.m_(3, 0);
    m_(0, 1) = r0 * m.m_(0, 1) + r1 * m.m_(1, 1) + r2 * m.m_(2, 1) + r3 * m.m_(3, 1);
    m_(0, 2) = r0 * m.m_(0, 2) + r1 * m.m_(1, 2) + r2 * m.m_(2, 2) + r3 * m.m_(3, 2);
    m_(0, 3) = r0 * m.m_(0, 3) + r1 * m.m_(1, 3) + r2 * m.m_(2, 3) + r3 * m.m_(3, 3);
    
    r0 = m_(1, 0);
    r1 = m_(1, 1);
    r2 = m_(1, 2);
    r3 = m_(1, 3);
    
    m_(1, 0) = r0 * m.m_(0, 0) + r1 * m.m_(1, 0) + r2 * m.m_(2, 0) + r3 * m.m_(3, 0);
    m_(1, 1) = r0 * m.m_(0, 1) + r1 * m.m_(1, 1) + r2 * m.m_(2, 1) + r3 * m.m_(3, 1);
    m_(1, 2) = r0 * m.m_(0, 2) + r1 * m.m_(1, 2) + r2 * m.m_(2, 2) + r3 * m.m_(3, 2);
    m_(1, 3) = r0 * m.m_(0, 3) + r1 * m.m_(1, 3) + r2 * m.m_(2, 3) + r3 * m.m_(3, 3);
    
    r0 = m_(2, 0);
    r1 = m_(2, 1);
    r2 = m_(2, 2);
    r3 = m_(2, 3);
    
    m_(2, 0) = r0 * m.m_(0, 0) + r1 * m.m_(1, 0) + r2 * m.m_(2, 0) + r3 * m.m_(3, 0);
    m_(2, 1) = r0 * m.m_(0, 1) + r1 * m.m_(1, 1) + r2 * m.m_(2, 1) + r3 * m.m_(3, 1);
    m_(2, 2) = r0 * m.m_(0, 2) + r1 * m.m_(1, 2) + r2 * m.m_(2, 2) + r3 * m.m_(3, 2);
    m_(2, 3) = r0 * m.m_(0, 3) + r1 * m.m_(1, 3) + r2 * m.m_(2, 3) + r3 * m.m_(3, 3);
    
    r0 = m_(3, 0);
    r1 = m_(3, 1);
    r2 = m_(3, 2);
    r3 = m_(3, 3);
    
    m_(3, 0) = r0 * m.m_(0, 0) + r1 * m.m_(1, 0) + r2 * m.m_(2, 0) + r3 * m.m_(3, 0);
    m_(3, 1) = r0 * m.m_(0, 1) + r1 * m.m_(1, 1) + r2 * m.m_(2, 1) + r3 * m.m_(3, 1);
    m_(3, 2) = r0 * m.m_(0, 2) + r1 * m.m_(1, 2) + r2 * m.m_(2, 2) + r3 * m.m_(3, 2);
    m_(3, 3) = r0 * m.m_(0, 3) + r1 * m.m_(1, 3) + r2 * m.m_(2, 3) + r3 * m.m_(3, 3);

    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix4<T>& Matrix4<T>::operator*=(T s)
{
    m_(0, 0) *= s;
    m_(0, 1) *= s;
    m_(0, 2) *= s;
    m_(0, 3) *= s;
    
    m_(1, 0) *= s;
    m_(1, 1) *= s;
    m_(1, 2) *= s;
    m_(1, 3) *= s;
    
    m_(2, 0) *= s;
    m_(2, 1) *= s;
    m_(2, 2) *= s;
    m_(2, 3) *= s;
    
    m_(3, 0) *= s;
    m_(3, 1) *= s;
    m_(3, 2) *= s;
    m_(3, 3) *= s;
    
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix4<T>& Matrix4<T>::operator/=(T s)
{
    assert(s != (T)0.0); // Division epsilon?
    
    T invs = (T)1.0 / s;

    m_(0, 0) *= invs;
    m_(0, 1) *= invs;
    m_(0, 2) *= invs;
    m_(0, 3) *= invs;
    
    m_(1, 0) *= invs;
    m_(1, 1) *= invs;
    m_(1, 2) *= invs;
    m_(1, 3) *= invs;
    
    m_(2, 0) *= invs;
    m_(2, 1) *= invs;
    m_(2, 2) *= invs;
    m_(2, 3) *= invs;
    
    m_(3, 0) *= invs;
    m_(3, 1) *= invs;
    m_(3, 2) *= invs;
    m_(3, 3) *= invs;
    
    return *this;
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix4<T> operator+(const Matrix4<T>& m0, const Matrix4<T>& m1)
{
    return Matrix4<T>
        (m0.m_(0, 0) + m1.m_(0, 0), m0.m_(0, 1) + m1.m_(0, 1), m0.m_(0, 2) + m1.m_(0, 2), m0.m_(0, 3) + m1.m_(0, 3),
         m0.m_(1, 0) + m1.m_(1, 0), m0.m_(1, 1) + m1.m_(1, 1), m0.m_(1, 2) + m1.m_(1, 2), m0.m_(1, 3) + m1.m_(1, 3),
         m0.m_(2, 0) + m1.m_(2, 0), m0.m_(2, 1) + m1.m_(2, 1), m0.m_(2, 2) + m1.m_(2, 2), m0.m_(2, 3) + m1.m_(2, 3),
         m0.m_(3, 0) + m1.m_(3, 0), m0.m_(3, 1) + m1.m_(3, 1), m0.m_(3, 2) + m1.m_(3, 2), m0.m_(3, 3) + m1.m_(3, 3),
         m_angleUnit,
         m_vectorConvention,
         m_coordSysHandedness,
         m_rotationHandedness,
         m_storage);
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix4<T> operator-(const Matrix4<T>& m0, const Matrix4<T>& m1)
{
    return Matrix4<T>
        (m0.m_(0, 0) - m1.m_(0, 0), m0.m_(0, 1) - m1.m_(0, 1), m0.m_(0, 2) - m1.m_(0, 2), m0.m_(0, 3) - m1.m_(0, 3),
         m0.m_(1, 0) - m1.m_(1, 0), m0.m_(1, 1) - m1.m_(1, 1), m0.m_(1, 2) - m1.m_(1, 2), m0.m_(1, 3) - m1.m_(1, 3),
         m0.m_(2, 0) - m1.m_(2, 0), m0.m_(2, 1) - m1.m_(2, 1), m0.m_(2, 2) - m1.m_(2, 2), m0.m_(2, 3) - m1.m_(2, 3),
         m0.m_(3, 0) - m1.m_(3, 0), m0.m_(3, 1) - m1.m_(3, 1), m0.m_(3, 2) - m1.m_(3, 2), m0.m_(3, 3) - m1.m_(3, 3),
         m_angleUnit,
         m_vectorConvention,
         m_coordSysHandedness,
         m_rotationHandedness,
         m_storage);
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix4<T> operator*(const Matrix4<T>& m0, const Matrix4<T>& m1)
{
    return Matrix4<T>
        (m0.m_(0, 0) * m1.m_(0, 0) + m0.m_(0, 1) * m1.m_(1, 0) + m0.m_(0, 2) * m1.m_(2, 0) + m0.m_(0, 3) * m1.m_(3, 0),
         m0.m_(0, 0) * m1.m_(0, 1) + m0.m_(0, 1) * m1.m_(1, 1) + m0.m_(0, 2) * m1.m_(2, 1) + m0.m_(0, 3) * m1.m_(3, 1),
         m0.m_(0, 0) * m1.m_(0, 2) + m0.m_(0, 1) * m1.m_(1, 2) + m0.m_(0, 2) * m1.m_(2, 2) + m0.m_(0, 3) * m1.m_(3, 2),
         m0.m_(0, 0) * m1.m_(0, 3) + m0.m_(0, 1) * m1.m_(1, 3) + m0.m_(0, 2) * m1.m_(2, 3) + m0.m_(0, 3) * m1.m_(3, 3),     
         m0.m_(1, 0) * m1.m_(0, 0) + m0.m_(1, 1) * m1.m_(1, 0) + m0.m_(1, 2) * m1.m_(2, 0) + m0.m_(1, 3) * m1.m_(3, 0),
         m0.m_(1, 0) * m1.m_(0, 1) + m0.m_(1, 1) * m1.m_(1, 1) + m0.m_(1, 2) * m1.m_(2, 1) + m0.m_(1, 3) * m1.m_(3, 1),
         m0.m_(1, 0) * m1.m_(0, 2) + m0.m_(1, 1) * m1.m_(1, 2) + m0.m_(1, 2) * m1.m_(2, 2) + m0.m_(1, 3) * m1.m_(3, 2),
         m0.m_(1, 0) * m1.m_(0, 3) + m0.m_(1, 1) * m1.m_(1, 3) + m0.m_(1, 2) * m1.m_(2, 3) + m0.m_(1, 3) * m1.m_(3, 3),     
         m0.m_(2, 0) * m1.m_(0, 0) + m0.m_(2, 1) * m1.m_(1, 0) + m0.m_(2, 2) * m1.m_(2, 0) + m0.m_(2, 3) * m1.m_(3, 0),
         m0.m_(2, 0) * m1.m_(0, 1) + m0.m_(2, 1) * m1.m_(1, 1) + m0.m_(2, 2) * m1.m_(2, 1) + m0.m_(2, 3) * m1.m_(3, 1),
         m0.m_(2, 0) * m1.m_(0, 2) + m0.m_(2, 1) * m1.m_(1, 2) + m0.m_(2, 2) * m1.m_(2, 2) + m0.m_(2, 3) * m1.m_(3, 2),
         m0.m_(2, 0) * m1.m_(0, 3) + m0.m_(2, 1) * m1.m_(1, 3) + m0.m_(2, 2) * m1.m_(2, 3) + m0.m_(2, 3) * m1.m_(3, 3), 
         m0.m_(3, 0) * m1.m_(0, 0) + m0.m_(3, 1) * m1.m_(1, 0) + m0.m_(3, 2) * m1.m_(2, 0) + m0.m_(3, 3) * m1.m_(3, 0),
         m0.m_(3, 0) * m1.m_(0, 1) + m0.m_(3, 1) * m1.m_(1, 1) + m0.m_(3, 2) * m1.m_(2, 1) + m0.m_(3, 3) * m1.m_(3, 1),
         m0.m_(3, 0) * m1.m_(0, 2) + m0.m_(3, 1) * m1.m_(1, 2) + m0.m_(3, 2) * m1.m_(2, 2) + m0.m_(3, 3) * m1.m_(3, 2),
         m0.m_(3, 0) * m1.m_(0, 3) + m0.m_(3, 1) * m1.m_(1, 3) + m0.m_(3, 2) * m1.m_(2, 3) + m0.m_(3, 3) * m1.m_(3, 3),
         m0.m_angleUnit,
         m0.m_vectorConvention,
         m0.m_coordSysHandedness,
         m0.m_rotationHandedness,
         m0.m_storage);
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix4<T> operator*(T s, const Matrix4<T>& m)
{
    return Matrix4<T>(s * m.m_(0, 0), s * m.m_(0, 1), s * m.m_(0, 2), s * m.m_(0, 3),
                      s * m.m_(1, 0), s * m.m_(1, 1), s * m.m_(1, 2), s * m.m_(1, 3),
                      s * m.m_(2, 0), s * m.m_(2, 1), s * m.m_(2, 2), s * m.m_(2, 3),
                      s * m.m_(3, 0), s * m.m_(3, 1), s * m.m_(3, 2), s * m.m_(3, 3),
                      m_angleUnit,
                      m_vectorConvention,
                      m_coordSysHandedness,
                      m_rotationHandedness,
                      m_storage);
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix4<T> operator*(const Matrix4<T>& m, T s)
{
    return Matrix4<T>(m.m_(0, 0) * s, m.m_(0, 1) * s, m.m_(0, 2) * s, m.m_(0, 3) * s,
                      m.m_(1, 0) * s, m.m_(1, 1) * s, m.m_(1, 2) * s, m.m_(1, 3) * s,
                      m.m_(2, 0) * s, m.m_(2, 1) * s, m.m_(2, 2) * s, m.m_(2, 3) * s,
                      m.m_(3, 0) * s, m.m_(3, 1) * s, m.m_(3, 2) * s, m.m_(3, 3) * s,
                      m_angleUnit,
                      m_vectorConvention,
                      m_coordSysHandedness,
                      m_rotationHandedness,
                      m_storage);
}
// --------------------------------------------------------------------------------------
template <class T> inline Matrix4<T> operator/(const Matrix4<T>& m, T s)
{
    assert(s != (T)0.0); // Division epsilon?
    
    T invs = (T)1.0 / s;
    
    return Matrix4<T>
        (m.m_(0, 0) * invs, m.m_(0, 1) * invs, m.m_(0, 2) * invs, m.m_(0, 3) * invs,
         m.m_(1, 0) * invs, m.m_(1, 1) * invs, m.m_(1, 2) * invs, m.m_(1, 3) * invs,
         m.m_(2, 0) * invs, m.m_(2, 1) * invs, m.m_(2, 2) * invs, m.m_(2, 3) * invs,
         m.m_(3, 0) * invs, m.m_(3, 1) * invs, m.m_(3, 2) * invs, m.m_(3, 3) * invs,
         m_angleUnit,
         m_vectorConvention,
         m_coordSysHandedness,
         m_rotationHandedness,
         m_storage);
}
// --------------------------------------------------------------------------------------
template <class T> inline std::ostream& operator<<(std::ostream& os, const Matrix4<T>& m)
{
    for (int i = 0; i < 4; ++i)
    {
        os << "[ ";
        for (int j = 0; j < 4; ++j)
            os << m.Get(i, j) << " ";
        os << "]" << std::endl;
    }
    
    return os;
}
// --------------------------------------------------------------------------------------

} // namespace cml

#endif

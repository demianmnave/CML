// Here are some code samples from the math library in its current form.

// First are some functions from the Matrix4 class. The first several functions assume
// column vectors and matching coordinate system and rotation handedness. Once we've
// figured out the best way to do it, they will be revised to support different conventions.

// Note that I will probably change 'T' to something more descriptive, such as 'Real'.

// --------------------------------------------------------------------------------------
// Standard algorithm (from Shoemake's article) for extracting a quaternion from a matrix.
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
        result[j] = (m_(i, j)  + m_[j][i]) * s;
        result[k] = (m_(i, k)  + m_[k][i]) * s;
        result[3] = (m_(k, j)  - m_[j][k]) * s;
    }
    q.Set(result);
}

// --------------------------------------------------------------------------------------
// This function rotates the 3x3 portion of the matrix about one of its local basis
// vectors, specified by 'i'.
// --------------------------------------------------------------------------------------

template <class T> void Matrix4<T>::RotateAboutLocalAxis(unsigned int i, T angle)
{
    assert(i < 3);
    
    unsigned int j, k;
    Math<>::GetCyclicPermutation(i, j, k);
    
    T u[3], v[3];
    T s, c;
    Math<T>::SinCos(ConvertAngle(angle), s, c);
    
    u[0] = c * m_(0, j) + s * m_(0, k);
    u[1] = c * m_(1, j) + s * m_(1, k);
    u[2] = c * m_(2, j) + s * m_(2, k);
    
    v[0] = c * m_(0, k) - s * m_(0, j) ;
    v[1] = c * m_(1, k) - s * m_(1, j);
    v[2] = c * m_(2, k) - s * m_(2, j);
    
    m_(0, j) = u[0];
    m_(1, j) = u[1];
    m_(2, j) = u[2];
    
    m_(0, k) = v[0];
    m_(1, k) = v[1];
    m_(2, k) = v[2];
}

// --------------------------------------------------------------------------------------
// Creates an orthonormal basis from a single vector. The 'u' argument allows the
// caller to select which basis vector will be aligned with the input vector.
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
// Orthogonalizes the 3x3 portion of the matrix.
//
// If n = 0, a simple orthogonalization using cross products is executed, with 'u'
// specifying the axis whose direction remains unchanged. n > 0 will first perform n
// iterations of iterative Gram-Schmidt, and then ensure orthogonality with the cross-product
// method.
// --------------------------------------------------------------------------------------

template <class T> void Matrix3<T>::Orthogonalize(unsigned int u, unsigned int n, T k)
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
        
        T invdot00 = (T)1.0 / dot00;
        T invdot11 = (T)1.0 / dot11;
        T invdot22 = (T)1.0 / dot22;
        
        T s01 = k * dot01 * invdot11;
        T s02 = k * dot02 * invdot22;
        T s10 = k * dot01 * invdot00;
        T s12 = k * dot12 * invdot22;
        T s20 = k * dot02 * invdot00;
        T s21 = k * dot12 * invdot11;
        
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
// This function is based on a great article by Shoemake in one of the Graphics
// Gems books. The function constructs a matrix from Euler angles in any order, such
// as XYZ, YZX, XYX, etc. (I've also written functions to extract Euler angles in any order,
// and for construction and extraction for groups of two rather than three angles.)
//
// Note that in the final version, 'i', 'odd' and 'repeat' will be encoded in named
// constants such as XYZ.
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
// This is just the standard axis-angle-to-matrix conversion. I've included it because
// it has some of the placeholder code (here used to determine how to set up the rotation
// matrix) that I hope to replace with template-based techniques.
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
// Rotates a quaternion about one of its local basis vectors, specified by 'i'.
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
// One of my aims with the library is to document the algorithms used, either as comments
// in the code files, or perhaps in separate documents. I've left this material out of
// the proceeding functions, but have included it here to show what I have in mind.
//
// This is a nice little algorithm for constructing a quaternion to rotate from one
// vector to another that was posted online by 'minorlogic'. I'm assuming the algorithm
// is fair game, as he has discussed it on a number of online forums.
// --------------------------------------------------------------------------------------

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
// So it would be convenient if we could somehow express q using only these terms.
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
// If we know a priori that v1 and v2 are unit-length, we have:
//
// [c, 1 + d]
//
// Whichever version we use, normalizing as our final step gives us our unit-length result.
//
// All of the methods mentioned fail when the angle between v1 and v2 is near pi.
// This is at it should be, since in this case there is no unique solution.
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

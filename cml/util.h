/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef cml_util_h
#define cml_util_h

#include <cml/constants.h>

namespace cml {

/** sign of input value as double */
template < typename T >
double sign(T value) {
    return value < T(0) ? -1.0 : (value > T(0) ? 1.0 : 0.0);
}

/** clamp input value to the range [min, max] */
template < typename T >
T clamp(T value, T min, T max) {
    return std::max(std::min(value, max), min);
}

/** test input value for inclusion in [min, max] */
template < typename T >
bool in_range(T value, T min, T max) {
    return value >= min && value <= max;
}

/** map input value from [min1, max1] to [min2, max2] */
template < typename T >
T map_range(T value, T min1, T max1, T min2, T max2) {
    return min2 + ((value - min1) / (max1 - min1)) * (max2 - min2);
}


/** wrap std::acos() and clamp argument to [-1, 1] */
template < typename T >
T acos_safe(T theta) {
    return T(std::acos(clamp(theta, T(-1.0), T(1.0))));
}

/** wrap std::asin() and clamp argument to [-1, 1] */
template < typename T >
T asin_safe(T theta) {
    return T(std::asin(clamp(theta, T(-1.0), T(1.0))));
}

/** wrap std::sqrt() and clamp argument to [0, inf) */
template < typename T >
T sqrt_safe(T value) {
    return T(std::sqrt(std::max(value, T(0.0))));
}


/** for convenient squaring of expressions */
template < typename T >
T sqr(T value) {
    return value * value;
}

/** inverse square root */
template < typename T >
T inv_sqrt(T value) {
    return T(1.0 / std::sqrt(value));
}


// The next few functions deal with indexing. next() and prev() are useful for
// operations involving the vertices of a polygon or other cyclic set, and
// cyclic_permutation() is used by various functions that deal with axes or
// basis vectors in a generic way. As these functions are only relevant for
// unsigned integer types, I've just used size_t, but there may be reasons I
// haven't thought of that they should be templated.

/** return next, with cycling, in a series of N non-negative integers */
inline size_t next(size_t i, size_t N) {
    return (i + 1) % N;
}

/** return previous, with cycling, in a series of N non-negative integers */
inline size_t prev(size_t i, size_t N) {
    return i ? (i - 1) : (N - 1);
}

/** cyclic permutation of the set { 0, 1 }, starting with 'first' */
inline void cyclic_permutation(size_t first, size_t& i, size_t& j) {
    i = first;
    j = next(i, 2);
}

/** cyclic permutation of the set { 0, 1, 2 }, starting with 'first' */
inline void cyclic_permutation(size_t first, size_t& i, size_t& j, size_t& k)
{
    i = first;
    j = next(i, 3);
    k = next(j, 3);
}

/** cyclic permutation of the set { 0, 1, 2, 3 }, starting with 'first' */
inline void cyclic_permutation(
        size_t first, size_t& i, size_t& j, size_t& k, size_t& l)
{
    i = first;
    j = next(i, 4);
    k = next(j, 4);
    l = next(k, 4);
}


/** convert radians to degrees */
template < typename T >
T deg(T theta) {
    return theta * constants::deg_per_rad;
}

/** convert degrees to radians */
template < typename T >
T rad(T theta) {
    return theta * constants::rad_per_deg;
}


/** linear interpolation of 2 values.
 *
 * @note The data points are assumed to be sampled at u = 0 and u = 1, so
 * for interpolation u must lie between 0 and 1.
 */
template <typename T, typename Scalar>
T lerp(const T& f0, const T& f1, Scalar u) {
    return (Scalar(1.0) - u) * f0 + u * f1;
}

/** bilinear interpolation of 4 values.
 *
 * @note The data points are assumed to be sampled at the corners of a unit
 * square, so for interpolation u and v must lie between 0 and 1,
 */
template <typename T, typename Scalar>
T bilerp(const T& f00, const T& f10,
         const T& f01, const T& f11,
         Scalar u, Scalar v)
{
    Scalar uv = u * v;
    return (
        (Scalar(1.0) - u - v + uv) * f00 +
                          (u - uv) * f10 +
                          (v - uv) * f01 +
                                uv * f11
    );
}

/** trilinear interpolation of 8 values.
 *
 * @note The data values are assumed to be sampled at the corners of a unit
 * cube, so for interpolation, u, v, and w must lie between 0 and 1.
 */
template <typename T, typename Scalar>
T trilerp(const T& f000, const T& f100,
          const T& f010, const T& f110,
          const T& f001, const T& f101,
          const T& f011, const T& f111,
          Scalar u, Scalar v, Scalar w)
{
    Scalar uv = u * v;
    Scalar vw = v * w;
    Scalar wu = w * u;
    Scalar uvw = uv * w;
    
    return (
        (Scalar(1.0) - u - v - w + uv + vw + wu - uvw) * f000 +
                                   (u - uv - wu + uvw) * f100 +
                                   (v - uv - vw + uvw) * f010 +
                                            (uv - uvw) * f110 +
                                   (w - vw - wu + uvw) * f001 +
                                            (wu - uvw) * f101 +
                                            (vw - uvw) * f011 +
                                                   uvw * f111
    );
}

} // namespace cml

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp

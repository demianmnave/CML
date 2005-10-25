// --------------------------------------------------------------------------------------
// FILE: jykMath.h
// AUTHOR: Jesse Krebs
// --------------------------------------------------------------------------------------

#ifndef JYKMATH_H
#define JYKMATH_H

#include <cmath>
#include <cfloat>
#include <assert.h>

/* --------------------------------------------------------------------------------------

I don't have any preconceived notions about how this should be implemented. I just think
there should be wrappers for c++ functions (to allow for custom implementations), as well
as some commonly used constants, and functions such as Max and Min.

As I think I mentioned earlier, I'm not sure what the best way to wrap the c++ functions
is, i.e. should there be different versions for float, etc.

-------------------------------------------------------------------------------------- */ 

namespace jyk {

template <class T = float>
class Math
{
public:

    static const T PI;
    static const T TWO_PI;
    static const T PI_OVER_2;
    static const T PI_OVER_4;
    static const T DEG_TO_RAD;
    static const T RAD_TO_DEG;
    static const T EPSILON;
    static const T MAX_REAL;
    static const T SQRT_2;
    static const T SQRT_3;
    static const T SQRT_5;
    static const T SQRT_6;
    static const T COS_PI_OVER_4;
    static const T E;
    
    static T Sin(T val);
    static T Cos(T val);
    static T Tan(T val);
    static T ASin(T val);
    static T ACos(T val);
    static T ASinSafe(T val);
    static T ACosSafe(T val);
    static T ATan(T val);
    static T ATan2(T y, T x);
    static T Floor(T val);
    static T Ceil(T val);
    static T Fabs(T val);
    static T FMod(T val1, T val2);
    static T Pow(T base, T exp);
    static T Log(T val);
    static T Exp(T val);
    static T Square(T val);
    static T Sqrt(T val);
    static T SqrtSafe(T val);
    static T InvSqrt(T val);
    static T Min(T val1, T val2);
    static T Max(T val1, T val2);
    static T Clamp(T val, T min, T max);
    static T UnitRandom();
    static T Random(T min, T max);
    static T DegToRad(T val);
    static T RadToDeg(T val);
    
    // Regarding the random() functions, I may investigate more sophisticated random number
    // generators at some point, but those will probably go in a separate class. Here we'll
    // just stick with std::rand().

    // The SinCos() function is to allow for a custom implementation that can calculate
    // the sine and cosine of an angle more efficiently in one shot than in two separate
    // calls to sin() and cos(). I don't know how important this is to include.
    static void SinCos(T val, T& s, T& c);
    static void Swap(T& val1, T& val2);
    static void Sort(T& val1, T& val2);
    static bool InRange(T val, T min, T max);
    static bool Compare(T val1, T val2, T epsilon = EPSILON);
    static void SeedRandom(T val);

    // I added these because I'm using cyclic permuations a lot in the vector and matrix
    // code. It's a little esoteric though, so I may ditch these functions and just do
    // the permuations in place.
    static unsigned int Next(unsigned int i, unsigned int n);  
    static void GetCyclicPermutation(unsigned int i, unsigned int& j);
    static void GetCyclicPermutation(unsigned int i, unsigned int& j, unsigned int& k);
    
    // There are some other things I have code for and plan to support in the library,
    // such as root finding and so on. I'm not worrying about that for now, though, and
    // in any case they will probably go in separate classes.
};
// --------------------------------------------------------------------------------------
template <class T> const T Math<T>::PI =                ATan((T)1.0) * (T)4.0; // acos(-1)? atan2(0, -1)?
template <class T> const T Math<T>::TWO_PI =            PI * (T)2.0;
template <class T> const T Math<T>::PI_OVER_2 =         PI / (T)2.0;
template <class T> const T Math<T>::PI_OVER_4 =         PI / (T)4.0;
template <class T> const T Math<T>::DEG_TO_RAD =        PI / (T)180.0;
template <class T> const T Math<T>::RAD_TO_DEG =        (T)180.0 / PI;
// Default epsilons is an unresolved issue. There should probably be different values for
// different circumstances, as well as different precisions.
template <class T> const T Math<T>::EPSILON =           (T)0.001;
template <class T> const T Math<T>::SQRT_2 =            Math<T>::Sqrt((T)2.0);
template <class T> const T Math<T>::SQRT_3 =            Math<T>::Sqrt((T)3.0);
template <class T> const T Math<T>::SQRT_5 =            Math<T>::Sqrt((T)5.0);
template <class T> const T Math<T>::SQRT_6 =            Math<T>::Sqrt((T)6.0);
template <class T> const T Math<T>::COS_PI_OVER_4 =     Math<T>::Cos(PI_OVER_4);
// Need to double-check value of e and decide on number of places
template <class T> const T Math<T>::E =                 2.71828182845904523536028747135266249775724709369995;
// --------------------------------------------------------------------------------------
inline float Math<float>::Sin(float val)
{
    return std::sinf(val);
}
// --------------------------------------------------------------------------------------
inline float Math<float>::Cos(float val)
{
    return std::cosf(val);
}
// --------------------------------------------------------------------------------------
inline float Math<float>::Tan(float val)
{
    return std::tanf(val);
}
// --------------------------------------------------------------------------------------
inline float Math<float>::ASin(float val)
{
    return std::asinf(val);
}
// --------------------------------------------------------------------------------------
inline float Math<float>::ACos(float val)
{
    return std::acosf(val);
}
// --------------------------------------------------------------------------------------
inline float Math<float>::ASinSafe(float val)
{
    return std::asinf(Clamp(val, -1.0f, 1.0f));
}
// --------------------------------------------------------------------------------------
inline float Math<float>::ACosSafe(float val)
{
    return std::acosf(Clamp(val, -1.0f, 1.0f));
}
// --------------------------------------------------------------------------------------
inline float Math<float>::ATan(float val)
{
    return std::atanf(val);
}
// --------------------------------------------------------------------------------------
inline float Math<float>::ATan2(float y, float x)
{
    return std::atan2f(y, x);
}
// --------------------------------------------------------------------------------------
inline float Math<float>::Sqrt(float val)
{
    return std::sqrtf(val);
}
// --------------------------------------------------------------------------------------
inline float Math<float>::SqrtSafe(float val)
{
    return std::sqrtf(Fabs(val));
}
// --------------------------------------------------------------------------------------
inline float Math<float>::Floor(float val)
{
    return std::floorf(val);
}
// --------------------------------------------------------------------------------------
inline float Math<float>::Ceil(float val)
{
    return std::ceilf(val);
}
// --------------------------------------------------------------------------------------
inline float Math<float>::Fabs(float val)
{
    return std::fabsf(val);
}
// --------------------------------------------------------------------------------------
inline float Math<float>::FMod(float val1, float val2)
{
    return std::fmodf(val1, val2);
}
// --------------------------------------------------------------------------------------
inline float Math<float>::Pow(float base, float exp)
{
    return std::powf(base, exp);
}
// --------------------------------------------------------------------------------------
inline float Math<float>::Log(float val)
{
    return std::logf(val);
}
// --------------------------------------------------------------------------------------
inline float Math<float>::Exp(float val)
{
    return std::expf(val);
}
// --------------------------------------------------------------------------------------
inline double Math<double>::Sin(double val)
{
    return sin(val);
}
// --------------------------------------------------------------------------------------
inline double Math<double>::Cos(double val)
{
    return cos(val);
}
// --------------------------------------------------------------------------------------
inline double Math<double>::Tan(double val)
{
    return tan(val);
}
// --------------------------------------------------------------------------------------
inline double Math<double>::ASin(double val)
{
    return asin(val);
}
// --------------------------------------------------------------------------------------
inline double Math<double>::ACos(double val)
{
    return acos(val);
}
// --------------------------------------------------------------------------------------
inline double Math<double>::ASinSafe(double val)
{
    return asin(Clamp(val, -1.0, 1.0));
}
// --------------------------------------------------------------------------------------
inline double Math<double>::ACosSafe(double val)
{
    return acos(Clamp(val, -1.0, 1.0));
}
// --------------------------------------------------------------------------------------
inline double Math<double>::ATan(double val)
{
    return atan(val);
}
// --------------------------------------------------------------------------------------
inline double Math<double>::ATan2(double y, double x)
{
    return atan2(y, x);
}
// --------------------------------------------------------------------------------------
inline double Math<double>::Sqrt(double val)
{
    return sqrt(val);
}
// --------------------------------------------------------------------------------------
inline double Math<double>::SqrtSafe(double val)
{
    return sqrt(Fabs(val));
}
// --------------------------------------------------------------------------------------
inline double Math<double>::Floor(double val)
{
    return floor(val);
}
// --------------------------------------------------------------------------------------
inline double Math<double>::Ceil(double val)
{
    return ceil(val);
}
// --------------------------------------------------------------------------------------
inline double Math<double>::Fabs(double val)
{
    return std::fabs(val);
}
// --------------------------------------------------------------------------------------
inline double Math<double>::FMod(double val1, double val2)
{
    return fmod(val1, val2);
}
// --------------------------------------------------------------------------------------
inline double Math<double>::Pow(double base, double exp)
{
    return pow(base, exp);
}
// --------------------------------------------------------------------------------------
inline double Math<double>::Log(double val)
{
    return log(val);
}
// --------------------------------------------------------------------------------------
inline double Math<double>::Exp(double val)
{
    return exp(val);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::Sin(T val)
{
    return (T)sin((double)val);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::Cos(T val)
{
    return (T)cos((double)val);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::Tan(T val)
{
    return (T)tan((double)val);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::ASin(T val)
{
    return (T)asin((double)val);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::ACos(T val)
{

    return (T)acos((double)val);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::ASinSafe(T val)
{
    return (T)asin((double)Clamp(val, (T)-1.0, (T)1.0));
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::ACosSafe(T val)
{

    return (T)acos((double)Clamp(val, (T)-1.0, (T)1.0));
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::ATan(T val)
{
    return (T)atanf((double)val);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::ATan2(T y, T x)
{
    return (T)atan2((double)y, (double)x);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::Sqrt(T val)
{
    return (T)sqrt((double)val);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::SqrtSafe(T val)
{
    return (T)sqrt((double)Fabs(val));
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::Floor(T val)
{
    return (T)floor((double)val);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::Ceil(T val)
{
    return (T)ceil((double)val);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::Fabs(T val)
{
    return (T)fabs((double)val);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::FMod(T val1, T val2)
{
    return (T)fmod((double)val1, (double)val2);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::Pow(T base, T exp)
{
    return (T)pow((double)base, (double)exp);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::Log(T val)
{
    return (T)log((double)val);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::Exp(T val)
{
    return (T)exp((double)val);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::Square(T val)
{
    return val * val;
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::InvSqrt(T val)
{
    return (T)1.0 / Sqrt(val);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::Min(T val1, T val2)
{
    return val1 < val2 ? val1 : val2;
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::Max(T val1, T val2)
{
    return val1 > val2 ? val1 : val2;
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::Clamp(T val, T min, T max)
{
    assert(min <= max);
    if (val < min)
        return min;
    if (val > max)
        return max;
    return val;
}
// --------------------------------------------------------------------------------------
template <class T> inline void Math<T>::SinCos(T val, T& s, T& c)
{
    s = Sin(val);
    c = Cos(val);
}
// --------------------------------------------------------------------------------------
template <class T> inline void Math<T>::Swap(T& val1, T& val2)
{
    T temp = val1;
    val1 = val2;
    val2 = temp;
}
// --------------------------------------------------------------------------------------
template <class T> inline void Math<T>::Sort(T& val1, T& val2)
{
    if (val1 > val2)
        Swap(val1, val2);
}
// --------------------------------------------------------------------------------------
template <class T> inline bool Math<T>::InRange(T val, T min, T max)
{
    assert(min <= max);
    return val >= min && val <= max;
}
// --------------------------------------------------------------------------------------
template <class T> inline bool Math<T>::Compare(T val1, T val2, T epsilon)
{
    return Fabs(val1 - val2) < epsilon;
}
// --------------------------------------------------------------------------------------
template <class T> inline void Math<T>::SeedRandom(T val)
{
    srand(val);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::UnitRandom()
{
    return ((T)std::rand())/((T)RAND_MAX);
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::Random(T min, T max)
{
    assert(min <= max);
    return min + (max - min) * UnitRandom();
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::DegToRad(T val)
{
    return val * DEG_TO_RAD;
}
// --------------------------------------------------------------------------------------
template <class T> inline T Math<T>::RadToDeg(T val)
{
    return val * RAD_TO_DEG;
}
// --------------------------------------------------------------------------------------
inline unsigned int Math<>::Next(unsigned int i, unsigned int n)
{
    return (i + 1) % n;
}
// --------------------------------------------------------------------------------------
inline void Math<>::GetCyclicPermutation(unsigned int i, unsigned int& j)
{
    assert(i < 2);
    j = (i + 1) % 2;
}
// --------------------------------------------------------------------------------------
inline void Math<>::GetCyclicPermutation(unsigned int i, unsigned int& j, unsigned int& k)
{
    assert(i < 3);
    j = (i + 1) % 3;
    k = (j + 1) % 3;
}
// --------------------------------------------------------------------------------------
    
} // namespace jyk    
    
#endif

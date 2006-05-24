/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Useful constants.
 */

#ifndef cml_constants_h
#define cml_constants_h

#include <cmath>

#if !defined(M_PI)
#define M_PI 3.14159265358979323846264338327950288
#endif

#if !defined(M_SQRT2)
#define M_SQRT2 1.41421356237309504880168872420969808
#endif

#if !defined(M_E)
#define M_E 2.71828182845904523536028747135266250
#endif

namespace cml {
namespace constants {

    const double pi = M_PI;
    const double two_pi = 2.*M_PI;
    const double inv_pi = 1./M_PI;                      /* 1/pi */
    const double inv_two_pi = 1./(2.*M_PI);             /* 1/(2*pi) */
    const double pi_over_2 = M_PI/2.;                   /* pi/2 */
    const double pi_over_4 = M_PI/4.;                   /* pi/4 */
    const double deg_per_rad = 180./M_PI;
    const double rad_per_deg = M_PI/180.;
    const double sqrt_2 = M_SQRT2;
    const double sqrt_3 = 1.73205080756887729352744634150587237;
    const double sqrt_5 = 2.23606797749978969640917366873127624;
    const double sqrt_6 = 2.44948974278317809819728407470589139;
    const double e = M_E;
   
} // namespace constants
} // namespace cml



#if 0
// Demian:

// These are constants that I would like to make available. I considered a
// few different ways we might do so, such as:

// float theta = cml::pi(); // always return double
// float theta = cml::pi<float>(); // template function
// float theta = cml::constants<float>::pi(); // 'constants' struct

// I imagine there are other, fancier template-based solutions as well that
// would deal with the scalar type in a more sophisticated way. I've
// implemented the struct version here, but you're welcome to change it to
// whatever you like. Also, I'll be happy to make any necessary changes myself
// if it's something I can do.

// The version I chose is the most verbose, but typedef'ing it:

// float theta = constants_t::pi();

// Makes it more manageable.

namespace cml {

template < typename Real >
struct constants
{
    typedef Real value_type;
    
private:

    /** For convenience */
    typedef value_type T;

public:

private:

    /** For convenience */
    typedef vector< T, fixed<2> > vector2_t;
    typedef vector< T, fixed<3> > vector3_t;
    
public:

    // In my library I've found it useful to make various vector constants
    // (the zero vector and cardinal basis vectors) available. This isn't
    // strictly necessary, but can often reduce 2 or 3 lines of code to 1,
    // which is nice.
    
    // They probably don't belong in this struct, but I've just put them here
    // for the time being. Another possible home for them would be the vector
    // class.

    // Note: If and when we have vector constructors of the form:
    
    // vector3_t v(0.0, 0.0, 0.0);
    
    // The arrays won't be necessary. Also, the arrays are non-const because
    // there's currently no vector constructor which takes a constant array as
    // an argument.

    /** zero vector in 2D */
    static vector2_t zero_2D() {
        /*const*/ T zero[] = { T(0.0), T(0.0) };
        const vector2_t value(zero);
        return value;
    }

    /** zero vector in 3D */
    static vector3_t zero_3D() {
        /*const*/ T zero[] = { T(0.0), T(0.0), T(0.0) };
        const vector3_t value(zero);
        return value;
    }
    
    /** cardinal x axis in 2D */
    static vector3_t x_axis_2D() {
        return axis_2D(0);
    }
    
    /** cardinal y axis in 2D */
    static vector3_t y_axis_2D() {
        return axis_2D(1);
    }
    
    /** cardinal x axis in 3D */
    static vector3_t x_axis_3D() {
        return axis_3D(0);
    }
    
    /** cardinal y axis in 3D */
    static vector3_t y_axis_3D() {
        return axis_3D(1);
    }
    
    /** cardinal z axis in 3D */
    static vector3_t z_axis_3D() {
        return axis_3D(2);
    }

    // Again, these functions probably shouldn't be in this struct, as we
    // probably shouldn't be dealing with arguments and range-checking here
    // (the % is just a placeholder for proper error-checking on the
    // argument). These functions also aren't strictly necessary, but I have
    // them in my library because I sometimes find it handy to be able to
    // access the cardinal axes by index.
    
    /** cardinal axis by index in 2D */
    static vector2_t axis_2D(size_t i) {
        /*const*/ T x_axis[] = { T(1.0), T(0.0) };
        /*const*/ T y_axis[] = { T(0.0), T(1.0) };
        const vector2_t axes[] = {
            vector2_t(x_axis),
            vector2_t(y_axis)
        };
        
        return axes[i % 2];
    }
    
    /** cardinal axis by index in 3D */
    static vector3_t axis_3D(size_t i) {
        /*const*/ T x_axis[] = { T(1.0), T(0.0), T(0.0) };
        /*const*/ T y_axis[] = { T(0.0), T(1.0), T(0.0) };
        /*const*/ T z_axis[] = { T(0.0), T(0.0), T(1.0) };
        const vector3_t axes[] = {
            vector3_t(x_axis),
            vector3_t(y_axis),
            vector3_t(z_axis)
        };
        
        return axes[i % 3];
    }
};

} // namespace cml
#endif

#endif

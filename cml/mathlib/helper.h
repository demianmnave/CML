/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief
 */

#ifndef helper_h
#define helper_h

#include <cstddef>
#include <cml/constants.h>

namespace cml {

/* Helper classes for axis order, coordinate system handedness, z-clipping
 * range and spherical coordinate type.
 *
 * @todo: Figure out the best way to handle this.
 *
 * Initially I used enumerations for these parameters, but switched to class
 * objects to prevent the passing of erroneous values for arguments. However,
 * it had slipped my mind that type is enforced with C++ enums, so passing of
 * correct arguments would have been ensured anyway. Duh.
 *
 * Still, enums seem a little clunky, so maybe this is better. We'll see.
 *
 * Also, these should go in their own file, but I couldn't think of a name for
 * it. And finally, they should probably be taken out of the detail namespace,
 * as users may want to declare variables of these types. The only issue with
 * that is that some functions have argument names that are the same as the
 * class names, so those will probably have to be revised.
 *
 * Update: Ok, I backed myself into a bit of a corner here and had to do some
 * hackery to get myself out. In short, I made the helper object global, which
 * worked fine within an Xcode project, but not (I think) in the CML as a
 * standalone library.
 *
 * Rather than re-write a lot of code, I did some hacks in this file so that
 * the code elsewhere would only require minimal changes. The motivation was
 * basically to avoid yet another delay in getting the library out, but once
 * things have settled down a bit I'll redo all this. From the user's
 * perspective, all that really matters is that there is some constant or
 * global or static object that can be passed to represent a particular
 * handedness, Euler-angle order, or what have you. Once we've settled on a
 * syntax for this, updating user code to reflect it should be a simple matter
 * of a few search-and-replace's.
 */

/** A class to represent Euler angle orders */
template < class T > // Hack
class euler_order_
{
public:

    euler_order_(size_t first, bool odd, bool repeat)
        : m_odd(odd), m_repeat(repeat)
    {
        // TODO: reverse_cyclic_permutation()? reverse argument?
        //cyclic_permutation(first, m_i, m_j, m_k);
        // TODO: Use cyclic_permutation(), but currently having a problem
        // including util.h.
        m_i = first;
        m_j = (m_i + 1) % 3;
        m_k = (m_i + 2) % 3;
        //if (m_odd) { std::swap(m_j,m_k); }
        // TODO: Use std::swap (ouch)
        if (m_odd) {
            size_t temp = m_j;
            m_j = m_k;
            m_k = temp;
        }
    }
    
    size_t i() const { return m_i; }
    size_t j() const { return m_j; }
    size_t k() const { return m_k; }
    bool odd() const { return m_odd; }
    bool repeat() const { return m_repeat; }

    static const euler_order_ xyz;
    static const euler_order_ xzy;
    static const euler_order_ xyx;
    static const euler_order_ xzx;
    static const euler_order_ yzx;
    static const euler_order_ yxz;
    static const euler_order_ yzy;
    static const euler_order_ yxy;
    static const euler_order_ zxy;
    static const euler_order_ zyx;
    static const euler_order_ zxz;
    static const euler_order_ zyz;

protected:

    size_t m_i;
    size_t m_j;
    size_t m_k;
    bool   m_odd;
    bool   m_repeat;
};

template< class T > const euler_order_<T> euler_order_<T>::xyz(0,false,false);
template< class T > const euler_order_<T> euler_order_<T>::xzy(0,true, false);
template< class T > const euler_order_<T> euler_order_<T>::xyx(0,false,true );
template< class T > const euler_order_<T> euler_order_<T>::xzx(0,true, true );
template< class T > const euler_order_<T> euler_order_<T>::yzx(1,false,false);
template< class T > const euler_order_<T> euler_order_<T>::yxz(1,true, false);
template< class T > const euler_order_<T> euler_order_<T>::yzy(1,false,true );
template< class T > const euler_order_<T> euler_order_<T>::yxy(1,true, true );
template< class T > const euler_order_<T> euler_order_<T>::zxy(2,false,false);
template< class T > const euler_order_<T> euler_order_<T>::zyx(2,true, false);
template< class T > const euler_order_<T> euler_order_<T>::zxz(2,false,true );
template< class T > const euler_order_<T> euler_order_<T>::zyz(2,true, true );

typedef euler_order_<size_t> euler_order; // Hack

/** A class to represent axis orders (non-repeating) */
template < class T > // Hack
class axis_order_ : public euler_order_<T>
{
public:

    axis_order_(size_t first, bool odd) : euler_order_<T>(first, odd, false) {}
    axis_order_ swapped() const {
        return axis_order_(this->m_j, !(this->m_odd));
    }
    
    static const axis_order_ xyz;
    static const axis_order_ xzy;
    static const axis_order_ yzx;
    static const axis_order_ yxz;
    static const axis_order_ zxy;
    static const axis_order_ zyx;
};

template< class T > const axis_order_<T> axis_order_<T>::xyz(0,false);
template< class T > const axis_order_<T> axis_order_<T>::xzy(0,true );
template< class T > const axis_order_<T> axis_order_<T>::yzx(1,false);
template< class T > const axis_order_<T> axis_order_<T>::yxz(1,true );
template< class T > const axis_order_<T> axis_order_<T>::zxy(2,false);
template< class T > const axis_order_<T> axis_order_<T>::zyx(2,true );

typedef axis_order_<size_t> axis_order; // Hack

/** A class to represent 2D axis orders (non-repeating) */
template < class T > // Hack
class axis_order_2D_
{
public:

    axis_order_2D_(size_t first) : m_i(first), m_j((first+1) % 2) {}
    
    size_t i() const { return m_i; }
    size_t j() const { return m_j; }
    bool odd() const { return m_i == 1; }
    
    static const axis_order_2D_ xy;
    static const axis_order_2D_ yx;

private:

    size_t m_i;
    size_t m_j;
};

template< class T > const axis_order_2D_<T> axis_order_2D_<T>::xy(0);
template< class T > const axis_order_2D_<T> axis_order_2D_<T>::yx(1);

typedef axis_order_2D_<size_t> axis_order_2D; // Hack

/** A class to represent the handedness of a coordinate system */
template < class T > // Hack
class handedness_ {
    public : handedness_(bool left) : m_sign(left ? 1 : -1) {}
    public : template < class S > S sign() const { return S(m_sign); }
    private: int m_sign;
    
    public: static const handedness_ left_handed;
    public: static const handedness_ right_handed;
};

template< class T > const handedness_<T> handedness_<T>::left_handed(true);
template< class T > const handedness_<T> handedness_<T>::right_handed(false);

typedef handedness_<size_t> handedness; // Hack

/** A class to represent the z-clipping range of a projection matrix */
template < class T > // Hack
class z_clip_ {
    public : z_clip_(bool neg_one) : m_clip(neg_one ? -1 : 0) {}
    public : int clip() const { return m_clip; }
    private: int m_clip;
    
    public: static const z_clip_ neg_one;
    public: static const z_clip_ zero;
};

template< class T > const z_clip_<T> z_clip_<T>::neg_one(true);
template< class T > const z_clip_<T> z_clip_<T>::zero(false);

typedef z_clip_<size_t> z_clip; // Hack

/** A class to represent the type for spherical coordinate conversion */
template < class T > // Hack
class spherical_type_ {
    public : spherical_type_(bool latitude) : m_latitude(latitude) {}
    public : template < class S > S convert(S phi) const {
        return m_latitude ? constants<S>::pi_over_2() - phi : phi;
    }
    private: bool m_latitude;
    
    public: static const spherical_type_ latitude;
    public: static const spherical_type_ colatitude;
};

template< class T > const spherical_type_<T> spherical_type_<T>::latitude(true);
template< class T > const spherical_type_<T> spherical_type_<T>::colatitude(false);

typedef spherical_type_<size_t> spherical_type; // Hack

} // namespace cml

#endif
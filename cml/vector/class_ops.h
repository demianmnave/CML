/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 *  @brief Vector class operators.
 */

#ifndef vector_class_ops_h
#define vector_class_ops_h

/** Copy-construct a vector.
 *
 * @note This is required for GCC4, otherwise it won't elide the copy
 * constructor.
 *
 * @bug Make sure that either eliding the copy constructor for dynamic
 * arrays is safe, or  the compiler doesn't elide the copy constructor.
 */
#define CML_VEC_COPY_FROM_VECTYPE(_add_)                            \
vector(const vector_type& v) _add_ {                                \
    typedef et::OpAssign<Element,Element> OpT;                      \
    et::UnrollAssignment<OpT>(*this,v);                             \
}

/** Construct from an arbitrary vector.
 *
 * @param v the vector to copy from.
 */
#define CML_VEC_COPY_FROM_VEC                                       \
template<typename E, class AT>                                      \
vector(const vector<E,AT>& m) {                                     \
    typedef et::OpAssign<Element,E> OpT;                            \
    et::UnrollAssignment<OpT>(*this,m);                             \
}

/** Construct from a vector expression.
 *
 * @param expr the expression to copy from.
 */
#define CML_VEC_COPY_FROM_VECXPR                                    \
template<class XprT>                                                \
vector(VECXPR_ARG_TYPE e) {                                         \
    /* Verify that a promotion exists at compile time: */           \
    typedef typename et::VectorPromote<                             \
        vector_type, typename XprT::result_type>::type result_type; \
    typedef typename XprT::value_type src_value_type;               \
    typedef et::OpAssign<Element,src_value_type> OpT;               \
    et::UnrollAssignment<OpT>(*this,e);                             \
}

/** Assign from the same vector type.
 *
 * @param v the vector to copy from.
 */
#define CML_VEC_ASSIGN_FROM_VECTYPE                                 \
vector_type& operator=(const vector_type& v) {                      \
    typedef et::OpAssign<Element,Element> OpT;                      \
    et::UnrollAssignment<OpT>(*this,v);                             \
    return *this;                                                   \
}

/** Assign this vector from another using the given elementwise op.
 *
 * This allows assignment from arbitrary vector types.
 *
 * @param _op_ the operator (e.g. +=)
 * @param _op_name_ the op functor (e.g. et::OpAssign)
 */
#define CML_VEC_ASSIGN_FROM_VEC(_op_, _op_name_)                    \
template<typename E, class AT> vector_type&                         \
operator _op_ (const cml::vector<E,AT>& m) {                        \
    typedef _op_name_ <Element,E> OpT;                              \
    cml::et::UnrollAssignment<OpT>(*this,m);                        \
    return *this;                                                   \
}

/** Declare a function to assign this vector from a vector expression.
 *
 * @param _op_ the operator (e.g. +=)
 * @param _op_name_ the op functor (e.g. et::OpAssign)
 */
#define CML_VEC_ASSIGN_FROM_VECXPR(_op_, _op_name_)                 \
template<class XprT> vector_type&                                   \
operator _op_ (VECXPR_ARG_TYPE e) {                                 \
    /* Verify that a promotion exists at compile time: */           \
    typedef typename et::VectorPromote<                             \
        vector_type, typename XprT::result_type>::type result_type; \
    typedef typename XprT::value_type src_value_type;               \
    typedef _op_name_ <Element,src_value_type> OpT;                 \
    cml::et::UnrollAssignment<OpT>(*this,e);                        \
    return *this;                                                   \
}

/** Declare a function to assign this vector from a scalar.
 *
 * @param _op_ the operator (e.g. *=)
 * @param _op_name_ the op functor (e.g. et::OpAssign)
 *
 * @internal This shouldn't be used for ops, like +=, which aren't
 * defined in vector algebra.
 */
#define CML_VEC_ASSIGN_FROM_SCALAR(_op_, _op_name_)                 \
vector_type& operator _op_ (const value_type s) {                   \
    typedef _op_name_ <Element,Element> OpT;                        \
    cml::et::UnrollAssignment<OpT>(*this,s);                        \
    return *this;                                                   \
}

#endif

// -------------------------------------------------------------------------
// vim:ft=cpp

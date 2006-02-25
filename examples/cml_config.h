/* An example config file. */
/* A config file is generally the way to define configuration macros.  This
 * should be done automatically, though, not by the user:
 */
#define CML_NO_DEFAULT_EXPR_TRAITS
#define CML_VECTOR_UNROLL_LIMIT 25
#define CML_NO_2D_UNROLLER
//#define CML_IGNORE_VECTOR_ORIENTATION
#define CML_ENFORCE_VECTOR_ORIENTATION_ON_COPY
#define CML_DEFAULT_ARRAY_LAYOUT cml::row_major
#define CML_ALWAYS_PROMOTE_TO_DEFAULT_LAYOUT
#define CML_DEFAULT_ARRAY_ALLOC std::allocator<void>

/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <iostream>
#include <cml/vector/fixed.h>
#include <cml/vector/fixed_external.h>

/* Testing headers: */
#define BOOST_TEST_MODULE scalar_node1
#include <boost/test/included/unit_test.hpp>


namespace cml {

namespace op {

template<class Scalar1, class Scalar2>
struct binary_multiply
{
  typedef decltype(Scalar1() * Scalar2()) result_type;
  result_type apply(const Scalar1& v1, const Scalar2& v2) const { return v1*v2; }
};

template<class Scalar1, class Scalar2>
struct binary_divide
{
  typedef decltype(Scalar1() / Scalar2()) result_type;
  result_type apply(const Scalar1& v1, const Scalar2& v2) const { return v1/v2; }
};

} // namespace op



template<class SubNode, class Scalar, class Op> class vector_scalar_node;

template<class SubNode, class Scalar, class Op>
struct vector_traits< vector_scalar_node<SubNode,Scalar,Op> >
{
  typedef typename Op::result_type			value_type;
  typedef value_type					immutable_value;
};

template<class SubNode, class Scalar, class Op>
class vector_scalar_node
: public readable_vector< vector_scalar_node<SubNode,Scalar,Op> >
{
  public:

    typedef vector_scalar_node<SubNode,Scalar,Op>	node_type;
    typedef vector_traits<node_type>			traits_type;
    typedef typename traits_type::value_type		value_type;
    typedef typename traits_type::immutable_value	immutable_value;


  public:

    explicit vector_scalar_node(const SubNode& sub, const Scalar& v)
      : m_sub(sub), m_v(v) {}


  public:

    int size() const { return m_sub.size(); }

    immutable_value get(int i) const {
      return Op().apply(m_sub.get(i), m_v);
    }


  protected:

    const SubNode&		m_sub;
    const Scalar		m_v;
};

template<class Readable, class Scalar> auto
operator*(
  const readable_vector<Readable>& sub,
  const Scalar&			   v
  )
-> vector_scalar_node<Readable, Scalar,
  op::binary_multiply<typename Readable::value_type, Scalar>>
{
  return vector_scalar_node<Readable, Scalar, op::binary_multiply<
    typename Readable::value_type, Scalar>>(sub,v);
}

template<class Readable, class Scalar> auto
operator*(
  const Scalar&			   v,
  const readable_vector<Readable>& sub
  )
-> decltype(operator*(sub,v))
{
  return operator*(sub,v);
}

template<class Readable, class Scalar> auto
operator/(
  const readable_vector<Readable>& sub,
  const Scalar&			   v
  )
-> vector_scalar_node<Readable, Scalar,
  op::binary_divide<typename Readable::value_type, Scalar>>
{
  return vector_scalar_node<Readable, Scalar, op::binary_divide<
    typename Readable::value_type, Scalar>>(sub,v);
}

} // namespace cml


BOOST_AUTO_TEST_CASE(scalar_multiply1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  auto xpr = 2.*v1;
  BOOST_CHECK_EQUAL(xpr.size(), 3);
  BOOST_CHECK_EQUAL(xpr[0], 2.);
  BOOST_CHECK_EQUAL(xpr[1], 4.);
  BOOST_CHECK_EQUAL(xpr[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_multiply2)
{
  double av1[] = { 1., 2., 3. };
  cml::vector<double, cml::external<3>> v1(av1);
  auto xpr = 2.*v1;
  BOOST_CHECK_EQUAL(xpr.size(), 3);
  BOOST_CHECK_EQUAL(xpr[0], 2.);
  BOOST_CHECK_EQUAL(xpr[1], 4.);
  BOOST_CHECK_EQUAL(xpr[2], 6.);
}

BOOST_AUTO_TEST_CASE(scalar_divide1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 2., 4., 6. };
  auto xpr = v1/2.;
  BOOST_CHECK_EQUAL(xpr.size(), 3);
  BOOST_CHECK_EQUAL(xpr[0], 1.);
  BOOST_CHECK_EQUAL(xpr[1], 2.);
  BOOST_CHECK_EQUAL(xpr[2], 3.);
}

BOOST_AUTO_TEST_CASE(scalar_divide2)
{
  double av1[] = { 2., 4., 6. };
  cml::vector<double, cml::external<3>> v1(av1);
  auto xpr = v1/2.;
  BOOST_CHECK_EQUAL(xpr.size(), 3);
  BOOST_CHECK_EQUAL(xpr[0], 1.);
  BOOST_CHECK_EQUAL(xpr[1], 2.);
  BOOST_CHECK_EQUAL(xpr[2], 3.);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2

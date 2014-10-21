/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/vector/fixed.h>
#include <cml/vector/fixed_external.h>

/* Testing headers: */
#define BOOST_TEST_MODULE binary_node1
#include <boost/test/included/unit_test.hpp>


namespace cml {

namespace op {

template<class Scalar1, class Scalar2>
struct binary_minus
{
  typedef decltype(Scalar1() - Scalar2()) result_type;
  result_type apply(const Scalar1& v1, const Scalar2& v2) const { return v1-v2; }
};

template<class Scalar1, class Scalar2>
struct binary_plus
{
  typedef decltype(Scalar1() + Scalar2()) result_type;
  result_type apply(const Scalar1& v1, const Scalar2& v2) const { return v1+v2; }
};

} // namespace op



template<class SubNode1, class SubNode2, class Op> class vector_binary_node;

template<class SubNode1, class SubNode2, class Op>
struct vector_traits< vector_binary_node<SubNode1,SubNode2,Op> >
{
  typedef typename Op::result_type			value_type;
  typedef value_type					immutable_value;
};

template<class SubNode1, class SubNode2, class Op>
class vector_binary_node
: public readable_vector< vector_binary_node<SubNode1,SubNode2,Op> >
{
  public:

    typedef vector_binary_node<SubNode1,SubNode2,Op>	node_type;
    typedef vector_traits<node_type>			traits_type;
    typedef typename traits_type::value_type		value_type;
    typedef typename traits_type::immutable_value	immutable_value;


  public:

    explicit vector_binary_node(const SubNode1& sub1, const SubNode2& sub2)
      : m_sub1(sub1), m_sub2(sub2)
      {
	// cml::require_same_size(sub1, sub2);
      }


  public:

    int size() const { return m_sub1.size(); }

    immutable_value get(int i) const {
      return Op().apply(m_sub1.get(i), m_sub2.get(i));
    }


  protected:

    const SubNode1&		m_sub1;
    const SubNode2&		m_sub2;
};

template<class Readable1, class Readable2> auto
operator-(
  const readable_vector<Readable1>& sub1,
  const readable_vector<Readable2>& sub2
  )
-> vector_binary_node<Readable1, Readable2, op::binary_minus<
  typename Readable1::value_type, typename Readable2::value_type>>
{
  return vector_binary_node<Readable1, Readable2, op::binary_minus<
    typename Readable1::value_type, typename Readable2::value_type>>(sub1,sub2);
}

template<class Readable1, class Readable2> auto
operator+(
  const readable_vector<Readable1>& sub1,
  const readable_vector<Readable2>& sub2
  )
-> vector_binary_node<Readable1, Readable2, op::binary_plus<
  typename Readable1::value_type, typename Readable2::value_type>>
{
  return vector_binary_node<Readable1, Readable2, op::binary_plus<
    typename Readable1::value_type, typename Readable2::value_type>>(sub1,sub2);
}

} // namespace cml


BOOST_AUTO_TEST_CASE(binary_minus1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> v2 = { 4., 5., 6. };
  auto xpr = v1 - v2;
  BOOST_CHECK_EQUAL(xpr.size(), 3);
  BOOST_CHECK_EQUAL(xpr[0], -3.);
  BOOST_CHECK_EQUAL(xpr[1], -3.);
  BOOST_CHECK_EQUAL(xpr[2], -3.);
}

BOOST_AUTO_TEST_CASE(binary_plus1)
{
  cml::vector<double, cml::fixed<3>> v1 = { 1., 2., 3. };
  cml::vector<double, cml::fixed<3>> v2 = { 4., 5., 6. };
  auto xpr = v1 + v2;
  BOOST_CHECK_EQUAL(xpr.size(), 3);
  BOOST_CHECK_EQUAL(xpr[0], 5.);
  BOOST_CHECK_EQUAL(xpr[1], 7.);
  BOOST_CHECK_EQUAL(xpr[2], 9.);
}

BOOST_AUTO_TEST_CASE(binary_minus2)
{
  double av1[] = { 1., 2., 3. };
  cml::vector<double, cml::external<3>> v1(av1);
  cml::vector<double, cml::fixed<3>> v2 = { 4., 5., 6. };
  auto xpr = v1 - v2;
  BOOST_CHECK_EQUAL(xpr.size(), 3);
  BOOST_CHECK_EQUAL(xpr[0], -3.);
  BOOST_CHECK_EQUAL(xpr[1], -3.);
  BOOST_CHECK_EQUAL(xpr[2], -3.);
}

BOOST_AUTO_TEST_CASE(binary_plus2)
{
  double av1[] = { 1., 2., 3. };
  cml::vector<double, cml::external<3>> v1(av1);
  cml::vector<double, cml::fixed<3>> v2 = { 4., 5., 6. };
  auto xpr = v1 + v2;
  BOOST_CHECK_EQUAL(xpr.size(), 3);
  BOOST_CHECK_EQUAL(xpr[0], 5.);
  BOOST_CHECK_EQUAL(xpr[1], 7.);
  BOOST_CHECK_EQUAL(xpr[2], 9.);
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2

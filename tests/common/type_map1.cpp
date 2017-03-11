/* -*- C++ -*- ------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/
/** @file
 */

#include <cml/common/mpl/type_map.h>

/* Testing headers: */
#define BOOST_TEST_MODULE type_map1
#include <boost/test/unit_test.hpp>

template<class T1, class T2>
struct table_item
{
  typedef T1 first;
  typedef T2 second;
};

BOOST_AUTO_TEST_CASE(map1)
{
  using cml::type_map;
  typedef type_map<
    /**/  table_item<int,int>
    ,     table_item<float,int>
    ,     table_item<double,int>
    > int_table;

  typedef int_table::find_second<int>::type Ti;
  BOOST_CHECK(Ti::value);
  BOOST_CHECK((std::is_same<Ti::type, int>::value));

  typedef int_table::find_first<int>::type Ti2;
  BOOST_CHECK(Ti2::value);
  BOOST_CHECK((std::is_same<Ti2::type, int>::value));

  typedef int_table::find_first<float>::type Tf1;
  BOOST_CHECK(Tf1::value);
  BOOST_CHECK((std::is_same<Tf1::type, int>::value));

  typedef int_table::find_second<float>::type Tf2;
  BOOST_CHECK(!Tf2::value);
  BOOST_CHECK((std::is_same<Tf2::type, void>::value));

  typedef int_table::find_first<double>::type Td1;
  BOOST_CHECK(Td1::value);
  BOOST_CHECK((std::is_same<Td1::type, int>::value));

  typedef int_table::find_second<double>::type Td2;
  BOOST_CHECK(!Td2::value);
  BOOST_CHECK((std::is_same<Td2::type, void>::value));
}

// -------------------------------------------------------------------------
// vim:ft=cpp:sw=2

/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#include <cml/common/mpl/type_map.h>

/* Testing headers: */
#include "catch_runner.h"

template<class T1, class T2> struct table_item
{
  using first = T1;
  using second = T2;
};

CATCH_TEST_CASE("map1")
{
  using cml::type_map;
  using int_table = type_map<
    /**/ table_item<int, int>, table_item<float, int>, table_item<double, int>>;

  using Ti = int_table::find_second<int>::type;
  CATCH_CHECK(Ti::value);
  CATCH_CHECK((std::is_same<Ti::type, int>::value));

  using Ti2 = int_table::find_first<int>::type;
  CATCH_CHECK(Ti2::value);
  CATCH_CHECK((std::is_same<Ti2::type, int>::value));

  using Tf1 = int_table::find_first<float>::type;
  CATCH_CHECK(Tf1::value);
  CATCH_CHECK((std::is_same<Tf1::type, int>::value));

  using Tf2 = int_table::find_second<float>::type;
  CATCH_CHECK(!Tf2::value);
  CATCH_CHECK((std::is_same<Tf2::type, void>::value));

  using Td1 = int_table::find_first<double>::type;
  CATCH_CHECK(Td1::value);
  CATCH_CHECK((std::is_same<Td1::type, int>::value));

  using Td2 = int_table::find_second<double>::type;
  CATCH_CHECK(!Td2::value);
  CATCH_CHECK((std::is_same<Td2::type, void>::value));
}

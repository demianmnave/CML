/*-------------------------------------------------------------------------
 @@COPYRIGHT@@
 *-----------------------------------------------------------------------*/

#include <cml/common/mpl/type_table.h>

/* Testing headers: */
#include "catch_runner.h"

template<class T1, class T2, class T> struct table_item
{
  using first = T1;
  using second = T2;
  using type = T;
};

CATCH_TEST_CASE("map1")
{
  using cml::type_table;
  using int_table = type_table<
    /**/ table_item<int, int, int>, table_item<int, float, float>,
    table_item<int, double, double>>;

  using Tii = int_table::find<int, int>::type;
  CATCH_CHECK(Tii::value);

  using Tid = int_table::find<int, double>::type;
  CATCH_CHECK(Tid::value);

  using Tdi = int_table::find<double, int>::type;
  CATCH_CHECK(Tdi::value);

  using Tic = int_table::find<int, char>::type;
  CATCH_CHECK(!Tic::value);

  using Tic = int_table::find<char, int>::type;
  CATCH_CHECK(!Tic::value);
}

struct map_struct
{
  template<class T1, class T2, class T> struct table_item
  {
    using first = T1;
    using second = T2;
    using type = T;
  };

  using int_table = cml::type_table<
    /**/ table_item<int, int, int>, table_item<int, float, float>,
    table_item<int, double, double>>;
};

CATCH_TEST_CASE("map_struct1")
{
  using int_table = map_struct::int_table;

  using Tii = int_table::find<int, int>::type;
  CATCH_CHECK(Tii::value);

  using Tid = int_table::find<int, double>::type;
  CATCH_CHECK(Tid::value);

  using Tdi = int_table::find<double, int>::type;
  CATCH_CHECK(Tdi::value);

  using Tic = int_table::find<int, char>::type;
  CATCH_CHECK(!Tic::value);

  using Tic = int_table::find<char, int>::type;
  CATCH_CHECK(!Tic::value);
}

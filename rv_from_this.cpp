#include <typeinfo>
#include <iostream>
#include <cml/cml.h>

int main()
{
#if 1
  {
    typedef cml::vector<double,cml::fixed<3>> vector3_t;
    auto xpr = vector3_t().cardinal(0) + 5.*vector3_t(1.,1.,1.);
    std::clog << typeid(xpr).name() << std::endl;
    std::clog << "...1" << std::endl;
    std::clog << xpr[0] << std::endl;
    std::clog << "...2" << std::endl;
  }
  std::clog << "...3" << std::endl;
#endif

#if 0
  auto xpr = cml::vector<double,cml::fixed<3>>(1., 2., 3.).zero();
  std::clog << typeid(xpr).name() << std::endl;
  std::clog << xpr[0] << std::endl;
#endif

#if 0
  std::clog
    << (cml::vector<double,cml::fixed<3>>(1., 2., 3.).zero())[0]
    << std::endl;
#endif

#if 0
  typedef cml::vector<double,cml::fixed<3>> vector3_t;
  vector3_t v1; v1.zero();
  auto xpr = v1 + 5.*vector3_t(1.,1.,1.);
  std::clog << typeid(xpr).name() << std::endl;
  std::clog << xpr[0] << std::endl;
#endif
}

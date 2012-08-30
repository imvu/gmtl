// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

// This file was originally part of PyJuggler.

// PyJuggler is (C) Copyright 2002, 2003 by Patrick Hartling
// Distributed under the GNU Lesser General Public License 2.1.  (See
// accompanying file COPYING.txt or http://www.gnu.org/copyleft/lesser.txt)

// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl/Math.h>

// Using =======================================================================
using namespace boost::python;

// Declarations ================================================================


namespace gmtlWrappers
{
   template<typename T, typename U>
   T lerp(const U& lerp, const T& a, const T& b)
   {
      T result;
      gmtl::Math::lerp(result, lerp, a, b);
      return result;
   }

   template<typename T>
   tuple quadraticFormula(const T& a, const T& b, const T& c)
   {
      T r1, r2;
      bool result = gmtl::Math::quadraticFormula(r1, r2, a, b, c);
      return make_tuple(result, r1, r2);
   }
}

namespace
{

class Fake : public boost::noncopyable
{
};

}


// Module ======================================================================
void _Export_gmtl_Math_h()
{
    // Retained (temporarily) for backwards compatibility.
    def("deg2Rad", (double (*)(double))&gmtl::Math::deg2Rad);
    def("deg2Rad", (float (*)(float))&gmtl::Math::deg2Rad);
    def("rad2Deg", (float (*)(float))&gmtl::Math::rad2Deg);
    def("rad2Deg", (double (*)(double))&gmtl::Math::rad2Deg);

    scope* gmtl_Math_scope = new scope(
    class_< Fake, boost::noncopyable >("Math", no_init)
        .def("sign", (int (*)(int)) &gmtl::Math::sign)
        .def("sign", (int (*)(float)) &gmtl::Math::sign)
        .def("sign", (int (*)(double)) &gmtl::Math::sign)
        .def("fastInvSqrt", &gmtl::Math::fastInvSqrt)
        .def("fastInvSqrt2", &gmtl::Math::fastInvSqrt2)
        .def("fastInvSqrt3", &gmtl::Math::fastInvSqrt3)
        .def("deg2Rad", (double (*)(double))&gmtl::Math::deg2Rad)
        .def("deg2Rad", (float (*)(float))&gmtl::Math::deg2Rad)
        .def("rad2Deg", (float (*)(float))&gmtl::Math::rad2Deg)
        .def("rad2Deg", (double (*)(double))&gmtl::Math::rad2Deg)
        .def("factorial", (double (*)(double)) &gmtl::Math::factorial)
        .def("factorial", (float (*)(float)) &gmtl::Math::factorial)
        .def("factorial", (int (*)(int)) &gmtl::Math::factorial)
        .def("lerp",
            (double (*)(const double&, const double&, const double&)) &gmtlWrappers::lerp)
        .def("lerp",
            (float (*)(const float&, const float&, const float&)) &gmtlWrappers::lerp)
        .def("quadraticFormula",
            (tuple (*)(const double&, const double&, const double&)) &gmtlWrappers::quadraticFormula)
        .def("quadraticFormula",
            (tuple (*)(const float&, const float&, const float&)) &gmtlWrappers::quadraticFormula)
        .staticmethod("sign")
        .staticmethod("fastInvSqrt")
        .staticmethod("fastInvSqrt2")
        .staticmethod("fastInvSqrt3")
        .staticmethod("deg2Rad")
        .staticmethod("rad2Deg")
        .staticmethod("factorial")
        .staticmethod("lerp")
        .staticmethod("quadraticFormula")
    );

    delete gmtl_Math_scope;
}

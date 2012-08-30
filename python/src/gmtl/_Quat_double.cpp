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
#include <gmtl/Quat.h>
#include <gmtl/Output.h>
#include <gmtl-wrappers.h>
#include <gmtl-getData-wrappers.h>
#include <gmtl-pickle.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_Quat_double()
{
    scope* gmtl_Quat_double_scope = new scope(
    class_< gmtl::Quat<double> >("Quatd", init<  >())
        .def(init< const double&, const double&, const double&, const double& >())
        .def(init< const gmtl::Quat<double> & >())
        .def("set", &gmtl::Quat<double>::set)
        .def("get", &gmtl::Quat<double>::get)
        .def("getData", (tuple (*)(gmtl::Quat<double>*)) &gmtlWrappers::Quat_getData)
        .def("set",
             (gmtl::Quat<double>& (gmtl::Quat<double>::*)(const gmtl::Quat<double>&)) &gmtl::Quat<double>::operator=,
             return_internal_reference<1>())
        .add_property("data", (tuple (*)(gmtl::Quat<double>*)) &gmtlWrappers::Quat_getData)
        .def("__getitem__", (double& (gmtl::Quat<double>::*)(const int)) &gmtl::Quat<double>::operator[], return_value_policy<copy_non_const_reference>())
        .def("__setitem__", (void (*)(gmtl::Quatd*, const unsigned, double)) &gmtlWrappers::setArrayElement)
        .def_pickle(gmtlPickle::Quat_pickle<double>())
        .def(self * self)
        .def(self *= self)
        .def(-self)
        .def(self * gmtl::Vec3d())
        .def(self * double())
        .def(self *= double())
        .def(self / self)
        .def(self /= self)
        .def(self / double())
//        .def(self /= double())
        .def(self + self)
        .def(self += self)
        .def(self - self)
        .def(self -= self)
        .def(self == self)
        .def(self != self)
        .def(self_ns::str(self))
    );

    enum_< gmtl::Quat<double>::Params >("Params")
        .value("Size", gmtl::Quat<double>::Size)
    ;

    delete gmtl_Quat_double_scope;

}

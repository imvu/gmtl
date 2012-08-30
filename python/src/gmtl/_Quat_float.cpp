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
void _Export_Quat_float()
{
    scope* gmtl_Quat_float_scope = new scope(
    class_< gmtl::Quat<float> >("Quatf", init<  >())
        .def(init< const float&, const float&, const float&, const float& >())
        .def(init< const gmtl::Quat<float> & >())
        .def("set", &gmtl::Quat<float>::set)
        .def("get", &gmtl::Quat<float>::get)
        .def("getData", (tuple (*)(gmtl::Quat<float>*)) &gmtlWrappers::Quat_getData)
        .def("set",
             (gmtl::Quat<float>& (gmtl::Quat<float>::*)(const gmtl::Quat<float>&)) &gmtl::Quat<float>::operator=,
             return_internal_reference<1>())
        .add_property("data", (tuple (*)(gmtl::Quat<float>*)) &gmtlWrappers::Quat_getData)
        .def("__getitem__", (float& (gmtl::Quat<float>::*)(const int)) &gmtl::Quat<float>::operator[], return_value_policy<copy_non_const_reference>())
        .def("__setitem__", (void (*)(gmtl::Quatf*, const unsigned, float)) &gmtlWrappers::setArrayElement)
        .def_pickle(gmtlPickle::Quat_pickle<float>())
        .def(self * self)
        .def(self *= self)
        .def(-self)
        .def(self * gmtl::Vec3f())
        .def(self * float())
        .def(self *= float())
        .def(self / self)
        .def(self /= self)
        .def(self / float())
//        .def(self /= float())
        .def(self + self)
        .def(self += self)
        .def(self - self)
        .def(self -= self)
        .def(self == self)
        .def(self != self)
        .def(self_ns::str(self))
    );

    enum_< gmtl::Quat<float>::Params >("Params")
        .value("Size", gmtl::Quat<float>::Size)
    ;

    delete gmtl_Quat_float_scope;

}

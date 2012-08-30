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
#include <gmtl/VecBase.h>
#include <gmtl/Output.h>
#include <gmtl-wrappers.h>
#include <gmtl-array-wrappers.h>
#include <gmtl-getData-wrappers.h>
#include <gmtl-pickle.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_VecBase_float_3()
{
    scope* gmtl_VecBase_float_3_scope = new scope(
    class_< gmtl::VecBase<float,3> >("VecBase3f", init<  >())
        .def(init< const gmtl::VecBase<float,3> & >())
        .def(init< const float &, const float &, const float & >())
        .def("set", (void (gmtl::VecBase<float,3>::*)(const float &, const float &, const float &) )&gmtl::VecBase<float,3>::set)
        .def("set", (void (*)(gmtl::VecBase<float,3>*, list))&gmtlWrappers::VecBase_set)
        .def("set",
             (gmtl::VecBase<float,3>& (gmtl::VecBase<float,3>::*)(const gmtl::VecBase<float,3>&)) &gmtl::VecBase<float,3>::operator=,
             return_internal_reference<1>())
        .def("getData", (tuple (*)(gmtl::VecBase<float,3>*)) &gmtlWrappers::VecBase_3_getData)
        .add_property("data", (tuple (*)(gmtl::VecBase<float,3>*)) &gmtlWrappers::VecBase_3_getData)
        .def("__getitem__", (float& (gmtl::VecBase<float,3>::*)(const unsigned) ) &gmtl::VecBase<float,3>::operator[], return_value_policy<copy_non_const_reference>())
        .def("__setitem__", (void (*)(gmtl::VecBase<float,3>*, const unsigned, float)) &gmtlWrappers::setArrayElement)
        .def_pickle(gmtlPickle::VecBase3_pickle<float>())
        .def(-self)
        .def(self += self)
        .def(self + self)
        .def(self -= self)
        .def(self - self)
        .def(self *= float())
        .def(self * float())
        .def(float() * self)
        .def(self /= float())
        .def(self / float())
        .def(self == self)
        .def(self != self)
        .def(self_ns::str(self))
    );

    enum_< gmtl::VecBase<float,3>::Params >("Params")
        .value("Size", gmtl::VecBase<float,3>::Size)
    ;

    delete gmtl_VecBase_float_3_scope;

}

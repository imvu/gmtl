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
#include <gmtl/EulerAngle.h>
#include <gmtl/EulerAngleOps.h>
#include <gmtl/Output.h>
#include <gmtl-wrappers.h>
#include <gmtl-getData-wrappers.h>
#include <gmtl-pickle.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_EulerAngle_float_gmtl_ZXY()
{
    scope* gmtl_EulerAngle_float_gmtl_ZXY_scope = new scope(
    class_< gmtl::EulerAngle<float,gmtl::ZXY> >("EulerAngleZXYf", init<  >())
        .def(init< const gmtl::EulerAngle<float,gmtl::ZXY> & >())
        .def(init< float, float, float >())
        .def("set", &gmtl::EulerAngle<float,gmtl::ZXY>::set)
        .def("getData", (tuple (*)(gmtl::EulerAngle<float,gmtl::ZXY>*)) &gmtlWrappers::EulerAngle_getData)
        .def("set",
             (gmtl::EulerAngle<float, gmtl::ZXY>& (gmtl::EulerAngle<float, gmtl::ZXY>::*)(const gmtl::EulerAngle<float, gmtl::ZXY>&)) &gmtl::EulerAngle<float, gmtl::ZXY>::operator=,
             return_internal_reference<1>())
        .add_property("data", (tuple (*)(gmtl::EulerAngle<float,gmtl::ZXY>*)) &gmtlWrappers::EulerAngle_getData)
        .def("__getitem__", (float& (gmtl::EulerAngle<float,gmtl::ZXY>::*)(const unsigned) ) &gmtl::EulerAngle<float,gmtl::ZXY>::operator[], return_value_policy<copy_non_const_reference>())
        .def("__setitem__", (void (*)(gmtl::EulerAngle<float,gmtl::ZXY>*, const unsigned, float)) &gmtlWrappers::setArrayElement)
        .def_pickle(gmtlPickle::EulerAngle_pickle<float, gmtl::ZXY>())
        .def(self == self)
        .def(self != self)
        .def(self_ns::str(self))
    );

    enum_< gmtl::EulerAngle<float,gmtl::ZXY>::Params >("Params")
        .value("Order", gmtl::EulerAngle<float,gmtl::ZXY>::Order)
        .value("Size", gmtl::EulerAngle<float,gmtl::ZXY>::Size)
    ;

    delete gmtl_EulerAngle_float_gmtl_ZXY_scope;

}

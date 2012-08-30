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
#include <gmtl/AxisAngle.h>
#include <gmtl/Output.h>
#include <gmtl-pickle.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_AxisAngle_float()
{
    scope* gmtl_AxisAngle_float_scope = new scope(
    class_< gmtl::AxisAngle<float>, bases< gmtl::VecBase<float,4> > >("AxisAnglef", init<  >())
        .def(init< const gmtl::AxisAngle<float> & >())
        .def(init< const float &, const float &, const float &, const float & >())
        .def(init< const float &, const gmtl::Vec<float,3> & >())
        .def("set", (void (gmtl::AxisAngle<float>::*)(const float &, const float &, const float &, const float &) )&gmtl::AxisAngle<float>::set)
        .def("set", (void (gmtl::AxisAngle<float>::*)(const float &, const gmtl::Vec<float,3> &) )&gmtl::AxisAngle<float>::set)
        .def("setAxis", &gmtl::AxisAngle<float>::setAxis)
        .def("setAngle", &gmtl::AxisAngle<float>::setAngle)
        .def("getAxis", &gmtl::AxisAngle<float>::getAxis)
        .def("getAngle", &gmtl::AxisAngle<float>::getAngle, return_value_policy< copy_const_reference >())
        .def("set",
             (gmtl::AxisAngle<float>& (gmtl::AxisAngle<float>::*)(const gmtl::AxisAngle<float>&)) &gmtl::AxisAngle<float>::operator=,
             return_internal_reference<1>())
        .def_pickle(gmtlPickle::AxisAngle_pickle<float>())
        .def(self == self)
        .def(self != self)
        .def(self_ns::str(self))
    );

    enum_< gmtl::AxisAngle<float>::Params >("Params")
        .value("Size", gmtl::AxisAngle<float>::Size)
    ;

    delete gmtl_AxisAngle_float_scope;

}

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
void _Export_AxisAngle_double()
{
    scope* gmtl_AxisAngle_double_scope = new scope(
    class_< gmtl::AxisAngle<double>, bases< gmtl::VecBase<double, 4> > >("AxisAngled", init<  >())
        .def(init< const gmtl::AxisAngle<double> & >())
        .def(init< const double &, const double &, const double &, const double & >())
        .def(init< const double &, const gmtl::Vec<double,3> & >())
        .def("set", (void (gmtl::AxisAngle<double>::*)(const double &, const double &, const double &, const double &) )&gmtl::AxisAngle<double>::set)
        .def("set", (void (gmtl::AxisAngle<double>::*)(const double &, const gmtl::Vec<double,3> &) )&gmtl::AxisAngle<double>::set)
        .def("setAxis", &gmtl::AxisAngle<double>::setAxis)
        .def("setAngle", &gmtl::AxisAngle<double>::setAngle)
        .def("getAxis", &gmtl::AxisAngle<double>::getAxis)
        .def("getAngle", &gmtl::AxisAngle<double>::getAngle, return_value_policy< copy_const_reference >())
        .def("set",
             (gmtl::AxisAngle<double>& (gmtl::AxisAngle<double>::*)(const gmtl::AxisAngle<double>&)) &gmtl::AxisAngle<double>::operator=,
             return_internal_reference<1>())
        .def_pickle(gmtlPickle::AxisAngle_pickle<double>())
        .def(self == self)
        .def(self != self)
        .def(self_ns::str(self))
    );

    enum_< gmtl::AxisAngle<double>::Params >("Params")
        .value("Size", gmtl::AxisAngle<double>::Size)
    ;

    delete gmtl_AxisAngle_double_scope;

}

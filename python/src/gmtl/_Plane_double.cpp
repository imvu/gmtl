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
#include <gmtl/Plane.h>
#include <gmtl/PlaneOps.h>
#include <gmtl/Output.h>
#include <gmtl-pickle.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_Plane_double()
{
    class_< gmtl::Plane<double> >("Planed", init<  >())
        .def(init< const gmtl::Point<double,3> &, const gmtl::Point<double,3> &, const gmtl::Point<double,3> & >())
        .def(init< const gmtl::Vec<double,3> &, const gmtl::Point<double,3> & >())
        .def(init< const gmtl::Vec<double,3> &, const double & >())
        .def(init< const gmtl::Plane<double> & >())
        .def_readwrite("norm", &gmtl::Plane<double>::mNorm)
        .def_readwrite("offset", &gmtl::Plane<double>::mOffset)
        .def("getNormal", &gmtl::Plane<double>::getNormal, return_value_policy< copy_const_reference >())
        .def("setNormal", &gmtl::Plane<double>::setNormal)
        .def("getOffset", &gmtl::Plane<double>::getOffset, return_value_policy< copy_const_reference >())
        .def("setOffset", &gmtl::Plane<double>::setOffset)
        .def("set",
             (gmtl::Plane<double>& (gmtl::Plane<double>::*)(const gmtl::Plane<double>&)) &gmtl::Plane<double>::operator=,
             return_internal_reference<1>())
        .def_pickle(gmtlPickle::Plane_pickle<double>())
        .def(self == self)
        .def(self != self)
        .def(self_ns::str(self))
    ;

}

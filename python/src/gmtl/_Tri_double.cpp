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
#include <gmtl/Tri.h>
#include <gmtl/TriOps.h>
#include <gmtl/Output.h>
#include <gmtl-wrappers.h>
#include <gmtl-pickle.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_Tri_double()
{
    class_< gmtl::Tri<double> >("Trid", init<  >())
        .def(init< const gmtl::Point<double,3> &, const gmtl::Point<double,3> &, const gmtl::Point<double,3> & >())
        .def(init< const gmtl::Tri<double> & >())
        .def("edge", (gmtl::Vec<double, 3> (gmtl::Tri<double>::*)(int) const) &gmtl::Tri<double>::edge)
        .def("edge", (gmtl::Vec<double, 3> (gmtl::Tri<double>::*)(int, int) const) &gmtl::Tri<double>::edge)
        .def("set", &gmtl::Tri<double>::set)
        .def("set",
             (gmtl::Tri<double>& (gmtl::Tri<double>::*)(const gmtl::Tri<double>&)) &gmtl::Tri<double>::operator=,
             return_internal_reference<1>())
        .def("__getitem__", (gmtl::Point<double, 3>& (gmtl::Tri<double>::*)(const unsigned)) &gmtl::Tri<double>::operator[], return_internal_reference< 1 >())
        .def("__setitem__", (void (*)(gmtl::Tri<double>*, const unsigned, const gmtl::Point<double, 3>&)) gmtlWrappers::setArrayElement)
        .def_pickle(gmtlPickle::Tri_pickle<double>())
        .def(self == self)
        .def(self != self)
        .def(self_ns::str(self))
    ;

}

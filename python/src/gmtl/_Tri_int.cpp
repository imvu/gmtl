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
void _Export_Tri_int()
{
    class_< gmtl::Tri<int> >("Trii", init<  >())
        .def(init< const gmtl::Point<int,3> &, const gmtl::Point<int,3> &, const gmtl::Point<int,3> & >())
        .def(init< const gmtl::Tri<int> & >())
        .def("edge", (gmtl::Vec<int, 3> (gmtl::Tri<int>::*)(int) const) &gmtl::Tri<int>::edge)
        .def("edge", (gmtl::Vec<int, 3> (gmtl::Tri<int>::*)(int, int) const) &gmtl::Tri<int>::edge)
        .def("set", &gmtl::Tri<int>::set)
        .def("set",
             (gmtl::Tri<int>& (gmtl::Tri<int>::*)(const gmtl::Tri<int>&)) &gmtl::Tri<int>::operator=,
             return_internal_reference<1>())
        .def("__getitem__", (gmtl::Point<int, 3>& (gmtl::Tri<int>::*)(const unsigned)) &gmtl::Tri<int>::operator[], return_internal_reference< 1 >())
        .def("__setitem__", (void (*)(gmtl::Tri<int>*, const unsigned, const gmtl::Point<int, 3>&)) gmtlWrappers::setArrayElement)
        .def_pickle(gmtlPickle::Tri_pickle<int>())
        .def(self == self)
        .def(self != self)
        .def(self_ns::str(self))
    ;

}

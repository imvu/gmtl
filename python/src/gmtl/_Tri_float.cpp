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
void _Export_Tri_float()
{
    class_< gmtl::Tri<float> >("Trif", init<  >())
        .def(init< const gmtl::Point<float,3> &, const gmtl::Point<float,3> &, const gmtl::Point<float,3> & >())
        .def(init< const gmtl::Tri<float> & >())
        .def("edge", (gmtl::Vec<float, 3> (gmtl::Tri<float>::*)(int) const) &gmtl::Tri<float>::edge)
        .def("edge", (gmtl::Vec<float, 3> (gmtl::Tri<float>::*)(int, int) const) &gmtl::Tri<float>::edge)
        .def("set", &gmtl::Tri<float>::set)
        .def("set",
             (gmtl::Tri<float>& (gmtl::Tri<float>::*)(const gmtl::Tri<float>&)) &gmtl::Tri<float>::operator=,
             return_internal_reference<1>())
        .def("__getitem__", (gmtl::Point<float, 3>& (gmtl::Tri<float>::*)(const unsigned)) &gmtl::Tri<float>::operator[], return_internal_reference< 1 >())
        .def("__setitem__", (void (*)(gmtl::Tri<float>*, const unsigned, const gmtl::Point<float, 3>&)) gmtlWrappers::setArrayElement)
        .def_pickle(gmtlPickle::Tri_pickle<float>())
        .def(self == self)
        .def(self != self)
        .def(self_ns::str(self))
    ;

}

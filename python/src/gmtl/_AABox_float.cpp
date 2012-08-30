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
#include <gmtl/AABox.h>
#include <gmtl/AABoxOps.h>
#include <gmtl/Output.h>
#include <gmtl-pickle.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_AABox_float()
{
    class_< gmtl::AABox<float> >("AABoxf", init<  >())
        .def(init< const gmtl::Point<float,3> &, const gmtl::Point<float,3> & >())
        .def(init< const gmtl::AABox<float> & >())
        .def_readwrite("min", &gmtl::AABox<float>::mMin)
        .def_readwrite("max", &gmtl::AABox<float>::mMax)
        .def_readwrite("empty", &gmtl::AABox<float>::mEmpty)
        .def("getMin", &gmtl::AABox<float>::getMin, return_value_policy< copy_const_reference >())
        .def("getMax", &gmtl::AABox<float>::getMax, return_value_policy< copy_const_reference >())
        .def("isEmpty", &gmtl::AABox<float>::isEmpty)
        .def("setMin", &gmtl::AABox<float>::setMin)
        .def("setMax", &gmtl::AABox<float>::setMax)
        .def("setEmpty", &gmtl::AABox<float>::setEmpty)
        .def("set",
             (gmtl::AABox<float>& (gmtl::AABox<float>::*)(const gmtl::AABox<float>&)) &gmtl::AABox<float>::operator=,
             return_internal_reference<1>())
        .def_pickle(gmtlPickle::AABox_pickle<float>())
        .def(self == self)
        .def(self != self)
        .def(self_ns::str(self))
    ;

}

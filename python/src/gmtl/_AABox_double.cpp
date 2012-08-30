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
void _Export_AABox_double()
{
    class_< gmtl::AABox<double> >("AABoxd", init<  >())
        .def(init< const gmtl::Point<double,3> &, const gmtl::Point<double,3> & >())
        .def(init< const gmtl::AABox<double> & >())
        .def_readwrite("min", &gmtl::AABox<double>::mMin)
        .def_readwrite("max", &gmtl::AABox<double>::mMax)
        .def_readwrite("empty", &gmtl::AABox<double>::mEmpty)
        .def("getMin", &gmtl::AABox<double>::getMin, return_value_policy< copy_const_reference >())
        .def("getMax", &gmtl::AABox<double>::getMax, return_value_policy< copy_const_reference >())
        .def("isEmpty", &gmtl::AABox<double>::isEmpty)
        .def("setMin", &gmtl::AABox<double>::setMin)
        .def("setMax", &gmtl::AABox<double>::setMax)
        .def("setEmpty", &gmtl::AABox<double>::setEmpty)
        .def("set",
             (gmtl::AABox<double>& (gmtl::AABox<double>::*)(const gmtl::AABox<double>&)) &gmtl::AABox<double>::operator=,
             return_internal_reference<1>())
        .def_pickle(gmtlPickle::AABox_pickle<double>())
        .def(self == self)
        .def(self != self)
        .def(self_ns::str(self))
    ;

}

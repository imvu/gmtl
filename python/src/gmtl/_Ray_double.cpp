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
#include <gmtl/Ray.h>
#include <gmtl/RayOps.h>
#include <gmtl/Xforms.h>
#include <gmtl/Output.h>
#include <gmtl-pickle.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_Ray_double()
{
    class_< gmtl::Ray<double> >("Rayd", init<  >())
        .def(init< const gmtl::Point<double,3> &, const gmtl::Vec<double,3> & >())
        .def(init< const gmtl::Ray<double> & >())
        .def_readwrite("origin", &gmtl::Ray<double>::mOrigin)
        .def_readwrite("dir", &gmtl::Ray<double>::mDir)
        .def("getOrigin", &gmtl::Ray<double>::getOrigin, return_value_policy< copy_const_reference >())
        .def("setOrigin", &gmtl::Ray<double>::setOrigin)
        .def("getDir", &gmtl::Ray<double>::getDir, return_value_policy< copy_const_reference >())
        .def("setDir", &gmtl::Ray<double>::setDir)
        .def("set",
             (gmtl::Ray<double>& (gmtl::Ray<double>::*)(const gmtl::Ray<double>&)) &gmtl::Ray<double>::operator=,
             return_internal_reference<1>())
        .def_pickle(gmtlPickle::Ray_pickle<double>())
        .def(self == self)
        .def(self != self)
        .def(self *= gmtl::Matrix<double,3,3>())
        .def(self *= gmtl::Matrix<double,4,4>())
        .def(self_ns::str(self))
    ;

}

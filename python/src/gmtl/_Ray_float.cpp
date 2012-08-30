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
void _Export_Ray_float()
{
    class_< gmtl::Ray<float> >("Rayf", init<  >())
        .def(init< const gmtl::Point<float,3> &, const gmtl::Vec<float,3> & >())
        .def(init< const gmtl::Ray<float> & >())
        .def_readwrite("origin", &gmtl::Ray<float>::mOrigin)
        .def_readwrite("dir", &gmtl::Ray<float>::mDir)
        .def("getOrigin", &gmtl::Ray<float>::getOrigin, return_value_policy< copy_const_reference >())
        .def("setOrigin", &gmtl::Ray<float>::setOrigin)
        .def("getDir", &gmtl::Ray<float>::getDir, return_value_policy< copy_const_reference >())
        .def("setDir", &gmtl::Ray<float>::setDir)
        .def("set",
             (gmtl::Ray<float>& (gmtl::Ray<float>::*)(const gmtl::Ray<float>&)) &gmtl::Ray<float>::operator=,
             return_internal_reference<1>())
        .def_pickle(gmtlPickle::Ray_pickle<double>())
        .def(self == self)
        .def(self != self)
        .def(self *= gmtl::Matrix<float,3,3>())
        .def(self *= gmtl::Matrix<float,4,4>())
        .def(self_ns::str(self))
    ;

}

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
#include <gmtl/Sphere.h>
#include <gmtl/SphereOps.h>
#include <gmtl/Output.h>
#include <gmtl-pickle.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_Sphere_double()
{
    class_< gmtl::Sphere<double> >("Sphered", init<  >())
        .def(init< const gmtl::Point<double,3> &, const double & >())
        .def(init< const gmtl::Sphere<double> & >())
        .def_readwrite("center", &gmtl::Sphere<double>::mCenter)
        .def_readwrite("radius", &gmtl::Sphere<double>::mRadius)
        .def("getCenter", &gmtl::Sphere<double>::getCenter, return_value_policy< copy_const_reference >())
        .def("getRadius", &gmtl::Sphere<double>::getRadius, return_value_policy< copy_const_reference >())
        .def("setCenter", &gmtl::Sphere<double>::setCenter)
        .def("setRadius", &gmtl::Sphere<double>::setRadius)
        .def("set",
             (gmtl::Sphere<double>& (gmtl::Sphere<double>::*)(const gmtl::Sphere<double>&)) &gmtl::Sphere<double>::operator=,
             return_internal_reference<1>())
        .def_pickle(gmtlPickle::Sphere_pickle<double>())
        .def(self == self)
        .def(self != self)
        .def(self_ns::str(self))
    ;

}

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
void _Export_Sphere_float()
{
    class_< gmtl::Sphere<float> >("Spheref", init<  >())
        .def(init< const gmtl::Point<float,3> &, const float & >())
        .def(init< const gmtl::Sphere<float> & >())
        .def_readwrite("center", &gmtl::Sphere<float>::mCenter)
        .def_readwrite("radius", &gmtl::Sphere<float>::mRadius)
        .def("getCenter", &gmtl::Sphere<float>::getCenter, return_value_policy< copy_const_reference >())
        .def("getRadius", &gmtl::Sphere<float>::getRadius, return_value_policy< copy_const_reference >())
        .def("setCenter", &gmtl::Sphere<float>::setCenter)
        .def("setRadius", &gmtl::Sphere<float>::setRadius)
        .def("set",
             (gmtl::Sphere<float>& (gmtl::Sphere<float>::*)(const gmtl::Sphere<float>&)) &gmtl::Sphere<float>::operator=,
             return_internal_reference<1>())
        .def_pickle(gmtlPickle::Sphere_pickle<float>())
        .def(self == self)
        .def(self != self)
        .def(self_ns::str(self))
    ;

}

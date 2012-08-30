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
void _Export_Plane_float()
{
    class_< gmtl::Plane<float> >("Planef", init<  >())
        .def(init< const gmtl::Point<float,3> &, const gmtl::Point<float,3> &, const gmtl::Point<float,3> & >())
        .def(init< const gmtl::Vec<float,3> &, const gmtl::Point<float,3> & >())
        .def(init< const gmtl::Vec<float,3> &, const float & >())
        .def(init< const gmtl::Plane<float> & >())
        .def_readwrite("norm", &gmtl::Plane<float>::mNorm)
        .def_readwrite("offset", &gmtl::Plane<float>::mOffset)
        .def("getNormal", &gmtl::Plane<float>::getNormal, return_value_policy< copy_const_reference >())
        .def("setNormal", &gmtl::Plane<float>::setNormal)
        .def("getOffset", &gmtl::Plane<float>::getOffset, return_value_policy< copy_const_reference >())
        .def("setOffset", &gmtl::Plane<float>::setOffset)
        .def("set",
             (gmtl::Plane<float>& (gmtl::Plane<float>::*)(const gmtl::Plane<float>&)) &gmtl::Plane<float>::operator=,
             return_internal_reference<1>())
        .def_pickle(gmtlPickle::Plane_pickle<float>())
        .def(self == self)
        .def(self != self)
        .def(self_ns::str(self))
    ;

}

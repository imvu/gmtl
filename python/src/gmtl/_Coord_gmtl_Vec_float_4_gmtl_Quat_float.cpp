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
#include <gmtl/Coord.h>
#include <gmtl/QuatOps.h>
#include <gmtl/CoordOps.h>
#include <gmtl/Output.h>
#include <gmtl-pickle.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_Coord_gmtl_Vec_float_4_gmtl_Quat_float()
{
    scope* gmtl_Coord_gmtl_Vec_float_4_gmtl_Quat_float_scope = new scope(
    class_< gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > >("Coord4fQuat", init<  >())
        .def(init< const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > & >())
        .def(init< const gmtl::Vec<float,4> &, const gmtl::Quat<float> & >())
        .def_readwrite("pos", &gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> >::mPos)
        .def_readwrite("rot", &gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> >::mRot)
        .def("getPos", &gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> >::getPos, return_internal_reference< 1 >())
        .def("getRot", &gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> >::getRot, return_internal_reference< 1 >())
        .def("set",
             (gmtl::Coord<gmtl::Vec<float, 4>, gmtl::Quat<float> >& (gmtl::Coord<gmtl::Vec<float, 4>, gmtl::Quat<float> >::*)(const gmtl::Coord<gmtl::Vec<float, 4>, gmtl::Quat<float> >&)) &gmtl::Coord<gmtl::Vec<float, 4>, gmtl::Quat<float> >::operator=,
             return_internal_reference<1>())
        .def_pickle(gmtlPickle::Coord_pickle< gmtl::Vec<float, 4>,gmtl::Quat<float> >())
        .def(self == self)
        .def(self != self)
        .def(self_ns::str(self))
    );

    enum_< gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> >::Params >("Params")
        .value("RotSize", gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> >::RotSize)
        .value("PosSize", gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> >::PosSize)
    ;

    delete gmtl_Coord_gmtl_Vec_float_4_gmtl_Quat_float_scope;

}

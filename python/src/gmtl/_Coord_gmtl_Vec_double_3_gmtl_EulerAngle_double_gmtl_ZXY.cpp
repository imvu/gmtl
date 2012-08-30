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
#include <gmtl/EulerAngleOps.h>
#include <gmtl/CoordOps.h>
#include <gmtl/Output.h>
#include <gmtl-pickle.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_Coord_gmtl_Vec_double_3_gmtl_EulerAngle_double_gmtl_ZXY()
{
    scope* gmtl_Coord_gmtl_Vec_double_3_gmtl_EulerAngle_double_gmtl_ZXY_scope = new scope(
    class_< gmtl::Coord<gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::ZXY> > >("Coord3dZXY", init<  >())
        .def(init< const gmtl::Coord<gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::ZXY> > & >())
        .def(init< const gmtl::Vec<double,3> &, const gmtl::EulerAngle<double,gmtl::ZXY> & >())
        .def_readwrite("pos", &gmtl::Coord<gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::ZXY> >::mPos)
        .def_readwrite("rot", &gmtl::Coord<gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::ZXY> >::mRot)
        .def("getPos", &gmtl::Coord<gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::ZXY> >::getPos, return_internal_reference< 1 >())
        .def("getRot", &gmtl::Coord<gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::ZXY> >::getRot, return_internal_reference< 1 >())
        .def("set",
             (gmtl::Coord<gmtl::Vec<double, 3>, gmtl::EulerAngle<double, gmtl::ZXY> >& (gmtl::Coord<gmtl::Vec<double, 3>, gmtl::EulerAngle<double, gmtl::ZXY> >::*)(const gmtl::Coord<gmtl::Vec<double, 3>, gmtl::EulerAngle<double, gmtl::ZXY> >&)) &gmtl::Coord<gmtl::Vec<double, 3>, gmtl::EulerAngle<double, gmtl::ZXY> >::operator=,
             return_internal_reference<1>())
        .def_pickle(gmtlPickle::Coord_pickle< gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::ZXY> >())
        .def(self == self)
        .def(self != self)
        .def(self_ns::str(self))
    );

    enum_< gmtl::Coord<gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::ZXY> >::Params >("Params")
        .value("RotSize", gmtl::Coord<gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::ZXY> >::RotSize)
        .value("PosSize", gmtl::Coord<gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::ZXY> >::PosSize)
    ;

    delete gmtl_Coord_gmtl_Vec_double_3_gmtl_EulerAngle_double_gmtl_ZXY_scope;

}

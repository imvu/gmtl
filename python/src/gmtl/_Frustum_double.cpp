// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl/Frustum.h>
#include <gmtl-getData-wrappers.h>
#include <gmtl-pickle.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_Frustum_double()
{
    scope* gmtl_Frustum_double_scope = new scope(
    class_< gmtl::Frustum<double> >("Frustumd", init<  >())
        .def(init< const gmtl::Frustum<double> & >())
        .def(init< const gmtl::Matrix44d & >())
        .def(init< const gmtl::Matrix44d &, const gmtl::Matrix44d & >())
        .add_property("planes",
                      (tuple (*)(gmtl::Frustum<double>*)) &gmtlWrappers::Frustum_getPlanes)
        .def("extractPlanes",
             (void(gmtl::Frustum<double>::*)(const gmtl::Matrix44d&, const gmtl::Matrix44d&)) &gmtl::Frustum<double>::extractPlanes)
        .def("extractPlanes",
             (void(gmtl::Frustum<double>::*)(const gmtl::Matrix44d&)) &gmtl::Frustum<double>::extractPlanes)
        .def_pickle(gmtlPickle::Frustum_pickle<double>())
    );

    enum_< gmtl::Frustum<double>::PlaneNames >("PlaneNames")
        .value("LEFT", gmtl::Frustum<double>::PLANE_LEFT)
        .value("RIGHT", gmtl::Frustum<double>::PLANE_RIGHT)
        .value("BOTTOM", gmtl::Frustum<double>::PLANE_BOTTOM)
        .value("TOP", gmtl::Frustum<double>::PLANE_TOP)
        .value("NEAR", gmtl::Frustum<double>::PLANE_NEAR)
        .value("FAR", gmtl::Frustum<double>::PLANE_FAR)
    ;

    delete gmtl_Frustum_double_scope;

}

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
void _Export_Frustum_float()
{
    scope* gmtl_Frustum_float_scope = new scope(
    class_< gmtl::Frustum<float> >("Frustumf", init<  >())
        .def(init< const gmtl::Frustum<float> & >())
        .def(init< const gmtl::Matrix44f & >())
        .def(init< const gmtl::Matrix44f &, const gmtl::Matrix44f & >())
        .add_property("planes",
                      (tuple (*)(gmtl::Frustum<float>*)) &gmtlWrappers::Frustum_getPlanes)
        .def("extractPlanes",
             (void(gmtl::Frustum<float>::*)(const gmtl::Matrix44f&, const gmtl::Matrix44f&)) &gmtl::Frustum<float>::extractPlanes)
        .def("extractPlanes",
             (void(gmtl::Frustum<float>::*)(const gmtl::Matrix44f&)) &gmtl::Frustum<float>::extractPlanes)
        .def_pickle(gmtlPickle::Frustum_pickle<float>())
    );

    enum_< gmtl::Frustum<float>::PlaneNames >("PlaneNames")
        .value("LEFT", gmtl::Frustum<float>::PLANE_LEFT)
        .value("RIGHT", gmtl::Frustum<float>::PLANE_RIGHT)
        .value("BOTTOM", gmtl::Frustum<float>::PLANE_BOTTOM)
        .value("TOP", gmtl::Frustum<float>::PLANE_TOP)
        .value("NEAR", gmtl::Frustum<float>::PLANE_NEAR)
        .value("FAR", gmtl::Frustum<float>::PLANE_FAR)
    ;

    delete gmtl_Frustum_float_scope;

}

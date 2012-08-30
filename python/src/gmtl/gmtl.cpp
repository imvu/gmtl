// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

// This file was originally part of PyJuggler.

// PyJuggler is (C) Copyright 2002, 2003 by Patrick Hartling
// Distributed under the GNU Lesser General Public License 2.1.  (See
// accompanying file COPYING.txt or http://www.gnu.org/copyleft/lesser.txt)

// Include =====================================================================
#include <boost/python.hpp>
#include <gmtl/Version.h>

// Exports =====================================================================
void _Export_AABox_double();
void _Export_AABox_float();
void _Export_Coord_gmtl_Vec_double_3_gmtl_AxisAngle_double();
void _Export_Coord_gmtl_Vec_double_3_gmtl_EulerAngle_double_gmtl_XYZ();
void _Export_Coord_gmtl_Vec_double_3_gmtl_EulerAngle_double_gmtl_ZXY();
void _Export_Coord_gmtl_Vec_double_3_gmtl_EulerAngle_double_gmtl_ZYX();
void _Export_Coord_gmtl_Vec_double_3_gmtl_Quat_double();
void _Export_Coord_gmtl_Vec_double_4_gmtl_AxisAngle_double();
void _Export_Coord_gmtl_Vec_double_4_gmtl_EulerAngle_double_gmtl_XYZ();
void _Export_Coord_gmtl_Vec_double_4_gmtl_EulerAngle_double_gmtl_ZXY();
void _Export_Coord_gmtl_Vec_double_4_gmtl_EulerAngle_double_gmtl_ZYX();
void _Export_Coord_gmtl_Vec_double_4_gmtl_Quat_double();
void _Export_Coord_gmtl_Vec_float_3_gmtl_AxisAngle_float();
void _Export_Coord_gmtl_Vec_float_3_gmtl_EulerAngle_float_gmtl_XYZ();
void _Export_Coord_gmtl_Vec_float_3_gmtl_EulerAngle_float_gmtl_ZXY();
void _Export_Coord_gmtl_Vec_float_3_gmtl_EulerAngle_float_gmtl_ZYX();
void _Export_Coord_gmtl_Vec_float_3_gmtl_Quat_float();
void _Export_Coord_gmtl_Vec_float_4_gmtl_AxisAngle_float();
void _Export_Coord_gmtl_Vec_float_4_gmtl_EulerAngle_float_gmtl_XYZ();
void _Export_Coord_gmtl_Vec_float_4_gmtl_EulerAngle_float_gmtl_ZXY();
void _Export_Coord_gmtl_Vec_float_4_gmtl_EulerAngle_float_gmtl_ZYX();
void _Export_Coord_gmtl_Vec_float_4_gmtl_Quat_float();
void _Export_EulerAngle_float_gmtl_XYZ();
void _Export_EulerAngle_float_gmtl_ZXY();
void _Export_EulerAngle_float_gmtl_ZYX();
void _Export_Matrix_float_3_3();
void _Export_Matrix_float_4_4();
void _Export_Plane_double();
void _Export_Plane_float();
void _Export_Quat_double();
void _Export_Quat_float();
void _Export_Ray_double();
void _Export_Ray_float();
void _Export_Sphere_double();
void _Export_Sphere_float();
void _Export_Tri_double();
void _Export_Tri_float();
void _Export_Tri_int();
void _Export_VecBase_double_2();
void _Export_VecBase_double_3();
void _Export_VecBase_double_4();
void _Export_VecBase_float_2();
void _Export_VecBase_float_3();
void _Export_VecBase_float_4();
void _Export_VecBase_int_2();
void _Export_VecBase_int_3();
void _Export_VecBase_int_4();
void _Export_AxisAngle_double();
void _Export_AxisAngle_float();
void _Export_LineSeg_double();
void _Export_LineSeg_float();
void _Export_Frustum_double();
void _Export_Frustum_float();
void _Export_Point_double_2();
void _Export_Point_double_3();
void _Export_Point_float_2();
void _Export_Point_float_3();
void _Export_Point_int_2();
void _Export_Point_int_3();
void _Export_Vec_double_2();
void _Export_Vec_double_3();
void _Export_Vec_double_4();
void _Export_Vec_float_2();
void _Export_Vec_float_3();
void _Export_Vec_float_4();
void _Export_Vec_int_2();
void _Export_Vec_int_3();
void _Export_Vec_int_4();
void _Export_gmtl_Math_h();
void _Export_gmtl_Defines_h();
void _Export_gmtl_MatrixOps_h();
void _Export_gmtl_CoordOps_h();
void _Export_gmtl_SphereOps_h();
void _Export_gmtl_AxisAngleOps_h();
void _Export_gmtl_EulerAngleOps_h();
void _Export_gmtl_AABoxOps_h();
void _Export_gmtl_RayOps_h();
void _Export_gmtl_TriOps_h();
void _Export_gmtl_QuatOps_h();
void _Export_gmtl_VecOps_h();
void _Export_gmtl_FrustumOps_h();
void _Export_gmtl_intersect_wrappers_h();
void _Export_gmtl_containment_wrappers_h();
void _Export_gmtl_LineSegOps_h();
void _Export_gmtl_PlaneOps_h();
void _Export_gmtl_Containment_h();
void _Export_gmtl_Generate_h();
void _Export_gmtl_Xforms_h();
void _Export_gmtl_wrappers_h();

// Module ======================================================================
BOOST_PYTHON_MODULE(gmtl)
{
    boost::python::scope().attr("__version__") = gmtl::getVersion();

    _Export_AABox_double();
    _Export_AABox_float();
    _Export_Coord_gmtl_Vec_double_3_gmtl_AxisAngle_double();
    _Export_Coord_gmtl_Vec_double_3_gmtl_EulerAngle_double_gmtl_XYZ();
    _Export_Coord_gmtl_Vec_double_3_gmtl_EulerAngle_double_gmtl_ZXY();
    _Export_Coord_gmtl_Vec_double_3_gmtl_EulerAngle_double_gmtl_ZYX();
    _Export_Coord_gmtl_Vec_double_3_gmtl_Quat_double();
    _Export_Coord_gmtl_Vec_double_4_gmtl_AxisAngle_double();
    _Export_Coord_gmtl_Vec_double_4_gmtl_EulerAngle_double_gmtl_XYZ();
    _Export_Coord_gmtl_Vec_double_4_gmtl_EulerAngle_double_gmtl_ZXY();
    _Export_Coord_gmtl_Vec_double_4_gmtl_EulerAngle_double_gmtl_ZYX();
    _Export_Coord_gmtl_Vec_double_4_gmtl_Quat_double();
    _Export_Coord_gmtl_Vec_float_3_gmtl_AxisAngle_float();
    _Export_Coord_gmtl_Vec_float_3_gmtl_EulerAngle_float_gmtl_XYZ();
    _Export_Coord_gmtl_Vec_float_3_gmtl_EulerAngle_float_gmtl_ZXY();
    _Export_Coord_gmtl_Vec_float_3_gmtl_EulerAngle_float_gmtl_ZYX();
    _Export_Coord_gmtl_Vec_float_3_gmtl_Quat_float();
    _Export_Coord_gmtl_Vec_float_4_gmtl_AxisAngle_float();
    _Export_Coord_gmtl_Vec_float_4_gmtl_EulerAngle_float_gmtl_XYZ();
    _Export_Coord_gmtl_Vec_float_4_gmtl_EulerAngle_float_gmtl_ZXY();
    _Export_Coord_gmtl_Vec_float_4_gmtl_EulerAngle_float_gmtl_ZYX();
    _Export_Coord_gmtl_Vec_float_4_gmtl_Quat_float();
    _Export_EulerAngle_float_gmtl_XYZ();
    _Export_EulerAngle_float_gmtl_ZXY();
    _Export_EulerAngle_float_gmtl_ZYX();
    _Export_Matrix_float_3_3();
    _Export_Matrix_float_4_4();
    _Export_Plane_double();
    _Export_Plane_float();
    _Export_Quat_double();
    _Export_Quat_float();
    _Export_Ray_double();
    _Export_Ray_float();
    _Export_Sphere_double();
    _Export_Sphere_float();
    _Export_Tri_double();
    _Export_Tri_float();
    _Export_Tri_int();
    _Export_VecBase_double_2();
    _Export_VecBase_double_3();
    _Export_VecBase_double_4();
    _Export_VecBase_float_2();
    _Export_VecBase_float_3();
    _Export_VecBase_float_4();
    _Export_VecBase_int_2();
    _Export_VecBase_int_3();
    _Export_VecBase_int_4();
    _Export_AxisAngle_double();
    _Export_AxisAngle_float();
    _Export_LineSeg_double();
    _Export_LineSeg_float();
    _Export_Frustum_double();
    _Export_Frustum_float();
    _Export_Point_double_2();
    _Export_Point_double_3();
    _Export_Point_float_2();
    _Export_Point_float_3();
    _Export_Point_int_2();
    _Export_Point_int_3();
    _Export_Vec_double_2();
    _Export_Vec_double_3();
    _Export_Vec_double_4();
    _Export_Vec_float_2();
    _Export_Vec_float_3();
    _Export_Vec_float_4();
    _Export_Vec_int_2();
    _Export_Vec_int_3();
    _Export_Vec_int_4();
    _Export_gmtl_Math_h();
    _Export_gmtl_Defines_h();
    _Export_gmtl_MatrixOps_h();
    _Export_gmtl_CoordOps_h();
    _Export_gmtl_SphereOps_h();
    _Export_gmtl_AxisAngleOps_h();
    _Export_gmtl_AABoxOps_h();
    _Export_gmtl_EulerAngleOps_h();
    _Export_gmtl_RayOps_h();
    _Export_gmtl_TriOps_h();
    _Export_gmtl_QuatOps_h();
    _Export_gmtl_VecOps_h();
    _Export_gmtl_intersect_wrappers_h();
    _Export_gmtl_containment_wrappers_h();
    _Export_gmtl_LineSegOps_h();
    _Export_gmtl_FrustumOps_h();
    _Export_gmtl_Containment_h();
    _Export_gmtl_Generate_h();
    _Export_gmtl_PlaneOps_h();
    _Export_gmtl_Xforms_h();
    _Export_gmtl_wrappers_h();
}

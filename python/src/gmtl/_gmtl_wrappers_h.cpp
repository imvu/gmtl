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
#include <gmtl-wrappers.h>

// Using =======================================================================
using namespace boost::python;

// Declarations ================================================================


namespace  {


BOOST_PYTHON_FUNCTION_OVERLOADS(makeDirCosMatrix33_overloads_3_6, gmtlWrappers::makeDirCosMatrix33, 3, 6)
BOOST_PYTHON_FUNCTION_OVERLOADS(makeDirCosMatrix44_overloads_3_6, gmtlWrappers::makeDirCosMatrix44, 3, 6)


}// namespace 


// Module ======================================================================
void _Export_gmtl_wrappers_h()
{
    def("makeAxesMatrix33", (gmtl::Matrix<double,3,3> (*)(const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &))&gmtlWrappers::makeAxesMatrix33);
    def("makeAxesMatrix33", (gmtl::Matrix<float,3,3> (*)(const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &))&gmtlWrappers::makeAxesMatrix33);
    def("makeAxesMatrix44", (gmtl::Matrix<double,4,4> (*)(const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &))&gmtlWrappers::makeAxesMatrix44);
    def("makeAxesMatrix44", (gmtl::Matrix<float,4,4> (*)(const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &))&gmtlWrappers::makeAxesMatrix44);
    def("makeDirCosMatrix33", (gmtl::Matrix<double,3,3> (*)(const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &))&gmtlWrappers::makeDirCosMatrix33, makeDirCosMatrix33_overloads_3_6());
    def("makeDirCosMatrix33", (gmtl::Matrix<float,3,3> (*)(const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &))&gmtlWrappers::makeDirCosMatrix33, makeDirCosMatrix33_overloads_3_6());
    def("makeDirCosMatrix44", (gmtl::Matrix<double,4,4> (*)(const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &))&gmtlWrappers::makeDirCosMatrix44, makeDirCosMatrix44_overloads_3_6());
    def("makeDirCosMatrix44", (gmtl::Matrix<float,4,4> (*)(const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &))&gmtlWrappers::makeDirCosMatrix44, makeDirCosMatrix44_overloads_3_6());
    def("makeRotEulerAngleXYZ", (gmtl::EulerAngle<float,gmtl::XYZ> (*)(const gmtl::Matrix<float,4,4> &))&gmtlWrappers::makeRotEulerAngleXYZ);
    def("makeRotEulerAngleXYZ", (gmtl::EulerAngle<double,gmtl::XYZ> (*)(const gmtl::Matrix<double,4,4> &))&gmtlWrappers::makeRotEulerAngleXYZ);
    def("makeRotEulerAngleZXY", (gmtl::EulerAngle<float,gmtl::ZXY> (*)(const gmtl::Matrix<float,4,4> &))&gmtlWrappers::makeRotEulerAngleZXY);
    def("makeRotEulerAngleZXY", (gmtl::EulerAngle<double,gmtl::ZXY> (*)(const gmtl::Matrix<double,4,4> &))&gmtlWrappers::makeRotEulerAngleZXY);
    def("makeRotEulerAngleZYX", (gmtl::EulerAngle<float,gmtl::ZYX> (*)(const gmtl::Matrix<float,4,4> &))&gmtlWrappers::makeRotEulerAngleZYX);
    def("makeRotEulerAngleZYX", (gmtl::EulerAngle<double,gmtl::ZYX> (*)(const gmtl::Matrix<double,4,4> &))&gmtlWrappers::makeRotEulerAngleZYX);
    def("makeRotMatrix33", (gmtl::Matrix<double,3,3> (*)(const gmtl::Quat<double> &))&gmtlWrappers::makeRotMatrix33);
    def("makeRotMatrix33", (gmtl::Matrix<float,3,3> (*)(const gmtl::Quat<float> &))&gmtlWrappers::makeRotMatrix33);
    def("makeRotMatrix33", (gmtl::Matrix<float,3,3> (*)(const gmtl::EulerAngle<float,gmtl::ZYX> &))&gmtlWrappers::makeRotMatrix33);
    def("makeRotMatrix33", (gmtl::Matrix<float,3,3> (*)(const gmtl::EulerAngle<float,gmtl::XYZ> &))&gmtlWrappers::makeRotMatrix33);
    def("makeRotMatrix33", (gmtl::Matrix<float,3,3> (*)(const gmtl::EulerAngle<float,gmtl::ZXY> &))&gmtlWrappers::makeRotMatrix33);
    def("makeRotMatrix33", (gmtl::Matrix<float,3,3> (*)(const gmtl::AxisAngle<float> &))&gmtlWrappers::makeRotMatrix33);
    def("makeRotMatrix33", (gmtl::Matrix<double,3,3> (*)(const gmtl::AxisAngle<double> &))&gmtlWrappers::makeRotMatrix33);
    def("makeRotMatrix44", (gmtl::Matrix<float,4,4> (*)(const gmtl::Quat<float> &))&gmtlWrappers::makeRotMatrix44);
    def("makeRotMatrix44", (gmtl::Matrix<float,4,4> (*)(const gmtl::EulerAngle<float,gmtl::XYZ> &))&gmtlWrappers::makeRotMatrix44);
    def("makeRotMatrix44", (gmtl::Matrix<float,4,4> (*)(const gmtl::EulerAngle<float,gmtl::ZXY> &))&gmtlWrappers::makeRotMatrix44);
    def("makeRotMatrix44", (gmtl::Matrix<double,4,4> (*)(const gmtl::Quat<double> &))&gmtlWrappers::makeRotMatrix44);
    def("makeRotMatrix44", (gmtl::Matrix<float,4,4> (*)(const gmtl::EulerAngle<float,gmtl::ZYX> &))&gmtlWrappers::makeRotMatrix44);
    def("makeRotMatrix44", (gmtl::Matrix<float,4,4> (*)(const gmtl::AxisAngle<float> &))&gmtlWrappers::makeRotMatrix44);
    def("makeRotMatrix44", (gmtl::Matrix<double,4,4> (*)(const gmtl::AxisAngle<double> &))&gmtlWrappers::makeRotMatrix44);
    def("makeRotMatrix44", (gmtl::Matrix<float,4,4> (*)(const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &))&gmtlWrappers::makeRotMatrix44);
    def("makeRotQuat", (gmtl::Quat<float> (*)(const gmtl::Matrix<float,4,4> &))&gmtlWrappers::makeRotQuat);
    def("makeRotQuat", (gmtl::Quat<double> (*)(const gmtl::Matrix<double,4,4> &))&gmtlWrappers::makeRotQuat);
    def("makeRotQuat", (gmtl::Quat<float> (*)(const gmtl::AxisAngle<float> &))&gmtlWrappers::makeRotQuat);
    def("makeRotQuat", (gmtl::Quat<double> (*)(const gmtl::AxisAngle<double> &))&gmtlWrappers::makeRotQuat);
    def("makeRotQuat", (gmtl::Quat<float> (*)(const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &))&gmtlWrappers::makeRotQuat);
    def("makeRotQuat", (gmtl::Quat<double> (*)(const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &))&gmtlWrappers::makeRotQuat);
    def("makeScaleMatrix33", (gmtl::Matrix<double,3,3> (*)(const double&))&gmtlWrappers::makeScaleMatrix33);
    def("makeScaleMatrix33", (gmtl::Matrix<double,3,3> (*)(const gmtl::Vec<double,2> &))&gmtlWrappers::makeScaleMatrix33);
    def("makeScaleMatrix33", (gmtl::Matrix<float,3,3> (*)(const float&))&gmtlWrappers::makeScaleMatrix33);
    def("makeScaleMatrix33", (gmtl::Matrix<double,3,3> (*)(const gmtl::Vec<double,3> &))&gmtlWrappers::makeScaleMatrix33);
    def("makeScaleMatrix33", (gmtl::Matrix<float,3,3> (*)(const gmtl::Vec<float,2> &))&gmtlWrappers::makeScaleMatrix33);
    def("makeScaleMatrix33", (gmtl::Matrix<float,3,3> (*)(const gmtl::Vec<float,3> &))&gmtlWrappers::makeScaleMatrix33);
    def("makeScaleMatrix44", (gmtl::Matrix<double,4,4> (*)(const double&))&gmtlWrappers::makeScaleMatrix44);
    def("makeScaleMatrix44", (gmtl::Matrix<double,4,4> (*)(const gmtl::Vec<double,4> &))&gmtlWrappers::makeScaleMatrix44);
    def("makeScaleMatrix44", (gmtl::Matrix<float,4,4> (*)(const float&))&gmtlWrappers::makeScaleMatrix44);
    def("makeScaleMatrix44", (gmtl::Matrix<double,4,4> (*)(const gmtl::Vec<double,3> &))&gmtlWrappers::makeScaleMatrix44);
    def("makeScaleMatrix44", (gmtl::Matrix<float,4,4> (*)(const gmtl::Vec<float,4> &))&gmtlWrappers::makeScaleMatrix44);
    def("makeScaleMatrix44", (gmtl::Matrix<float,4,4> (*)(const gmtl::Vec<float,3> &))&gmtlWrappers::makeScaleMatrix44);
    def("makeTransMatrix33", (gmtl::Matrix<double,3,3> (*)(const gmtl::Vec<double,2> &))&gmtlWrappers::makeTransMatrix33);
    def("makeTransMatrix33", (gmtl::Matrix<float,3,3> (*)(const gmtl::Vec<float,2> &))&gmtlWrappers::makeTransMatrix33);
    def("makeTransMatrix33", (gmtl::Matrix<double,3,3> (*)(const gmtl::Vec<double,3> &))&gmtlWrappers::makeTransMatrix33);
    def("makeTransMatrix33", (gmtl::Matrix<float,3,3> (*)(const gmtl::Vec<float,3> &))&gmtlWrappers::makeTransMatrix33);
    def("makeTransMatrix44", (gmtl::Matrix<double,4,4> (*)(const gmtl::Vec<double,3> &))&gmtlWrappers::makeTransMatrix44);
    def("makeTransMatrix44", (gmtl::Matrix<float,4,4> (*)(const gmtl::Vec<float,3> &))&gmtlWrappers::makeTransMatrix44);
    def("makeTransVec3", (gmtl::Vec<double,3> (*)(const gmtl::Matrix<double,4,4> &))&gmtlWrappers::makeTransVec3);
    def("makeTransVec3", (gmtl::Vec<float,3> (*)(const gmtl::Matrix<float,4,4> &))&gmtlWrappers::makeTransVec3);
    def("makeTransVec3", (gmtl::Vec<double,3> (*)(const gmtl::Matrix<double,3,3> &))&gmtlWrappers::makeTransVec3);
    def("makeTransVec3", (gmtl::Vec<float,3> (*)(const gmtl::Matrix<float,3,3> &))&gmtlWrappers::makeTransVec3);
    def("makeTransVec2", (gmtl::Vec<double,2> (*)(const gmtl::Matrix<double,3,3> &))&gmtlWrappers::makeTransVec2);
    def("makeTransVec2", (gmtl::Vec<float,2> (*)(const gmtl::Matrix<float,3,3> &))&gmtlWrappers::makeTransVec2);
    def("makeTransPoint3", (gmtl::Point<double,3> (*)(const gmtl::Matrix<double,4,4> &))&gmtlWrappers::makeTransPoint3);
    def("makeTransPoint3", (gmtl::Point<float,3> (*)(const gmtl::Matrix<float,4,4> &))&gmtlWrappers::makeTransPoint3);
}

// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl-CoordOps.h>

// Using =======================================================================
using namespace boost::python;

// Declarations ================================================================
namespace  {


BOOST_PYTHON_FUNCTION_OVERLOADS(isEqual_overloads_2_3, gmtl::isEqual, 2, 3)


}// namespace 

// Module ======================================================================
void _Export_gmtl_CoordOps_h()
{
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::XYZ> > &, const gmtl::Coord<gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::XYZ> > &, double))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<double, 4>,gmtl::AxisAngle<double> > &, const gmtl::Coord<gmtl::Vec<double, 4>,gmtl::AxisAngle<double> > &, double))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::AxisAngle<float> > &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::AxisAngle<float> > &, float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<double, 4>,gmtl::Quat<double> > &, const gmtl::Coord<gmtl::Vec<double, 4>,gmtl::Quat<double> > &, double))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > &, float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > &, float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::ZXY> > &, const gmtl::Coord<gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::ZXY> > &, double))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::ZYX> > &, const gmtl::Coord<gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::ZYX> > &, double))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<double, 3>,gmtl::Quat<double> > &, const gmtl::Coord<gmtl::Vec<double, 3>,gmtl::Quat<double> > &, double))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > &, float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<double, 4>,gmtl::EulerAngle<double, gmtl::ZXY> > &, const gmtl::Coord<gmtl::Vec<double, 4>,gmtl::EulerAngle<double, gmtl::ZXY> > &, double))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<double, 4>,gmtl::EulerAngle<double, gmtl::ZYX> > &, const gmtl::Coord<gmtl::Vec<double, 4>,gmtl::EulerAngle<double, gmtl::ZYX> > &, double))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<double, 4>,gmtl::EulerAngle<double, gmtl::XYZ> > &, const gmtl::Coord<gmtl::Vec<double, 4>,gmtl::EulerAngle<double, gmtl::XYZ> > &, double))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > &, float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > &, float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<double, 3>,gmtl::AxisAngle<double> > &, const gmtl::Coord<gmtl::Vec<double, 3>,gmtl::AxisAngle<double> > &, double))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::AxisAngle<float> > &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::AxisAngle<float> > &, float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > &, float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > &, float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > &, float))&gmtl::isEqual, isEqual_overloads_2_3());
}

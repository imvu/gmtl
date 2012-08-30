// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl-Generate.h>

// Using =======================================================================
using namespace boost::python;

// Declarations ================================================================


namespace  {


BOOST_PYTHON_FUNCTION_OVERLOADS(setDirCos_overloads_4_7, gmtl::setDirCos, 4, 7)


}// namespace 


// Module ======================================================================
void _Export_gmtl_Generate_h()
{
    def("makeConj", (gmtl::Quat<double> (*)(const gmtl::Quat<double> &))&gmtl::makeConj);
    def("makeConj", (gmtl::Quat<float> (*)(const gmtl::Quat<float> &))&gmtl::makeConj);
    def("makeCross", (gmtl::Vec<int,3> (*)(const gmtl::Vec<int,3> &, const gmtl::Vec<int,3> &))&gmtl::makeCross);
    def("makeCross", (gmtl::Vec<float,3> (*)(const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &))&gmtl::makeCross);
    def("makeCross", (gmtl::Vec<double,3> (*)(const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &))&gmtl::makeCross);
    def("makeInvert", (gmtl::Quat<float> (*)(const gmtl::Quat<float> &))&gmtl::makeInvert);
    def("makeInvert", (gmtl::Quat<double> (*)(const gmtl::Quat<double> &))&gmtl::makeInvert);
    def("makeInvert", (gmtl::Matrix<double,4,4> (*)(const gmtl::Matrix<double,4,4> &))&gmtl::makeInvert);
    def("makeInvert", (gmtl::Matrix<float,3,3> (*)(const gmtl::Matrix<float,3,3> &))&gmtl::makeInvert);
    def("makeInvert", (gmtl::Matrix<float,4,4> (*)(const gmtl::Matrix<float,4,4> &))&gmtl::makeInvert);
    def("makeInvert", (gmtl::Matrix<double,3,3> (*)(const gmtl::Matrix<double,3,3> &))&gmtl::makeInvert);
    def("makeNormal", (gmtl::Quat<float> (*)(const gmtl::Quat<float> &))&gmtl::makeNormal);
    def("makeNormal", (gmtl::Quat<double> (*)(const gmtl::Quat<double> &))&gmtl::makeNormal);
    def("makeNormal", (gmtl::Vec<float,4> (*)(gmtl::Vec<float,4>))&gmtl::makeNormal);
    def("makeNormal", (gmtl::Vec<double,4> (*)(gmtl::Vec<double,4>))&gmtl::makeNormal);
    def("makeNormal", (gmtl::Vec<float,3> (*)(gmtl::Vec<float,3>))&gmtl::makeNormal);
    def("makeNormal", (gmtl::Vec<double,3> (*)(gmtl::Vec<double,3>))&gmtl::makeNormal);
    def("makeNormal", (gmtl::AxisAngle<float> (*)(const gmtl::AxisAngle<float> &))&gmtl::makeNormal);
    def("makeNormal", (gmtl::AxisAngle<double> (*)(const gmtl::AxisAngle<double> &))&gmtl::makeNormal);
    def("makePure", (gmtl::Quat<float> (*)(const gmtl::Vec<float,3> &))&gmtl::makePure);
    def("makePure", (gmtl::Quat<double> (*)(const gmtl::Vec<double,3> &))&gmtl::makePure);
    def("makeTranspose", (gmtl::Matrix<float,3,3> (*)(const gmtl::Matrix<float,3,3> &))&gmtl::makeTranspose);
    def("makeTranspose", (gmtl::Matrix<float,4,4> (*)(const gmtl::Matrix<float,4,4> &))&gmtl::makeTranspose);
    def("makeTranspose", (gmtl::Matrix<double,3,3> (*)(const gmtl::Matrix<double,3,3> &))&gmtl::makeTranspose);
    def("makeTranspose", (gmtl::Matrix<double,4,4> (*)(const gmtl::Matrix<double,4,4> &))&gmtl::makeTranspose);
    def("makeVec", (gmtl::Vec<float,3> (*)(const gmtl::Quat<float> &))&gmtl::makeVec);
    def("makeVec", (gmtl::Vec<double,3> (*)(const gmtl::Quat<double> &))&gmtl::makeVec);
    def("makeXRot", (float (*)(const gmtl::Matrix<float,3,3> &))&gmtl::makeXRot);
    def("makeXRot", (float (*)(const gmtl::Matrix<float,4,4> &))&gmtl::makeXRot);
    def("makeXRot", (double (*)(const gmtl::Matrix<double,3,3> &))&gmtl::makeXRot);
    def("makeXRot", (double (*)(const gmtl::Matrix<double,4,4> &))&gmtl::makeXRot);
    def("makeYRot", (float (*)(const gmtl::Matrix<float,4,4> &))&gmtl::makeYRot);
    def("makeYRot", (double (*)(const gmtl::Matrix<double,3,3> &))&gmtl::makeYRot);
    def("makeYRot", (float (*)(const gmtl::Matrix<float,3,3> &))&gmtl::makeYRot);
    def("makeYRot", (double (*)(const gmtl::Matrix<double,4,4> &))&gmtl::makeYRot);
    def("makeZRot", (float (*)(const gmtl::Matrix<float,3,3> &))&gmtl::makeZRot);
    def("makeZRot", (double (*)(const gmtl::Matrix<double,3,3> &))&gmtl::makeZRot);
    def("makeZRot", (float (*)(const gmtl::Matrix<float,4,4> &))&gmtl::makeZRot);
    def("makeZRot", (double (*)(const gmtl::Matrix<double,4,4> &))&gmtl::makeZRot);
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::Quat<double> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Quat<float> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::AxisAngle<float> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Quat<float> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::AxisAngle<float> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::AxisAngle<float> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::AxisAngle<float> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<double,3,3> & (*)(gmtl::Matrix<double,3,3> &, const gmtl::Quat<double> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::EulerAngle<float,gmtl::ZXY> & (*)(gmtl::EulerAngle<float,gmtl::ZXY> &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::EulerAngle<float,gmtl::ZXY> & (*)(gmtl::EulerAngle<float,gmtl::ZXY> &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::EulerAngle<float,gmtl::ZYX> & (*)(gmtl::EulerAngle<float,gmtl::ZYX> &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::EulerAngle<float,gmtl::ZYX> & (*)(gmtl::EulerAngle<float,gmtl::ZYX> &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::EulerAngle<float,gmtl::XYZ> & (*)(gmtl::EulerAngle<float,gmtl::XYZ> &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::EulerAngle<float,gmtl::XYZ> & (*)(gmtl::EulerAngle<float,gmtl::XYZ> &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Quat<double> & (*)(gmtl::Quat<double> &, const gmtl::Matrix<double,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::AxisAngle<float> & (*)(gmtl::AxisAngle<float> &, gmtl::Quat<float>))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::AxisAngle<double> & (*)(gmtl::AxisAngle<double> &, gmtl::Quat<double>))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::AxisAngle<float> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::EulerAngle<float,gmtl::ZXY> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::EulerAngle<float,gmtl::ZYX> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::EulerAngle<float,gmtl::XYZ> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Quat<double> & (*)(gmtl::Quat<double> &, const gmtl::AxisAngle<double> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::EulerAngle<float,gmtl::ZXY> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::EulerAngle<float,gmtl::ZYX> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::EulerAngle<float,gmtl::XYZ> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::AxisAngle<double> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::AxisAngle<float> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::EulerAngle<double,gmtl::XYZ> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::EulerAngle<double,gmtl::ZYX> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::EulerAngle<double,gmtl::ZXY> &))&gmtl::set, return_internal_reference< 1 >());
    def("setAxes", (gmtl::Matrix<double,3,3> & (*)(gmtl::Matrix<double,3,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &))&gmtl::setAxes, return_internal_reference< 1 >());
    def("setAxes", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &))&gmtl::setAxes, return_internal_reference< 1 >());
    def("setAxes", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &))&gmtl::setAxes, return_internal_reference< 1 >());
    def("setAxes", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &))&gmtl::setAxes, return_internal_reference< 1 >());
#ifndef _MSC_VER
    def("setDirCos", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &))&gmtl::setDirCos,
        setDirCos_overloads_4_7()[return_internal_reference<1>()]);
    def("setDirCos", (gmtl::Matrix<double,3,3> & (*)(gmtl::Matrix<double,3,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &))&gmtl::setDirCos,
        setDirCos_overloads_4_7()[return_internal_reference<1>()]);
    def("setDirCos", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &))&gmtl::setDirCos,
        setDirCos_overloads_4_7()[return_internal_reference<1>()]);
    def("setDirCos", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &))&gmtl::setDirCos,
        setDirCos_overloads_4_7()[return_internal_reference<1>()]);
#endif
    def("setFrustum", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, float, float, float, float, float, float))&gmtl::setFrustum, return_internal_reference< 1 >());
    def("setFrustum", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, double, double, double, double, double, double))&gmtl::setFrustum, return_internal_reference< 1 >());
    def("setPerspective", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, float, float, float, float))&gmtl::setPerspective, return_internal_reference< 1 >());
    def("setPerspective", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, double, double, double, double))&gmtl::setPerspective, return_internal_reference< 1 >());
    def("setPure", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::Vec<float,3> &))&gmtl::setPure, return_internal_reference< 1 >());
    def("setPure", (gmtl::Quat<double> & (*)(gmtl::Quat<double> &, const gmtl::Vec<double,3> &))&gmtl::setPure, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > &, const gmtl::Matrix<float,3,3> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::Quat<double> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > &, const gmtl::Matrix<float,3,3> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > &, const gmtl::Matrix<float,3,3> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > &, const gmtl::Matrix<float,3,3> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > &, const gmtl::Matrix<float,3,3> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > &, const gmtl::Matrix<float,3,3> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Quat<double> & (*)(gmtl::Quat<double> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > &, const gmtl::Matrix<float,3,3> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::EulerAngle<float,gmtl::XYZ> & (*)(gmtl::EulerAngle<float,gmtl::XYZ> &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::EulerAngle<float,gmtl::ZXY> & (*)(gmtl::EulerAngle<float,gmtl::ZXY> &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::EulerAngle<float,gmtl::ZYX> & (*)(gmtl::EulerAngle<float,gmtl::ZYX> &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Quat<double> & (*)(gmtl::Quat<double> &, const gmtl::Matrix<double,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::AxisAngle<float> & (*)(gmtl::AxisAngle<float> &, gmtl::Quat<float>))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::AxisAngle<double> & (*)(gmtl::AxisAngle<double> &, gmtl::Quat<double>))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::EulerAngle<float,gmtl::ZXY> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::EulerAngle<float,gmtl::ZYX> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::EulerAngle<float,gmtl::XYZ> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::AxisAngle<float> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::AxisAngle<float> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::AxisAngle<double> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::AxisAngle<float> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::EulerAngle<float,gmtl::XYZ> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::EulerAngle<float,gmtl::ZYX> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::EulerAngle<float,gmtl::ZXY> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::EulerAngle<double,gmtl::XYZ> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::EulerAngle<float,gmtl::ZXY> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::EulerAngle<float,gmtl::ZYX> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::EulerAngle<float,gmtl::XYZ> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::EulerAngle<double,gmtl::ZXY> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::EulerAngle<double,gmtl::ZYX> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > &, const gmtl::Matrix<float,3,3> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Quat<float> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Quat<float> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<double,3,3> & (*)(gmtl::Matrix<double,3,3> &, const gmtl::Quat<double> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setScale", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Vec<float,2> &))&gmtl::setScale, return_internal_reference< 1 >());
    def("setScale", (gmtl::Matrix<double,3,3> & (*)(gmtl::Matrix<double,3,3> &, const double))&gmtl::setScale, return_internal_reference< 1 >());
    def("setScale", (gmtl::Matrix<double,3,3> & (*)(gmtl::Matrix<double,3,3> &, const gmtl::Vec<double,2> &))&gmtl::setScale, return_internal_reference< 1 >());
    def("setScale", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const float))&gmtl::setScale, return_internal_reference< 1 >());
    def("setScale", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Vec<float,3> &))&gmtl::setScale, return_internal_reference< 1 >());
    def("setScale", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const double))&gmtl::setScale, return_internal_reference< 1 >());
    def("setScale", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::Vec<double,3> &))&gmtl::setScale, return_internal_reference< 1 >());
    def("setScale", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const float))&gmtl::setScale, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Vec<float,4> & (*)(gmtl::Vec<float,4> &, const gmtl::Matrix<float,4,4> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Vec<float,3> & (*)(gmtl::Vec<float,3> &, const gmtl::Matrix<float,3,3> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Vec<double,3> & (*)(gmtl::Vec<double,3> &, const gmtl::Matrix<double,4,4> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Vec<float,3> & (*)(gmtl::Vec<float,3> &, const gmtl::Matrix<float,4,4> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Vec<float,4> & (*)(gmtl::Vec<float,4> &, const gmtl::Matrix<float,3,3> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Vec<float,2> & (*)(gmtl::Vec<float,2> &, const gmtl::Matrix<float,3,3> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Vec<double,2> & (*)(gmtl::Vec<double,2> &, const gmtl::Matrix<double,3,3> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::VecBase<float,4> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::VecBase<float,3> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::VecBase<float,4> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::VecBase<float,3> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::VecBase<double,3> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::VecBase<float,2> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Matrix<double,3,3> & (*)(gmtl::Matrix<double,3,3> &, const gmtl::VecBase<double,2> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setRow", (void (*)(gmtl::Vec<float, 3>&, const gmtl::Matrix<float, 3, 3>&, unsigned))&gmtl::setRow);
    def("setRow", (void (*)(gmtl::Vec<double, 3>&, const gmtl::Matrix<double, 3, 3>&, unsigned))&gmtl::setRow);
    def("setRow", (void (*)(gmtl::Vec<float, 4>&, const gmtl::Matrix<float, 4, 4>&, unsigned))&gmtl::setRow);
    def("setRow", (void (*)(gmtl::Vec<double, 4>&, const gmtl::Matrix<double, 4, 4>&, unsigned))&gmtl::setRow);
    def("makeRow", (gmtl::Vec<float, 3> (*)(const gmtl::Matrix<float, 3, 3>&, unsigned))&gmtl::makeRow);
    def("makeRow", (gmtl::Vec<double, 3> (*)(const gmtl::Matrix<double, 3, 3>&, unsigned))&gmtl::makeRow);
    def("makeRow", (gmtl::Vec<float, 4> (*)(const gmtl::Matrix<float, 4, 4>&, unsigned))&gmtl::makeRow);
    def("makeRow", (gmtl::Vec<double, 4> (*)(const gmtl::Matrix<double, 4, 4>&, unsigned))&gmtl::makeRow);
    def("setColumn", (void (*)(gmtl::Vec<float, 3>&, const gmtl::Matrix<float, 3, 3>&, unsigned))&gmtl::setColumn);
    def("setColumn", (void (*)(gmtl::Vec<double, 3>&, const gmtl::Matrix<double, 3, 3>&, unsigned))&gmtl::setColumn);
    def("setColumn", (void (*)(gmtl::Vec<float, 4>&, const gmtl::Matrix<float, 4, 4>&, unsigned))&gmtl::setColumn);
    def("setColumn", (void (*)(gmtl::Vec<double, 4>&, const gmtl::Matrix<double, 4, 4>&, unsigned))&gmtl::setColumn);
    def("makeColumn", (gmtl::Vec<float, 3> (*)(const gmtl::Matrix<float, 3, 3>&, unsigned))&gmtl::makeColumn);
    def("makeColumn", (gmtl::Vec<double, 3> (*)(const gmtl::Matrix<double, 3, 3>&, unsigned))&gmtl::makeColumn);
    def("makeColumn", (gmtl::Vec<float, 4> (*)(const gmtl::Matrix<float, 4, 4>&, unsigned))&gmtl::makeColumn);
    def("makeColumn", (gmtl::Vec<double, 4> (*)(const gmtl::Matrix<double, 4, 4>&, unsigned))&gmtl::makeColumn);
}

// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl-Xforms.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_gmtl_Xforms_h()
{
    def("xform", (gmtl::LineSeg<float> & (*)(gmtl::LineSeg<float> &, const gmtl::Matrix<float,4,4> &, const gmtl::LineSeg<float> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::LineSeg<double> & (*)(gmtl::LineSeg<double> &, const gmtl::Matrix<double,4,4> &, const gmtl::LineSeg<double> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Ray<float> & (*)(gmtl::Ray<float> &, const gmtl::Matrix<float,4,4> &, const gmtl::Ray<float> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Ray<double> & (*)(gmtl::Ray<double> &, const gmtl::Matrix<double,4,4> &, const gmtl::Ray<double> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Point<float,4> & (*)(gmtl::Point<float,4> &, const gmtl::Matrix<float,4,4> &, const gmtl::Point<float,4> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Point<float,3> & (*)(gmtl::Point<float,3> &, const gmtl::Matrix<float,4,4> &, const gmtl::Point<float,3> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Point<double,4> & (*)(gmtl::Point<double,4> &, const gmtl::Matrix<double,4,4> &, const gmtl::Point<double,4> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Point<float,4> & (*)(gmtl::Point<float,4> &, const gmtl::Matrix<float,4,4> &, const gmtl::Point<float,4> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Vec<double,4> & (*)(gmtl::Vec<double,4> &, const gmtl::Matrix<double,4,4> &, const gmtl::Vec<double,4> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Vec<double,3> & (*)(gmtl::Vec<double,3> &, const gmtl::Matrix<double,4,4> &, const gmtl::Vec<double,3> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Vec<float,4> & (*)(gmtl::Vec<float,4> &, const gmtl::Matrix<float,4,4> &, const gmtl::Vec<float,4> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Vec<float,3> & (*)(gmtl::Vec<float,3> &, const gmtl::Matrix<float,4,4> &, const gmtl::Vec<float,3> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Vec<double,4> & (*)(gmtl::Vec<double,4> &, const gmtl::Matrix<double,4,4> &, const gmtl::Vec<double,4> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Vec<float,4> & (*)(gmtl::Vec<float,4> &, const gmtl::Matrix<float,4,4> &, const gmtl::Vec<float,4> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Vec<double,3> & (*)(gmtl::Vec<double,3> &, const gmtl::Matrix<double,3,3> &, const gmtl::Vec<double,3> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Vec<float,3> & (*)(gmtl::Vec<float,3> &, const gmtl::Matrix<float,3,3> &, const gmtl::Vec<float,3> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Vec<double,2> & (*)(gmtl::Vec<double,2> &, const gmtl::Matrix<double,3,3> &, const gmtl::Vec<double,2> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Vec<float,2> & (*)(gmtl::Vec<float,2> &, const gmtl::Matrix<float,3,3> &, const gmtl::Vec<float,2> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::VecBase<double,3> & (*)(gmtl::VecBase<double,3> &, const gmtl::Quat<double> &, const gmtl::VecBase<double,3> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Point<double,4> & (*)(gmtl::Point<double,4> &, const gmtl::Matrix<double,4,4> &, const gmtl::Point<double,4> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Point<double,3> & (*)(gmtl::Point<double,3> &, const gmtl::Matrix<double,4,4> &, const gmtl::Point<double,3> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Point<double,3> & (*)(gmtl::Point<double,3> &, const gmtl::Matrix<double,3,3> &, const gmtl::Point<double,3> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Point<float,3> & (*)(gmtl::Point<float,3> &, const gmtl::Matrix<float,3,3> &, const gmtl::Point<float,3> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::VecBase<float,3> & (*)(gmtl::VecBase<float,3> &, const gmtl::Quat<float> &, const gmtl::VecBase<float,3> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Point<double,2> & (*)(gmtl::Point<double,2> &, const gmtl::Matrix<double,3,3> &, const gmtl::Point<double,2> &))&gmtl::xform, return_internal_reference< 1 >());
    def("xform", (gmtl::Point<float,2> & (*)(gmtl::Point<float,2> &, const gmtl::Matrix<float,3,3> &, const gmtl::Point<float,2> &))&gmtl::xform, return_internal_reference< 1 >());
}

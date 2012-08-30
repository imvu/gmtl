// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl-MatrixOps.h>

// Using =======================================================================
using namespace boost::python;

// Declarations ================================================================
namespace  {


BOOST_PYTHON_FUNCTION_OVERLOADS(isEqual_overloads_2_3, gmtl::isEqual, 2, 3)


}// namespace 

// Module ======================================================================
void _Export_gmtl_MatrixOps_h()
{
    def("add", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Matrix<float,4,4> &, const gmtl::Matrix<float,4,4> &))&gmtl::add, return_internal_reference< 1 >());
    def("add", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Matrix<float,3,3> &, const gmtl::Matrix<float,3,3> &))&gmtl::add, return_internal_reference< 1 >());
    def("identity", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &))&gmtl::identity, return_internal_reference< 1 >());
    def("identity", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &))&gmtl::identity, return_internal_reference< 1 >());
    def("invertTrans", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Matrix<float,3,3> &))&gmtl::invertTrans, return_internal_reference< 1 >());
    def("invertTrans", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Matrix<float,4,4> &))&gmtl::invertTrans, return_internal_reference< 1 >());
    def("invertOrthogonal", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Matrix<float,3,3> &))&gmtl::invertOrthogonal, return_internal_reference< 1 >());
    def("invertOrthogonal", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Matrix<float,4,4> &))&gmtl::invertOrthogonal, return_internal_reference< 1 >());
    def("invertAffine", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Matrix<float,3,3> &))&gmtl::invertAffine, return_internal_reference< 1 >());
    def("invertAffine", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Matrix<float,4,4> &))&gmtl::invertAffine, return_internal_reference< 1 >());
    def("invert", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Matrix<float,3,3> &))&gmtl::invert, return_internal_reference< 1 >());
    def("invert", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Matrix<float,4,4> &))&gmtl::invert, return_internal_reference< 1 >());
    def("invert", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &))&gmtl::invert, return_internal_reference< 1 >());
    def("invert", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &))&gmtl::invert, return_internal_reference< 1 >());
    def("invertFull_GJ", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Matrix<float,3,3> &))&gmtl::invertFull_GJ, return_internal_reference< 1 >());
    def("invertFull_GJ", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Matrix<float,4,4> &))&gmtl::invertFull_GJ, return_internal_reference< 1 >());
    def("invertFull", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Matrix<float,3,3> &))&gmtl::invertFull, return_internal_reference< 1 >());
    def("invertFull", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Matrix<float,4,4> &))&gmtl::invertFull, return_internal_reference< 1 >());
    def("mult", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Matrix<float,4,4> &, const gmtl::Matrix<float,4,4> &))&gmtl::mult, return_internal_reference< 1 >());
    def("mult", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Matrix<float,3,3> &, const float &))&gmtl::mult, return_internal_reference< 1 >());
    def("mult", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Matrix<float,4,4> &, const float &))&gmtl::mult, return_internal_reference< 1 >());
    def("mult", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, float))&gmtl::mult, return_internal_reference< 1 >());
    def("mult", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Matrix<float,3,3> &, const gmtl::Matrix<float,3,3> &))&gmtl::mult, return_internal_reference< 1 >());
    def("mult", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, float))&gmtl::mult, return_internal_reference< 1 >());
    def("postMult", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Matrix<float,3,3> &))&gmtl::postMult, return_internal_reference< 1 >());
    def("postMult", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Matrix<float,4,4> &))&gmtl::postMult, return_internal_reference< 1 >());
    def("preMult", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Matrix<float,3,3> &))&gmtl::preMult, return_internal_reference< 1 >());
    def("preMult", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Matrix<float,4,4> &))&gmtl::preMult, return_internal_reference< 1 >());
    def("sub", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Matrix<float,4,4> &, const gmtl::Matrix<float,4,4> &))&gmtl::sub, return_internal_reference< 1 >());
    def("sub", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Matrix<float,3,3> &, const gmtl::Matrix<float,3,3> &))&gmtl::sub, return_internal_reference< 1 >());
    def("transpose", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Matrix<float,3,3> &))&gmtl::transpose, return_internal_reference< 1 >());
    def("transpose", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Matrix<float,4,4> &))&gmtl::transpose, return_internal_reference< 1 >());
    def("transpose", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &))&gmtl::transpose, return_internal_reference< 1 >());
    def("transpose", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &))&gmtl::transpose, return_internal_reference< 1 >());
    def("zero", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &))&gmtl::zero, return_internal_reference< 1 >());
    def("zero", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &))&gmtl::zero, return_internal_reference< 1 >());
    def("isEqual", (bool (*)(const gmtl::Matrix<float,4,4> &, const gmtl::Matrix<float,4,4> &, const float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Matrix<float,3,3> &, const gmtl::Matrix<float,3,3> &, const float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("combineMatrixStates", &gmtl::combineMatrixStates);
}

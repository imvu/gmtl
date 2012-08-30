// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl-PlaneOps.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_gmtl_PlaneOps_h()
{
    def("findNearestPt", (float (*)(const gmtl::Plane<float> &, const gmtl::Point<float,3> &, gmtl::Point<float,3> &))&gmtl::findNearestPt);
    def("findNearestPt", (double (*)(const gmtl::Plane<double> &, const gmtl::Point<double,3> &, gmtl::Point<double,3> &))&gmtl::findNearestPt);
    def("reflect", (void (*)(gmtl::Point<float,3> &, const gmtl::Plane<float> &, const gmtl::Point<float,3> &))&gmtl::reflect);
    def("reflect", (void (*)(gmtl::Point<double,3> &, const gmtl::Plane<double> &, const gmtl::Point<double,3> &))&gmtl::reflect);
    def("distance", (double (*)(const gmtl::Plane<double> &, const gmtl::Point<double,3> &))&gmtl::distance);
    def("distance", (float (*)(const gmtl::Plane<float> &, const gmtl::Point<float,3> &))&gmtl::distance);
    def("whichSide", (gmtl::PlaneSide (*)(const gmtl::Plane<double> &, const gmtl::Point<double,3> &))&gmtl::whichSide);
    def("whichSide", (gmtl::PlaneSide (*)(const gmtl::Plane<float> &, const gmtl::Point<float,3> &))&gmtl::whichSide);
    def("whichSide", (gmtl::PlaneSide (*)(const gmtl::Plane<double> &, const gmtl::Point<double,3> &, const double &))&gmtl::whichSide);
    def("whichSide", (gmtl::PlaneSide (*)(const gmtl::Plane<float> &, const gmtl::Point<float,3> &, const float &))&gmtl::whichSide);
    def("isEqual", (bool (*)(const gmtl::Plane<float> &, const gmtl::Plane<float> &, const float &))&gmtl::isEqual);
    def("isEqual", (bool (*)(const gmtl::Plane<double> &, const gmtl::Plane<double> &, const double &))&gmtl::isEqual);
}

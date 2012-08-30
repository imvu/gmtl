// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl-LineSegOps.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_gmtl_LineSegOps_h()
{
    def("distance", (float (*)(const gmtl::LineSeg<float> &, const gmtl::Point<float,3> &))&gmtl::distance);
    def("distance", (double (*)(const gmtl::LineSeg<double> &, const gmtl::Point<double,3> &))&gmtl::distance);
    def("distanceSquared", (double (*)(const gmtl::LineSeg<double> &, const gmtl::Point<double,3> &))&gmtl::distanceSquared);
    def("distanceSquared", (float (*)(const gmtl::LineSeg<float> &, const gmtl::Point<float,3> &))&gmtl::distanceSquared);
    def("findNearestPt", (gmtl::Point<float,3> (*)(const gmtl::LineSeg<float> &, const gmtl::Point<float,3> &))&gmtl::findNearestPt);
    def("findNearestPt", (gmtl::Point<double,3> (*)(const gmtl::LineSeg<double> &, const gmtl::Point<double,3> &))&gmtl::findNearestPt);
}

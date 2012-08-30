// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl-RayOps.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_gmtl_RayOps_h()
{
    def("isEqual", (bool (*)(const gmtl::Ray<double> &, const gmtl::Ray<double> &, const double &))&gmtl::isEqual);
    def("isEqual", (bool (*)(const gmtl::Ray<float> &, const gmtl::Ray<float> &, const float &))&gmtl::isEqual);
}

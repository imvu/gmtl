// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl-FrustumOps.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_gmtl_FrustumOps_h()
{
    def("normalize", (void (*)(gmtl::Frustum<float> &))&gmtl::normalize);
    def("normalize", (void (*)(gmtl::Frustum<double> &))&gmtl::normalize);
}

// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl-containment-wrappers.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_gmtl_containment_wrappers_h()
{
    def("isInVolume", (tuple (*)(const gmtl::Frustum<float> &, const gmtl::Point<float, 3> &))&gmtlWrappers::isInVolume);
    def("isInVolume", (tuple (*)(const gmtl::Frustum<double> &, const gmtl::Point<double, 3> &))&gmtlWrappers::isInVolume);
}

// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl-TriOps.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_gmtl_TriOps_h()
{
    def("center", (gmtl::Point<double,3> (*)(const gmtl::Tri<double> &))&gmtl::center);
    def("center", (gmtl::Point<int,3> (*)(const gmtl::Tri<int> &))&gmtl::center);
    def("center", (gmtl::Point<float,3> (*)(const gmtl::Tri<float> &))&gmtl::center);
    def("normal", (gmtl::Vec<double,3> (*)(const gmtl::Tri<double> &))&gmtl::normal);
    def("normal", (gmtl::Vec<int,3> (*)(const gmtl::Tri<int> &))&gmtl::normal);
    def("normal", (gmtl::Vec<float,3> (*)(const gmtl::Tri<float> &))&gmtl::normal);
    def("isEqual", (bool (*)(const gmtl::Tri<float> &, const gmtl::Tri<float> &, const float &))&gmtl::isEqual);
    def("isEqual", (bool (*)(const gmtl::Tri<double> &, const gmtl::Tri<double> &, const double &))&gmtl::isEqual);
}

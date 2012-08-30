// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

// This file was originally part of PyJuggler.

// PyJuggler is (C) Copyright 2002, 2003 by Patrick Hartling
// Distributed under the GNU Lesser General Public License 2.1.  (See
// accompanying file COPYING.txt or http://www.gnu.org/copyleft/lesser.txt)

// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl-intersect-wrappers.h>

// Using =======================================================================
using namespace boost::python;


// Module ======================================================================
void _Export_gmtl_intersect_wrappers_h()
{
   def("intersect", (tuple (*)(const gmtl::AABox<float>&, const gmtl::AABox<float>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::AABox<double>&, const gmtl::AABox<double>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::AABox<float>&, const gmtl::Point<float,3>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::AABox<double>&, const gmtl::Point<double,3>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::AABox<float>&, const gmtl::Vec<float,3>&, const gmtl::AABox<float>&, const gmtl::Vec<float,3>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::AABox<float>&, const gmtl::LineSeg<float>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::AABox<double>&, const gmtl::LineSeg<double>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::LineSeg<float>&, const gmtl::AABox<float>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::LineSeg<double>&, const gmtl::AABox<double>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::AABox<float>&, const gmtl::Ray<float>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::AABox<double>&, const gmtl::Ray<double>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::Ray<float>&, const gmtl::AABox<float>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::Ray<double>&, const gmtl::AABox<double>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::AABox<double>&, const gmtl::Vec<double,3>&, const gmtl::AABox<double>&, const gmtl::Vec<double,3>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::Sphere<float>&, const gmtl::Vec<float,3>&, const gmtl::Sphere<float>&, const gmtl::Vec<float,3>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::Sphere<double>&, const gmtl::Vec<double,3>&, const gmtl::Sphere<double>&, const gmtl::Vec<double,3>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::AABox<float>&, const gmtl::Sphere<float>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::AABox<double>&, const gmtl::Sphere<double>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::Sphere<float>&, const gmtl::AABox<float>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::Sphere<double>&, const gmtl::AABox<double>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::Sphere<float>&, const gmtl::Point<float,3>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::Sphere<double>&, const gmtl::Point<double,3>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::Sphere<float>&, const gmtl::Ray<float>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::Sphere<double>&, const gmtl::Ray<double>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::Sphere<float>&, const gmtl::LineSeg<float>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::Sphere<double>&, const gmtl::LineSeg<double>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::Plane<float>&, const gmtl::Ray<float>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::Plane<double>&, const gmtl::Ray<double>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::Plane<float>&, const gmtl::LineSeg<float>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::Plane<double>&, const gmtl::LineSeg<double>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::Tri<float>&, const gmtl::Ray<float>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::Tri<float>&, const gmtl::Ray<float>&)) &gmtlWrappers::intersect);
   def("intersectDoubleSided", (tuple (*)(const gmtl::Tri<double>&, const gmtl::Ray<double>&)) &gmtlWrappers::intersectDoubleSided);
   def("intersectDoubleSided", (tuple (*)(const gmtl::Tri<double>&, const gmtl::Ray<double>&)) &gmtlWrappers::intersectDoubleSided);
   def("intersect", (tuple (*)(const gmtl::Tri<float>&, const gmtl::LineSeg<float>&)) &gmtlWrappers::intersect);
   def("intersect", (tuple (*)(const gmtl::Tri<double>&, const gmtl::LineSeg<double>&)) &gmtlWrappers::intersect);
   def("intersectVolume", (tuple (*)(const gmtl::Sphere<float>&, const gmtl::Ray<float>&)) &gmtlWrappers::intersectVolume);
   def("intersectVolume", (tuple (*)(const gmtl::Sphere<double>&, const gmtl::Ray<double>&)) &gmtlWrappers::intersectVolume);
   def("intersectVolume", (tuple (*)(const gmtl::Sphere<float>&, const gmtl::LineSeg<float>&)) &gmtlWrappers::intersectVolume);
   def("intersectVolume", (tuple (*)(const gmtl::Sphere<double>&, const gmtl::LineSeg<double>&)) &gmtlWrappers::intersectVolume);
}

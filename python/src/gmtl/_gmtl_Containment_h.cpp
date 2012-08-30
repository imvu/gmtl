// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl-Containment.h>

// Using =======================================================================
using namespace boost::python;

// Declarations ================================================================
namespace gmtlWrappers
{

template<typename DATA_TYPE>
void makeVolume(gmtl::Sphere<DATA_TYPE>& container, list pts)
{
   const unsigned int size = extract<unsigned int>(pts.attr("__len__")());
   std::vector< gmtl::Point<DATA_TYPE, 3> > pt_vec(size);

   for ( unsigned int i = 0; i < size; ++i )
   {
#if defined(__GNUC__) && __GNUC__ == 3 && __GNUC_MINOR__ == 2
      gmtl::Point<DATA_TYPE, 3> temp = extract< gmtl::Point<DATA_TYPE, 3> >(pts[i]);
      pt_vec[i] = temp;
#else
      pt_vec[i] = extract< gmtl::Point<DATA_TYPE, 3> >(pts[i]);
#endif
   }

   gmtl::makeVolume(container, pt_vec);
}

}

namespace  {


BOOST_PYTHON_FUNCTION_OVERLOADS(isOnVolume_overloads_2_3, gmtl::isOnVolume, 2, 3)


}// namespace 

// Module ======================================================================
void _Export_gmtl_Containment_h()
{
    def("extendVolume", (void (*)(gmtl::Sphere<double> &, const gmtl::Sphere<double> &))&gmtl::extendVolume, return_internal_reference< 1 >());
    def("extendVolume", (void (*)(gmtl::Sphere<float> &, const gmtl::Sphere<float> &))&gmtl::extendVolume, return_internal_reference< 1 >());
    def("extendVolume", (void (*)(gmtl::Sphere<float> &, const gmtl::Point<float,3> &))&gmtl::extendVolume, return_internal_reference< 1 >());
    def("extendVolume", (void (*)(gmtl::AABox<double> &, const gmtl::Point<double,3> &))&gmtl::extendVolume, return_internal_reference< 1 >());
    def("extendVolume", (void (*)(gmtl::AABox<double> &, const gmtl::AABox<double> &))&gmtl::extendVolume, return_internal_reference< 1 >());
    def("extendVolume", (void (*)(gmtl::AABox<float> &, const gmtl::AABox<float> &))&gmtl::extendVolume, return_internal_reference< 1 >());
    def("extendVolume", (void (*)(gmtl::Sphere<double> &, const gmtl::Point<double,3> &))&gmtl::extendVolume, return_internal_reference< 1 >());
    def("extendVolume", (void (*)(gmtl::AABox<float> &, const gmtl::Point<float,3> &))&gmtl::extendVolume, return_internal_reference< 1 >());
    def("isInVolume", (bool (*)(const gmtl::Sphere<float> &, const gmtl::Sphere<float> &))&gmtl::isInVolume);
    def("isInVolume", (bool (*)(const gmtl::Sphere<double> &, const gmtl::Point<double,3> &))&gmtl::isInVolume);
    def("isInVolume", (bool (*)(const gmtl::Sphere<double> &, const gmtl::Sphere<double> &))&gmtl::isInVolume);
    def("isInVolume", (bool (*)(const gmtl::Sphere<float> &, const gmtl::Point<float,3> &))&gmtl::isInVolume);
    def("isInVolume", (bool (*)(const gmtl::AABox<double> &, const gmtl::Point<double,3> &))&gmtl::isInVolume);
    def("isInVolume", (bool (*)(const gmtl::AABox<float> &, const gmtl::Point<float,3> &))&gmtl::isInVolume);
    def("isInVolume", (bool (*)(const gmtl::AABox<double> &, const gmtl::AABox<double> &))&gmtl::isInVolume);
    def("isInVolume", (bool (*)(const gmtl::AABox<float> &, const gmtl::AABox<float> &))&gmtl::isInVolume);
    def("isInVolume", (bool (*)(const gmtl::Frustum<double> &, const gmtl::Sphere<double> &))&gmtl::isInVolume);
    def("isInVolume", (bool (*)(const gmtl::Frustum<float> &, const gmtl::Sphere<float> &))&gmtl::isInVolume);
    def("isInVolume", (bool (*)(const gmtl::Frustum<double> &, const gmtl::AABox<double> &))&gmtl::isInVolume);
    def("isInVolume", (bool (*)(const gmtl::Frustum<float> &, const gmtl::AABox<float> &))&gmtl::isInVolume);
    def("isInVolume", (bool (*)(const gmtl::Frustum<double> &, const gmtl::Tri<double> &))&gmtl::isInVolume);
    def("isInVolume", (bool (*)(const gmtl::Frustum<float> &, const gmtl::Tri<float> &))&gmtl::isInVolume);
    def("isInVolumeExclusive", (bool (*)(const gmtl::AABox<double> &, const gmtl::Point<double,3> &))&gmtl::isInVolumeExclusive);
    def("isInVolumeExclusive", (bool (*)(const gmtl::AABox<float> &, const gmtl::Point<float,3> &))&gmtl::isInVolumeExclusive);
    def("isOnVolume", (bool (*)(const gmtl::Sphere<double> &, const gmtl::Point<double,3> &, const double &))&gmtl::isOnVolume, isOnVolume_overloads_2_3());
    def("isOnVolume", (bool (*)(const gmtl::Sphere<float> &, const gmtl::Point<float,3> &, const float &))&gmtl::isOnVolume, isOnVolume_overloads_2_3());
    def("makeVolume", (void (*)(gmtl::Sphere<float> &, list))&gmtlWrappers::makeVolume, return_internal_reference< 1 >());
    def("makeVolume", (void (*)(gmtl::AABox<float> &, const gmtl::Sphere<float> &))&gmtl::makeVolume, return_internal_reference< 1 >());
    def("makeVolume", (void (*)(gmtl::Sphere<double> &, list))&gmtlWrappers::makeVolume, return_internal_reference< 1 >());
    def("makeVolume", (void (*)(gmtl::AABox<double> &, const gmtl::Sphere<double> &))&gmtl::makeVolume, return_internal_reference< 1 >());
}

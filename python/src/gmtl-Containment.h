// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _PYGMTL_CONTAINMENT_H_
#define _PYGMTL_CONTAINMENT_H_

// This file makes declarations of the templated function instantiations
// needed for Boost.Python to do its thing.

#include <gmtl/Containment.h>


#if ! defined(__APPLE__)
namespace gmtl
{
   template bool isInVolume(const gmtl::Spheref&, const gmtl::Point3f&);
   template bool isInVolume(const gmtl::Sphered&, const gmtl::Point3d&);

   template bool isInVolume(const gmtl::Spheref&, const gmtl::Spheref&);
   template bool isInVolume(const gmtl::Sphered&, const gmtl::Sphered&);

   template void extendVolume(gmtl::Spheref&, const gmtl::Point3f&);
   template void extendVolume(gmtl::Sphered&, const gmtl::Point3d&);

   template void extendVolume(gmtl::Spheref&, const gmtl::Spheref&);
   template void extendVolume(gmtl::Sphered&, const gmtl::Sphered&);

   template void makeVolume(gmtl::Spheref&, const std::vector<gmtl::Point3f>&);
   template void makeVolume(gmtl::Sphered&, const std::vector<gmtl::Point3d>&);

   template bool isOnVolume(const gmtl::Spheref&, const gmtl::Point3f&);
   template bool isOnVolume(const gmtl::Sphered&, const gmtl::Point3d&);

   template bool isOnVolume(const gmtl::Spheref&, const gmtl::Point3f&,
                            const float&);
   template bool isOnVolume(const gmtl::Sphered&, const gmtl::Point3d&,
                            const double&);

   template bool isInVolume(const gmtl::AABoxf&, const gmtl::Point3f&);
   template bool isInVolume(const gmtl::AABoxd&, const gmtl::Point3d&);

   template bool isInVolumeExclusive(const gmtl::AABoxf&, const gmtl::Point3f&);
   template bool isInVolumeExclusive(const gmtl::AABoxd&, const gmtl::Point3d&);

   template bool isInVolume(const gmtl::AABoxf&, const gmtl::AABoxf&);
   template bool isInVolume(const gmtl::AABoxd&, const gmtl::AABoxd&);

   template void extendVolume(gmtl::AABoxf&, const gmtl::Point3f&);
   template void extendVolume(gmtl::AABoxd&, const gmtl::Point3d&);

   template void extendVolume(gmtl::AABoxf&, const gmtl::AABoxf&);
   template void extendVolume(gmtl::AABoxd&, const gmtl::AABoxd&);

   template void makeVolume(gmtl::AABoxf&, const gmtl::Spheref&);
   template void makeVolume(gmtl::AABoxd&, const gmtl::Sphered&);

   template bool isInVolume(const Frustumf&, const Spheref&);
   template bool isInVolume(const Frustumd&, const Sphered&);

   template bool isInVolume(const Frustumf&, const AABoxf&);
   template bool isInVolume(const Frustumd&, const AABoxd&);

   template bool isInVolume(const Frustumf&, const Trif&);
   template bool isInVolume(const Frustumd&, const Trid&);
}
#endif


#endif /* _PYGMTL_CONTAINMENT_H_ */

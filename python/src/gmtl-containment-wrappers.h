// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _PYGMTL_GMTL_CONTAINMENT_WRAPPERS_H_
#define _PYGMTL_GMTL_CONTAINMENT_WRAPPERS_H_

// This file makes declarations of the templated function instantiations
// needed for Boost.Python to do its thing.  More specifically, the functions
// defined here wrap instantiations of gmtl::intersect() and change the return
// type to be a Python tuple.

#include <boost/python/tuple.hpp>

#include <gmtl/Containment.h>


namespace gmtlWrappers
{
   using namespace boost::python;

   template<typename T>
   tuple isInVolume(const gmtl::Frustum<T>& frustum,
                    const gmtl::Point<T, 3>& point)
   {
      unsigned int index;
      bool result = gmtl::isInVolume(frustum, point, index);
      return make_tuple(result, index);
   }
}

#if ! defined(__APPLE__)
namespace gmtlWrappers
{
   template tuple isInVolume(const gmtl::Frustumf&, const gmtl::Point3f&);
   template tuple isInVolume(const gmtl::Frustumd&, const gmtl::Point3d&);
}
#endif


#endif /* _PYGMTL_GMTL_CONTAINMENT_WRAPPERS_H_ */

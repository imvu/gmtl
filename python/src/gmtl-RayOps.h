// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _PYGMTL_RAY_OPS_H_
#define _PYGMTL_RAY_OPS_H_

// This file makes declarations of the templated function instantiations
// needed for Boost.Python to do its thing.

#include <gmtl/Ray.h>
#include <gmtl/RayOps.h>


#if ! defined(__APPLE__)
namespace gmtl
{
   template bool isEqual(const gmtl::Rayd&, const gmtl::Rayd&,
                         const double&);
   template bool isEqual(const gmtl::Rayf&, const gmtl::Rayf&,
                         const float&);
}
#endif


#endif /* _PYGMTL_LINE_SEG_OPS_H_ */

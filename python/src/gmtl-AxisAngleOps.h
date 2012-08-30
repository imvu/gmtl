// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _PYGMTL_AXIS_ANGLE_OPS_H_
#define _PYGMTL_AXIS_ANGLE_OPS_H_

// This file makes declarations of the templated function instantiations
// needed for Boost.Python to do its thing.

#include <gmtl/AxisAngle.h>
#include <gmtl/AxisAngleOps.h>


#if ! defined(__APPLE__)
namespace gmtl
{
   template bool isEqual(const AxisAnglef&, const AxisAnglef&, const float);
   template bool isEqual(const AxisAngled&, const AxisAngled&, const double);
}
#endif


#endif /* _PYGMTL_AXIS_ANGLE_OPS_H_ */

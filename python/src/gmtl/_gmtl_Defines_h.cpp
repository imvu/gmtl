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
#include <gmtl/Defines.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_gmtl_Defines_h()
{
    enum_< gmtl::PlaneSide >("PlaneSide")
        .value("NEG_SIDE", gmtl::NEG_SIDE)
        .value("POS_SIDE", gmtl::POS_SIDE)
        .value("ON_PLANE", gmtl::ON_PLANE)
    ;

    enum_< gmtl::VectorIndex >("VectorIndex")
        .value("Xelt", gmtl::Xelt)
        .value("Yelt", gmtl::Yelt)
        .value("Welt", gmtl::Welt)
        .value("Zelt", gmtl::Zelt)
    ;

}

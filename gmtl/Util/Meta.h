// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_METAPROGRAMMING_H
#define _GMTL_METAPROGRAMMING_H

#include <gmtl/Defines.h>

/* Taken from boost (see boost.org) */

// Helper macro GMTL_JOIN:
// The following piece of macro magic joins the two
// arguments together, even when one of the arguments is
// itself a macro (see 16.3.1 in C++ standard).  The key
// is that macro expansion of macro arguments does not
// occur in BOOST_DO_JOIN2 but does in BOOST_DO_JOIN.
//
#define GMTL_JOIN( X, Y ) GMTL_DO_JOIN( X, Y )
#define GMTL_DO_JOIN( X, Y ) GMTL_DO_JOIN2(X,Y)
#define GMTL_DO_JOIN2( X, Y ) X##Y


#endif

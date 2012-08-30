// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _PYGMTL_CALLABLE_WRAPPERS_H_
#define _PYGMTL_CALLABLE_WRAPPERS_H_

// This file makes declarations of the templated function instantiations
// needed for Boost.Python to do its thing.

#include <gmtl/Matrix.h>


namespace gmtlWrappers
{
   template<typename DATA_TYPE, unsigned ROWS, unsigned COLS>
   DATA_TYPE callable(gmtl::Matrix<DATA_TYPE, ROWS, COLS>* m,
                      const unsigned int row, const unsigned int col)
   {
      return (*m)(row, col);
   }
}

#if ! defined(__APPLE__)
namespace gmtlWrappers
{
   template float callable(gmtl::Matrix33f*, const unsigned int,
                           const unsigned int);
   template float callable(gmtl::Matrix44f*, const unsigned int,
                           const unsigned int);
}
#endif


#endif /* _PYGMTL_CALLABLE_WRAPPERS_H_ */

// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_MATRIXSTATETRACKING_TEST_H_
#define _GMTL_MATRIXSTATETRACKING_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   class MatrixStateTrackingTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE( MatrixStateTrackingTest );

      CPPUNIT_TEST( testMatrixStateTracking );

      CPPUNIT_TEST_SUITE_END();

   public:
      void testMatrixStateTracking();
   };
}

#endif

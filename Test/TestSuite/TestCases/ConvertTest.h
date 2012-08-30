// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_CONVERT_TEST_H_
#define _GMTL_CONVERT_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

/// @todo test convert( vec, matrix ), convert( matrix, vec )

namespace gmtlTest
{
   class ConvertTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(ConvertTest);

      CPPUNIT_TEST(testConvertVecToPureQuat);
      CPPUNIT_TEST(testConvertQuatMat_MatQuat);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testConvertVecToPureQuat();
      void testConvertQuatMat_MatQuat();
   };
}

#endif

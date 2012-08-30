// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_AABOX_OPS_TEST_H_
#define _GMTL_AABOX_OPS_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class AABoxOpsTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(AABoxOpsTest);

      CPPUNIT_TEST(testEqualityCompare);
      CPPUNIT_TEST(testIsEqual);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testEqualityCompare();
      void testIsEqual();
   };

   /**
    * Metric tests.
    */
   class AABoxOpsMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(AABoxOpsMetricTest);

      CPPUNIT_TEST(testTimingEqualityCompare);
      CPPUNIT_TEST(testTimingIsEqual);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testTimingEqualityCompare();
      void testTimingIsEqual();
   };
}

#endif

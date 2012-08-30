// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_COORD_COMPARE_TEST_
#define _GMTL_COORD_COMPARE_TEST_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class CoordCompareTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(CoordCompareTest);

      CPPUNIT_TEST(testCoordEqualityFloatTest);
      CPPUNIT_TEST(testCoordEqualityDoubleTest);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testCoordEqualityFloatTest();
      void testCoordEqualityDoubleTest();
   };

   /**
    * Metric tests.
    */
   class CoordCompareMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(CoordCompareMetricTest);

      CPPUNIT_TEST(testCoordTimingOpEqualityTest);
      CPPUNIT_TEST(testCoordTimingOpNotEqualityTest);
      CPPUNIT_TEST(testCoordTimingIsEqualTest);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testCoordTimingOpEqualityTest();
      void testCoordTimingOpNotEqualityTest();
      void testCoordTimingIsEqualTest();
   };
}

#endif

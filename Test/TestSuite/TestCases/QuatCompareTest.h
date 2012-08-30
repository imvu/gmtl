// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_QUAT_COMPARE_TEST_H_
#define _GMTL_QUAT_COMPARE_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class QuatCompareTest : public CppUnit::TestCase
   {
      CPPUNIT_TEST_SUITE(QuatCompareTest);

      CPPUNIT_TEST(testQuatEquiv);
      CPPUNIT_TEST(testQuatEqualityFloatTest);
      CPPUNIT_TEST(testQuatEqualityDoubleTest);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testQuatEquiv();
      void testQuatEqualityFloatTest();
      void testQuatEqualityDoubleTest();
   };

   /**
    * Metric tests.
    */
   class QuatCompareMetricTest : public CppUnit::TestCase
   {
      CPPUNIT_TEST_SUITE(QuatCompareMetricTest);

      CPPUNIT_TEST(testQuatTimingOpEqualityTest);
      CPPUNIT_TEST(testQuatTimingOpNotEqualityTest);
      CPPUNIT_TEST(testQuatTimingIsEqualTest);
      CPPUNIT_TEST(testQuatTimingEquiv);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testQuatTimingOpEqualityTest();
      void testQuatTimingOpNotEqualityTest();
      void testQuatTimingIsEqualTest();
      void testQuatTimingEquiv();
   };
}

#endif

// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_EULER_ANGLE_COMPARE_TEST_H_
#define _GMTL_EULER_ANGLE_COMPARE_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class EulerAngleCompareTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(EulerAngleCompareTest);

      CPPUNIT_TEST(testEulerAngleEqualityFloatTest);
      CPPUNIT_TEST(testEulerAngleEqualityDoubleTest);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testEulerAngleEqualityFloatTest();
      void testEulerAngleEqualityDoubleTest();
   };

   /**
    * Metric tests.
    */
   class EulerAngleCompareMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(EulerAngleCompareMetricTest);

      CPPUNIT_TEST(testEulerAngleTimingOpEqualityTest);
      CPPUNIT_TEST(testEulerAngleTimingOpNotEqualityTest);
      CPPUNIT_TEST(testEulerAngleTimingIsEqualTest);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testEulerAngleTimingOpEqualityTest();
      void testEulerAngleTimingOpNotEqualityTest();
      void testEulerAngleTimingIsEqualTest();
   };
}

#endif

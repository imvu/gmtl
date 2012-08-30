// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _AXIS_ANGLE_COMPARE_TEST_H_
#define _AXIS_ANGLE_COMPARE_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class AxisAngleCompareTest : public CppUnit::TestCase
   {
      CPPUNIT_TEST_SUITE(AxisAngleCompareTest);

      CPPUNIT_TEST(testAxisAngleEqualityFloatTest);
      CPPUNIT_TEST(testAxisAngleEqualityDoubleTest);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testAxisAngleEqualityFloatTest();
      void testAxisAngleEqualityDoubleTest();
   };

   /**
    * Metric tests.
    */
   class AxisAngleCompareMetricTest : public CppUnit::TestCase
   {
      CPPUNIT_TEST_SUITE(AxisAngleCompareMetricTest);

      CPPUNIT_TEST(testAxisAngleTimingOpEqualityTest);
      CPPUNIT_TEST(testAxisAngleTimingOpNotEqualityTest);
      CPPUNIT_TEST(testAxisAngleTimingIsEqualTest);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testAxisAngleTimingOpEqualityTest();
      void testAxisAngleTimingOpNotEqualityTest();
      void testAxisAngleTimingIsEqualTest();
   };
}

#endif

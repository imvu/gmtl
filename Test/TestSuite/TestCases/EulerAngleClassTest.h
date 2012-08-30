// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_EULER_ANGLE_CLASS_TEST_H_
#define _GMTL_EULER_ANGLE_CLASS_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class EulerAngleClassTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(EulerAngleClassTest);

      CPPUNIT_TEST(testEulerAngleClassTestCreation);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testEulerAngleClassTestCreation();
   };

   /**
    * Metric tests.
    */
   class EulerAngleClassMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(EulerAngleClassMetricTest);

      CPPUNIT_TEST(testEulerAngleTimingDefaultConstructor);
      CPPUNIT_TEST(testEulerAngleTimingElementConstructor);
      CPPUNIT_TEST(testEulerAngleTimingCopyConstructor);
      CPPUNIT_TEST(testEulerAngleTimingSet);
      CPPUNIT_TEST(testEulerAngleTimingOpBracket);
      CPPUNIT_TEST(testEulerAngleTimingGetData);
      CPPUNIT_TEST(testEulerAngleTimingOpEqual);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testEulerAngleTimingDefaultConstructor();
      void testEulerAngleTimingElementConstructor();
      void testEulerAngleTimingCopyConstructor();
      void testEulerAngleTimingSet();
      void testEulerAngleTimingOpBracket();
      void testEulerAngleTimingGetData();
      void testEulerAngleTimingOpEqual();
   };
}

#endif

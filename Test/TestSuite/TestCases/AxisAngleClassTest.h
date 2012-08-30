// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _AXIS_ANGLE_CLASS_TEST_
#define _AXIS_ANGLE_CLASS_TEST_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class AxisAngleClassTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(AxisAngleClassTest);

      CPPUNIT_TEST(testAxisAngleClassTestCreation);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testAxisAngleClassTestCreation();
   };

   /**
    * Metric tests.
    */
   class AxisAngleClassMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(AxisAngleClassMetricTest);

      CPPUNIT_TEST(testAxisAngleTimingDefaultConstructor);
      CPPUNIT_TEST(testAxisAngleTimingElementConstructor);
      CPPUNIT_TEST(testAxisAngleTimingCopyConstructor);
      CPPUNIT_TEST(testAxisAngleTimingSet);
      CPPUNIT_TEST(testAxisAngleTimingOpBracket);
      CPPUNIT_TEST(testAxisAngleTimingGetData);
      CPPUNIT_TEST(testAxisAngleTimingOpEqual);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testAxisAngleTimingDefaultConstructor();
      void testAxisAngleTimingElementConstructor();
      void testAxisAngleTimingCopyConstructor();
      void testAxisAngleTimingSet();
      void testAxisAngleTimingOpBracket();
      void testAxisAngleTimingGetData();
      void testAxisAngleTimingOpEqual();
   };
}

#endif

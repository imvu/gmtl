// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_MATRIX_COMPARE_TEST_H_
#define _GMTL_MATRIX_COMPARE_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class MatrixCompareTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(MatrixCompareTest);

      CPPUNIT_TEST(testMatEqualityFloatTest);
      CPPUNIT_TEST(testMatEqualityDoubleTest);
      CPPUNIT_TEST(testMatEqualityIntTest);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testMatEqualityFloatTest();
      void testMatEqualityDoubleTest();
      void testMatEqualityIntTest();
   };

   /**
    * Metric tests.
    */
   class MatrixCompareMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(MatrixCompareMetricTest);

      CPPUNIT_TEST(testMatTimingOpEqualityTest);
      CPPUNIT_TEST(testMatTimingOpNotEqualityTest);
      CPPUNIT_TEST(testMatTimingIsEqualTest);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testMatTimingOpEqualityTest();
      void testMatTimingOpNotEqualityTest();
      void testMatTimingIsEqualTest();
   };
}

#endif

// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_VEC_GEN_TEST_H_
#define _GMTL_VEC_GEN_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class VecGenTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(VecGenTest);

      CPPUNIT_TEST(testMakeVecFromQuat);
      CPPUNIT_TEST(testMakeNormalVecFromVec);
      CPPUNIT_TEST(testMatrixRowAccess);
      CPPUNIT_TEST(testMatrixColumnAccess);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testMakeVecFromQuat();
      void testMakeNormalVecFromVec();

      void testMatrixRowAccess();
      void testMatrixColumnAccess();
   };

   /**
    * Metric tests.
    */
   class VecGenMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(VecGenMetricTest);

      CPPUNIT_TEST(testGenTimingMakeNormalVec1);
      CPPUNIT_TEST(testGenTimingMakeNormalVec2);
      CPPUNIT_TEST(testGenTimingMakeNormalVec3);
      CPPUNIT_TEST(testGenTimingMakeNormalVec4);
      CPPUNIT_TEST(testGenTimingMakeVec);

      CPPUNIT_TEST_SUITE_END();

   public:
      //-- timing tests --//
      void testGenTimingMakeNormalVec1();
      void testGenTimingMakeNormalVec2();
      void testGenTimingMakeNormalVec3();
      void testGenTimingMakeNormalVec4();
      void testGenTimingMakeVec();
   };
}

#endif

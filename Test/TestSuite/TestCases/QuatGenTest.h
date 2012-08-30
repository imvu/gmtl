// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_QUAT_GEN_TEST_H_
#define _GMTL_QUAT_GEN_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

/// @todo test/timing on makeRot( quat ) (euler version)

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class QuatGenTest : public CppUnit::TestCase
   {
      CPPUNIT_TEST_SUITE(QuatGenTest);

      CPPUNIT_TEST(testQuatMakePure);
      CPPUNIT_TEST(testQuatMakeConj);
      CPPUNIT_TEST(testQuatMakeInvert);
      CPPUNIT_TEST(testQuatMakeRot);
      CPPUNIT_TEST(testQuatGetRot);
      CPPUNIT_TEST(testQuatMakeGetMakeRot);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testQuatMakePure();
      void testQuatMakeConj();
      void testQuatMakeInvert();
      void testQuatMakeRot();
      void testQuatGetRot();
      void testQuatMakeGetMakeRot();
   };

   /**
    * Metric tests.
    */
   class QuatGenMetricTest : public CppUnit::TestCase
   {
      CPPUNIT_TEST_SUITE(QuatGenMetricTest);

      CPPUNIT_TEST(testGenTimingMakeInvert1);
      CPPUNIT_TEST(testGenTimingMakeInvert2);
      CPPUNIT_TEST(testGenTimingMakeConj);
      CPPUNIT_TEST(testGenTimingMakePure);
      CPPUNIT_TEST(testGenTimingMakeNormalQuat);
      CPPUNIT_TEST(testGenTimingMakeRot);
      CPPUNIT_TEST(testGenTimingSetRot);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testGenTimingMakeInvert1();
      void testGenTimingMakeInvert2();
      void testGenTimingMakeConj();
      void testGenTimingMakePure();
      void testGenTimingMakeNormalQuat();
      void testGenTimingMakeRot();
      void testGenTimingSetRot();
   };
}

#endif

// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_QUAT_OPS_TEST_H_
#define _GMTL_QUAT_OPS_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class QuatOpsTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(QuatOpsTest);

      CPPUNIT_TEST(testQuatMult);
      CPPUNIT_TEST(testQuatDiv);
      CPPUNIT_TEST(testQuatVectorMult);
      CPPUNIT_TEST(testQuatVectorAdd);
      CPPUNIT_TEST(testQuatVectorSub);
      CPPUNIT_TEST(testQuatVectorDot);
      CPPUNIT_TEST(testQuatNorm);
      CPPUNIT_TEST(testQuatMag);
      CPPUNIT_TEST(testQuatNormalize);
      CPPUNIT_TEST(testQuatConj);
      CPPUNIT_TEST(testQuatNegate);
      CPPUNIT_TEST(testQuatInvert);
      CPPUNIT_TEST(testQuatSlerp);
      CPPUNIT_TEST(testQuatLerp);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testQuatMult();
      void testQuatDiv();
      void testQuatVectorMult();
      void testQuatVectorAdd();
      void testQuatVectorSub();
      void testQuatVectorDot();
      void testQuatNorm();
      void testQuatMag();
      void testQuatNormalize();
      void testQuatConj();
      void testQuatNegate();
      void testQuatInvert();
      void testQuatSlerp();
      void testQuatLerp();
   };

   /**
    * Metric tests.
    */
   class QuatOpsMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(QuatOpsMetricTest);

      CPPUNIT_TEST(testQuatTimingNegate);
      CPPUNIT_TEST(testQuatTimingOperatorMinus);
      CPPUNIT_TEST(testQuatTimingMult);
      CPPUNIT_TEST(testQuatTimingOperatorMult);
      CPPUNIT_TEST(testQuatTimingDiv);
      CPPUNIT_TEST(testQuatTimingLerp);
      CPPUNIT_TEST(testQuatTimingVectorMult);
      CPPUNIT_TEST(testQuatTimingVectorAdd);
      CPPUNIT_TEST(testQuatTimingVectorSub);
      CPPUNIT_TEST(testQuatTimingVectorDot);
      CPPUNIT_TEST(testQuatTimingNorm);
      CPPUNIT_TEST(testQuatTimingMag);
      CPPUNIT_TEST(testQuatTimingNormalize);
      CPPUNIT_TEST(testQuatTimingConj);
      CPPUNIT_TEST(testQuatTimingInvert);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testQuatTimingNegate();
      void testQuatTimingOperatorMinus();
      void testQuatTimingMult();
      void testQuatTimingOperatorMult();
      void testQuatTimingDiv();
      void testQuatTimingLerp();
      void testQuatTimingVectorMult();
      void testQuatTimingVectorAdd();
      void testQuatTimingVectorSub();
      void testQuatTimingVectorDot();
      void testQuatTimingNorm();
      void testQuatTimingMag();
      void testQuatTimingNormalize();
      void testQuatTimingConj();
      void testQuatTimingInvert();
   };
}

#endif

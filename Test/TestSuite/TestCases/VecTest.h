// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_VEC_TEST_H_
#define _GMTL_VEC_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class VecTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(VecTest);

      CPPUNIT_TEST(testVecMeta);

      CPPUNIT_TEST(testCreation);
      CPPUNIT_TEST(testCopyConstruct);
      CPPUNIT_TEST(testConstructors);
      CPPUNIT_TEST(testSet);
      CPPUNIT_TEST(testSetPtr);
      CPPUNIT_TEST(testGetData);
      CPPUNIT_TEST(testEqualityCompare);
      CPPUNIT_TEST(testIsEqual);
      CPPUNIT_TEST(testOpNegate);
      CPPUNIT_TEST(testOpPlusEq);
      CPPUNIT_TEST(testOpPlus);
      CPPUNIT_TEST(testOpMinusEq);
      CPPUNIT_TEST(testOpMinus);
      CPPUNIT_TEST(testOpMultScalarEq);
      CPPUNIT_TEST(testOpMultScalar);
      CPPUNIT_TEST(testOpScalarVecMult);
      CPPUNIT_TEST(testOpDivScalarEq);
      CPPUNIT_TEST(testOpDivScalar);
      CPPUNIT_TEST(testDot);
      CPPUNIT_TEST(testLength);
      CPPUNIT_TEST(testNormalize);
      CPPUNIT_TEST(testIsNormalized);
      CPPUNIT_TEST(testIsNormalizedEps);
      CPPUNIT_TEST(testCross);
      CPPUNIT_TEST(testReflect);
      CPPUNIT_TEST(testLerp);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testVecMeta();

      void testCreation();
      void testCopyConstruct();
      void testConstructors();
      void testSet();
      void testSetPtr();
      void testGetData();

      // -- Test comparison -- //
      void testEqualityCompare();
      void testIsEqual();
      void testOpNegate();
      void testOpPlusEq();
      void testOpPlus();
      void testOpMinusEq();
      void testOpMinus();
      void testOpMultScalarEq();
      void testOpMultScalar();
      void testOpScalarVecMult();
      void testOpDivScalarEq();
      void testOpDivScalar();

      // ---- Vec specific functions --- //
      void testDot();
      void testLength();
      void testNormalize();
      void testIsNormalized();
      void testIsNormalizedEps();
      void testCross();
      void testReflect();
      void testLerp();
   };

   /**
    * Metric tests
    */
   class VecMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(VecMetricTest);

      CPPUNIT_TEST(testVecMetaPerf);
      CPPUNIT_TEST(testTimingCreation);
      CPPUNIT_TEST(testTimingCopyConstruct);
      CPPUNIT_TEST(testTimingConstructors);
      CPPUNIT_TEST(testTimingSet);
      CPPUNIT_TEST(testTimingSetPtr);
      CPPUNIT_TEST(testTimingEqualityCompare);
      CPPUNIT_TEST(testTimingIsEqual);
      CPPUNIT_TEST(testTimingOpNegate);
      CPPUNIT_TEST(testTimingOpPlusEq);
      CPPUNIT_TEST(testTimingOpPlus);
      CPPUNIT_TEST(testTimingOpMinusEq);
      CPPUNIT_TEST(testTimingOpMinus);
      CPPUNIT_TEST(testTimingOpMultScalarEq);
      CPPUNIT_TEST(testTimingOpMultScalar);
      CPPUNIT_TEST(testTimingOpScalarVecMult);
      CPPUNIT_TEST(testTimingOpDivScalarEq);
      CPPUNIT_TEST(testTimingOpDivScalar);
      CPPUNIT_TEST(testTimingGroupedOps);
      CPPUNIT_TEST(testTimingDot);
      CPPUNIT_TEST(testTimingLength);
      CPPUNIT_TEST(testTimingNormalize);
      CPPUNIT_TEST(testTimingIsNormalized);
      CPPUNIT_TEST(testTimingIsNormalizedEps);
      CPPUNIT_TEST(testTimingCross);
      CPPUNIT_TEST(testTimingLerp);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testVecMetaPerf();

      void testTimingCreation();
      void testTimingCopyConstruct();
      void testTimingConstructors();
      void testTimingSet();
      void testTimingSetPtr();
      void testTimingEqualityCompare();
      void testTimingIsEqual();
      void testTimingOpNegate();
      void testTimingOpPlusEq();
      void testTimingOpPlus();
      void testTimingOpMinusEq();
      void testTimingOpMinus();
      void testTimingOpMultScalarEq();
      void testTimingOpMultScalar();
      void testTimingOpScalarVecMult();
      void testTimingOpDivScalarEq();
      void testTimingOpDivScalar();
      void testTimingGroupedOps();
      void testTimingDot();
      void testTimingLength();
      void testTimingNormalize();
      void testTimingIsNormalized();
      void testTimingIsNormalizedEps();
      void testTimingCross();
      void testTimingLerp();
   };
}

#endif

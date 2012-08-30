// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_MATRIX_OPS_TEST_SUITE_H_
#define _GMTL_MATRIX_OPS_TEST_SUITE_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class MatrixOpsTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(MatrixOpsTest);

      CPPUNIT_TEST(testMatrixIdentity);
      CPPUNIT_TEST(testMatrixSetTrans);
      CPPUNIT_TEST(testMatrixTranspose);
      CPPUNIT_TEST(testMatrixAddSub);
      CPPUNIT_TEST(testMatrixMult);
      CPPUNIT_TEST(testMatrixScalarMult);
      CPPUNIT_TEST(testMatInvert);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testMatrixIdentity();
      void testMatrixSetTrans();
      void testMatrixTranspose();
      void testMatrixAddSub();
      void testMatrixMult();
      void testMatrixScalarMult();
      void testMatInvert();
   };

   /**
    * Metric tests.
    */
   class MatrixOpsMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(MatrixOpsMetricTest);

      CPPUNIT_TEST(testMatrixTimeIdentity44f);
      CPPUNIT_TEST(testTimingMakeTrans);
      CPPUNIT_TEST(testMatrixTimeTranspose44f);
      CPPUNIT_TEST(testMatrixTimeTranspose33d);
      CPPUNIT_TEST(testMatrixTimeMult44_mult);
      CPPUNIT_TEST(testMatrixTimeMult44_operatorStar);
      CPPUNIT_TEST(testMatrixTimeMult44f_operatorStarStar);
      CPPUNIT_TEST(testMatrixTimeMult44d_operatorStarStar);
      CPPUNIT_TEST(testMatrixTimeMult33f_operatorStarStar);
      CPPUNIT_TEST(testMatrixTimeMult33d_operatorStarStar);
      CPPUNIT_TEST(testMatrixTimeAdd44);
      CPPUNIT_TEST(testMatrixTimeSub44);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testMatrixTimeIdentity44f();
      void testTimingMakeTrans();
      void testMatrixTimeTranspose44f();
      void testMatrixTimeTranspose33d();
      void testMatrixTimeMult44_mult();
      void testMatrixTimeMult44_operatorStar();
      void testMatrixTimeMult44f_operatorStarStar();
      void testMatrixTimeMult44d_operatorStarStar();
      void testMatrixTimeMult33f_operatorStarStar();
      void testMatrixTimeMult33d_operatorStarStar();
      void testMatrixTimeAdd44();
      void testMatrixTimeSub44();
   };
}

#endif

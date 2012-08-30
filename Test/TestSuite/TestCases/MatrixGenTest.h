// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_MATRIX_GEN_TEST_H_
#define _GMTL_MATRIX_GEN_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class MatrixGenTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(MatrixGenTest);

      CPPUNIT_TEST(testMatrixsetViewing);
      CPPUNIT_TEST(testMatrixsetTrans);
      CPPUNIT_TEST(testMatrixsetAxes);
      CPPUNIT_TEST(testMatrixsetDirCos);
      CPPUNIT_TEST(testMatrixsetScale);
      CPPUNIT_TEST(testMatrixsetRot);
      CPPUNIT_TEST(testMatrixsetRotEuler);
      CPPUNIT_TEST(testMatrixgetRotEuler);
      CPPUNIT_TEST(testMatrixGetSetRotEuler);
      CPPUNIT_TEST(testMatrixmakeInverse);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testMatrixsetViewing();
      void testMatrixsetTrans();
      void testMatrixsetAxes();
      void testMatrixsetDirCos();
      void testMatrixsetScale();
      void testMatrixsetRot();
      void testMatrixsetRotEuler();
      void testMatrixgetRotEuler();
      void testMatrixGetSetRotEuler();
      void testMatrixmakeInverse();
   };

   /**
    * Metric tests.
    */
   class MatrixGenMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(MatrixGenMetricTest);

      CPPUNIT_TEST(testTimingsetTrans);
      CPPUNIT_TEST(testTimingsetScale);
      CPPUNIT_TEST(testTimingsetRot33);
      CPPUNIT_TEST(testTimingsetRot34);
      CPPUNIT_TEST(testTimingsetRot44);
      CPPUNIT_TEST(testTimingGetRot);
      CPPUNIT_TEST(testTimingsetRotEuler33);
      CPPUNIT_TEST(testTimingsetRotEuler34);
      CPPUNIT_TEST(testTimingsetRotEuler44);
      CPPUNIT_TEST(testTimingsetDirCos33);
      CPPUNIT_TEST(testTimingsetDirCos34);
      CPPUNIT_TEST(testTimingsetDirCos44);
      CPPUNIT_TEST(testTimingsetAxes33);
      CPPUNIT_TEST(testTimingsetAxes34);
      CPPUNIT_TEST(testTimingsetAxes44);
      CPPUNIT_TEST(testTimingsetAxes);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testTimingsetTrans();
      void testTimingsetScale();
      void testTimingsetRot33();
      void testTimingsetRot34();
      void testTimingsetRot44();
      void testTimingGetRot();
      void testTimingsetRotEuler33();
      void testTimingsetRotEuler34();
      void testTimingsetRotEuler44();
      void testTimingsetDirCos33();
      void testTimingsetDirCos34();
      void testTimingsetDirCos44();
      void testTimingsetAxes33();
      void testTimingsetAxes34();
      void testTimingsetAxes44();
      void testTimingsetAxes();
   };
}

#endif

// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_MATRIX_CLASS_TEST_H_
#define _GMTL_MATRIX_CLASS_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class MatrixClassTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(MatrixClassTest);

      CPPUNIT_TEST(testMatrixIdentity);
      CPPUNIT_TEST(testMatrixSetPtr);
      CPPUNIT_TEST(testMatrixSetTransposePtr);
      CPPUNIT_TEST(testMatrix44Creation);
      CPPUNIT_TEST(testMatrix34Creation);
      CPPUNIT_TEST(testMatrix33Creation);
      CPPUNIT_TEST(testMatrix23Creation);
      CPPUNIT_TEST(testMatrix22Creation);

      CPPUNIT_TEST_SUITE_END();

   public:
      // test out operations using identity matrix
      void testMatrixIdentity();

      // make sure set( float* ) works
      void testMatrixSetPtr();

      // make sure set( float* ) works
      void testMatrixSetTransposePtr();

      // more general creation tests..
      // tests default constructor, copy constructor, set()
      //       operator() operator[]
      void testMatrix44Creation();
      void testMatrix34Creation();
      void testMatrix33Creation();
      void testMatrix23Creation();
      void testMatrix22Creation();
   };

   /**
    * Metric tests.
    */
   class MatrixClassMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(MatrixClassMetricTest);

      CPPUNIT_TEST(testTimingDefaultConstructor);
      CPPUNIT_TEST(testTimingCopyConstructor);
      CPPUNIT_TEST(testTimingOpEqual);
      CPPUNIT_TEST(testTimingOpParen);
      CPPUNIT_TEST(testTimingOpBracket);
      CPPUNIT_TEST(testTimingSetPtr);
      CPPUNIT_TEST(testTimingSetTransposePtr);
      CPPUNIT_TEST(testTimingGetData);
      CPPUNIT_TEST(testTimingSet);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testTimingDefaultConstructor();
      void testTimingCopyConstructor();

      void testTimingOpEqual();
      void testTimingOpParen();
      void testTimingOpBracket();

      void testTimingSetPtr();
      void testTimingSetTransposePtr();
      void testTimingGetData();
      void testTimingSet();
   };
}

#endif

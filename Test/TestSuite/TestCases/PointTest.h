// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_POINT_TEST_H_
#define _GMTL_POINT_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class PointTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(PointTest);

      CPPUNIT_TEST(testCreation);
      CPPUNIT_TEST(testCopyConstruct);
      CPPUNIT_TEST(testConstructors);
      CPPUNIT_TEST(testSet);
      CPPUNIT_TEST(testSetPtr);
      CPPUNIT_TEST(testGetData);
      CPPUNIT_TEST(testEqualityCompare);
      CPPUNIT_TEST(testIsEqual);
      CPPUNIT_TEST(testOpPlusEq);
      CPPUNIT_TEST(testOpPlus);
      CPPUNIT_TEST(testOpMinusEq);
      CPPUNIT_TEST(testOpMinus);
      CPPUNIT_TEST(testOpMultScalarEq);
      CPPUNIT_TEST(testOpMultScalar);
      CPPUNIT_TEST(testOpDivScalarEq);
      CPPUNIT_TEST(testOpDivScalar);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testCreation();
      void testCopyConstruct();
      void testConstructors();

      void testSet();
      void testSetPtr();
      void testGetData();

      // -- Test comparison -- //
      void testEqualityCompare();
      void testIsEqual();

      // ---------------------------------- //
      // ---------- Math ops -------------- //
      // ---------------------------------- //
      void testOpPlusEq();
      void testOpPlus();
      void testOpMinusEq();
      void testOpMinus();
      void testOpMultScalarEq();
      void testOpMultScalar();
      void testOpDivScalarEq();
      void testOpDivScalar();
   };


   /**
    * Metric tests.
    */
   class PointMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(PointMetricTest);

      CPPUNIT_TEST(testTimingCreation);
      CPPUNIT_TEST(testTimingCopyConstruct);
      CPPUNIT_TEST(testTimingConstructors);
      CPPUNIT_TEST(testTimingSet);
      CPPUNIT_TEST(testTimingSetPtr);
      CPPUNIT_TEST(testTimingEqualityCompare);
      CPPUNIT_TEST(testTimingIsEqual);
      CPPUNIT_TEST(testTimingOpPlusEq);
      CPPUNIT_TEST(testTimingOpPlus);
      CPPUNIT_TEST(testTimingOpMinusEq);
      CPPUNIT_TEST(testTimingOpMinus);
      CPPUNIT_TEST(testTimingOpMultScalarEq);
      CPPUNIT_TEST(testTimingOpMultScalar);
      CPPUNIT_TEST(testTimingOpDivScalarEq);
      CPPUNIT_TEST(testTimingOpDivScalar);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testTimingCreation();
      void testTimingCopyConstruct();
      void testTimingConstructors();

      void testTimingSet();
      void testTimingSetPtr();
      void testTimingGetData();

      void testTimingEqualityCompare();
      void testTimingIsEqual();

      void testTimingOpPlusEq();
      void testTimingOpPlus();
      void testTimingOpMinusEq();
      void testTimingOpMinus();
      void testTimingOpMultScalarEq();
      void testTimingOpMultScalar();
      void testTimingOpDivScalarEq();
      void testTimingOpDivScalar();
   };
}

#endif

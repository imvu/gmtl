// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _TRI_TEST_H_
#define _TRI_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functional tests.
    */
   class TriTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(TriTest);

      CPPUNIT_TEST(testCreation);
      CPPUNIT_TEST(testCopyConstruct);
      CPPUNIT_TEST(testConstructors);
      CPPUNIT_TEST(testVertexAccessor);
      CPPUNIT_TEST(testEdges);
      CPPUNIT_TEST(testEqualOps);
      CPPUNIT_TEST(testIsEqual);
      CPPUNIT_TEST(testCenter);
      CPPUNIT_TEST(testNormal);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testCreation();
      void testCopyConstruct();
      void testConstructors();

      //---------------------------------------------------------------------------
      // Begin testing accessors
      //---------------------------------------------------------------------------
      void testVertexAccessor();
      void testEdges();

      //---------------------------------------------------------------------------
      // Begin testing comparators
      //---------------------------------------------------------------------------
      void testEqualOps();
      void testIsEqual();
      void testCenter();
      void testNormal();
   };

   /**
    * Metric tests.
    */
   class TriMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(TriMetricTest);

      CPPUNIT_TEST(testTimingCreation);
      CPPUNIT_TEST(testTimingCopyConstruct);
      CPPUNIT_TEST(testTimingConstructors);
      CPPUNIT_TEST(testTimingVertexAccessor);
      CPPUNIT_TEST(testTimingEdges);
      CPPUNIT_TEST(testTimingEqualOps);
      CPPUNIT_TEST(testTimingIsEqual);
      CPPUNIT_TEST(testTimingCenter);
      CPPUNIT_TEST(testTimingNormal);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testTimingCreation();
      void testTimingCopyConstruct();
      void testTimingConstructors();
      void testTimingVertexAccessor();
      void testTimingEdges();
      void testTimingEqualOps();
      void testTimingIsEqual();
      void testTimingCenter();
      void testTimingNormal();
   };
}

#endif

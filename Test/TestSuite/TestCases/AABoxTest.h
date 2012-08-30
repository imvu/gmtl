// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_AABOX_TEST_H_
#define _GMTL_AABOX_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class AABoxTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(AABoxTest);

      CPPUNIT_TEST(testCreation);
      CPPUNIT_TEST(testCopyConstruct);
      CPPUNIT_TEST(testConstructors);
      CPPUNIT_TEST(testGetMin);
      CPPUNIT_TEST(testGetMax);
      CPPUNIT_TEST(testIsEmpty);
      CPPUNIT_TEST(testSetMin);
      CPPUNIT_TEST(testSetMax);
      CPPUNIT_TEST(testSetEmpty);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testCreation();
      void testCopyConstruct();
      void testConstructors();

      // -- Test accessors --//
      void testGetMin();
      void testGetMax();
      void testIsEmpty();

      // -- Test setters --//
      void testSetMin();
      void testSetMax();
      void testSetEmpty();
   };

   /**
    * Metric tests.
    */
   class AABoxMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(AABoxMetricTest);

      CPPUNIT_TEST(testTimingCreation);
      CPPUNIT_TEST(testTimingCopyConstruct);
      CPPUNIT_TEST(testTimingConstructors);
      CPPUNIT_TEST(testTimingGetMin);
      CPPUNIT_TEST(testTimingGetMax);
      CPPUNIT_TEST(testTimingIsEmpty);
      CPPUNIT_TEST(testTimingSetMin);
      CPPUNIT_TEST(testTimingSetMax);
      CPPUNIT_TEST(testTimingSetEmpty);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testTimingCreation();
      void testTimingCopyConstruct();
      void testTimingConstructors();

      // -- Test accessors --//
      void testTimingGetMin();
      void testTimingGetMax();
      void testTimingIsEmpty();

      // -- Test setters --//
      void testTimingSetMin();
      void testTimingSetMax();
      void testTimingSetEmpty();
   };
}

#endif

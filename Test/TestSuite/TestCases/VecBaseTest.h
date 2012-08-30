// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_VEC_BASE_TEST_H_
#define _GMTL_VEC_BASE_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class VecBaseTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(VecBaseTest);

      CPPUNIT_TEST(testVecBaseCreation);
      CPPUNIT_TEST(testCopyConstruct);
      CPPUNIT_TEST(testConstructors);
      CPPUNIT_TEST(testSet);
      CPPUNIT_TEST(testSetPtr);
      CPPUNIT_TEST(testGetData);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testVecBaseCreation();
      void testCopyConstruct();
      void testConstructors();

      void testSet();
      void testSetPtr();
      void testGetData();
   };

   /**
    * Metric tests.
    */
   class VecBaseMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(VecBaseMetricTest);

      CPPUNIT_TEST(testTimingVecBaseCreation);
      CPPUNIT_TEST(testTimingCopyConstruct);
      CPPUNIT_TEST(testTimingConstructors);
      CPPUNIT_TEST(testTimingSet);
      CPPUNIT_TEST(testTimingSetPtr);
      CPPUNIT_TEST(testTimingGetData);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testTimingVecBaseCreation();
      void testTimingCopyConstruct();
      void testTimingConstructors();

      void testTimingSet();
      void testTimingSetPtr();
      void testTimingGetData();
   };
}

#endif

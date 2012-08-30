// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_COORD_CLASS_TEST_H_
#define _GMTL_COORD_CLASS_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class CoordClassTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(CoordClassTest);

      CPPUNIT_TEST(testCoordClassTestCreation);
      CPPUNIT_TEST(testMultiArgConstructors);

      CPPUNIT_TEST_SUITE_END();

   public:
      // Correctness tests
      void testCoordClassTestCreation();
      void testMultiArgConstructors();
   };

   /**
    * Metric tests.
    */
   class CoordClassMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(CoordClassMetricTest);

      CPPUNIT_TEST(testCoordTimingDefaultConstructor);
      CPPUNIT_TEST(testCoordTimingElementConstructor);
      CPPUNIT_TEST(testCoordTimingCopyConstructor);
      CPPUNIT_TEST(testCoordTimingGet);
      CPPUNIT_TEST(testCoordTimingOpEqual);

      CPPUNIT_TEST_SUITE_END();

   public:
      // Performance tests
      void testCoordTimingDefaultConstructor();
      void testCoordTimingElementConstructor();
      void testCoordTimingCopyConstructor();
      void testCoordTimingGet();
      void testCoordTimingOpEqual();

   };
}

#endif

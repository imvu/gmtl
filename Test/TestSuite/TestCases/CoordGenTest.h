// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_COORD_GEN_TEST_H_
#define _GMTL_COORD_GEN_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

/// @todo test/timing on makeRot( quat ) (euler version)

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class CoordGenTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(CoordGenTest);

      CPPUNIT_TEST(testCoordSetMatrix);
      CPPUNIT_TEST(testCoordMakeCoord);
      CPPUNIT_TEST(testCoordGetMatrix);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testCoordSetMatrix();
      void testCoordMakeCoord();
      void testCoordGetMatrix();
   };

   /**
    * Metric tests.
    */
   class CoordGenMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(CoordGenMetricTest);

      CPPUNIT_TEST(testGenTimingMakeCoord);
      CPPUNIT_TEST(testGenTimingMakeMatrix);
      CPPUNIT_TEST(testGenTimingSetCoord);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testGenTimingMakeCoord();
      void testGenTimingMakeMatrix();
      void testGenTimingSetCoord();
   };
}

#endif

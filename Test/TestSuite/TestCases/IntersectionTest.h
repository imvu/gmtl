// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_INTERSECTION_TEST_H_
#define _GMTL_INTERSECTION_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class IntersectionTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(IntersectionTest);

      CPPUNIT_TEST(testIntersectAABoxAABox);
      CPPUNIT_TEST(testIntersectAABoxPoint);
      CPPUNIT_TEST(testIntersectAABoxLineSeg);
      CPPUNIT_TEST(testIntersectAABoxRay);
      CPPUNIT_TEST(testIntersectAABoxSphere);

      CPPUNIT_TEST(testIntersectAABoxSweep);
      CPPUNIT_TEST(testIntersectSphereSweep);

	  CPPUNIT_TEST(testIntersectRayPlane);
	  CPPUNIT_TEST(testIntersectLineSegPlane);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testIntersectAABoxAABox();
      void testIntersectAABoxPoint();
      void testIntersectAABoxLineSeg();
      void testIntersectAABoxRay();
      void testIntersectAABoxSphere();

      void testIntersectAABoxSweep();
      void testIntersectSphereSweep();

	  void testIntersectRayPlane();
	  void testIntersectLineSegPlane();
   };

   /**
    * Metric tests.
    */
   class IntersectionMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(IntersectionMetricTest);

      CPPUNIT_TEST(testTimingIntersectAABoxAABox);
      CPPUNIT_TEST(testTimingIntersectAABoxPoint);

      CPPUNIT_TEST(testTimingIntersectAABoxSweep);
      CPPUNIT_TEST(testTimingIntersectSphereSweep);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testTimingIntersectAABoxAABox();
      void testTimingIntersectAABoxPoint();

      void testTimingIntersectAABoxSweep();
      void testTimingIntersectSphereSweep();
   };
}

#endif

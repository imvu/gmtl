// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_PLANE_TEST_H_
#define _GMTL_PLANE_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

#include <gmtl/Plane.h>

namespace gmtlTest
{
   class PlaneTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(PlaneTest);

      CPPUNIT_TEST(testCreation);
      CPPUNIT_TEST(testThreePtCreation);
      CPPUNIT_TEST(testNormPtCreation);
      CPPUNIT_TEST(testNormOffsetCreation);
      CPPUNIT_TEST(testCopyConstruct);
      CPPUNIT_TEST(testEqualityCompare);
      CPPUNIT_TEST(testIsEqual);
      CPPUNIT_TEST(testDistance);
      CPPUNIT_TEST(testWhichSide);
      CPPUNIT_TEST(testFindNearestPt);
      CPPUNIT_TEST(testFindReflect);

      CPPUNIT_TEST_SUITE_END();

   public:
      void setUp();

      // ------------------------
      // CREATION TESTS
      // ------------------------
      void testCreation();
      void testThreePtCreation();
      void testNormPtCreation();
      void testNormOffsetCreation();
      void testCopyConstruct();

      // --------------------------
      // Comparison tests
      // --------------------------
      void testEqualityCompare();
      void testIsEqual();

      // --------------------------
      // Operations tests
      // --------------------------
      void testDistance();
      void testWhichSide();
      void testFindNearestPt();

	  void testFindReflect();

   protected:
      gmtl::Point<float, 3> origin;
      gmtl::Point<float, 3> x1_pt;
      gmtl::Point<float, 3> y1_pt;
      gmtl::Point<float, 3> z1_pt;
      gmtl::Vec<float, 3> x1_v;
      gmtl::Vec<float, 3> y1_v;
      gmtl::Vec<float, 3> z1_v;

      gmtl::Plane<float> xy_plane;
      gmtl::Plane<float> zx_plane;
      gmtl::Plane<float> yz_plane;
   };
}

#endif

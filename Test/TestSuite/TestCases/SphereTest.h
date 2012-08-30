// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _SPHERE_TEST_H
#define _SPHERE_TEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   class SphereTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(SphereTest);

      CPPUNIT_TEST(testCreation);
      CPPUNIT_TEST(testCopyConstruct);
      CPPUNIT_TEST(testConstructors);
      CPPUNIT_TEST(testGetCenter);
      CPPUNIT_TEST(testGetRadius);
      CPPUNIT_TEST(testEqualityCompare);
      CPPUNIT_TEST(testIsEqual);
      CPPUNIT_TEST(testIsInVolumePoint);
      CPPUNIT_TEST(testIsInVolumeSphere);
      CPPUNIT_TEST(testIsOnVolume);
      CPPUNIT_TEST(testExtendVolumePoint);
      CPPUNIT_TEST(testExtendVolumeSphere);
      CPPUNIT_TEST(testMakeVolumePoint);
      CPPUNIT_TEST(testSphereIntersections);
//      CPPUNIT_TEST(testMakeVolumeSphere);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testCreation();
      void testCopyConstruct();
      void testConstructors();

      // -- Test accessors --//
      void testGetCenter();
      void testGetRadius();

      // -- Test setters --//
      void testSetCenter();
      void testSetRadius();

      // -- Test comparison -- //
      void testEqualityCompare();
      void testIsEqual();

      // intersection tests
      static void testSphereIntersect( float x, float y, float z );
      void testSphereIntersections();

      //---------------------------------------------------------------------------
      // Containment tests
      //---------------------------------------------------------------------------
      void testIsInVolumePoint();
      void testIsInVolumeSphere();
      void testIsOnVolume();
      void testExtendVolumePoint();
      void testExtendVolumeSphere();
      void testMakeVolumePoint();
   //   void testMakeVolumeSphere();
   };

   class SphereMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(SphereMetricTest);

      CPPUNIT_TEST(testTimingCreation);
      CPPUNIT_TEST(testTimingCopyConstruct);
      CPPUNIT_TEST(testTimingConstructors);
      CPPUNIT_TEST(testTimingGetCenter);
      CPPUNIT_TEST(testTimingGetRadius);
      CPPUNIT_TEST(testTimingEqualityCompare);
      CPPUNIT_TEST(testTimingIsEqual);
      CPPUNIT_TEST(testTimingIsInVolumePoint);
      CPPUNIT_TEST(testTimingIsInVolumeSphere);
      CPPUNIT_TEST(testTimingIsOnVolume);
      CPPUNIT_TEST(testTimingExtendVolumePoint);
      CPPUNIT_TEST(testTimingExtendVolumeSphere);
      CPPUNIT_TEST(testTimingMakeVolumePoint);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testTimingCreation();
      void testTimingCopyConstruct();
      void testTimingConstructors();

      // -- Test accessors --//
      void testTimingGetCenter();
      void testTimingGetRadius();

      // -- Test setters --//
      void testTimingSetCenter();
      void testTimingSetRadius();

      // -- Test comparison -- //
      void testTimingEqualityCompare();
      void testTimingIsEqual();

      //---------------------------------------------------------------------------
      // Containment testTimings
      //---------------------------------------------------------------------------
      void testTimingIsInVolumePoint();
      void testTimingIsInVolumeSphere();
      void testTimingIsOnVolume();
      void testTimingExtendVolumePoint();
      void testTimingExtendVolumeSphere();
      void testTimingMakeVolumePoint();
   };
}

#endif

// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_AABOX_CONTAIN_TEST_H_
#define _GMTL_AABOX_CONTAIN_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   class AABoxContainTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(AABoxContainTest);

      CPPUNIT_TEST(testIsInVolumePt);
      CPPUNIT_TEST(testIsInVolumeAABox);
      CPPUNIT_TEST(testExtendVolumePt);
      CPPUNIT_TEST(testExtendVolumeAABox);
      CPPUNIT_TEST(testMakeVolumeSphere);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testIsInVolumePt();
      void testIsInVolumeAABox();
      void testExtendVolumePt();
      void testExtendVolumeAABox();
      void testMakeVolumeSphere();
   };

   class AABoxContainMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(AABoxContainMetricTest);

      CPPUNIT_TEST(testTimingIsInVolumePt);
      CPPUNIT_TEST(testTimingIsInVolumeAABox);
      CPPUNIT_TEST(testTimingExtendVolumePt);
      CPPUNIT_TEST(testTimingExtendVolumeAABox);

      CPPUNIT_TEST_SUITE_END();

   public:
      //---------------------------------------------------------------------------
      // Performance tests
      //---------------------------------------------------------------------------
      void testTimingIsInVolumePt();
      void testTimingIsInVolumeAABox();
      void testTimingExtendVolumePt();
      void testTimingExtendVolumeAABox();
   };
}

#endif

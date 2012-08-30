// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_XFORM_TEST_H_
#define _GMTL_XFORM_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class XformTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(XformTest);

      CPPUNIT_TEST(testQuatVecXform);
      CPPUNIT_TEST(weird_XformQuatVec_InvConj_SanityCheck);
      CPPUNIT_TEST(testMatVecXform);
      CPPUNIT_TEST(testMatPointXform);
      CPPUNIT_TEST(testMatRayXform);
      CPPUNIT_TEST(testMatLineSegXform);
      
      CPPUNIT_TEST_SUITE_END();

   public:
      void testQuatVecXform();
      void weird_XformQuatVec_InvConj_SanityCheck();
      void testMatVecXform();
      void testMatPointXform();
      void testMatLineSegXform();
      void testMatRayXform();
   };

   /**
    * Metric tests.
    */
   class XformMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(XformMetricTest);

      CPPUNIT_TEST(testTimingXformQuatVec3);
      CPPUNIT_TEST(testTimingXformMatVecComplete);
      CPPUNIT_TEST(testTimingXformMatVecPartial);
      CPPUNIT_TEST(testTimingXformMatPointComplete);
      CPPUNIT_TEST(testTimingXformMatPointPartial);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testTimingXformQuatVec3();
      void testTimingXformMatVecComplete();
      void testTimingXformMatVecPartial();
      void testTimingXformMatPointComplete();
      void testTimingXformMatPointPartial();
   };
}

#endif

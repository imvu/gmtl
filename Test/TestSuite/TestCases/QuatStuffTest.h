// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_QUAT_STUFF_TEST_H_
#define _GMTL_QUAT_STUFF_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /** a hodge podge of tests.  stuff that is a little higher level, some real world tests, etc... */
   class QuatStuffTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(QuatStuffTest);

      CPPUNIT_TEST(makeRotTest);
      CPPUNIT_TEST(xformVecSweepTest);
      CPPUNIT_TEST(makeRotGetRotSanityTest);
      CPPUNIT_TEST(simpleQuatProductTest);
      CPPUNIT_TEST(secondQuatProductTest);
      CPPUNIT_TEST(xformVecTest);
      CPPUNIT_TEST(specialCases);
      CPPUNIT_TEST(vectorScaleTest);
      CPPUNIT_TEST(quatAdd);
      CPPUNIT_TEST(pureQuatMultTest);

      CPPUNIT_TEST_SUITE_END();

   public:
      void makeRotTest();
      void xformVecSweepTest();
      void makeRotGetRotSanityTest();

      void simpleQuatProductTest();

      /// another quaternion product test
      void secondQuatProductTest();
      void xformVecTest();

      /// just trying stuff out... TODO think of a good add test...
      void specialCases();

      /**
       * just trying stuff out... TODO think of a good way to test this ability...
       * TODO: could we use a vector (pure quat) to scale a quat in a
       *        more robust way?  pretty sure we can... rewrite scaleAngle to use this
       *        method instead....
       */
      void vectorScaleTest();

      /// just trying stuff out... TODO think of a good add test...
      void quatAdd();

      /**
       * using a vector to increment rotation, much like angular velocity
       * here angular velocity is defined as a gmtl::Vec3f "w", using right hand rule
       * things spin at |w| speed and on the w vector.
       *
       * just trying stuff out... TODO think of a good way to test this ability...
       */
      void pureQuatMultTest();
   };
}

#endif

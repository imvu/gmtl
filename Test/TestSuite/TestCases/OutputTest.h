// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_OUTPUT_TEST_H_
#define _GMTL_OUTPUT_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class OutputTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(OutputTest);

      CPPUNIT_TEST(testVec);
      CPPUNIT_TEST(testPoint);
      CPPUNIT_TEST(testMatrix);
      CPPUNIT_TEST(testQuat);
      CPPUNIT_TEST(testTri);
      CPPUNIT_TEST(testPlane);
      CPPUNIT_TEST(testSphere);
      CPPUNIT_TEST(testAABox);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testVec();
      void testPoint();
      void testMatrix();
      void testQuat();
      void testTri();
      void testPlane();
      void testSphere();
      void testAABox();
   };
}

#endif

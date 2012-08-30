// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_MATH_TEST_H_
#define _GMTL_MATH_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   class MathTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(MathTest);

      CPPUNIT_TEST(testQuadraticFormula);
      CPPUNIT_TEST(testSigni);
      CPPUNIT_TEST(testSignf);
      CPPUNIT_TEST(testZeroClampf);
      CPPUNIT_TEST(testZeroClampd);
      CPPUNIT_TEST_SUITE_END();

   public:
      void testQuadraticFormula();
      void testSigni();
      void testSignf();
      void testZeroClampf();
      void testZeroClampd();

   };

   class MathMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(MathMetricTest);

      CPPUNIT_TEST(testTimingZeroClampf);
      CPPUNIT_TEST(testTimingZeroClampd);
      CPPUNIT_TEST(testFastInvSqrt);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testTimingZeroClampf();
      void testTimingZeroClampd();
      void testFastInvSqrt();
   };
}

#endif

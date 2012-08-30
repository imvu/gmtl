// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_QUAT_CLASS_TEST_H_
#define _GMTL_QUAT_CLASS_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   class QuatClassTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(QuatClassTest);

      CPPUNIT_TEST(testQuatClassTestCreation);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testQuatClassTestCreation();
   };

   class QuatClassMetricTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(QuatClassMetricTest);

      CPPUNIT_TEST(testQuatTimingDefaultConstructor);
      CPPUNIT_TEST(testQuatTimingElementConstructor);
      CPPUNIT_TEST(testQuatTimingCopyConstructor);
      CPPUNIT_TEST(testQuatTimingGet);
      CPPUNIT_TEST(testQuatTimingSet);
      CPPUNIT_TEST(testQuatTimingOpBracket);
      CPPUNIT_TEST(testQuatTimingGetData);
      CPPUNIT_TEST(testQuatTimingOpEqual);

      CPPUNIT_TEST_SUITE_END();

   public:
      void testQuatTimingDefaultConstructor();
      void testQuatTimingElementConstructor();
      void testQuatTimingCopyConstructor();
      void testQuatTimingGet();
      void testQuatTimingSet();
      void testQuatTimingOpBracket();
      void testQuatTimingGetData();
      void testQuatTimingOpEqual();
   };
}

#endif

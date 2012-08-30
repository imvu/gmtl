// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "QuatClassTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Quat.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(QuatClassTest);
   CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(QuatClassMetricTest, Suites::metric());

   void QuatClassTest::testQuatClassTestCreation()
   {
      // test that it initializes to the multiplication identity
      gmtl::Quat<float> q;
      CPPUNIT_ASSERT( q[gmtl::Xelt] == 0.0f );
      CPPUNIT_ASSERT( q[gmtl::Yelt] == 0.0f );
      CPPUNIT_ASSERT( q[gmtl::Zelt] == 0.0f );
      CPPUNIT_ASSERT( q[gmtl::Welt] == 1.0f );

      // try out get...
      float x = 102, y = 103, z = 101, w = 100;
      q.get( x, y, z, w );
      CPPUNIT_ASSERT( x == 0.0f );
      CPPUNIT_ASSERT( y == 0.0f );
      CPPUNIT_ASSERT( z == 0.0f );
      CPPUNIT_ASSERT( w == 1.0f );

      // try out set...
      q.set( 1, 2, 3, 4 );
      CPPUNIT_ASSERT( q[gmtl::Xelt] == 1.0f );
      CPPUNIT_ASSERT( q[gmtl::Yelt] == 2.0f );
      CPPUNIT_ASSERT( q[gmtl::Zelt] == 3.0f );
      CPPUNIT_ASSERT( q[gmtl::Welt] == 4.0f );

      // try out setting with brackets
      q[gmtl::Xelt] = 5;
      q[gmtl::Yelt] = 6;
      q[gmtl::Zelt] = 7;
      q[gmtl::Welt] = 8;
      CPPUNIT_ASSERT( q[gmtl::Xelt] == 5.0f );
      CPPUNIT_ASSERT( q[gmtl::Yelt] == 6.0f );
      CPPUNIT_ASSERT( q[gmtl::Zelt] == 7.0f );
      CPPUNIT_ASSERT( q[gmtl::Welt] == 8.0f );
      q.get( x, y, z, w );
      CPPUNIT_ASSERT( x == 5.0f );
      CPPUNIT_ASSERT( y == 6.0f );
      CPPUNIT_ASSERT( z == 7.0f );
      CPPUNIT_ASSERT( w == 8.0f );

      // try out element constructor
      gmtl::Quat<float> q2( 10, 11, 12, 13 );
      CPPUNIT_ASSERT( q2[gmtl::Xelt] == 10.0f );
      CPPUNIT_ASSERT( q2[gmtl::Yelt] == 11.0f );
      CPPUNIT_ASSERT( q2[gmtl::Zelt] == 12.0f );
      CPPUNIT_ASSERT( q2[gmtl::Welt] == 13.0f );

      // try out copy constructor
      gmtl::Quat<float> q3( q );
      CPPUNIT_ASSERT( q3[gmtl::Xelt] == 5.0f );
      CPPUNIT_ASSERT( q3[gmtl::Yelt] == 6.0f );
      CPPUNIT_ASSERT( q3[gmtl::Zelt] == 7.0f );
      CPPUNIT_ASSERT( q3[gmtl::Welt] == 8.0f );

      // try out operator=() function
      gmtl::Quat<float> q4;
      CPPUNIT_ASSERT( q4[gmtl::Xelt] == 0.0f );
      CPPUNIT_ASSERT( q4[gmtl::Yelt] == 0.0f );
      CPPUNIT_ASSERT( q4[gmtl::Zelt] == 0.0f );
      CPPUNIT_ASSERT( q4[gmtl::Welt] == 1.0f );
      q4 = q2;
      CPPUNIT_ASSERT( q4[gmtl::Xelt] == 10.0f );
      CPPUNIT_ASSERT( q4[gmtl::Yelt] == 11.0f );
      CPPUNIT_ASSERT( q4[gmtl::Zelt] == 12.0f );
      CPPUNIT_ASSERT( q4[gmtl::Welt] == 13.0f );

      // check out the const identities...
      gmtl::Quat<float> q9( gmtl::QUAT_IDENTITYF );
      CPPUNIT_ASSERT( q9[gmtl::Xelt] == 0.0f );
      CPPUNIT_ASSERT( q9[gmtl::Yelt] == 0.0f );
      CPPUNIT_ASSERT( q9[gmtl::Zelt] == 0.0f );
      CPPUNIT_ASSERT( q9[gmtl::Welt] == 1.0f );

      gmtl::Quat<float> q10( gmtl::QUAT_MULT_IDENTITYF );
      CPPUNIT_ASSERT( q10[gmtl::Xelt] == 0.0f );
      CPPUNIT_ASSERT( q10[gmtl::Yelt] == 0.0f );
      CPPUNIT_ASSERT( q10[gmtl::Zelt] == 0.0f );
      CPPUNIT_ASSERT( q10[gmtl::Welt] == 1.0f );

      gmtl::Quat<float> q11( gmtl::QUAT_ADD_IDENTITYF );
      CPPUNIT_ASSERT( q11[gmtl::Xelt] == 0.0f );
      CPPUNIT_ASSERT( q11[gmtl::Yelt] == 0.0f );
      CPPUNIT_ASSERT( q11[gmtl::Zelt] == 0.0f );
      CPPUNIT_ASSERT( q11[gmtl::Welt] == 0.0f );
   }

   void QuatClassMetricTest::testQuatTimingDefaultConstructor()
   {
      const long iters( 400000 );
      float use_value(1);

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of def constructor
         gmtl::Quat<float> q;
         use_value += q.mData[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatTest/DefaultConstructor", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value != 0 );
   }

   void QuatClassMetricTest::testQuatTimingElementConstructor()
   {
      const long iters( 400000 );
      float use_value(1);

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of element constructor
         gmtl::Quat<float> q2( 10, 11, 12, 13 );
         use_value += q2.mData[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatTest/ElementConstructor", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value != 0 );
   }

   void QuatClassMetricTest::testQuatTimingCopyConstructor()
   {
      const long iters( 400000 );
      float use_value(1);
      gmtl::Quat<float> q( 67, 68, 69, 60 );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of copy constructor
         gmtl::Quat<float> q3( q );
         use_value += q3.mData[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatTest/CopyConstructor", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value != 0 );
   }


   void QuatClassMetricTest::testQuatTimingGet()
   {
      const long iters( 400000 );
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();
      gmtl::Quat<float> q;
      float x = 102, y = 103, z = 101, w = 100;
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of get...
         q.get( x, y, z, w );
         use_value = use_value + x + y + z + w;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatTest/get()", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }

   void QuatClassMetricTest::testQuatTimingSet()
   {
      const long iters( 400000 );
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();
      gmtl::Quat<float> q;
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of set...
         q.set( 1, 2, 3, 4 );
         use_value += q[gmtl::Xelt];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatTest/set()", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value >= 0.0f );
   }

   void QuatClassMetricTest::testQuatTimingOpBracket()
   {
      const long iters( 400000 );
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();
      gmtl::Quat<float> q;
      float x = 102, y = 103, z = 101, w = 100;
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of brackets
         q[gmtl::Xelt] = x;
         q[gmtl::Yelt] = y;
         q[gmtl::Zelt] = z;
         q[gmtl::Welt] = w;
         use_value = use_value + x + y + z + w;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatTest/operator[]()", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }

   void QuatClassMetricTest::testQuatTimingGetData()
   {
      const long iters( 400000 );
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();
      gmtl::Quat<float> q;
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of getData...
         const float* d = q.getData();
         use_value += d[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatTest/getData()", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }

   void QuatClassMetricTest::testQuatTimingOpEqual()
   {
      const long iters( 400000 );
      gmtl::Quat<float> q4, q2( 0, 2, 1, 3 );
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of operator=() function
         q4 = q2;
         q2[0] += q4[2];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatTest/operator=()", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( q4[0] != 3498.0f );
   }
}

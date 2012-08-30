// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "EulerAngleClassTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/EulerAngle.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(EulerAngleClassTest);
   CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(EulerAngleClassMetricTest, Suites::metric());

   void EulerAngleClassTest::testEulerAngleClassTestCreation()
   {
      // test that it initializes to the identity
      gmtl::EulerAngleXYZf q;
      CPPUNIT_ASSERT( q[0] == 0.0f );
      CPPUNIT_ASSERT( q[1] == 0.0f );
      CPPUNIT_ASSERT( q[2] == 0.0f );

      // try out set...
      q.set( 1.0f, 2.0f, 3.0f );
      CPPUNIT_ASSERT( q[0] == 1.0f );
      CPPUNIT_ASSERT( q[1] == 2.0f );
      CPPUNIT_ASSERT( q[2] == 3.0f );

      // try out setting with brackets
      q[0] = 5.0f;
      q[1] = 6.0f;
      q[2] = 7.0f;
      CPPUNIT_ASSERT( q[0] == 5.0f );
      CPPUNIT_ASSERT( q[1] == 6.0f );
      CPPUNIT_ASSERT( q[2] == 7.0f );
     
      // try out element constructor
      gmtl::EulerAngleZYXf q2( 10.0f, 11.0f, 12.0f );
      CPPUNIT_ASSERT( q2[0] == 10.0f );
      CPPUNIT_ASSERT( q2[1] == 11.0f );
      CPPUNIT_ASSERT( q2[2] == 12.0f );

      // try out copy constructor
      gmtl::EulerAngleXYZf q3( q );
      CPPUNIT_ASSERT( q3[0] == 5.0f );
      CPPUNIT_ASSERT( q3[1] == 6.0f );
      CPPUNIT_ASSERT( q3[2] == 7.0f );

      // try out operator=() function
      gmtl::EulerAngleXYZf q4;
      CPPUNIT_ASSERT( q4[0] == 0.0f );
      CPPUNIT_ASSERT( q4[1] == 0.0f );
      CPPUNIT_ASSERT( q4[2] == 0.0f );
      gmtl::EulerAngleZYXf q13;
      q13 = q2;
      CPPUNIT_ASSERT( q13[0] == 10.0f );
      CPPUNIT_ASSERT( q13[1] == 11.0f );
      CPPUNIT_ASSERT( q13[2] == 12.0f );

      // check out the const identities...
      gmtl::EulerAngleXYZf q9( gmtl::EULERANGLE_IDENTITY_XYZF );
      CPPUNIT_ASSERT( q9[0] == 0.0f );
      CPPUNIT_ASSERT( q9[1] == 0.0f );
      CPPUNIT_ASSERT( q9[2] == 0.0f );
   }

   void EulerAngleClassMetricTest::testEulerAngleTimingDefaultConstructor()
   {
      const long iters( 400000 );
      float use_value(1);

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of def constructor
         gmtl::EulerAngleXYZf q;
         use_value += q[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("EulerAngleTest/DefaultConstructor", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value != 0 );
   }

   void EulerAngleClassMetricTest::testEulerAngleTimingElementConstructor()
   {
      const long iters( 400000 );
      float use_value(1);

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of element constructor
         gmtl::EulerAngleXYZf q2( 10.0f, 11.0f, 12.0f );
         use_value += q2[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("EulerAngleTest/ElementConstructor", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value != 0 );
   }

   void EulerAngleClassMetricTest::testEulerAngleTimingCopyConstructor()
   {
      const long iters( 400000 );
      float use_value(1);
      gmtl::EulerAngleXYZf q( 67.0f, 68.0f, 69.0f );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of copy constructor
         gmtl::EulerAngleXYZf q3( q );
         use_value += q3[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("EulerAngleTest/CopyConstructor", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value != 0 );
   }

   void EulerAngleClassMetricTest::testEulerAngleTimingSet()
   {
      const long iters( 400000 );
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();
      gmtl::EulerAngleXYZf q;
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of set...
         q.set( 1, 2, 3 );
         use_value += q[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("EulerAngleTest/set()", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value >= 0.0f );
   }

   void EulerAngleClassMetricTest::testEulerAngleTimingOpBracket()
   {
      const long iters( 400000 );
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();
      gmtl::EulerAngleXYZf q;
      float x = 102.0f, y = 103.0f, z = 101.0f;
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of brackets
         q[0] = x;
         q[1] = y;
         q[2] = z;
         use_value = use_value + x + y + z;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("EulerAngleTest/operator[]()", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }

   void EulerAngleClassMetricTest::testEulerAngleTimingGetData()
   {
      const long iters( 400000 );
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();
      gmtl::EulerAngleXYZf q( 1, 2, 3 );
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of getData...
         const float* d = q.getData();
         use_value += d[1];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("EulerAngleTest/getData()", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }

   void EulerAngleClassMetricTest::testEulerAngleTimingOpEqual()
   {
      const long iters( 400000 );
      gmtl::EulerAngleXYZf q4, q2( 0.0f, 2.0f, 1.0f );
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of operator=() function
         q4 = q2;
         q2[0] += q4[2];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("EulerAngleTest/operator=()", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( q4[0] != 3498.0f );
   }
}

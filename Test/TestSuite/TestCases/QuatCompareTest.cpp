// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "QuatCompareTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Quat.h>
#include <gmtl/QuatOps.h>

namespace gmtlTest
{
   template<typename T>
   class testEqual
   {
   public:
      static void go()
      {
         gmtl::Quat<T> quat1, quat2;
         quat1.set( (T)1.0, (T)2.0, (T)34.0, (T)4.0 );
         quat1 = quat2;
         CPPUNIT_ASSERT( quat1 == quat2 );
         CPPUNIT_ASSERT( quat2 == quat1 );

         // Test that != works on all elements
         for (int j = 0; j < 4; ++j)
         {
            quat2[j] = (T)1221.0f;
            CPPUNIT_ASSERT(  (quat1 != quat2) );
            CPPUNIT_ASSERT( !(quat1 == quat2) );
            quat2[j] = quat1[j]; // put it back
         }

         // Test for epsilon equals working
         CPPUNIT_ASSERT( gmtl::isEqual( quat1, quat2 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( quat1, quat2, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( quat2, quat1, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( quat2, quat1, (T)100000.0f ) );
         T eps = (T)10.0;
         for (int j = 0; j < 4; ++j)
         {
               quat2[j] = quat1[j] - (eps / (T)2.0);
               CPPUNIT_ASSERT(  gmtl::isEqual( quat1, quat2, eps ) );
               CPPUNIT_ASSERT( !gmtl::isEqual( quat1, quat2, (T)(eps / 3.0) ) );
               quat2[j] = quat1[j]; // put it back
         }
      }
   };

   template<typename T>
   class testEquiv
   {
   public:
      static void go()
      {
         gmtl::Quat<T> quat1((T)1.0, (T)2.0, (T)34.0, (T)4.0),
                       quat2(-(T)1.0, -(T)2.0, -(T)34.0, -(T)4.0),
                       quat3((T)1.0, (T)2.0, (T)34.0, (T)4.0),
                       quat4;

         // Test for geometric equivelency
         CPPUNIT_ASSERT( gmtl::isEquiv( quat1, quat2 ) );
         CPPUNIT_ASSERT( gmtl::isEquiv( quat1, quat2, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEquiv( quat2, quat1, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEquiv( quat2, quat1, (T)100000.0f ) );

         // Test for geometric equivelency
         CPPUNIT_ASSERT( gmtl::isEquiv( quat1, quat3 ) );
         CPPUNIT_ASSERT( gmtl::isEquiv( quat1, quat3, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEquiv( quat3, quat1, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEquiv( quat3, quat1, (T)100000.0f ) );

         // Test for geometric un-equivelency
         CPPUNIT_ASSERT( !gmtl::isEquiv( quat1, quat4 ) );
         CPPUNIT_ASSERT( !gmtl::isEquiv( quat1, quat4, (T)0.0f ) );
         CPPUNIT_ASSERT( !gmtl::isEquiv( quat4, quat1, (T)0.0f ) );
         CPPUNIT_ASSERT( !gmtl::isEquiv( quat4, quat1, (T)30.0f ) );
      }
   };

   void QuatCompareTest::testQuatEquiv()
   {
      testEquiv<float>::go();
      testEquiv<double>::go();
   }

   void QuatCompareTest::testQuatEqualityFloatTest()
   {
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
   }

   void QuatCompareTest::testQuatEqualityDoubleTest()
   {
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
   }

   void QuatCompareMetricTest::testQuatTimingOpEqualityTest()
   {
      // Test overhead of creation
      const long iters(400000);

      gmtl::Quat<float> src_quat11;
      gmtl::Quat<float> src_quat22;
      gmtl::Quat<float> src_quat33;
      gmtl::Quat<float> src_quat34;
      gmtl::Quat<float> src_quat44;
      gmtl::Quat<double> src_quat101;

      // half of them will be equal
      src_quat11[0] = 1.0f;
      src_quat22[2] = 1.0f;
      src_quat33[3] = 2.0f;

      gmtl::Quat<float> test_quat11( src_quat11 );
      gmtl::Quat<float> test_quat22( src_quat22 );
      gmtl::Quat<float> test_quat33( src_quat33 );
      gmtl::Quat<float> test_quat34( src_quat34 );
      gmtl::Quat<float> test_quat44( src_quat44 );
      gmtl::Quat<double> test_quat101( src_quat101 );

      // half will be not equal
      src_quat34[0] = 2.0f;
      src_quat44[1] = 3.0f;
      src_quat101[3] = 1.0;

      unsigned true_count(0);

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         if (src_quat11 == test_quat11)
            ++true_count;
         if (src_quat22 == test_quat22)
            ++true_count;
         if (src_quat33 == test_quat33)
            ++true_count;
         if (src_quat34 == test_quat34)
            ++true_count;
         if (src_quat44 == test_quat44)
            ++true_count;
         if (src_quat101 == test_quat101)
            ++true_count;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatCompareTest/operator==", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // Make sure the compiler doesn't optimize out true_count
      CPPUNIT_ASSERT( true_count > 0 );
   }

   void QuatCompareMetricTest::testQuatTimingOpNotEqualityTest()
   {
      // Test overhead of creation
      const long iters(400000);

      gmtl::Quat<float> src_quat11;
      gmtl::Quat<float> src_quat22;
      gmtl::Quat<float> src_quat33;
      gmtl::Quat<float> src_quat34;
      gmtl::Quat<float> src_quat44;
      gmtl::Quat<double> src_quat101;

      // half will be equal
      src_quat11[0] = 1.0f;
      src_quat22[2] = 1.0f;
      src_quat33[3] = 2.0f;

      gmtl::Quat<float> test_quat11( src_quat11 );
      gmtl::Quat<float> test_quat22( src_quat22 );
      gmtl::Quat<float> test_quat33( src_quat33 );
      gmtl::Quat<float> test_quat34( src_quat34 );
      gmtl::Quat<float> test_quat44( src_quat44 );
      gmtl::Quat<double> test_quat101( src_quat101 );

      // half will be not equal
      src_quat34[0] = 2.0f;
      src_quat44[1] = 3.0f;
      src_quat101[3] = 1.0f;

      unsigned true_count(0);

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         if (src_quat11 != test_quat11)
            ++true_count;
         if (src_quat22 != test_quat22)
            ++true_count;
         if (src_quat33 != test_quat33)
            ++true_count;
         if (src_quat34 != test_quat34)
            ++true_count;
         if (src_quat44 != test_quat44)
            ++true_count;
         if (src_quat101 != test_quat101)
            ++true_count;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatCompareTest/operator!=", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // Make sure the compiler doesn't optimize out true_count
      CPPUNIT_ASSERT( true_count > 0 );
   }

   void QuatCompareMetricTest::testQuatTimingIsEqualTest()
   {
      // Test overhead of creation
      const long iters(400000);

      gmtl::Quat<float> src_quat11;
      gmtl::Quat<float> src_quat22;
      gmtl::Quat<float> src_quat33;
      gmtl::Quat<float> src_quat34;
      gmtl::Quat<float> src_quat44;
      gmtl::Quat<double> src_quat101;

      // half will be equal
      src_quat11[0] = 1.0f;
      src_quat22[1] = 1.0f;
      src_quat33[2] = 2.0f;

      gmtl::Quat<float> test_quat11( src_quat11 );
      gmtl::Quat<float> test_quat22( src_quat22 );
      gmtl::Quat<float> test_quat33( src_quat33 );
      gmtl::Quat<float> test_quat34( src_quat34 );
      gmtl::Quat<float> test_quat44( src_quat44 );
      gmtl::Quat<double> test_quat101( src_quat101 );

      // half will be not equal
      src_quat34[3] = 23.0f;
      src_quat44[2] = 234.0f;
      src_quat101[1] = 1234.0f;

      unsigned true_count(0);

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         if (gmtl::isEqual( src_quat11,  test_quat11, 0.0f ))
            ++true_count;
         if (gmtl::isEqual( src_quat22,  test_quat22, 0.2f ))
            ++true_count;
         if (gmtl::isEqual( src_quat33,  test_quat33, 0.3f ))
            ++true_count;
         if (gmtl::isEqual( src_quat34,  test_quat34, 0.6f ))
            ++true_count;
         if (gmtl::isEqual( src_quat44,  test_quat44, 0.8f ))
            ++true_count;
         if (gmtl::isEqual( src_quat101, test_quat101, double(111.1) ))
            ++true_count;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatCompareTest/isEqual(...)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // Make sure the compiler doesn't optimize out true_count
      CPPUNIT_ASSERT( true_count > 0 );
   }

   void QuatCompareMetricTest::testQuatTimingEquiv()
   {
      gmtl::Quatf quat1(1.0, 2.0, 34.0, 4.0),
                       quat2(-1.0, -2.0, -34.0, -4.0);

      unsigned true_count(0);
      const long iters(200000);
      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         if (gmtl::isEquiv( quat1, quat2, 0.0001f ) )
            ++true_count;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("QuatCompareTest/isEquiv(quat,quat,tol)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // Make sure the compiler doesn't optimize out true_count
      CPPUNIT_ASSERT( true_count > 0 );
   }
}

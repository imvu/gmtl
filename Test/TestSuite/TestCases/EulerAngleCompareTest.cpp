// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "EulerAngleCompareTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/EulerAngle.h>
#include <gmtl/EulerAngleOps.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(EulerAngleCompareTest);
   CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(EulerAngleCompareMetricTest, Suites::metric());

   template<typename T>
   class testEqual
   {
   public:
      static void go()
      {
         gmtl::EulerAngle<T, gmtl::ZYX> euler1, euler2;
         euler1.set( (T)1.0, (T)2.0, (T)34.0 );
         euler1 = euler2;
         CPPUNIT_ASSERT( euler1 == euler2 );
         CPPUNIT_ASSERT( euler2 == euler1 );

         // Test that != works on all elements
         for (int j = 0; j < 3; ++j)
         {
            euler2[j] = (T)1221.0f;
            CPPUNIT_ASSERT(  (euler1 != euler2) );
            CPPUNIT_ASSERT( !(euler1 == euler2) );
            euler2[j] = euler1[j]; // put it back
         }

         // just for fun
         CPPUNIT_ASSERT(  (euler1 == euler2) );
         CPPUNIT_ASSERT( !(euler1 != euler2) );

         // Test for epsilon equals working
         CPPUNIT_ASSERT( gmtl::isEqual( euler1, euler2 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( euler1, euler2, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( euler2, euler1, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( euler2, euler1, (T)100000.0f ) );
         T eps = (T)10.0;
         for (int j = 0; j < 3; ++j)
         {
            euler2[j] = euler1[j] - (eps / (T)2.0);
            CPPUNIT_ASSERT(  gmtl::isEqual( euler1, euler2, eps ) );
            CPPUNIT_ASSERT( !gmtl::isEqual( euler1, euler2, (T)(eps / 3.0) ) );
            euler2[j] = euler1[j]; // put it back
         }
      }
   };

   void EulerAngleCompareTest::testEulerAngleEqualityFloatTest()
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

   void EulerAngleCompareTest::testEulerAngleEqualityDoubleTest()
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

   void EulerAngleCompareMetricTest::testEulerAngleTimingOpEqualityTest()
   {
      // Test overhead of creation
      const long iters(400000);

      gmtl::EulerAngleXYZf src_quat11;
      gmtl::EulerAngleXYZf src_quat22;
      gmtl::EulerAngleXYZf src_quat33;
      gmtl::EulerAngleXYZf src_quat34;
      gmtl::EulerAngleXYZf src_quat44;
      gmtl::EulerAngleXYZd src_quat101;

      // half of them will be equal
      src_quat11[0] = 1.0f;
      src_quat22[2] = 1.0f;
      src_quat33[1] = 2.0f;

      gmtl::EulerAngleXYZf test_quat11( src_quat11 );
      gmtl::EulerAngleXYZf test_quat22( src_quat22 );
      gmtl::EulerAngleXYZf test_quat33( src_quat33 );
      gmtl::EulerAngleXYZf test_quat34( src_quat34 );
      gmtl::EulerAngleXYZf test_quat44( src_quat44 );
      gmtl::EulerAngleXYZd test_quat101( src_quat101 );

      // half will be not equal
      src_quat34[0] = 2.0f;
      src_quat44[1] = 3.0f;
      src_quat101[2] = 1.0;

      unsigned true_count(0);

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
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
      CPPUNIT_ASSERT_METRIC_TIMING_LE("EulerAngleCompareTest/operator==", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // Make sure the compiler doesn't optimize out true_count
      CPPUNIT_ASSERT( true_count > 0 );
   }

   void EulerAngleCompareMetricTest::testEulerAngleTimingOpNotEqualityTest()
   {
      // Test overhead of creation
      const long iters(400000);

      gmtl::EulerAngleXYZf src_quat11;
      gmtl::EulerAngleXYZf src_quat22;
      gmtl::EulerAngleXYZf src_quat33;
      gmtl::EulerAngleXYZf src_quat34;
      gmtl::EulerAngleXYZf src_quat44;
      gmtl::EulerAngleXYZd src_quat101;

      // half will be equal
      src_quat11[0] = 1.0f;
      src_quat22[2] = 1.0f;
      src_quat33[1] = 2.0f;

      gmtl::EulerAngleXYZf test_quat11( src_quat11 );
      gmtl::EulerAngleXYZf test_quat22( src_quat22 );
      gmtl::EulerAngleXYZf test_quat33( src_quat33 );
      gmtl::EulerAngleXYZf test_quat34( src_quat34 );
      gmtl::EulerAngleXYZf test_quat44( src_quat44 );
      gmtl::EulerAngleXYZd test_quat101( src_quat101 );

      // half will be not equal
      src_quat34[0] = 2.0f;
      src_quat44[1] = 3.0f;
      src_quat101[2] = 1.0f;

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
      CPPUNIT_ASSERT_METRIC_TIMING_LE("EulerAngleCompareTest/operator!=", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // Make sure the compiler doesn't optimize out true_count
      CPPUNIT_ASSERT( true_count > 0 );
   }

   void EulerAngleCompareMetricTest::testEulerAngleTimingIsEqualTest()
   {
      // Test overhead of creation
      const long iters(400000);

      gmtl::EulerAngleXYZf src_quat11;
      gmtl::EulerAngleXYZf src_quat22;
      gmtl::EulerAngleXYZf src_quat33;
      gmtl::EulerAngleXYZf src_quat34;
      gmtl::EulerAngleXYZf src_quat44;
      gmtl::EulerAngleXYZd src_quat101;

      // half will be equal
      src_quat11[0] = 1.0f;
      src_quat22[1] = 1.0f;
      src_quat33[2] = 2.0f;

      gmtl::EulerAngleXYZf test_quat11( src_quat11 );
      gmtl::EulerAngleXYZf test_quat22( src_quat22 );
      gmtl::EulerAngleXYZf test_quat33( src_quat33 );
      gmtl::EulerAngleXYZf test_quat34( src_quat34 );
      gmtl::EulerAngleXYZf test_quat44( src_quat44 );
      gmtl::EulerAngleXYZd test_quat101( src_quat101 );

      // half will be not equal
      src_quat34[0] = 23.0f;
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
      CPPUNIT_ASSERT_METRIC_TIMING_LE("EulerAngleCompareTest/isEqual(...)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // Make sure the compiler doesn't optimize out true_count
      CPPUNIT_ASSERT( true_count > 0 );
   }
}

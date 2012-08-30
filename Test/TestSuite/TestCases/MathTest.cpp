// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "MathTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Math.h>
#include <iostream>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(MathTest);
   CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(MathMetricTest, Suites::metric());

   void MathTest::testQuadraticFormula()
   {
      float r1, r2;

      // Real roots
      CPPUNIT_ASSERT(gmtl::Math::quadraticFormula(r1, r2, 1.0f, 3.0f, 2.0f));
      CPPUNIT_ASSERT(r1 == -1);
      CPPUNIT_ASSERT(r2 == -2);

      CPPUNIT_ASSERT(gmtl::Math::quadraticFormula(r1, r2, 1.0f, 5.0f, 6.0f));
      CPPUNIT_ASSERT(r1 == -2);
      CPPUNIT_ASSERT(r2 == -3);

      // Imaginary roots
      CPPUNIT_ASSERT(! gmtl::Math::quadraticFormula(r1, r2, 1.0f, 2.0f, 3.0f));
   }

   template< class T >
   void testSign()
   {
      T val;

      val = T(2.5);
      CPPUNIT_ASSERT(gmtl::Math::sign(val) == 1);

      val = T(-2.5);
      CPPUNIT_ASSERT(gmtl::Math::sign(val) == -1);

      val = T(0);
      CPPUNIT_ASSERT(gmtl::Math::sign(val) == 0);
   }

   template< class T >
   void testZeroClamp()
   {
      T val;

      val = T(0.5);
      CPPUNIT_ASSERT( gmtl::Math::zeroClamp(val) == val );
      CPPUNIT_ASSERT( gmtl::Math::zeroClamp(val, T(0.49)) == val );
      CPPUNIT_ASSERT( gmtl::Math::zeroClamp(val, T(0.50)) == T(0) );
      CPPUNIT_ASSERT( gmtl::Math::zeroClamp(val, T(0.51)) == T(0) );

      val = T(25.0);
      CPPUNIT_ASSERT( gmtl::Math::zeroClamp(val) == val );
      CPPUNIT_ASSERT( gmtl::Math::zeroClamp(val, T(24.9)) == val );
      CPPUNIT_ASSERT( gmtl::Math::zeroClamp(val, T(25.0)) == T(0) );
      CPPUNIT_ASSERT( gmtl::Math::zeroClamp(val, T(25.1)) == T(0) );
   }

   template< class T >
   void testTimingZeroClamp()
   {
      // test performance
      const long iters(400000);
      T use_val(0);
      T val = T(0);

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         val += T(0.5);
         use_val += gmtl::Math::zeroClamp( val, T(0.4) );
         use_val += gmtl::Math::zeroClamp( val, T(0.2) );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      std::string typeName = std::string("MathTest/ZeroClamp[") + std::string(typeid(T).name()) + std::string("]");
      CPPUNIT_ASSERT_METRIC_TIMING_LE(typeName, iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize out use_val
      CPPUNIT_ASSERT( use_val > 0 );
   }

   void MathTest::testSigni()
   {
      testSign<int>();
   }

   void MathTest::testSignf()
   {
      testSign<float>();
   }

   void MathTest::testZeroClampf()
   {
      testZeroClamp<float>();
   }

   void MathTest::testZeroClampd()
   {
      testZeroClamp<double>();
   }

   void MathMetricTest::testTimingZeroClampf()
   {
      testTimingZeroClamp<float>();
   }

   void MathMetricTest::testTimingZeroClampd()
   {
      testTimingZeroClamp<double>();
   }

   void MathMetricTest::testFastInvSqrt()
   {

      /*
      std::cout << "--- Inverse sqrts ---" << std::endl;
      for(float x=0.001;x<10.0f;x+=0.05f)
      {
         std::cout << x << ", "
                   << 1.0/gmtl::Math::sqrt(x) << ", "
                   << gmtl::Math::fastInvSqrt(x) << ", "
                   << gmtl::Math::fastInvSqrt2(x) << ", "
                   << gmtl::Math::fastInvSqrt3(x) << std::endl;
      }

      std::cout << "---- more ----" << std::endl;
      for(float x=1;x<10000.0f;x+=100.0f)
      {
         std::cout << x << ", "
                   << 1.0/gmtl::Math::sqrt(x) << ", "
                   << gmtl::Math::fastInvSqrt(x) << ", "
                   << gmtl::Math::fastInvSqrt2(x) << ", "
                   << gmtl::Math::fastInvSqrt3(x) << std::endl;
      }
      */

      const long iters(100000);

      {
         // stdInvSqrt
         float use_val(0);
         float val(0.001f);

        CPPUNIT_METRIC_START_TIMING();
        for (long iter = 0; iter < iters; ++iter)
        {
           val += 0.05f;
           use_val += (1.0f/gmtl::Math::sqrt(val));
        }

        CPPUNIT_METRIC_STOP_TIMING();
        std::string typeName = std::string("MathTest/stdInvSqrt");
        CPPUNIT_ASSERT_METRIC_TIMING_LE(typeName, iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

        // make sure the compiler doesn't optimize out use_val
        CPPUNIT_ASSERT( use_val > 0 );
      }

      {
         // fastInvSqrt
         float use_val(0);
         float val(0.001f);

        CPPUNIT_METRIC_START_TIMING();
        for (long iter = 0; iter < iters; ++iter)
        {
           val += 0.05f;
           use_val += gmtl::Math::fastInvSqrt(val);
        }

        CPPUNIT_METRIC_STOP_TIMING();
        std::string typeName = std::string("MathTest/fastInvSqrt");
        CPPUNIT_ASSERT_METRIC_TIMING_LE(typeName, iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

        // make sure the compiler doesn't optimize out use_val
        CPPUNIT_ASSERT( use_val > 0 );
      }

      {
         // fastInvSqrt2
         float use_val(0);
         float val(0.001f);

        CPPUNIT_METRIC_START_TIMING();
        for (long iter = 0; iter < iters; ++iter)
        {
           val += 0.05f;
           use_val += gmtl::Math::fastInvSqrt2(val);
        }

        CPPUNIT_METRIC_STOP_TIMING();
        std::string typeName = std::string("MathTest/fastInvSqrt2");
        CPPUNIT_ASSERT_METRIC_TIMING_LE(typeName, iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

        // make sure the compiler doesn't optimize out use_val
        CPPUNIT_ASSERT( use_val > 0 );
      }

      {
         // fastInvSqrt3
         float use_val(0);
         float val(0.001f);

        CPPUNIT_METRIC_START_TIMING();
        for (long iter = 0; iter < iters; ++iter)
        {
           val += 0.05f;
           use_val += gmtl::Math::fastInvSqrt3(val);
        }

        CPPUNIT_METRIC_STOP_TIMING();
        std::string typeName = std::string("MathTest/fastInvSqrt3");
        CPPUNIT_ASSERT_METRIC_TIMING_LE(typeName, iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

        // make sure the compiler doesn't optimize out use_val
        CPPUNIT_ASSERT( use_val > 0 );
      }

   }

}

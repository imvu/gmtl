// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "QuatGenTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <gmtl/Quat.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Generate.h>
#include <gmtl/AxisAngle.h>
#include <gmtl/AxisAngleOps.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(QuatGenTest);
   CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(QuatGenMetricTest, Suites::metric());

   //-- quat tests --//
   void QuatGenTest::testQuatMakePure()
   {
      gmtl::Vec<float, 3> vec( 121, 232, 343 );
      gmtl::Quat<float> quat( gmtl::makePure( vec ) ), q2;
      CPPUNIT_ASSERT( quat[gmtl::Xelt] == 121 );
      CPPUNIT_ASSERT( quat[gmtl::Yelt] == 232 );
      CPPUNIT_ASSERT( quat[gmtl::Zelt] == 343 );

      // make sure set works the same
      gmtl::setPure( q2, vec );
      CPPUNIT_ASSERT( q2[gmtl::Xelt] == 121 );
      CPPUNIT_ASSERT( q2[gmtl::Yelt] == 232 );
      CPPUNIT_ASSERT( q2[gmtl::Zelt] == 343 );
   }

   void QuatGenTest::testQuatMakeConj()
   {
      gmtl::Quat<float> quat( 0.0f,21.0f,31.0f,1234.0f );
      gmtl::Quat<float> quat2 = gmtl::makeConj( quat );

      // make sure the func didn't munge the data...
      CPPUNIT_ASSERT( quat[gmtl::Xelt] == 0.0f );
      CPPUNIT_ASSERT( quat[gmtl::Yelt] == 21.0f );
      CPPUNIT_ASSERT( quat[gmtl::Zelt] == 31.0f );
      CPPUNIT_ASSERT( quat[gmtl::Welt] == 1234.0f );

      // make sure conj worked.
      CPPUNIT_ASSERT( quat2[gmtl::Xelt] == -0.0f );
      CPPUNIT_ASSERT( quat2[gmtl::Yelt] == -21.0f );
      CPPUNIT_ASSERT( quat2[gmtl::Zelt] == -31.0f );
      CPPUNIT_ASSERT( quat2[gmtl::Welt] == 1234.0f );

      // make sure set works the same
      /// @todo no impl
      // gmtl::Quat<float> q2;
      //gmtl::setConj( q2, quat );
      //CPPUNIT_ASSERT( q2[gmtl::Xelt] == -0.0f );
      //CPPUNIT_ASSERT( q2[gmtl::Yelt] == -21.0f );
      //CPPUNIT_ASSERT( q2[gmtl::Zelt] == -31.0f );
      //CPPUNIT_ASSERT( q2[gmtl::Welt] == 1234.0f );
   }

   void QuatGenTest::testQuatMakeInvert()
   {
      // test out mult( result, quat, quat )
      const float eps = 0.0001f;
      gmtl::Quat<float> q( 0.2f, 0.33f, 0.44f, 0.101f ), expected_result( -0.567053f, -0.935637f, -1.24752f, 0.286362f );
      gmtl::Quat<float> q4( gmtl::makeInvert( q ) );
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result, q4, eps ) );

      // make sure set works the same
      /// @todo no impl
      // gmtl::Quat<float> q5;
      //gmtl::setInvert( q5, q );
      //CPPUNIT_ASSERT( gmtl::isEqual( expected_result, q5, eps ) );
   }

   void QuatGenTest::testQuatMakeRot()
   {
      const float eps = 0.0001f;
      gmtl::Quat<float> q1, q2;
      q1 = gmtl::make<gmtl::Quat<float> >( gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), 1.0f, 0.0f, 0.0f ) );
      q2 = gmtl::make<gmtl::Quat<float> >( gmtl::AxisAnglef( gmtl::Math::deg2Rad( 32.0f ), 0.0f, 1.0f, 0.0f ) );
      gmtl::Quat<float> expected_result1( 0.707107f, 0, 0, 0.707107f );
      gmtl::Quat<float> expected_result2( 0, 0.275637f, 0, 0.961262f );

      CPPUNIT_ASSERT( gmtl::isEqual( expected_result1, q1, eps ) );
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result2, q2, eps ) );
      CPPUNIT_ASSERT( gmtl::isNormalized( q1, eps ) );
      CPPUNIT_ASSERT( gmtl::isNormalized( q2, eps ) );

      // values from VR Juggler math lib...
      std::vector< gmtl::Quat<float> > quats;
      quats.push_back( gmtl::Quat<float>( 0, 0, 0, -1       ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.173648f, -0, -0.984808f) );
      quats.push_back( gmtl::Quat<float>( -0, -0.34202f, -0, -0.939693f ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.5f, -0, -0.866025f     ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.642788f, -0, -0.766044f) );
      quats.push_back( gmtl::Quat<float>( -0, -0.766044f, -0, -0.642788f) );
      quats.push_back( gmtl::Quat<float>( -0, -0.866025f, -0, -0.5f     ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.939693f, -0, -0.34202f ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.984808f, -0, -0.173648f) );
      quats.push_back( gmtl::Quat<float>( -0, -1, -0, 0    ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.984808f, -0, 0.173648f ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.939693f, -0, 0.34202f  ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.866025f, -0, 0.5f      ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.766044f, -0, 0.642788f ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.642788f, -0, 0.766044f ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.5f, -0, 0.866025f      ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.34202f, -0, 0.939693f  ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.173648f, -0, 0.984808f ) );
      quats.push_back( gmtl::Quat<float>( 0, 0, 0, 1                  ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.173648f, 0, 0.984808f    ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.34202f, 0, 0.939693f     ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.5f, 0, 0.866025f         ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.642788f, 0, 0.766044f    ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.766044f, 0, 0.642788f    ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.866025f, 0, 0.5f         ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.939693f, 0, 0.34202f     ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.984808f, 0, 0.173648f    ) );
      quats.push_back( gmtl::Quat<float>( 0, 1, 0, 0       ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.984808f, 0, -0.173648f   ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.939693f, 0, -0.34202f    ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.866025f, 0, -0.5f        ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.766044f, 0, -0.642788f   ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.642788f, 0, -0.766044f   ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.5f, 0, -0.866025f        ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.34202f, 0, -0.939693f    ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.173648f, 0, -0.984808f   ) );
      quats.push_back( gmtl::Quat<float>( -0, 0, -0, -1    ) );

      /// @todo check this against another math lib other than VR Juggler...
      int count = 0;
      for (int x = -360; x <= 360; x += 20)
      {
         gmtl::Quat<float> q3;
         CPPUNIT_ASSERT( count >= 0 );
         gmtl::set( q2, gmtl::AxisAnglef( gmtl::Math::deg2Rad( float(x) ), 0.0f, 1.0f, 0.0f ) );
         gmtl::set( q3, gmtl::AxisAnglef( gmtl::Math::deg2Rad( float(x) ), gmtl::Vec3f( 0.0f, 1.0f, 0.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( quats[count], q2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( q3, q2, eps ) );

         // make sure that makeRot and setRot do the same thing...
         CPPUNIT_ASSERT( gmtl::make<gmtl::Quat<float> >( gmtl::AxisAnglef( gmtl::Math::deg2Rad( float(x) ), 0.0f, 1.0f, 0.0f ) ) == q2 );
         CPPUNIT_ASSERT( gmtl::make<gmtl::Quat<float> >( gmtl::AxisAnglef( gmtl::Math::deg2Rad( float(x) ), gmtl::Vec3f( 0.0f, 1.0f, 0.0f ) ) ) == q3 );
         count++;
      }

   }

   void QuatGenTest::testQuatGetRot()
   {
      const float eps = 0.0001f;
      std::vector<gmtl::Vec4f> quats;
      quats.push_back( gmtl::Vec4f( 6.28319f, 1, 0, 0           ) );
      quats.push_back( gmtl::Vec4f( 5.93412f, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 5.58505f, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 5.23599f, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 4.88692f, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 4.53786f, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 4.18879f, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 3.83972f, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 3.49066f, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 3.14159f, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 2.79253f, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 2.44346f, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 2.0944f, -0, -1, -0         ) );
      quats.push_back( gmtl::Vec4f( 1.74533f, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 1.39626f, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 1.0472f, -0, -1, -0         ) );
      quats.push_back( gmtl::Vec4f( 0.698132f, -0, -1, -0       ) );
      quats.push_back( gmtl::Vec4f( 0.349066f, -0, -0.999999f, -0 ) );
      quats.push_back( gmtl::Vec4f( 0, 1, 0, 0                 ) );
      quats.push_back( gmtl::Vec4f( 0.349066f, 0, 0.999999f, 0   ) );
      quats.push_back( gmtl::Vec4f( 0.698132f, 0, 1, 0          ) );
      quats.push_back( gmtl::Vec4f( 1.0472f, 0, 1, 0            ) );
      quats.push_back( gmtl::Vec4f( 1.39626f, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 1.74533f, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 2.0944f, 0, 1, 0            ) );
      quats.push_back( gmtl::Vec4f( 2.44346f, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 2.79253f, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 3.14159f, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 3.49066f, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 3.83972f, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 4.18879f, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 4.53786f, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 4.88692f, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 5.23599f, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 5.58505f, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 5.93412f, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 6.28319f, 1, 0, 0           ) );

      /// @todo check this against another math lib other than VR Juggler...   (all the vals above look sane, but... )
      gmtl::Quat<float> q2;
      gmtl::AxisAnglef axisAngle;
      int count = 0;
      for (int x = -360; x <= 360; x += 20)
      {
         q2 = gmtl::make<gmtl::Quat<float> >( gmtl::AxisAnglef( gmtl::Math::deg2Rad( float(x) ), 0.0f, 1.0f, 0.0f ) );
         gmtl::set( axisAngle, q2 );
         CPPUNIT_ASSERT( gmtl::isEqual( quats[count], gmtl::Vec4f(axisAngle), eps ) );
         ++count;
      }
   }

   void QuatGenTest::testQuatMakeGetMakeRot()
   {
      const float eps = 0.0001f;
      gmtl::AxisAnglef axisAngle;
      gmtl::AxisAnglef axisAngle1;
      gmtl::Quat<float> q2, q3;
      for (int x = -360; x <= 360; x += 20)
      {
         q2 = gmtl::make<gmtl::Quat<float> >( gmtl::AxisAnglef( gmtl::Math::deg2Rad( float(x) ), 0.0f, 1.0f, 0.0f ) );
         gmtl::set( axisAngle, q2 );
         q3 = gmtl::make<gmtl::Quat<float> >( axisAngle );
         gmtl::set( axisAngle1, q3 );
         CPPUNIT_ASSERT( gmtl::isEqual( q3, q2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( axisAngle1, axisAngle, eps ) );
      }
   }


   //-- timing tests --//
   void QuatGenMetricTest::testGenTimingMakeInvert1()
   {
      gmtl::Quat<double> q1;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         q1 = gmtl::makeInvert( q1 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "QuatGenTest/makeInvert(quatd)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( q1[0] != 10000.0f );
   }

   void QuatGenMetricTest::testGenTimingMakeInvert2()
   {
      gmtl::Quat<float> q2;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         q2 = gmtl::makeInvert( q2 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "QuatGenTest/makeInvert(quatf)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( q2[0] != 10000.0f );
   }

   void QuatGenMetricTest::testGenTimingMakeConj()
   {
      gmtl::Quat<double> q1;
      const long iters(50000);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter = 0; iter < iters; ++iter)
      {
         q1 = gmtl::makeConj( q1 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "QuatGenTest/makeConj(quatd)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      gmtl::Quat<float> q2;
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         q2 = gmtl::makeConj( q2 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "QuatGenTest/makeConj(quatf)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( q2[0] != 10000.0f );
      CPPUNIT_ASSERT( q1[0] != 10000.0f );
   }

   void QuatGenMetricTest::testGenTimingMakePure()
   {
      gmtl::Quat<double> q1;
      gmtl::Vec<double, 3> v1;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter = 0; iter < iters; ++iter)
      {
         q1 = gmtl::makePure( v1 );
         q1[2] -= v1[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "QuatGenTest/makePure(vec3d)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      gmtl::Quat<float> q2;
      gmtl::Vec<float, 3> v2;
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         q2 = gmtl::makePure( v2 );
         q2[2] += v2[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "QuatGenTest/makePure(vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( q2[0] != 10000.0f );
      CPPUNIT_ASSERT( q1[0] != 10000.0f );
   }

   void QuatGenMetricTest::testGenTimingMakeNormalQuat()
   {
      gmtl::Quat<double> q1;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter = 0; iter < iters; ++iter)
      {
         q1 = gmtl::makeNormal( q1 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "QuatGenTest/makeNormal(quatd)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      gmtl::Quat<float> q2;
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         q2 = gmtl::makeNormal( q2 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "QuatGenTest/makeNormal(quatf)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( q2[0] != 10000.0f );
      CPPUNIT_ASSERT( q1[0] != 10000.0f );
   }

   void QuatGenMetricTest::testGenTimingMakeRot()
   {
      double bokd = 1;
      float bokf = 1;
      gmtl::Quat<double> q1;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter = 0; iter < iters; ++iter)
      {
         q1 = gmtl::make<gmtl::Quat<double> >( gmtl::makeNormal( gmtl::AxisAngled( bokd, bokd, bokd, bokd ) ) );
         bokd += q1[2];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "QuatGenTest/make<quatd>(axisangled)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      gmtl::Quat<float> q2; bokf = 1.0f;
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         q2 = gmtl::make<gmtl::Quat<float> >( gmtl::makeNormal( gmtl::AxisAnglef( bokf, bokf, bokf, bokf ) ) );
         bokf -= q2[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "QuatGenTest/make<quatf>(axisanglef)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%


      gmtl::Quat<double> q3; bokd = 1.0f;
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         q3 = gmtl::make<gmtl::Quat<double> >( gmtl::makeNormal( gmtl::AxisAngled( bokd, gmtl::Vec<double, 3>( bokd, bokd, bokd ) ) ) );
         bokd *= q3[1] + 1.234;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "QuatGenTest/make<quatd>(axisangled(r,vec))", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      gmtl::Quat<float> q4; bokf = 1.0f;
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         q4 = gmtl::make<gmtl::Quat<float> >( gmtl::makeNormal( gmtl::AxisAnglef( bokf, gmtl::Vec<float, 3>( bokf, bokf, bokf ) ) ) );
         bokf += q4[1] + 1.234f;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "QuatGenTest/make<quatf>(axisanglef(r,vec))", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%


      gmtl::Quat<double> q5;
      gmtl::Vec<double, 3> v4(1,2,3), v5(1,2,3);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         q5 = gmtl::makeRot<gmtl::Quat<double> >( gmtl::makeNormal(v4), gmtl::makeNormal(v5) );
         v4[2] += q5[1] + 1.234;
         v5[0] -= q5[2] + 1.234;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "QuatGenTest/make<quatd>(vec3d,vec3d)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      gmtl::Quat<float> q6;
      gmtl::Vec<float, 3> v6(1,2,3), v7(1,2,3);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         q6 = gmtl::makeRot<gmtl::Quat<float> >( gmtl::makeNormal(v6), gmtl::makeNormal(v7) );
         v6[2] += q6[1] + 1.234f;
         v7[0] -= q6[2] + 1.234f;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "QuatGenTest/make<quatf>(vec3f,vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      gmtl::AxisAnglef axisAngle;
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::set( axisAngle, q6 );
         q6[0] = axisAngle[0] + axisAngle[1] - axisAngle[2] - axisAngle[3];
         axisAngle[0] += q6[1] + 1.234f;
         axisAngle[1] -= q6[2] * -0.22f + 1.234f;
         axisAngle[2] += q6[1] + 0.1f;
         axisAngle[3] -= q6[2] - 0.99f;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "QuatGenTest/set(axisangle,quatf)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( bokf != 0.998f );
      CPPUNIT_ASSERT( bokd != 0.0998 );
      CPPUNIT_ASSERT( q1[0] != 10000.0f );
      CPPUNIT_ASSERT( q2[1] != 10000.0f );
      CPPUNIT_ASSERT( q3[2] != 10000.0f );
      CPPUNIT_ASSERT( q4[3] != 10000.0f );
      CPPUNIT_ASSERT( q5[0] != 10000.0f );
      CPPUNIT_ASSERT( q6[1] != 10000.0f );
   }


   void QuatGenMetricTest::testGenTimingSetRot()
   {
      double bokd = 1;
      float bokf = 1;
      gmtl::Quat<double> q1;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::set( q1, gmtl::makeNormal( gmtl::AxisAngled( bokd, bokd, bokd, bokd ) ) );
         bokd += q1[2];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "QuatGenTest/setRot(quatd,axisangled)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      gmtl::Quat<float> q2; bokf = 1.0f;
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::set( q2, gmtl::makeNormal( gmtl::AxisAnglef( bokf, bokf, bokf, bokf ) ) );
         bokf -= q2[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "QuatGenTest/setRot(quatf,axisanglef)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%


      gmtl::Quat<double> q3; bokd = 1.0f;
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::set( q3, gmtl::makeNormal( gmtl::AxisAngled( bokd, gmtl::Vec<double, 3>( bokd, bokd, bokd ) ) ) );
         bokd *= q3[1] + 1.2;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "QuatGenTest/setRot(quatd,axisangled(r,vec))", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      gmtl::Quat<float> q4; bokf = 1.0f;
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::set( q4, gmtl::makeNormal( gmtl::AxisAnglef( bokf, gmtl::Vec<float, 3>( bokf, bokf, bokf ) ) ) );
         bokf += q4[1] + 1.2f;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "QuatGenTest/setRot(quatf,axisanglef(r,vec))", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%


      gmtl::Quat<double> q5;
      gmtl::Vec<double, 3> v4(1,2,3), v5(1,2,3);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setRot( q5, gmtl::makeNormal( v4 ), gmtl::makeNormal( v5 ) );
         v4[2] += q5[1] + 1.2;
         v5[0] -= q5[2] + 1.2;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "QuatGenTest/setRot(quatd,vec3d,vec3d)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      gmtl::Quat<float> q6;
      gmtl::Vec<float, 3> v6(1,2,3), v7(1,2,3);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setRot( q6, gmtl::makeNormal( v6 ), gmtl::makeNormal( v7 ) );
         v6[2] += q6[1] + 1.2f;
         v7[0] -= q6[2] + 1.2f;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "QuatGenTest/setRot(quatf,vec3f,vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( bokf != 0.998f );
      CPPUNIT_ASSERT( bokd != 0.0998 );
      CPPUNIT_ASSERT( q1[0] != 10000.0f );
      CPPUNIT_ASSERT( q2[1] != 10000.0f );
      CPPUNIT_ASSERT( q3[2] != 10000.0f );
      CPPUNIT_ASSERT( q4[3] != 10000.0f );
      CPPUNIT_ASSERT( q5[0] != 10000.0f );
      CPPUNIT_ASSERT( q6[1] != 10000.0f );
   }
}

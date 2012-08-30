// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "QuatStuffTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Quat.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Xforms.h>
#include <gmtl/AxisAngle.h>
#include <gmtl/AxisAngleOps.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(QuatStuffTest);

   void QuatStuffTest::makeRotTest()
   {
      // make sure make rot produces a normalized quat (if not normalized, then it isn't a rotation)
      gmtl::Quatf q1, q2, q3, q4;
      // set the quat from the given euler params.
      q3 = gmtl::set( q1, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 45.0f ), 0.0f, 1.0f, 0.0f ) );
      q4 = gmtl::set( q2, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), 1.0f, 0.0f, 0.0f ) );
      gmtl::normalize( q3 );
      gmtl::normalize( q4 );

      // make sure that normalize doesn't change the rotation...
      CPPUNIT_ASSERT( gmtl::isEqual( q1, q3, 0.0001f ) );
      CPPUNIT_ASSERT( gmtl::isEqual( q2, q4, 0.0001f ) );
      
      CPPUNIT_ASSERT( gmtl::isEqual( q1, gmtl::makeRot<gmtl::Quatf>( gmtl::AxisAnglef( gmtl::Math::deg2Rad( 45.0f ), 0.0f, 1.0f, 0.0f ) ), 0.0001f ) );
      CPPUNIT_ASSERT( gmtl::isEqual( q2, gmtl::makeRot<gmtl::Quatf>( gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), 1.0f, 0.0f, 0.0f ) ), 0.0001f ) );

      // set the euler params from the given quat.
      gmtl::AxisAnglef axisAngle;
      gmtl::set( axisAngle, q1 );
      CPPUNIT_ASSERT( gmtl::isEqual( axisAngle, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 45.0f ), 0,1,0 ), 0.0001f ) );

      gmtl::set( axisAngle, q2 );
      CPPUNIT_ASSERT( gmtl::isEqual( axisAngle, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), 1,0,0 ), 0.0001f ) );
   }

   void QuatStuffTest::xformVecSweepTest()
   {
      // xform vector by quat (sweep over range of rotations)
      gmtl::Quatf q, q2;
      gmtl::Vec3f v( 0.0f, 0.0f, 1.0f );

      // Should go from 0,0,1 to 0,-1,0 to 0,0,-1 ....
      for (float x = 0; x <= 180.0f; x += 90)
      {
         gmtl::set( q, gmtl::AxisAnglef( gmtl::Math::deg2Rad( x ), 1.0f, 0.0f, 0.0f ) );
         q2 = gmtl::make<gmtl::Quatf>( gmtl::AxisAnglef( gmtl::Math::deg2Rad( x ), 1.0f, 0.0f, 0.0f ) );
         CPPUNIT_ASSERT( q2 == q );
         
         gmtl::Vec3f result( q * v );
         if (x == 0)
            CPPUNIT_ASSERT( result[0] < 0.001 && result[1] < 0.001 && result[2] > 0.999 );
         if (x == 90)
            CPPUNIT_ASSERT( result[0] < 0.001 && result[1] < -0.999 && result[2] < 0.001 );
         if (x == 180)
            CPPUNIT_ASSERT( result[0] < 0.001 && result[1] < 0.001 && result[2] < -0.999 );
      }
   }

   void QuatStuffTest::makeRotGetRotSanityTest()
   {
      // testing sanity of makeRot and getRot, then makeRot again...
      for (float i = -360; i <= 360; i+=20)
      {
         gmtl::Quatf q, q2;
         gmtl::AxisAnglef axisAngle;
         gmtl::set( q, gmtl::AxisAnglef( gmtl::Math::deg2Rad(i), 1.0f, 0.0f, 0.0f ) );
         gmtl::Quatf sanity = gmtl::make<gmtl::Quatf>( gmtl::AxisAnglef( gmtl::Math::deg2Rad(i), 1.0f, 0.0f, 0.0f ) );
         CPPUNIT_ASSERT( q == sanity );
      
         // set euler params from quat
         gmtl::set( axisAngle, q );
         
         // set quat from euler params
         gmtl::set( q2, axisAngle );
         
         sanity = gmtl::make<gmtl::Quatf>( axisAngle );
         CPPUNIT_ASSERT( q2 == sanity );
      
         
         // make i a positive by x*360, store in b.  needed so I can use the % operator with neg values..
         CPPUNIT_ASSERT( gmtl::isEqual( q, q2, 0.0001f ) );


         float b = i;
         while ( b < 0.0f)
         {
            b += 360.0f;
         }

         if (i >= 0.0f)
         {
            float c = gmtl::Math::abs( (float) ((int)(gmtl::Math::round(b)) % 360) );
            float temp1 = gmtl::Math::rad2Deg(axisAngle.getAngle()); temp1 = (float)((int)(gmtl::Math::round(temp1))%360);
            float temp2 = c + 0.5f;
            float temp3 = gmtl::Math::rad2Deg(axisAngle.getAngle()); temp3 = (float)((int)(gmtl::Math::round(temp3))%360);
            float temp4 = c - 0.5f;

            CPPUNIT_ASSERT( temp1 <= temp2 && temp3 >= temp4 );
         }
      }
   }


//   for (int x = 0; x < 4; ++x)
//             std::cout<<q[x]<<" "<<q2[x]<<std::endl;

   void QuatStuffTest::simpleQuatProductTest()
   {
      // Quat product: no rotation * rotation

      gmtl::Quatf q1, q2, q3;
      gmtl::set( q1, gmtl::AxisAnglef( 0.0f, 1.0f, 0.0f, 0.0f ) );
      gmtl::Quatf sanity = gmtl::make<gmtl::Quatf>( gmtl::AxisAnglef( 0.0f, 1.0f, 0.0f, 0.0f ) );
      CPPUNIT_ASSERT( q1 == sanity );
      
      gmtl::set( q2, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), 1.0f, 0.0f, 0.0f ) );
      sanity = gmtl::make<gmtl::Quatf>( gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), 1.0f, 0.0f, 0.0f ) );
      CPPUNIT_ASSERT( q2 == sanity );
      // [0 rotation] * [90deg about x] should be [90deg about x]

      // first rotate by q2, then by q1
      q3 = q1 * q2;

      gmtl::Vec3f v( 0,1,0 ), r;
      r = q3 * v;

      CPPUNIT_ASSERT( r[2] > 0.99f );
   }

   // another quaternion product test
   void QuatStuffTest::secondQuatProductTest()
   {
      // Quat product: rotation * rotation
      gmtl::Quatf q1, q2, q3;
      gmtl::set( q1, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 45.0f ), 0.0f,1.0f,0.0f ) );
      gmtl::set( q2, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), 1.0f,0.0f,0.0f ) );
      // [45 about Y] * [90 about X] should be [90deg about .7,0,-.7]

      // first rotate by q2, then by q1
      q3 = q1 * q2;

      gmtl::Vec3f v( 0,1,0 ), r;
      r = q3 * v;

      CPPUNIT_ASSERT( r[0] > 0.7 && r[2] > 0.7 );
   }

   void QuatStuffTest::xformVecTest()
   {
      // xform vec by quat
      gmtl::Quatf q1, q2;//, q3;
      gmtl::set( q1, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 45.0f ), 0.0f, -1.0f, 0.0f ) );
      gmtl::set( q2, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 45.0f ), 1.0f,  0.0f, 0.0f ) );

      gmtl::Vec3f v( 0,1,0 ), r;

      // (should not move)
      r = q1 * v;
      CPPUNIT_ASSERT( r[1] > 0.999 );

      // rotate forward
      r = q2 * v;
      CPPUNIT_ASSERT( r[1] > 0.7 && r[2] > 0.7 );
   }


   // just trying stuff out... TODO think of a good add test...
   void QuatStuffTest::specialCases()
   {
      gmtl::Quatf q( 0.0f, -0.000313354f, 0.0f, 1.0f );
      gmtl::AxisAnglef axisAngle;
      gmtl::set( axisAngle, q  );

      // testing...
      double half_angle = 0.000626708f * 0.5f;
      double sin_half_angle = gmtl::Math::sin( half_angle );
      double w = gmtl::Math::cos( half_angle );
      sin_half_angle += 1; // use sin_half_angle
      w += 1; // use w


      //gmtl::Quatf qq( 0,0,0,0 );
      // make sure that makeRot(180,0,1,0) doesn't yield [0,0,0,0]
      gmtl::Quatf qqq;
      gmtl::set( qqq, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 180.0f ), 0.0f, 1.0f, 0.0f ) );
      CPPUNIT_ASSERT( gmtl::Math::isEqual( qqq[gmtl::Welt], 0.0f, 0.0001f ) &&
                      qqq[gmtl::Xelt] == 0.0f &&
                      gmtl::Math::isEqual( qqq[gmtl::Yelt], 1.0f, 0.0001f ) &&
                      qqq[gmtl::Zelt] == 0.0f );
   }

   // just trying stuff out... TODO think of a good way to test this ability...
   // TODO: could we use a vector (pure quat) to scale a quat in a
   //        more robust way?  pretty sure we can... rewrite scaleAngle to use this
   //        method instead....
   void QuatStuffTest::vectorScaleTest()
   {
      //vector scale of a rotation quaternion\n"<<std::flush;
      //vector scale of a rotation quaternion yields an invalid rotation (only unit-quats define a rotation).\n"<<std::flush;

      // non normalized
      for (int x = 0; x < 360; ++x)
      {
         gmtl::Quatf q, q2;
         gmtl::set( q, gmtl::makeNormal( gmtl::AxisAnglef( gmtl::Math::deg2Rad( (float)x ), 0.7f, 0.0f, 0.7f ) ) );
         gmtl::mult( q2, q, 0.5f );

         // no longer a valid rotation (non-unit length).
         // should be normalized to define an actual rotation.
         CPPUNIT_ASSERT( !gmtl::isNormalized( q2 ) );

         gmtl::AxisAnglef axisAngle;
         gmtl::set( axisAngle, q2 );
         // @todo actually test this...assert?
      }

      // If normalized, then the scaled quat is equal to the original.
      // normalized.
      for (int x = 0; x < 360; ++x)
      {
         gmtl::Quatf q, q2;
         gmtl::set( q, gmtl::makeNormal( gmtl::AxisAnglef( gmtl::Math::deg2Rad( (float)x ), 0.7f, 0.0f, 0.7f ) ) );
         gmtl::mult( q2, q, 0.5f );
         gmtl::normalize( q2 );

         CPPUNIT_ASSERT( gmtl::isEqual( q2, q, 0.0001f ) );
      }

   }

   // just trying stuff out... TODO think of a good add test...
   void QuatStuffTest::quatAdd()
   {
      //quat add

      {
         gmtl::Quatf q, q1, q2;
         gmtl::set( q1, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), 1.0f, 0.0f, 0.0f ) );
         gmtl::set( q2, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 180.0f ), 1.0f, 0.0f, 0.0f ) );

         gmtl::add( q, q1, q2 );
         gmtl::normalize( q );
      }

      gmtl::Quatf q, q1;//, q2;
      gmtl::set( q1, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), 1.0f, 0.0f, 0.0f ) );

      q = q1 * q;
   }

   // using a vector to increment rotation, much like angular velocity
   // here angular velocity is defined as a gmtl::Vec3f "w", using right hand rule
   // things spin at |w| speed and on the w vector.
   //
   // just trying stuff out... TODO think of a good way to test this ability...
   void QuatStuffTest::pureQuatMultTest()
   {
      // pureQuatMultTest (angular velocity test)

      for (float x = 0; x < 100; ++x)
      {
         gmtl::Vec3f w( 0, x, 0 ); // angular velocity
         gmtl::Quatf q1, q2, wq( gmtl::makePure( w ) );
         gmtl::set( q1, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), 0.0f, 1.0f, 0.0f ) );

         q2 = wq * q1;
         //////q2.normalize();  // don't normalize, will not work!!!!!!!!!
      }

      gmtl::Vec3f ww( 0, 56, 0 );
      gmtl::Quatf q1, wq( gmtl::makePure( ww ) );
      gmtl::set( q1, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), 0.0f, 1.0f, 0.0f ) );

      const float& w1( wq[gmtl::Welt] );
      const float& w2( q1[gmtl::Welt] );
      gmtl::Vec3f v1( wq[gmtl::Xelt], wq[gmtl::Yelt], wq[gmtl::Zelt] );
      gmtl::Vec3f v2( q1[gmtl::Xelt], q1[gmtl::Yelt], q1[gmtl::Zelt] );

      float w = w1 * w2 - gmtl::dot( v1, v2 );
      gmtl::Vec3f v = (v2 * w1) + (v1 * w2) + gmtl::makeCross( v1, v2 );
      w += 1; // use w
      v[0] += 1; // use v
   }
}

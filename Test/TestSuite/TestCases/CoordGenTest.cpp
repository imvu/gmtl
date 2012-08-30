// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "CoordGenTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Generate.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/EulerAngle.h>
#include <gmtl/EulerAngleOps.h>
#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <gmtl/Coord.h>
#include <gmtl/CoordOps.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(CoordGenTest);
   CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(CoordGenMetricTest, Suites::metric());

   void CoordGenTest::testCoordSetMatrix()
   {
      // Test setting a matrix with a coord and then extracting it again.
      gmtl::Matrix44f mat1,mat2;

      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > q1,q2;

      q1.pos().set(2,3,4);
      q1.rot().set(0.2, 0.5, 0.6);

      gmtl::set(mat1, q1);    // set the mat
      gmtl::set(q2,mat1);     // extract it

      CPPUNIT_ASSERT(gmtl::isEqual(q1,q2,0.01f));

   }

   void CoordGenTest::testCoordMakeCoord()
   {
      gmtl::Matrix44f mat;
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > q1;

      // test translation with makeCoord
      /// @todo test rotation
      mat = gmtl::makeTrans<gmtl::Matrix44f>( gmtl::Vec3f( 1.0f, 2.0f, 3.0f ) );
      q1 = gmtl::make<gmtl::CoordVec3EulerAngleXYZf>( mat );
      CPPUNIT_ASSERT( q1.getPos()[0] == 1.0f );
      CPPUNIT_ASSERT( q1.getPos()[1] == 2.0f );
      CPPUNIT_ASSERT( q1.getPos()[2] == 3.0f );

      // test translation with setCoord
      /// @todo test rotation
      mat = gmtl::makeTrans<gmtl::Matrix44f>( gmtl::Vec3f( 4.0f, 5.0f, 6.0f ) );
      gmtl::set( q1, mat );
      CPPUNIT_ASSERT( q1.getPos()[0] == 4.0f );
      CPPUNIT_ASSERT( q1.getPos()[1] == 5.0f );
      CPPUNIT_ASSERT( q1.getPos()[2] == 6.0f );


      // make sure this compiles...
      ///@todo testme
      gmtl::set( q1, mat );
   }

   void CoordGenTest::testCoordGetMatrix()
   {
      gmtl::Matrix44f mat;
      gmtl::Vec3f trans( 1, 2, 3 );

      {
         gmtl::EulerAngle<float, gmtl::XYZ> rot( 4, 5, 6 );
         gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > q1( trans, rot );

         // test translation with make
         /// @todo test rotation
         mat = gmtl::make<gmtl::Matrix44f>( q1 );

         // test translation
         gmtl::Vec3f v2 = gmtl::makeTrans<gmtl::Vec3f>( mat );
         CPPUNIT_ASSERT( v2 == trans );

         // make sure this compiles...
         ///@todo testme
         gmtl::set( mat, q1 );
      }


      // do some of the euler tests to test out rotation...
      float eps = 0.001f;
      {
         gmtl::EulerAngle<float, gmtl::XYZ> rot( 4, 5, 6 );
         gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > q1( trans, rot );
         gmtl::Matrix33f mat, expected_result33;
         expected_result33.set( 0.683013f, -0.183013f, 0.707107f,
                                0.683013f, -0.183013f, -0.707107f,
                                0.258819f, 0.965926f, 0.0f );
         q1.rot()[0] = gmtl::Math::deg2Rad( 90.0f );
         q1.rot()[1] = gmtl::Math::deg2Rad( 45.0f );
         q1.rot()[2] = gmtl::Math::deg2Rad( 15.0f );

         mat = gmtl::make<gmtl::Matrix33f>( q1 );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }

      {
         gmtl::EulerAngle<float, gmtl::ZYX> rot( 4, 5, 6 );
         gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::ZYX> > q1( trans, rot );
         gmtl::Matrix34f mat, expected_result34;
         expected_result34.set( -0.645974f, -0.560068f, 0.518692f, gmtl::Math::deg2Rad( 1.0f ),
                                 0.287606f, -0.807979f, -0.514249f,gmtl::Math::deg2Rad( 2.0f ),
                                 0.707107f, -0.183013f, 0.683013f, gmtl::Math::deg2Rad( 3.0f ) );
         q1.pos()[0] = gmtl::Math::deg2Rad( 1.0f );
         q1.pos()[1] = gmtl::Math::deg2Rad( 2.0f );
         q1.pos()[2] = gmtl::Math::deg2Rad( 3.0f );
         q1.rot()[0] = gmtl::Math::deg2Rad( 156.0f );
         q1.rot()[1] = gmtl::Math::deg2Rad( -45.0f );
         q1.rot()[2] = gmtl::Math::deg2Rad( -15.0f );
         mat = gmtl::make<gmtl::Matrix34f>( q1 );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );
      }

      {
         gmtl::EulerAngle<float, gmtl::ZXY> rot( 4, 5, 6 );
         gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::ZXY> > q1( trans, rot );
         gmtl::Matrix44f mat, expected_result44;
         expected_result44.set( -0.918494f, 0.283617f, -0.275553f,gmtl::Math::deg2Rad( 1.0f ),
                                -0.395247f, -0.637014f, 0.66181f, gmtl::Math::deg2Rad( 2.0f ),
                                 0.0121696f, 0.71678f, 0.697193f, gmtl::Math::deg2Rad( 3.0f ),
                                 0,0,0,1 );

         q1.pos()[0] = gmtl::Math::deg2Rad( 1.0f );
         q1.pos()[1] = gmtl::Math::deg2Rad( 2.0f );
         q1.pos()[2] = gmtl::Math::deg2Rad( 3.0f );
         q1.rot()[0] = gmtl::Math::deg2Rad( -156.0f  );
         q1.rot()[1] = gmtl::Math::deg2Rad(  45.7892892f );
         q1.rot()[2] = gmtl::Math::deg2Rad( -361.0f );

         mat = gmtl::make<gmtl::Matrix44f>( q1 );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat, eps ) );
      }
   }


   void CoordGenMetricTest::testGenTimingMakeCoord()
   {
      gmtl::Matrix44f mat;
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > q1;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter = 0; iter < iters; ++iter)
      {
         q1 = gmtl::make<gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > >( mat );
         mat[3][1] += q1.getPos()[2];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "CoordGenTest/makeCoord<Matrix33f>(mat,XYZ)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%


      CPPUNIT_ASSERT( q1.pos()[1] != 10000.0f );
   }

   void CoordGenMetricTest::testGenTimingMakeMatrix()
   {
      gmtl::Matrix44f mat;
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > q1;

      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter = 0; iter < iters; ++iter)
      {
         mat = gmtl::make<gmtl::Matrix44f>( q1 );
         q1.pos()[2] += mat[3][3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "CoordGenTest/make<Matrix44f>(q1,XYZ)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( q1.pos()[1] != 10000.0f );
   }


   void CoordGenMetricTest::testGenTimingSetCoord()
   {
      gmtl::Matrix44f mat;
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > q1;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::set( q1, mat );
         mat[3][3] += q1.getPos()[2];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "CoordGenTest/set(coord,mat)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( q1.pos()[1] != 10000.0f );
   }
}

// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "PlaneTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/PlaneOps.h>

namespace gmtlTest
{
   void PlaneTest::setUp()
   {
      origin.set( 0,0,0 );
      x1_v.set( 1,0,0 );
      y1_v.set( 0,1,0 );
      z1_v.set( 0,0,1 );
      x1_pt.set( 1,0,0 );
      y1_pt.set( 0,1,0 );
      z1_pt.set( 0,0,1 );
      xy_plane = gmtl::Plane<float>(origin,x1_pt,y1_pt);
      zx_plane = gmtl::Plane<float>(origin,z1_pt,x1_pt);
      yz_plane = gmtl::Plane<float>(origin,y1_pt,z1_pt);
   }

   // ------------------------
   // CREATION TESTS
   // ------------------------
   void PlaneTest::testCreation()
   {
      gmtl::Plane<float> test_plane;
      gmtl::Vec<float, 3> zeroVec(0,0,0);
      CPPUNIT_ASSERT( test_plane.mNorm == zeroVec );
      CPPUNIT_ASSERT( test_plane.mOffset == 0.0f );

      // Test overhead of creation
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Plane<float> test_plane2;
         use_value += test_plane2.mOffset + 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/DefaultCreationOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }

   void PlaneTest::testThreePtCreation()
   {
      // Check normals of the standard planes
      CPPUNIT_ASSERT(xy_plane.mNorm == z1_v);    // Z-Plane
      CPPUNIT_ASSERT(zx_plane.mNorm == y1_v);    // Y-Plane
      CPPUNIT_ASSERT(yz_plane.mNorm == x1_v);    // Z-Plane
      CPPUNIT_ASSERT(xy_plane.mOffset == 0.0f);
      CPPUNIT_ASSERT(zx_plane.mOffset == 0.0f);
      CPPUNIT_ASSERT(yz_plane.mOffset == 0.0f);

      // Test offset of some simple planes
      gmtl::Plane<float> test_plane;
      test_plane = gmtl::Plane<float>(
           gmtl::Point<float, 3>(1.0,0.0,0.0),
           gmtl::Point<float, 3>(1.0,1.0,0.0),
           gmtl::Point<float, 3>(1.0,0.0,1.0)
      );
      CPPUNIT_ASSERT(test_plane.mNorm == x1_v);
      CPPUNIT_ASSERT(test_plane.mOffset == 1.0f);

      // Test overhead of creation
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Plane<float> test_plane( x1_pt, y1_pt, z1_pt );
         test_plane.mOffset = 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/ThreePtCreationOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void PlaneTest::testNormPtCreation()
   {
      gmtl::Plane<float> test_plane;
      test_plane = gmtl::Plane<float>(x1_v, origin);    // X-axis through origin
      CPPUNIT_ASSERT(test_plane.mNorm == x1_v);
      CPPUNIT_ASSERT(test_plane.mOffset == 0.0f);

      test_plane = gmtl::Plane<float>(x1_v, x1_pt);    // X-axis through 1,0,0
      CPPUNIT_ASSERT(test_plane.mNorm == x1_v);
      CPPUNIT_ASSERT(test_plane.mOffset == 1.0f);

      test_plane = gmtl::Plane<float>(z1_v, x1_pt);    // Z-axis through 1,0,0
      CPPUNIT_ASSERT(test_plane.mNorm == z1_v);
      CPPUNIT_ASSERT(test_plane.mOffset == 0.0f);

      test_plane = gmtl::Plane<float>(z1_v, gmtl::Point<float, 3>(0,0,-1));    // Z-axis through 0,0,-1
      CPPUNIT_ASSERT(test_plane.mNorm == z1_v);
      CPPUNIT_ASSERT(test_plane.mOffset == -1.0f);

      // Test overhead of creation
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Plane<float> test_plane2( x1_v, z1_pt );
         test_plane2.mOffset = 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/NormPtCreationOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void PlaneTest::testNormOffsetCreation()
   {
      gmtl::Plane<float> test_plane(x1_v, 0.0f);    // X-axis through origin
      CPPUNIT_ASSERT(test_plane.mNorm == x1_v);
      CPPUNIT_ASSERT(test_plane.mOffset == 0.0f);

      // Test overhead of creation
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Plane<float> test_plane2( x1_v, 25.0f );
         test_plane2.mOffset = 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/NormOffsetCreationOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void PlaneTest::testCopyConstruct()
   {
      gmtl::Plane<float> test_plane( xy_plane );
      CPPUNIT_ASSERT( test_plane.mNorm == xy_plane.mNorm );
      CPPUNIT_ASSERT( test_plane.mOffset == xy_plane.mOffset );

      // Test overhead of creation
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Plane<float> test_plane2( test_plane );
         test_plane2.mOffset = 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/CopyConstructOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   // --------------------------
   // Comparison tests
   // --------------------------
   void PlaneTest::testEqualityCompare()
   {
      gmtl::Plane<float> test_plane1( x1_v, 35.0f );
      gmtl::Plane<float> test_plane2( test_plane1 );

      CPPUNIT_ASSERT( test_plane1 == test_plane2 );
      CPPUNIT_ASSERT( !(test_plane1 != test_plane2) );

      // set equal, vary normal
      test_plane2 = test_plane1;
      test_plane2.mNorm[0] += 2.0f;
      CPPUNIT_ASSERT( test_plane1 != test_plane2 );
      CPPUNIT_ASSERT( !(test_plane1 == test_plane2) );

      // set equal, vary offset
      test_plane2 = test_plane1;
      test_plane2.mOffset += 2.0f;
      CPPUNIT_ASSERT( test_plane1 != test_plane2 );
      CPPUNIT_ASSERT( !(test_plane1 == test_plane2) );

      // test comparison performance
      const long iters(400000);
      unsigned true_count(0);

      // -- Equality
      test_plane2 = test_plane1;

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0; iter<iters; ++iter )
      {
         test_plane1.mOffset += 1.0f;
         test_plane2.mOffset += 2.0f;
         if ( test_plane1 == test_plane2 )
            true_count++;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/EqualityCompareOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // -- Inequality
      test_plane1.mNorm = x1_v;
      test_plane1.mOffset = 0.0f;
      test_plane2 = test_plane1;

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0; iter<iters; ++iter )
      {
         test_plane1.mOffset += 1.0f;
         test_plane2.mOffset += 2.0f;
         if ( test_plane1 == test_plane2 )
            true_count++;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/InequalityCompareOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void PlaneTest::testIsEqual()
   {
      gmtl::Plane<float> test_plane1( x1_v, 0.0f );
      gmtl::Plane<float> test_plane2( test_plane1 );
      float eps(0.0f);

      for( eps=0.0f; eps<10.0f; eps+=0.05f )
      {
         CPPUNIT_ASSERT( gmtl::isEqual(test_plane1, test_plane2, eps) );
      }

      for ( unsigned elt=0; elt<4; ++elt )
      {
         test_plane2 = test_plane1;
         if ( elt < 3 ) {
            test_plane2.mNorm[elt] += 20.0f;
         } else {
            test_plane2.mOffset += 20.0f;
         }
         CPPUNIT_ASSERT( !gmtl::isEqual(test_plane1, test_plane2, 10.0f) );
         CPPUNIT_ASSERT( !gmtl::isEqual(test_plane1, test_plane2, 19.9f) );
         CPPUNIT_ASSERT( gmtl::isEqual(test_plane1, test_plane2, 20.1f) );
         CPPUNIT_ASSERT( gmtl::isEqual(test_plane1, test_plane2, 22.0f) );
      }

      // Test comparison performance
      const long iters(400000);
      unsigned true_count(0);

      // -- Equality
      CPPUNIT_METRIC_START_TIMING();
      test_plane2 = test_plane1;

      for( long iter=0;iter<iters; ++iter)
      {
         test_plane1.mOffset += 1.0f;
         test_plane2.mOffset += 2.0f;
         if(gmtl::isEqual(test_plane1, test_plane2, 1.0f) )
            true_count++;
         if(gmtl::isEqual(test_plane1, test_plane2, 0.1f) )
            true_count++;
         if(gmtl::isEqual(test_plane1, test_plane2, 100000.0f) )
            true_count++;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/isEqualOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   // --------------------------
   // Operations tests
   // --------------------------
   void PlaneTest::testDistance()
   {
      gmtl::Plane<float> test_plane( x1_v, 25.0f );
      CPPUNIT_ASSERT( gmtl::distance(test_plane, origin) == -25.0f );
      CPPUNIT_ASSERT( gmtl::distance(test_plane, x1_pt) == -24.0f );

      CPPUNIT_ASSERT( gmtl::distance(xy_plane, z1_pt) == 1.0f );

      gmtl::Point<float, 3> pt(-12.0f, 5.0f, -17.0f);
      CPPUNIT_ASSERT( gmtl::distance(xy_plane, pt) == -17.0f );

      gmtl::Plane<float> slanted_plane( gmtl::Vec<float, 3>(1.0f,1.0f,1.0f), origin );
      CPPUNIT_ASSERT( gmtl::distance(slanted_plane, origin) == 0.0f );

      pt.set(1.0f, 1.0f, 1.0f );
      CPPUNIT_ASSERT( gmtl::distance(slanted_plane, pt) > 0.0f ); 

      // Test distance performance
      const long iters(400000);
      float use_value(0.0f);

      // -- Equality
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         test_plane.mOffset += 1.0f;
         use_value = use_value + gmtl::distance(test_plane, y1_pt);
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/DistanceOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void PlaneTest::testWhichSide()
   {
      gmtl::PlaneSide answer;

      answer = gmtl::whichSide(xy_plane, gmtl::Point<float, 3>(0.0,0.0,1.0));
      CPPUNIT_ASSERT( answer == gmtl::POS_SIDE );

      answer = gmtl::whichSide(xy_plane, gmtl::Point<float, 3>(0.0,0.0,-12.0f));
      CPPUNIT_ASSERT( answer == gmtl::NEG_SIDE );

      answer = gmtl::whichSide(zx_plane, gmtl::Point<float, 3>(0.0,1e-10f,0.0f));
      CPPUNIT_ASSERT( answer == gmtl::POS_SIDE );

      answer = gmtl::whichSide(zx_plane, gmtl::Point<float, 3>(0.0,-1e-10f,0.0f));
      CPPUNIT_ASSERT( answer == gmtl::NEG_SIDE );

      answer = gmtl::whichSide(xy_plane, gmtl::Point<float, 3>(0.0,0.0,0.0));
      CPPUNIT_ASSERT( answer == gmtl::ON_PLANE );

      // Test whichSide performance
      const long iters(400000);
      unsigned true_count(0);

      // -- Equality
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0; iter<iters; ++iter)
      {
         if ( gmtl::distance(xy_plane, y1_pt) == gmtl::POS_SIDE )
            ++true_count;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/WhichSideOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void PlaneTest::testFindReflect()
   {
      gmtl::Planef plane( gmtl::Vec3f( 0,1,0 ), 0 );
      gmtl::Point3f point( 3,5,6 );
      gmtl::Point3f result;

      gmtl::reflect( result, plane, point );
      CPPUNIT_ASSERT( result == gmtl::Vec3f( 3,-5,6 ) );
   }
   
   void PlaneTest::testFindNearestPt()
   {
      gmtl::Point<float, 3> answer, test_point, correct_result;
      float dist;

      // XY dist to point off origin
      test_point = gmtl::Point<float, 3>(0.0,0.0,1.0);
      CPPUNIT_ASSERT(gmtl::distance(xy_plane, test_point) == gmtl::findNearestPt(xy_plane, test_point, answer));
      CPPUNIT_ASSERT(answer == origin);

      // XY dist to point at 12,21
      test_point = gmtl::Point<float, 3>(12.0,-21.0,-13.0);
      correct_result = gmtl::Point<float, 3>(12.0,-21.0,0.0);
      CPPUNIT_ASSERT(gmtl::distance(xy_plane, test_point) == gmtl::findNearestPt(xy_plane, test_point, answer));
      CPPUNIT_ASSERT(answer == correct_result);

      // XY dist to point on plane at -17.05, 0.334
      test_point = gmtl::Point<float, 3>(-17.05f,0.334f,0.0f);
      CPPUNIT_ASSERT(gmtl::distance(xy_plane, test_point) == gmtl::findNearestPt(xy_plane, test_point, answer));
      CPPUNIT_ASSERT(answer == test_point);

      // Test findNearestPt performance
      const long iters(400000);
      float use_value(0.0f);

      // -- Equality
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0; iter<iters; ++iter)
      {
         dist = gmtl::findNearestPt(xy_plane, test_point, answer);
         use_value = use_value + dist + answer[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/FindNearestPtOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
}

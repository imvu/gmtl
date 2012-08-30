// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "LineSegTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/LineSegOps.h>
#include <gmtl/Intersection.h>
#include <gmtl/Output.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(LineSegTest);
   CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(LineSegMetricTest, Suites::metric());

   void LineSegTest::setUp()
   {
      origin.set( 0,0,0 );
      x1_v.set( 1,0,0 );
      y1_v.set( 0,1,0 );
      z1_v.set( 0,0,1 );
      x1_pt.set( 1,0,0 );
      y1_pt.set( 0,1,0 );
      z1_pt.set( 0,0,1 );

      x1_lineseg = gmtl::LineSeg<float>(origin, x1_v);
      y1_lineseg = gmtl::LineSeg<float>(origin, y1_v);
      z1_lineseg = gmtl::LineSeg<float>(origin, z1_v);
   }

   void LineSegMetricTest::setUp()
   {
      origin.set( 0,0,0 );
      x1_v.set( 1,0,0 );
      y1_v.set( 0,1,0 );
      z1_v.set( 0,0,1 );
      x1_pt.set( 1,0,0 );
      y1_pt.set( 0,1,0 );
      z1_pt.set( 0,0,1 );

      x1_lineseg = gmtl::LineSeg<float>(origin, x1_v);
      y1_lineseg = gmtl::LineSeg<float>(origin, y1_v);
      z1_lineseg = gmtl::LineSeg<float>(origin, z1_v);
   }

   // ------------------------
   // CREATION TESTS
   // ------------------------
   void LineSegTest::testCreation()
   {
      gmtl::LineSeg<float> test_lineseg;
      gmtl::Vec<float, 3> zeroVec(0,0,0);
      CPPUNIT_ASSERT( test_lineseg.mOrigin == origin );
      CPPUNIT_ASSERT( test_lineseg.mDir == zeroVec );
   }

   void LineSegMetricTest::testTimingCreation()
   {
      // Test overhead of creation
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0; iter<iters; ++iter)
      {
         gmtl::LineSeg<float> test_lineseg;
         use_value += test_lineseg.mDir[0] + 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/DefaultCreationOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize this test out
      CPPUNIT_ASSERT( use_value > 0 );
   }

   void LineSegTest::testPtVecCreation()
   {
      CPPUNIT_ASSERT(x1_lineseg.mOrigin == origin);
      CPPUNIT_ASSERT(y1_lineseg.mOrigin == origin);
      CPPUNIT_ASSERT(z1_lineseg.mOrigin == origin);
      CPPUNIT_ASSERT(x1_lineseg.mDir == x1_v);
      CPPUNIT_ASSERT(y1_lineseg.mDir == y1_v);
      CPPUNIT_ASSERT(z1_lineseg.mDir == z1_v);

      gmtl::LineSeg<float> test_lineseg;
      gmtl::Vec<float, 3> vec(1.0, 1.0, 1.0);
      test_lineseg = gmtl::LineSeg<float>(x1_pt, vec);
      CPPUNIT_ASSERT(test_lineseg.mOrigin == x1_pt);
      CPPUNIT_ASSERT(test_lineseg.mDir == vec);

   }

   void LineSegMetricTest::testTimingPtVecCreation()
   {
      // Test overhead of creation
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0; iter<iters; ++iter)
      {
         gmtl::LineSeg<float> test_lineseg2(y1_pt, z1_v);
         use_value += test_lineseg2.mDir[0] + 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/PtVecCreationOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize this test out
      CPPUNIT_ASSERT( use_value > 0 );
   }

   void LineSegTest::testPtPtCreation()
   {
      gmtl::LineSeg<float> test_lineseg;
      test_lineseg = gmtl::LineSeg<float>(origin, x1_pt);
      CPPUNIT_ASSERT(test_lineseg.mOrigin == origin);
      CPPUNIT_ASSERT(test_lineseg.mDir == gmtl::Vec3f(x1_pt - origin));

      test_lineseg = gmtl::LineSeg<float>(x1_pt, y1_pt);
      CPPUNIT_ASSERT(test_lineseg.mOrigin == x1_pt);
      CPPUNIT_ASSERT(test_lineseg.mDir == gmtl::Vec3f(y1_pt - x1_pt));
   }

   void LineSegMetricTest::testTimingPtPtCreation()
   {
      // Test overhead of creation
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0; iter<iters; ++iter)
      {
         gmtl::LineSeg<float> test_lineseg2( x1_pt, z1_pt );
         use_value += test_lineseg2.mDir[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/PtPtCreationOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize this test out
      CPPUNIT_ASSERT( use_value != 0 );
   }

   void LineSegTest::testCopyConstruct()
   {
      gmtl::LineSeg<float> test_lineseg( x1_lineseg );
      CPPUNIT_ASSERT( test_lineseg.mOrigin == x1_lineseg.mOrigin );
      CPPUNIT_ASSERT( test_lineseg.mDir == x1_lineseg.mDir );
   }

   void LineSegMetricTest::testTimingCopyConstruct()
   {
      // Test overhead of creation
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0; iter<iters; ++iter)
      {
         gmtl::LineSeg<float> test_lineseg2( x1_lineseg );
         use_value += test_lineseg2.mDir[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/CopyConstructOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize this test out
      CPPUNIT_ASSERT( use_value > 0 );
   }

   void LineSegTest::testGetOrigin()
   {
      CPPUNIT_ASSERT( x1_lineseg.getOrigin() == origin );
      CPPUNIT_ASSERT( y1_lineseg.getOrigin() == origin );
      CPPUNIT_ASSERT( z1_lineseg.getOrigin() == origin );

      gmtl::Point<float, 3> pt( 25.0f, 23.0f, 0.0f );
      gmtl::LineSeg<float> test_lineseg( pt, x1_pt );
      CPPUNIT_ASSERT( test_lineseg.getOrigin() == pt );
   }

   void LineSegMetricTest::testTimingGetOrigin()
   {
      // Test overhead
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Point<float, 3> pt = x1_lineseg.getOrigin();
         use_value += pt[0] + 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/GetOriginOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize this test out
      CPPUNIT_ASSERT( use_value > 0 );
   }

   void LineSegTest::testSetOrigin()
   {
      gmtl::LineSeg<float> test_lineseg;
      test_lineseg.setOrigin( x1_pt );
      CPPUNIT_ASSERT( test_lineseg.getOrigin() == x1_pt );
   }

   void LineSegMetricTest::testTimingSetOrigin()
   {
      gmtl::LineSeg<float> test_lineseg;

      // Test overhead
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         test_lineseg.setOrigin( x1_pt );
         use_value += test_lineseg.mOrigin[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/SetOriginOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize this test out
      CPPUNIT_ASSERT( use_value > 0 );
   }

   void LineSegTest::testGetDir()
   {
      CPPUNIT_ASSERT( x1_lineseg.getDir() == x1_v );
      CPPUNIT_ASSERT( y1_lineseg.getDir() == y1_v );
      CPPUNIT_ASSERT( z1_lineseg.getDir() == z1_v );

      gmtl::Vec<float, 3> dir( 25.0f, 23.0f, 0.0f );
      gmtl::LineSeg<float> test_lineseg( x1_pt, dir );
      CPPUNIT_ASSERT( test_lineseg.getDir() == dir );
   }

   void LineSegMetricTest::testTimingGetDir()
   {
      // Test overhead
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Vec<float, 3> vec = x1_lineseg.getDir();
         use_value += vec[0] + 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/GetDirOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize this test out
      CPPUNIT_ASSERT( use_value > 0 );
   }

   void LineSegTest::testSetDir()
   {
      gmtl::LineSeg<float> test_lineseg;
      test_lineseg.setDir( x1_v );
      CPPUNIT_ASSERT( test_lineseg.getDir() == x1_v );
   }

   void LineSegMetricTest::testTimingSetDir()
   {
      gmtl::LineSeg<float> test_lineseg;

      // Test overhead
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         test_lineseg.setDir( x1_v );
         use_value += test_lineseg.mDir[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/SetDirOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize this test out
      CPPUNIT_ASSERT( use_value > 0 );
   }

   void LineSegTest::testGetLength()
   {
      gmtl::LineSeg<float> test_lineseg1(x1_pt, x1_v);
      CPPUNIT_ASSERT(test_lineseg1.getLength() == gmtl::length(x1_v));
   }

   void LineSegMetricTest::testTimingGetLength()
   {
      gmtl::LineSeg<float> lineseg;
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter=0; iter<iters; ++iter)
      {
         use_value += lineseg.getLength();
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/TimingGetLength", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize this test out
      CPPUNIT_ASSERT(use_value == 0);
   }

   // --------------------------
   // Comparison tests
   // --------------------------
   void LineSegTest::testEqualityCompare()
   {
      gmtl::LineSeg<float> test_lineseg1( x1_pt, x1_v );
      gmtl::LineSeg<float> test_lineseg2( test_lineseg1 );

      CPPUNIT_ASSERT( test_lineseg1 == test_lineseg2 );
      CPPUNIT_ASSERT( !(test_lineseg1 != test_lineseg2) );

      // set equal, vary origin
      test_lineseg2 = test_lineseg1;
      test_lineseg2.mOrigin[0] += 2.0f;
      CPPUNIT_ASSERT( test_lineseg1 != test_lineseg2 );
      CPPUNIT_ASSERT( !(test_lineseg1 == test_lineseg2) );

      // set equal, vary dir
      test_lineseg2 = test_lineseg1;
      test_lineseg2.mDir[0] += 2.0f;
      CPPUNIT_ASSERT( test_lineseg1 != test_lineseg2 );
      CPPUNIT_ASSERT( !(test_lineseg1 == test_lineseg2) );
   }

   void LineSegMetricTest::testTimingEqualityCompare()
   {
      gmtl::LineSeg<float> test_lineseg1( x1_pt, x1_v );
      gmtl::LineSeg<float> test_lineseg2( test_lineseg1 );

      // test comparison performance
      const long iters(400000);
      unsigned true_count(0);

      // -- Equality
      test_lineseg2 = test_lineseg1;

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0; iter<iters; ++iter )
      {
         if ( test_lineseg1 == test_lineseg2 )
            ++true_count;
         test_lineseg1.mOrigin[0] += 1.0f;
         test_lineseg2.mOrigin[0] += 2.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/EqualityCompareOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // -- Inequality
      test_lineseg1.mOrigin = x1_pt;
      test_lineseg1.mDir = x1_v;
      test_lineseg2 = test_lineseg1;

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0; iter<iters; ++iter )
      {
         if ( test_lineseg1 == test_lineseg2 )
            ++true_count;
         test_lineseg1.mOrigin[0] += 1.0f;
         test_lineseg2.mOrigin[0] += 2.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/InequalityCompareOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // make sure the compiler doesn't optimize this test out
      CPPUNIT_ASSERT( true_count > 0 );
   }

   void LineSegTest::testIsEqual()
   {
      gmtl::LineSeg<float> test_lineseg1( x1_pt, x1_v );
      gmtl::LineSeg<float> test_lineseg2( test_lineseg1 );
      float eps(0.0f);

      for( eps=0.0f; eps<10.0f; eps+=0.05f )
      {
         CPPUNIT_ASSERT( gmtl::isEqual(test_lineseg1, test_lineseg2, eps) );
      }

      for ( unsigned elt=0; elt<6; ++elt )
      {
         test_lineseg2 = test_lineseg1;
         if ( elt < 3 ) {
            test_lineseg2.mOrigin[elt] += 20.0f;
         } else {
            test_lineseg2.mDir[elt-3] += 20.0f;
         }
         CPPUNIT_ASSERT( !gmtl::isEqual(test_lineseg1, test_lineseg2, 10.0f) );
         CPPUNIT_ASSERT( !gmtl::isEqual(test_lineseg1, test_lineseg2, 19.9f) );
         CPPUNIT_ASSERT( gmtl::isEqual(test_lineseg1, test_lineseg2, 20.1f) );
         CPPUNIT_ASSERT( gmtl::isEqual(test_lineseg1, test_lineseg2, 22.0f) );
      }
   }

   void LineSegMetricTest::testTimingIsEqual()
   {
      gmtl::LineSeg<float> test_lineseg1( x1_pt, x1_v );
      gmtl::LineSeg<float> test_lineseg2( test_lineseg1 );

      // Test comparison performance
      const long iters(400000);
      unsigned true_count(0);

      // -- Equality
      CPPUNIT_METRIC_START_TIMING();
      test_lineseg2 = test_lineseg1;

      for( long iter=0;iter<iters; ++iter)
      {
         test_lineseg1.mOrigin[0] += 1.0f;
         test_lineseg2.mOrigin[0] += 2.0f;
         if(gmtl::isEqual(test_lineseg1, test_lineseg2, 1.0f) )
            true_count++;
         if(gmtl::isEqual(test_lineseg1, test_lineseg2, 0.1f) )
            true_count++;
         if(gmtl::isEqual(test_lineseg1, test_lineseg2, 100000.0f) )
            true_count++;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/isEqualOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }


   void LineSegTest::intersectLineSegPlane()
   {
      float t;
      bool result;
      gmtl::LineSeg<float> lineseg( gmtl::Point<float, 3>( 0,1,0 ), gmtl::Point<float, 3>( 0,-1,0 ) );
      gmtl::Plane<float> plane( gmtl::Vec<float, 3>( 0,1,0 ), 0 );
      result = gmtl::intersect( plane, lineseg, t );
      CPPUNIT_ASSERT( t == 0.5 && result == true );
   }

   void LineSegTest::intersectLineSegTri()
   {
      // test t...
      {
         bool result;
         gmtl::LineSeg<float> l( gmtl::Point3f( 0,1,0 ), gmtl::Point3f( 0,-1,0 ) );
         gmtl::Tri<float> tri( gmtl::Point3f( -1,0,1 ), gmtl::Point3f( 1,0,1 ), gmtl::Point3f( 0,0,-1 ) );
         float u, v, t;
         result = gmtl::intersect( tri, l, u, v, t );
         CPPUNIT_ASSERT( t == 0.5 && result == true );
      }
      // test t with non-normalized line seg length
      {
         bool result;
         gmtl::LineSeg<float> l( gmtl::Point3f( 0,5,0 ), gmtl::Point3f( 0,-10,0 ) );   // Straight down length 15
         gmtl::Tri<float> tri( gmtl::Point3f( -1,0,1 ), gmtl::Point3f( 1,0,1 ), gmtl::Point3f( 0,0,-1 ) );
         float u, v, t;
         result = gmtl::intersect( tri, l, u, v, t );
         CPPUNIT_ASSERT(true == result);
         CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3333f, t, 0.001f);
      }
      // test u and v...
      {
         bool result;
         gmtl::LineSeg<float> l( gmtl::Point3f( 0.25,1,-0.25 ), gmtl::Point3f( 0.25,-1,-0.25 ) );
         gmtl::Tri<float> tri( gmtl::Point3f( 0,0,0 ), gmtl::Point3f( 1,0,0 ), gmtl::Point3f( 0,0,-1 ) );
         float u, v, t;
         result = gmtl::intersect( tri, l, u, v, t );
         CPPUNIT_ASSERT( t == 0.5 && result == true );
         CPPUNIT_ASSERT( u == 0.25 && v == 0.25 );
      }

      // test outside of tri
      {
         bool result;
         gmtl::Tri<float> tri( gmtl::Point3f( 0,0,0 ), gmtl::Point3f( 1,0,0 ), gmtl::Point3f( 0,0,-1 ) );
         float u, v, t;
         result = gmtl::intersect( tri, gmtl::LineSeg<float>( gmtl::Point3f( -0.25,1,0 ), gmtl::Point3f( -0.25,-1,0 ) ), u, v, t );
         CPPUNIT_ASSERT( result == false );
         result = gmtl::intersect( tri, gmtl::LineSeg<float>( gmtl::Point3f( 0,1,0.25 ), gmtl::Point3f( 0,-1,0.25 ) ), u, v, t );
         CPPUNIT_ASSERT( result == false );

         // right on edge of tri should give intersection
         result = gmtl::intersect( tri, gmtl::LineSeg<float>( gmtl::Point3f( 0,1,0 ), gmtl::Point3f( 0,-1,0 ) ), u, v, t );
         CPPUNIT_ASSERT( t == 0.5 && result == true );
         // right off edge of tri should not
         result = gmtl::intersect( tri, gmtl::LineSeg<float>( gmtl::Point3f( -0.000001,1,0 ), gmtl::Point3f( -0.000001,-1,0 ) ), u, v, t );
         CPPUNIT_ASSERT( result == false );
      }


      // test other planes...
      {
         // x/y plane
         bool result;
         float u, v, t;
         result = gmtl::intersect( gmtl::Tri<float>( gmtl::Point3f( -1,0,0 ),
                                                      gmtl::Point3f( 0,0,0 ),
                                                      gmtl::Point3f( 0,1,0 ) ),
                                   gmtl::LineSeg<float>( gmtl::Point3f( 0,0,1 ), gmtl::Point3f( 0,0,0 ) ),
                                   u, v, t );
         CPPUNIT_ASSERT( t == 1.0 && result == true );

         // try flipped about the x/y plane
         result = gmtl::intersect( gmtl::Tri<float>( gmtl::Point3f( -1,0,0 ),
                                                      gmtl::Point3f( -2,0,0 ),
                                                      gmtl::Point3f( -1,1,0 ) ),
                                   gmtl::LineSeg<float>( gmtl::Point3f( -1.5,0,-1 ), gmtl::Point3f( -1.5,0,1 ) ),
                                   u, v, t );
         CPPUNIT_ASSERT( t == 0.5 && result == true );

         // make sure backfacing tri's don't intersect...
         result = gmtl::intersect( gmtl::Tri<float>( gmtl::Point3f( -1,0,0 ),
                                                      gmtl::Point3f( -2,0,0 ),
                                                      gmtl::Point3f( -1,1,0 ) ),
                                   gmtl::LineSeg<float>( gmtl::Point3f( -1.5,0,1 ), gmtl::Point3f( -1.5,0,-1 ) ),
                                   u, v, t );
         CPPUNIT_ASSERT( result == false );
      }
   }

   void LineSegTest::intersectRayPlane()
   {
      bool result;
      gmtl::Ray<float> r( gmtl::Point3f( 0,1,0 ), gmtl::Vec3f( 0,-1,0 ) );
      gmtl::Planef plane( gmtl::Vec3f( 0,1,0 ), 0 );
      float t;
      result = gmtl::intersect( plane, r, t );
      CPPUNIT_ASSERT( t == 1.0 && result == true );
   }

   void LineSegTest::intersectRayTri()
   {
      // test t
      {
         bool result;
         gmtl::Ray<float> r( gmtl::Point3f( 0,1,0 ), gmtl::Vec3f( 0,-1,0 ) );
         gmtl::Tri<float> tri( gmtl::Point3f( -1,0,1 ), gmtl::Point3f( 1,0,1 ), gmtl::Point3f( 0,0,-1 ) );
         float u, v, t;
         result = gmtl::intersect( tri, r, u, v, t );
         CPPUNIT_ASSERT( t == 1.0 && result == true );
      }

      // test u and v...
      {
         bool result;
         gmtl::Ray<float> l( gmtl::Point3f( 0.25,1,-0.25 ), gmtl::Vec3f( 0,-1,0 ) );
         gmtl::Tri<float> tri( gmtl::Point3f( 0,0,0 ), gmtl::Point3f( 1,0,0 ), gmtl::Point3f( 0,0,-1 ) );
         float u, v, t;
         result = gmtl::intersect( tri, l, u, v, t );
         CPPUNIT_ASSERT( t == 1.0 && result == true );
         CPPUNIT_ASSERT( u == 0.25 && v == 0.25 );
      }

      // test outside of tri
      {
         bool result;
         gmtl::Tri<float> tri( gmtl::Point3f( 0,0,0 ), gmtl::Point3f( 1,0,0 ), gmtl::Point3f( 0,0,-1 ) );
         float u, v, t;
         result = gmtl::intersect( tri, gmtl::Ray<float>( gmtl::Point3f( -0.25,1,0 ), gmtl::Vec3f( 0,-1,0 ) ), u, v, t );
         CPPUNIT_ASSERT( result == false );
         result = gmtl::intersect( tri, gmtl::Ray<float>( gmtl::Point3f( 0,1,0.25 ), gmtl::Vec3f( 0,-1,0 ) ), u, v, t );
         CPPUNIT_ASSERT( result == false );

         // right on edge of tri should give intersection
         result = gmtl::intersect( tri, gmtl::Ray<float>( gmtl::Point3f( 0,1,0 ), gmtl::Vec3f( 0,-1,0 ) ), u, v, t );
         CPPUNIT_ASSERT( t == 1.0 && result == true );
         // right off edge of tri should not
         result = gmtl::intersect( tri, gmtl::Ray<float>( gmtl::Point3f( -0.000001,1,0 ), gmtl::Vec3f( 0,-1,0 ) ), u, v, t );
         CPPUNIT_ASSERT( result == false );
      }


      // test other planes...
      {
         // x/y plane
         bool result;
         float u, v, t;
         result = gmtl::intersect( gmtl::Tri<float>( gmtl::Point3f( -1,0,0 ),
                                                      gmtl::Point3f( 0,0,0 ),
                                                      gmtl::Point3f( 0,1,0 ) ),
                                   gmtl::Ray<float>( gmtl::Point3f( 0,0,1 ), gmtl::Vec3f( 0,0,-1 ) ),
                                   u, v, t );
         CPPUNIT_ASSERT( t == 1.0 && result == true );

         // try flipped about the x/y plane
         result = gmtl::intersect( gmtl::Tri<float>( gmtl::Point3f( -1,0,0 ),
                                                      gmtl::Point3f( -2,0,0 ),
                                                      gmtl::Point3f( -1,1,0 ) ),
                                   gmtl::Ray<float>( gmtl::Point3f( -1.5,0,-1 ), gmtl::Vec3f( 0,0,1 ) ),
                                   u, v, t );
         CPPUNIT_ASSERT( t == 1.0 && result == true );

         // make sure backfacing tri's don't intersect...
         result = gmtl::intersect( gmtl::Tri<float>( gmtl::Point3f( -1,0,0 ),
                                                      gmtl::Point3f( -2,0,0 ),
                                                      gmtl::Point3f( -1,1,0 ) ),
                                   gmtl::Ray<float>( gmtl::Point3f( -1.5,0,1 ), gmtl::Vec3f( 0,0,-1 ) ),
                                   u, v, t );
         CPPUNIT_ASSERT( result == false );
      }
   }
/*
   void LineSegTest::testDistance()
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

   void LineSegTest::testWhichSide()
   {
      gmtl::Plane<float>::Side answer;

      answer = gmtl::whichSide(xy_plane, gmtl::Point<float, 3>(0.0,0.0,1.0));
      CPPUNIT_ASSERT( answer == gmtl::Plane<float>::POS_SIDE );

      answer = gmtl::whichSide(xy_plane, gmtl::Point<float, 3>(0.0,0.0,-12.0f));
      CPPUNIT_ASSERT( answer == gmtl::Plane<float>::NEG_SIDE );

      answer = gmtl::whichSide(zx_plane, gmtl::Point<float, 3>(0.0,1e-10f,0.0f));
      CPPUNIT_ASSERT( answer == gmtl::Plane<float>::POS_SIDE );

      answer = gmtl::whichSide(zx_plane, gmtl::Point<float, 3>(0.0,-1e-10f,0.0f));
      CPPUNIT_ASSERT( answer == gmtl::Plane<float>::NEG_SIDE );

      answer = gmtl::whichSide(xy_plane, gmtl::Point<float, 3>(0.0,0.0,0.0));
      CPPUNIT_ASSERT( answer == gmtl::Plane<float>::ON_PLANE );

      // Test whichSide performance
      const long iters(400000);
      bool true_count(0);

      // -- Equality
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0; iter<iters; ++iter)
      {
         if ( gmtl::distance(xy_plane, y1_pt) == gmtl::Plane<float>::POS_SIDE )
            ++true_count;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("PlaneTest/WhichSideOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
*/
   void LineSegTest::testFindNearestPt()
   {
      gmtl::Point<float, 3> answer, test_point, correct_result;
      gmtl::LineSeg<float> unit_line_seg(
         gmtl::Point<float, 3>(0.0f, 0.0f, 0.0f),
         gmtl::Vec<float, 3>(1.0f, 0.0f, 0.0f)
      );
      gmtl::LineSeg<float> test_line_seg(
         gmtl::Point<float, 3>(0.0f, 0.0f, 0.0f),
         gmtl::Vec<float, 3>(5.0f, 4.0f, 3.0f)
      );

      test_point = gmtl::Point<float, 3>(0.0f, 0.0f, 1.0f);
      correct_result = gmtl::Point<float, 3>(0.0f, 0.0f, 0.0f);
      answer = gmtl::findNearestPt(unit_line_seg, test_point);
      CPPUNIT_ASSERT(answer == correct_result);

      test_point = gmtl::Point<float, 3>(0.4f, 0.0f, 0.0f);
      correct_result = gmtl::Point<float, 3>(0.4f, 0.0f, 0.0f);
      answer = gmtl::findNearestPt(unit_line_seg, test_point);
      CPPUNIT_ASSERT(answer == correct_result);

      test_point = gmtl::Point<float, 3>(0.0f, 0.0f, 1.0f);
      correct_result = gmtl::Point<float, 3>(0.3f, 0.24f, 0.18f);
      answer = gmtl::findNearestPt(test_line_seg, test_point);
      CPPUNIT_ASSERT(answer == correct_result);

      // Test findNearestPt performance
      const long iters(400000);
      float use_value(0.0f);

      // -- Equality
      CPPUNIT_METRIC_START_TIMING();

      for ( long iter = 0; iter < iters; ++iter )
      {
         answer = gmtl::findNearestPt(test_line_seg, test_point);
         use_value = use_value + answer[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT_METRIC_TIMING_LE("LineSegTest/FindNearestPtOverhead",
                                      iters, 0.075f, 0.1f);
   }
}

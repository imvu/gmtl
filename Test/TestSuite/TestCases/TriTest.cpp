// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "TriTest.h"
#include "../Suites.h"
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Tri.h>
#include <gmtl/Vec.h>
#include <gmtl/TriOps.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(TriTest);
   CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TriMetricTest, Suites::metric());

   void TriTest::testCreation()
   {
      gmtl::Tri<float> test_tri;
      gmtl::Point<float, 3> zero(0,0,0);
      CPPUNIT_ASSERT(test_tri[0] == zero);
      CPPUNIT_ASSERT(test_tri[1] == zero);
      CPPUNIT_ASSERT(test_tri[2] == zero);
   }

   void TriMetricTest::testTimingCreation()
   {
      // test overhead of creation
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      for ( long iter=0; iter<iters; ++iter )
      {
         gmtl::Tri<float> test_tri2;
         test_tri2[0][0] = 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("TriTest/TriCreationOverhead", iters, 0.075f, 0.1f); // warn at 7.5%, error at 10%
   }

   void TriTest::testCopyConstruct()
   {
      gmtl::Tri<float> test_tri;
      test_tri[0][0] = 2.0f;
      test_tri[1][1] = 4.0f;
      test_tri[2][2] = 1.0f;

      gmtl::Tri<float> test_tri_copy(test_tri);

      CPPUNIT_ASSERT(test_tri_copy[0][0] == 2.0f);
      CPPUNIT_ASSERT(test_tri_copy[1][1] == 4.0f);
      CPPUNIT_ASSERT(test_tri_copy[2][2] == 1.0f);
   }

   void TriMetricTest::testTimingCopyConstruct()
   {
      // test copy construction overhead
      const long iters(400000);
      gmtl::Tri<float> test_tri2;
      test_tri2[0][0] = 2.0f;
      float use_value(0.0f);     // A temp just here to use the objs so the compiler (hopefully does not opt them out

      CPPUNIT_METRIC_START_TIMING();
      for ( long iter=0; iter<iters; ++iter )
      {
         gmtl::Tri<float> test_tri2_copy( test_tri2 );
         use_value += test_tri2_copy[0][0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("TriTest/CopyConstructOverhead", iters, 0.075f, 0.1f); // warn at 7.5%, error at 10%
   }

   void TriTest::testConstructors()
   {
      gmtl::Tri<float> test_tri(
            gmtl::Point<float, 3>(0,0,0),
            gmtl::Point<float, 3>(1,0,0),
            gmtl::Point<float, 3>(0,1,0)
      );
      gmtl::Point<float, 3> zero(0,0,0);
      gmtl::Point<float, 3> unitX(1,0,0);
      gmtl::Point<float, 3> unitY(0,1,0);
      CPPUNIT_ASSERT(test_tri[0] == zero);
      CPPUNIT_ASSERT(test_tri[1] == unitX);
      CPPUNIT_ASSERT(test_tri[2] == unitY);
   }

   void TriMetricTest::testTimingConstructors()
   {
      // Test constructor overhead
      const long iters(400000);
      float use_value(0.0f);     // A temp just here to use the objs so the compiler (hopefully does not opt them out

      CPPUNIT_METRIC_START_TIMING();
      for ( long iter=0; iter<iters; ++iter )
      {
         gmtl::Tri<float> test_tri2(
               gmtl::Point<float, 3>( 2.0f, 0.0f, -5.0f ),
               gmtl::Point<float, 3>( 1.0f, 2.0f, -5.0f ),
               gmtl::Point<float, 3>( 1.0f, -2.0f, -5.0f )
         );
         use_value = use_value + test_tri2[0][0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("TriTest/ConstructorsOverhead", iters, 0.075f, 0.1f); // warn at 7.5%, error at 10%
   }

   //---------------------------------------------------------------------------
   // Begin testing accessors
   //---------------------------------------------------------------------------
   void TriTest::testVertexAccessor()
   {
      gmtl::Point<float, 3> pt0( 2.0f, 0.0f, -5.0f );
      gmtl::Point<float, 3> pt1( 1.0f, 2.0f, -5.0f );
      gmtl::Point<float, 3> pt2( 1.0f, -2.0f, -5.0f );
      gmtl::Tri<float> test_tri( pt0, pt1, pt2 );
      CPPUNIT_ASSERT( test_tri[0] == pt0 );
      CPPUNIT_ASSERT( test_tri[1] == pt1 );
      CPPUNIT_ASSERT( test_tri[2] == pt2 );
   }

   void TriMetricTest::testTimingVertexAccessor()
   {
      gmtl::Point<float, 3> pt0( 2.0f, 0.0f, -5.0f );
      gmtl::Point<float, 3> pt1( 1.0f, 2.0f, -5.0f );
      gmtl::Point<float, 3> pt2( 1.0f, -2.0f, -5.0f );
      gmtl::Tri<float> test_tri( pt0, pt1, pt2 );

      // test operator[] overhead
      const long iters(400000);
      float use_value(0.0f);     // A temp just here to use the objs so the compiler (hopefully does not opt them out

      CPPUNIT_METRIC_START_TIMING();
      for ( long iter=0; iter<iters; ++iter )
      {
         pt0 = test_tri[0];
         use_value = use_value + pt0[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("TriTest/operator[]Overhead", iters, 0.075f, 0.1f); // warn at 7.5%, error at 10%
   }

   void TriTest::testEdges()
   {
      gmtl::Point<float, 3> p0( 0.0f, 0.0f, 0.0f );
      gmtl::Point<float, 3> p1( 1.0f, 0.0f, 0.0f );
      gmtl::Point<float, 3> p2( 0.0f, 1.0f, 0.0f );
      gmtl::Tri<float> test_tri( p0, p1, p2 );

      gmtl::Vec<float, 3> e0 = p1 - p0;
      gmtl::Vec<float, 3> e1 = p2 - p1;
      gmtl::Vec<float, 3> e2 = p0 - p2;
      CPPUNIT_ASSERT( test_tri.edge(0) == e0 );
      CPPUNIT_ASSERT( test_tri.edge(1) == e1 );
      CPPUNIT_ASSERT( test_tri.edge(2) == e2 );
   }

   void TriMetricTest::testTimingEdges()
   {
      gmtl::Point<float, 3> p0( 0.0f, 0.0f, 0.0f );
      gmtl::Point<float, 3> p1( 1.0f, 0.0f, 0.0f );
      gmtl::Point<float, 3> p2( 0.0f, 1.0f, 0.0f );
      gmtl::Tri<float> test_tri( p0, p1, p2 );
      gmtl::Vec<float, 3> e0 = p1 - p0;

      // test edge(..) overhead
      const long iters(400000);
      float use_value(0.0f);     // A temp just here to use the objs so the compiler (hopefully does not opt them out

      CPPUNIT_METRIC_START_TIMING();
      for ( long iter=0; iter<iters; ++iter )
      {
         e0 = test_tri.edge( iter % 3 );
         use_value = use_value + e0[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("TriTest/edgeOverhead", iters, 0.075f, 0.1f); // warn at 7.5%, error at 10%
   }

   //---------------------------------------------------------------------------
   // Begin testing comparators
   //---------------------------------------------------------------------------
   void TriTest::testEqualOps()
   {
      gmtl::Tri<float> test_tri1(
            gmtl::Point<float, 3>(0,0,0),
            gmtl::Point<float, 3>(1,0,0),
            gmtl::Point<float, 3>(0,1,0)
      );
      gmtl::Tri<float> test_tri2( test_tri1 );
      gmtl::Tri<float> test_tri3( test_tri1 );
      test_tri3[0][1] = 2.0f;

      CPPUNIT_ASSERT( test_tri1 == test_tri1 );
      CPPUNIT_ASSERT( !(test_tri1 != test_tri1) );

      CPPUNIT_ASSERT( test_tri1 == test_tri2 );
      CPPUNIT_ASSERT( !(test_tri1 != test_tri2) );
      CPPUNIT_ASSERT( test_tri2 == test_tri1 );
      CPPUNIT_ASSERT( !(test_tri2 != test_tri1) );

      CPPUNIT_ASSERT( !(test_tri1 == test_tri3) );
      CPPUNIT_ASSERT( test_tri1 != test_tri3 );
      CPPUNIT_ASSERT( !(test_tri3 == test_tri1) );
      CPPUNIT_ASSERT( test_tri3 != test_tri1 );
   }

   void TriMetricTest::testTimingEqualOps()
   {
      gmtl::Tri<float> test_tri1(
            gmtl::Point<float, 3>(0,0,0),
            gmtl::Point<float, 3>(1,0,0),
            gmtl::Point<float, 3>(0,1,0)
      );
      gmtl::Tri<float> test_tri2( test_tri1 );
      gmtl::Tri<float> test_tri3( test_tri1 );

      // test equal ops overhead
      const long iters(400000);
      long true_values(0);

      CPPUNIT_METRIC_START_TIMING();
      for ( long iter=0; iter<iters; ++iter )
      {
         if ( test_tri1 == test_tri2 )
            ++true_values;
         if ( test_tri1 != test_tri2 )
            ++true_values;
         if ( test_tri1 == test_tri3 )
            ++true_values;
         if ( test_tri1 != test_tri3 )
            ++true_values;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("TriTest/EqualOpsOverhead", iters, 0.075f, 0.1f); // warn at 7.5%, error at 10%
   }

   void TriTest::testIsEqual()
   {
      gmtl::Tri<float> test_tri1(
            gmtl::Point<float, 3>(0,0,0),
            gmtl::Point<float, 3>(2,0,0),
            gmtl::Point<float, 3>(1,2,0)
      );
      gmtl::Tri<float> test_tri2(test_tri1);
      float eps(0.0f);
      for ( eps=0.0f; eps<10.0f; eps+=0.05f )
      {
         CPPUNIT_ASSERT( gmtl::isEqual(test_tri1, test_tri2, eps) );
      }

      for( unsigned p=0; p<3; ++p )
      {
         for( unsigned elt=0; elt<3; ++elt )
         {
            test_tri2 = test_tri1;
            test_tri2[p][elt] += 20.0f;
            CPPUNIT_ASSERT( !gmtl::isEqual(test_tri1, test_tri2, 10.0f) );
            CPPUNIT_ASSERT( !gmtl::isEqual(test_tri1, test_tri2, 19.9f) );
            CPPUNIT_ASSERT( gmtl::isEqual(test_tri1, test_tri2, 20.1f) );
            CPPUNIT_ASSERT( gmtl::isEqual(test_tri1, test_tri2, 22.0f) );
         }
      }
   }

   void TriMetricTest::testTimingIsEqual()
   {
      gmtl::Tri<float> test_tri1(
            gmtl::Point<float, 3>(0,0,0),
            gmtl::Point<float, 3>(2,0,0),
            gmtl::Point<float, 3>(1,2,0)
      );
      gmtl::Tri<float> test_tri2(test_tri1);

      // test isEqual overhead
      const long iters(400000);
      long true_count(0);

      CPPUNIT_METRIC_START_TIMING();
      for ( long iter=0; iter<iters; ++iter )
      {
         test_tri1[0][1] += 0.1f;
         test_tri2[0][1] += 0.2f;
         if(gmtl::isEqual(test_tri1, test_tri2, 1.0f) )
            true_count++;
         if(gmtl::isEqual(test_tri1, test_tri2, 0.1f) )
            true_count++;
         if(gmtl::isEqual(test_tri1, test_tri2, 100000.0f) )
            true_count++;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("TriTest/IsEqualOverhead", iters, 0.075f, 0.1f); // warn at 7.5%, error at 10%
   }

   void TriTest::testCenter()
   {
      gmtl::Tri<float> test_tri(
            gmtl::Point<float, 3>(0,0,0),
            gmtl::Point<float, 3>(4,0,0),
            gmtl::Point<float, 3>(2,4,0)
      );
      gmtl::Vec<float, 3> center = gmtl::center(test_tri);
      gmtl::Vec<float, 3> correctCenter(2,(4.0f/3.0f),0);
      CPPUNIT_ASSERT( center == correctCenter );
   }

   void TriMetricTest::testTimingCenter()
   {
      gmtl::Tri<float> test_tri(
            gmtl::Point<float, 3>(0,0,0),
            gmtl::Point<float, 3>(4,0,0),
            gmtl::Point<float, 3>(2,4,0)
      );
      gmtl::Vec<float, 3> center = gmtl::center(test_tri);

      // test center overhead
      const long iters(400000);
      float use_value(0.0f);

      CPPUNIT_METRIC_START_TIMING();
      for ( long iter=0; iter<iters; ++iter )
      {
         test_tri[1][1] += 2.0f;
         center = gmtl::center(test_tri);
         use_value = use_value + center[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("TriTest/CenterOverhead", iters, 0.075f, 0.1f); // warn at 7.5%, error at 10%
   }

   void TriTest::testNormal()
   {
      gmtl::Tri<float> test_tri(
            gmtl::Point<float, 3>(0,0,0),
            gmtl::Point<float, 3>(4,0,0),
            gmtl::Point<float, 3>(2,4,0)
      );
      gmtl::Vec<float, 3> normal = gmtl::normal(test_tri);
      gmtl::Vec<float, 3> correctNormal(0,0,1);
      CPPUNIT_ASSERT( normal == correctNormal );
   }

   void TriMetricTest::testTimingNormal()
   {
      gmtl::Tri<float> test_tri(
            gmtl::Point<float, 3>(0,0,0),
            gmtl::Point<float, 3>(4,0,0),
            gmtl::Point<float, 3>(2,4,0)
      );
      gmtl::Vec<float, 3> normal = gmtl::normal(test_tri);

      // test normal overhead
      const long iters(400000);
      float use_value(0.0f);

      CPPUNIT_METRIC_START_TIMING();
      for ( long iter=0; iter<iters; ++iter )
      {
         test_tri[1][1] += 2.0f;
         normal = gmtl::normal(test_tri);
         use_value = use_value + normal[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("TriTest/NormalOverhead", iters, 0.075f, 0.1f); // warn at 7.5%, error at 10%
   }
}

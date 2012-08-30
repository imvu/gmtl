// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "AABoxTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/AABox.h>
#include <gmtl/VecOps.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(AABoxTest);
   CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(AABoxMetricTest, Suites::metric());

   void AABoxTest::testCreation()
   {
      gmtl::AABox<float> box;
      gmtl::Point<float, 3> zeroPoint;

      CPPUNIT_ASSERT( box.mMin == zeroPoint );
      CPPUNIT_ASSERT( box.mMax == zeroPoint );
      CPPUNIT_ASSERT( box.mEmpty == true );
   }

   void AABoxMetricTest::testTimingCreation()
   {
      // Test overhead of creation
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::AABox<float> box;
         use_value = use_value + box.mMin[0] + 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("AABoxTest/AABoxCreationOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }

   void AABoxTest::testCopyConstruct()
   {
      gmtl::AABox<float> box;

      box.mMin.set(-2.0f, -4.0f, -8.0f);
      box.mMax.set( 2.0f,  4.0f,  8.0f);
      box.mEmpty = false;

      gmtl::AABox<float> box_copy(box);

      CPPUNIT_ASSERT( box_copy.mMin == gmtl::Point3f(-2.0f, -4.0f, -8.0f) );
      CPPUNIT_ASSERT( box_copy.mMax == gmtl::Point3f( 2.0f,  4.0f,  8.0f) );
      CPPUNIT_ASSERT( box_copy.mEmpty == false );
   }

   void AABoxMetricTest::testTimingCopyConstruct()
   {
      // Test copy construction overhead
      const long iters(400000);
      gmtl::AABox<float> box2;
      box2.mMin[0] = 2.0f;
      float use_value(0);

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::AABox<float> box2_copy(box2);
         use_value += box2_copy.mMin[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("AABoxTest/CopyConstructOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }

   void AABoxTest::testConstructors()
   {
      gmtl::AABox<float> box( gmtl::Point3f(1.0f, 2.0f, 3.0f), gmtl::Point3f(4.0f, 5.0f, 6.0f) );
      CPPUNIT_ASSERT( box.mMin == gmtl::Point3f(1.0f, 2.0f, 3.0f) );
      CPPUNIT_ASSERT( box.mMax == gmtl::Point3f(4.0f, 5.0f, 6.0f) );
      CPPUNIT_ASSERT( box.mEmpty == false );
   }

   void AABoxMetricTest::testTimingConstructors()
   {
      // Test constructor
      const long iters(400000);
      float use_value(0.0f);

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::AABox<float> box2( gmtl::Point3f(1.0f, 2.0f, 3.0f), gmtl::Point3f(4.0f, 5.0f, 6.0f) );

         use_value = use_value + box2.mMin[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("AABoxTest/ConstructorsOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }

   // -- Test accessors --//
   void AABoxTest::testGetMin()
   {
      gmtl::Point3f amin( -1.0f, -2.0f, -3.0f );
      gmtl::AABox<float> box( amin, gmtl::Point3f() );
      CPPUNIT_ASSERT( box.getMin() == amin );
   }

   void AABoxMetricTest::testTimingGetMin()
   {
      gmtl::Point3f amin( -1.0f, -2.0f, -3.0f );
      gmtl::AABox<float> box( amin, gmtl::Point3f() );

      // Test getMin overhead
      const long iters(400000);
      float use_value(0.0f);

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         amin = box.getMin();
         use_value = use_value - amin[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("AABoxTest/GetMinOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }

   void AABoxTest::testGetMax()
   {
      gmtl::Point3f amax( 1.0f, 2.0f, 3.0f );
      gmtl::AABox<float> box( gmtl::Point3f(0,0,0), amax );
      CPPUNIT_ASSERT( box.getMax() == amax );
   }

   void AABoxMetricTest::testTimingGetMax()
   {
      gmtl::Point3f amax( 1.0f, 2.0f, 3.0f );
      gmtl::AABox<float> box( gmtl::Point3f(0,0,0), amax );

      // Test getMax overhead
      const long iters(400000);
      float use_value(0.0f);

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         amax = box.getMax();
         use_value = use_value + amax[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("AABoxTest/GetMaxOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }

   void AABoxTest::testIsEmpty()
   {
      gmtl::AABox<float> box;
      gmtl::AABox<float> box2( gmtl::Point3f(-1.0f, -2.0f, -3.0f), gmtl::Point3f(1.0f, 2.0f, 3.0f) );
      CPPUNIT_ASSERT( box.isEmpty() == true );
      CPPUNIT_ASSERT( box2.isEmpty() == false );
   }

   void AABoxMetricTest::testTimingIsEmpty()
   {
      gmtl::AABox<float> box;

      // Test getMax overhead
      const long iters(400000);
      long use_value(0);

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         bool empty = box.isEmpty();
         if (empty)
         {
            ++use_value;
         }
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("AABoxTest/IsEmptyOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }

   // -- Test setters --//
   void AABoxTest::testSetMin()
   {
      gmtl::AABox<float> box;
      gmtl::Point3f amin( -2.0f, -4.0f, -1.0f );
      box.setMin( amin );
      CPPUNIT_ASSERT( box.getMin() == amin );
   }

   void AABoxMetricTest::testTimingSetMin()
   {
      gmtl::AABox<float> box;
      gmtl::Point3f amin;

      // Test setMin overhead
      const long iters(400000);

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         amin.set( (float)iter, (float)iter, (float)iter );
         box.setMin( amin );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("AABoxTest/SetMinOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void AABoxTest::testSetMax()
   {
      gmtl::AABox<float> box;
      gmtl::Point3f amax( 2.0f, 4.0f, 1.0f );
      box.setMax( amax );
      CPPUNIT_ASSERT( box.getMax() == amax );
   }

   void AABoxMetricTest::testTimingSetMax()
   {
      gmtl::AABox<float> box;
      gmtl::Point3f amax;

      // Test setMax overhead
      const long iters(400000);

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         amax.set( (float)iter, (float)iter, (float)iter );
         box.setMax( amax );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("AABoxTest/SetMaxOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void AABoxTest::testSetEmpty()
   {
      gmtl::AABox<float> box;
      box.setEmpty( false );
      CPPUNIT_ASSERT( box.isEmpty() == false );
   }

   void AABoxMetricTest::testTimingSetEmpty()
   {
      gmtl::AABox<float> box;

      // Test setMax overhead
      const long iters(400000);
      long use_value(0);

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         box.setEmpty(true);
         if (box.mEmpty)
         {
            ++use_value;
         }
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("AABoxTest/SetEmptyOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }
}

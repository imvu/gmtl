// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "AABoxOpsTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/AABoxOps.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(AABoxOpsTest);
   CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(AABoxOpsMetricTest, Suites::metric());

   void AABoxOpsTest::testEqualityCompare()
   {
      {
         // Empty box against self
         gmtl::AABoxf empty;
         CPPUNIT_ASSERT(empty == empty);
         CPPUNIT_ASSERT(! (empty != empty));
      }
      {
         // Empty boxes with different min
         gmtl::AABoxf box1, box2;
         box1.setMin(gmtl::Point3f(-1,0,0));
         CPPUNIT_ASSERT(box1 != box2);
         CPPUNIT_ASSERT(! (box1 == box2));

         // Empty boxes with different max
         box1 = box2;
         box1.setMax(gmtl::Point3f(1,0,0));
         CPPUNIT_ASSERT(box1 != box2);
         CPPUNIT_ASSERT(! (box1 == box2));
      }
      {
         // Non-empty box against self
         gmtl::AABoxf box(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(1,1,1));
         CPPUNIT_ASSERT(box == box);
         CPPUNIT_ASSERT(! (box != box));
      }
      {
         // Non-empty boxes with different min
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(1,1,1));
         gmtl::AABoxf box2(gmtl::Point3f(0,0,0), gmtl::Point3f(1,1,1));
         CPPUNIT_ASSERT(box1 != box2);
         CPPUNIT_ASSERT(! (box1 == box2));
      }
      {
         // Non-empty boxes with different max
         gmtl::AABoxf box1(gmtl::Point3f(0,0,0), gmtl::Point3f(1,1,1));
         gmtl::AABoxf box2(gmtl::Point3f(0,0,0), gmtl::Point3f(2,2,2));
         CPPUNIT_ASSERT(box1 != box2);
         CPPUNIT_ASSERT(! (box1 == box2));
      }
   }

   void AABoxOpsMetricTest::testTimingEqualityCompare()
   {
      {
         // Equality
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(1,1,1));
         gmtl::AABoxf box2(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(2,2,2));
         const long iters(400000);
         unsigned true_count(0);
         CPPUNIT_METRIC_START_TIMING();

         for(long iter=0;iter<iters; ++iter)
         {
            if (box1 == box2)
            {
               ++true_count;
            }
         }

         CPPUNIT_METRIC_STOP_TIMING();
         CPPUNIT_ASSERT_METRIC_TIMING_LE("AABoxOpsTest/EqualityCompareOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

         CPPUNIT_ASSERT(true_count == 0);
      }
      {
         // Inequality
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(1,1,1));
         gmtl::AABoxf box2(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(2,2,2));
         const long iters(400000);
         unsigned true_count(0);
         CPPUNIT_METRIC_START_TIMING();

         for(long iter=0;iter<iters; ++iter)
         {
            if (box1 != box2)
            {
               ++true_count;
            }
         }

         CPPUNIT_METRIC_STOP_TIMING();
         CPPUNIT_ASSERT_METRIC_TIMING_LE("AABoxOpsTest/InequalityCompareOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

         CPPUNIT_ASSERT(true_count > 0);
      }
   }

   void AABoxOpsTest::testIsEqual()
   {
      gmtl::AABoxf box( gmtl::Point3f( -1,-2,-3 ), gmtl::Point3f( 4,5,6 ) ), 
                  bok( gmtl::Point3f( -1,-2,-3 ), gmtl::Point3f( 4,5,6 ) ), 
                  mok( gmtl::Point3f( -1,-2,-3 ), gmtl::Point3f( 4,5,7 ) );
      CPPUNIT_ASSERT( gmtl::isEqual( bok, box, 0.0001f ) );
      CPPUNIT_ASSERT( bok == box );
      CPPUNIT_ASSERT( bok != mok );
      CPPUNIT_ASSERT( !gmtl::isEqual( bok, mok, 0.0001f ) );
      CPPUNIT_ASSERT( gmtl::isEqual( bok, mok, 1.0001f ) );
   }

   void AABoxOpsMetricTest::testTimingIsEqual()
   {
      CPPUNIT_ASSERT(false);
   }
}

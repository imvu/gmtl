// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#define GMTL_COUNT_CONSTRUCT_CALLS 1      // Count the consturctor calls

#include "VecTest.h"
#include "../Suites.h"
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <gmtl/Point.h>
#include <gmtl/Generate.h>




namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(VecTest);
   CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(VecMetricTest, Suites::metric());

   void VecTest::testVecMeta()
   {
      gmtl::Vec<float,3>  vecb_1;
      gmtl::Vec<float,3>  vecb_2;
      vecb_2[0] = 5.0f;    // assign

      gmtl::Vec<float,3>  vecb_3(vecb_2);   // Copy construct
      CPPUNIT_ASSERT(vecb_3[0] == 5.0f);

      gmtl::Vec<float,3>  vecb_4(0,1,2);    // Construct with values
      vecb_1.set(5,6,7);                     // set
      gmtl::Vec<float,3>  vecb_5(0,1,2);    // Construct with values
      gmtl::Vec<float,3>  vecb_6(0,1,2);    // Construct with values

      vecb_2.mData[0] = 10;                  // Access data directly
      vecb_2.mData[1] = 12;

      CPPUNIT_ASSERT(vecb_2[1] == 12.0f);

      vecb_1 = vecb_2;
      CPPUNIT_ASSERT(vecb_1[1] == 12.0f);

      //unsigned ctr_count;
      vecb_2[0] = 10.0f;
      vecb_3[0] = 12.0f;
      vecb_4[0] = 15.0f;

      std::cout << "ctr cnt before v2+v3: " << gmtl::helpers::VecCtrCounterInstance()->get() << std::endl;

      vecb_1 = vecb_2 + vecb_3;
      CPPUNIT_ASSERT(22.0f == vecb_1[0]);
      std::cout << "ctr cnt after v2+v3: " << gmtl::helpers::VecCtrCounterInstance()->get() << std::endl;

      std::cout << "ctr cnt before v2+v3+v4: " << gmtl::helpers::VecCtrCounterInstance()->get() << std::endl;
      vecb_1 = (vecb_2+vecb_3) + vecb_4;
      CPPUNIT_ASSERT(37.0f == vecb_1[0]);
      std::cout << "ctr cnt after v2+v3+v4: " << gmtl::helpers::VecCtrCounterInstance()->get() << std::endl;

      vecb_2.set(1,2,3);
      vecb_3 = vecb_2;
      vecb_4 = vecb_2;
      vecb_5 = vecb_2;

      vecb_1 = vecb_2 + vecb_3 + vecb_4;

      std::cout << "ctr cnt after multi-add: " << gmtl::helpers::VecCtrCounterInstance()->get() << std::endl;

      vecb_1 = vecb_2 * 3.0f;

      CPPUNIT_ASSERT( vecb_1[0] == 3.0f);
      CPPUNIT_ASSERT( vecb_1[1] == 6.0f);
      CPPUNIT_ASSERT( vecb_1[2] == 9.0f);

      std::cout << "ctr cnt after vec*scalar: " << gmtl::helpers::VecCtrCounterInstance()->get() << std::endl;

      vecb_2.set(10, 20, 30);
      vecb_1 = vecb_2/10.0f;

      std::cout << "ctr cnt after vec/scalar: " << gmtl::helpers::VecCtrCounterInstance()->get() << std::endl;

      vecb_1 = (vecb_2 +vecb_3)-(vecb_4+vecb_5)+(3.0f*vecb_6);
      std::cout << "ctr cnt after (vecb_2 +vecb_3)-(vecb_4+vecb_5)+(3.0f*vecb_6): " << gmtl::helpers::VecCtrCounterInstance()->get() << std::endl;

      // Test implicit constructor
      //float length = gmtl::lengthSquared(vecb_1+vecb_2);
      float length = gmtl::lengthSquared<float,3>(vecb_1+vecb_2);

   }

   void VecMetricTest::testVecMetaPerf()
   {
      gmtl::Vec<float,3> vec1;
      gmtl::Vec<float,3> vec2;
      gmtl::Vec<float,3> vec3;
      float dot;

      dot = gmtl::dot(vec1,vec2+vec3);
      //dot = gmtl::dot(vec1,(vec2+vec3));

      /*
      gmtl::VecB<float,3> test_vec1(1.0, 2.0, 3.0);
      gmtl::VecB<float,3> test_vec2(2.0, 2.0, 2.0);
      gmtl::VecB<float,3> test_vec3(1.0, 2.0, 3.0);

      unsigned num_ctr_calls_start(gmtl::helpers::VecCtrCounterInstance()->get());

      // -- test op+ performance
      const float iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      test_vec3.set(5.0, 7.0, 9.0);

      for( float iter=0;iter<iters; ++iter)
      {
         test_vec3.set(iter, iter+1, iter+2);
         test_vec1 = test_vec3 + test_vec2;
      }

      test_vec2 = test_vec1;

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/VecB:OpPlusOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      unsigned avg_ctr_calls = (gmtl::helpers::VecCtrCounterInstance()->get()-num_ctr_calls_start)/unsigned(iters);
      CPPUNIT_ASSERT_METRIC_LE("VecTest/VecB:OpPlusOverhead:ctr-calls", avg_ctr_calls, 0.075f, 0.1f);

      {
         gmtl::VecB<float,4> const_vec1(4.0f, 5.0f, 6.0f, 7.8f);
         gmtl::VecB<float,4> const_vec2(1.0f, 2.0f, 3.0f, 4.8f);
         gmtl::VecB<float,4> const_vec3(7.0f, 11.0f, 12.0f, 24.0f);
         gmtl::VecB<float,4> vec1, vec2, vec3;

         gmtl::VecB<float,4> res_vec, total_vec;

         const unsigned long iters(10000);
         unsigned num_ctr_calls, used_ctr_calls, avg_ctr_calls;

         // -- test vec = vec+vec+vec
         vec1.set(1.0, 2.0, 3.0, 4.0f);
         vec2.set(3.0, 3.0, 3.0, 3.0);
         vec3.set(11.0, 21.0, 75.0, 2.0f);
         total_vec.set(0,0,0,0);
         num_ctr_calls = gmtl::helpers::VecCtrCounterInstance()->get();

         CPPUNIT_METRIC_START_TIMING();
         for( unsigned iter=0;iter<iters; ++iter)
         {
            // Do some work to make the vectors change a little
            vec1.set((float)iter, (float)iter+1, (float)iter+2, (float)iter+3);
            vec2[0] *= 0.00125f;
            vec3[2] *= -0.000345f;

            // Do the actually operation of interest
            res_vec = vec1+vec2+vec3;
            total_vec[0] += res_vec[0];
         }
         CPPUNIT_METRIC_STOP_TIMING();
         CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/VecB:vec+vec+vec:perf", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
         used_ctr_calls = gmtl::helpers::VecCtrCounterInstance()->get()-num_ctr_calls;
         avg_ctr_calls = used_ctr_calls/iters;
         CPPUNIT_ASSERT_METRIC_LE("VecTest/VecB:vec+vec+vec:ctr-calls", avg_ctr_calls, 0.075f, 0.1f);
     }
     */
   }


   void VecTest::testCreation()
   {
      gmtl::Vec<double, 3> vec;

      CPPUNIT_ASSERT( vec[0] == 0.0f);
      CPPUNIT_ASSERT( vec[1] == 0.0f);
      CPPUNIT_ASSERT( vec[2] == 0.0f);
   }

   void VecMetricTest::testTimingCreation()
   {
      // Test overhead of creation
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Vec<float, 2> test_vec2;
         test_vec2[0] = 1.0f;
         gmtl::Vec<float, 3> test_vec3;
         test_vec3[0] = 2.0f;
         gmtl::Vec<float, 4> test_vec4;
         test_vec4[0] = 3.0f;

         use_value = use_value + test_vec2[0] + test_vec3[0] + test_vec4[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/VecCreationOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }

   void VecTest::testCopyConstruct()
   {
      gmtl::Vec<double, 3> test_vec;

      test_vec[0] = 2.0f;
      test_vec[1] = 4.0f;
      test_vec[2] = 8.0f;

      gmtl::Vec<double, 3> test_vec_copy(test_vec);

      CPPUNIT_ASSERT( test_vec_copy[0] == 2.0f);
      CPPUNIT_ASSERT( test_vec_copy[1] == 4.0f);
      CPPUNIT_ASSERT( test_vec_copy[2] == 8.0f);
   }

   void VecMetricTest::testTimingCopyConstruct()
   {
      // Test copy construction overhead
      const long iters(400000);
      gmtl::Vec<float, 2> test_vec2;
      test_vec2[0] = 2.0f;
      gmtl::Vec<float, 3> test_vec3;
      test_vec2[0] = 3.0f;
      gmtl::Vec<float, 4> test_vec4;
      test_vec2[0] = 4.0f;
      float use_value(0);     // A temp just here to use the objs so the copiler (hopefully) does not opt them out

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Vec<float, 2> test_vec2_copy(test_vec2);
         use_value += test_vec2_copy[0];
         gmtl::Vec<float, 3> test_vec3_copy(test_vec3);
         use_value += test_vec3_copy[0];
         gmtl::Vec<float, 4> test_vec4_copy(test_vec4);
         use_value += test_vec4_copy[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/CopyConstructOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }


   void VecTest::testConstructors()
   {
      gmtl::Vec<float, 4> test_vec4(1.0f, 2.0f, 3.0f, 4.0f);
      CPPUNIT_ASSERT( test_vec4[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec4[1] == 2.0f);
      CPPUNIT_ASSERT( test_vec4[2] == 3.0f);
      CPPUNIT_ASSERT( test_vec4[3] == 4.0f);

      gmtl::Vec<float, 3> test_vec3(1.0f, 2.0f, 3.0f);
      CPPUNIT_ASSERT( test_vec3[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec3[1] == 2.0f);
      CPPUNIT_ASSERT( test_vec3[2] == 3.0f);

      gmtl::Vec<float, 2> test_vec2(1.0f, 2.0f);
      CPPUNIT_ASSERT( test_vec2[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec2[1] == 2.0f);

      gmtl::Vec<float, 1> test_vec1;
      test_vec1.set(1.0f);
      CPPUNIT_ASSERT( test_vec1[0] == 1.0f);
   }

   void VecMetricTest::testTimingConstructors()
   {
      // Test constructor
      const long iters(400000);
      float use_value(0.0f);     // A temp just here to use the objs so the copiler (hopefully) does not opt them out

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Vec<float, 4> test_vec4(1.0f, 2.0f, 3.0f, 4.0f);
         gmtl::Vec<float, 3> test_vec3(1.0f, 2.0f, 3.0f);
         gmtl::Vec<float, 2> test_vec2(1.0f, 2.0f);
         gmtl::Vec<float, 1> test_vec1;
         test_vec1.set(1.0f);

         use_value = use_value + test_vec4[3] + test_vec3[2] + test_vec2[1] + test_vec1[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/ConstructorsOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void VecTest::testSet()
   {
      gmtl::Vec<float, 4> test_vec4;
      test_vec4.set(1.0f, 2.0f, 3.0f, 4.0f);
      CPPUNIT_ASSERT( test_vec4[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec4[1] == 2.0f);
      CPPUNIT_ASSERT( test_vec4[2] == 3.0f);
      CPPUNIT_ASSERT( test_vec4[3] == 4.0f);

      gmtl::Vec<float, 3> test_vec3;
      test_vec3.set(1.0f, 2.0f, 3.0f);
      CPPUNIT_ASSERT( test_vec3[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec3[1] == 2.0f);
      CPPUNIT_ASSERT( test_vec3[2] == 3.0f);

      gmtl::Vec<float, 2> test_vec2;
      test_vec2.set(1.0f, 2.0f);
      CPPUNIT_ASSERT( test_vec2[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec2[1] == 2.0f);

      gmtl::Vec<float, 1> test_vec1;
      test_vec1.set(1.0f);
      CPPUNIT_ASSERT( test_vec1[0] == 1.0f);
   }

   void VecMetricTest::testTimingSet()
   {
      gmtl::Vec<float, 4> test_vec4;
      gmtl::Vec<float, 3> test_vec3;
      gmtl::Vec<float, 2> test_vec2;
      gmtl::Vec<float, 1> test_vec1;

      // Test constructor
      const float iters(400000);
      float use_value(0.0f);     // A temp just here to use the objs so the copiler (hopefully) does not opt them out

      CPPUNIT_METRIC_START_TIMING();

      for( float iter=0;iter<iters; ++iter)
      {
         test_vec4.set(iters+0, iters+1, iters+2, iters+3);
         test_vec3.set(iters+0, iters+1, iters+2);
         test_vec2.set(iters+0, iters+1);
         test_vec1.set(iters+0);

         use_value = use_value + test_vec4[3] + test_vec3[2] + test_vec2[1] + test_vec1[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/SetOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }

   void VecTest::testSetPtr()
   {
      float data[4] = {1.0f, 2.0f, 3.0f, 4.0f};

      gmtl::Vec<float, 4> test_vec4;
      test_vec4.set(data);
      CPPUNIT_ASSERT( test_vec4[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec4[1] == 2.0f);
      CPPUNIT_ASSERT( test_vec4[2] == 3.0f);
      CPPUNIT_ASSERT( test_vec4[3] == 4.0f);

      gmtl::Vec<float, 3> test_vec3;
      test_vec3.set(data);
      CPPUNIT_ASSERT( test_vec3[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec3[1] == 2.0f);
      CPPUNIT_ASSERT( test_vec3[2] == 3.0f);

      gmtl::Vec<float, 2> test_vec2;
      test_vec2.set(data);
      CPPUNIT_ASSERT( test_vec2[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec2[1] == 2.0f);

      gmtl::Vec<float, 1> test_vec1;
      test_vec1.set(data);
      CPPUNIT_ASSERT( test_vec1[0] == 1.0f);
   }

   void VecMetricTest::testTimingSetPtr()
   {
      float data[4] = {1.0f, 2.0f, 3.0f, 4.0f};
      gmtl::Vec<float, 4> test_vec4;
      gmtl::Vec<float, 3> test_vec3;
      gmtl::Vec<float, 2> test_vec2;
      gmtl::Vec<float, 1> test_vec1;

      // Test constructor
      const float iters(400000);
      float use_value(0.0f);     // A temp just here to use the objs so the copiler (hopefully) does not opt them out

      CPPUNIT_METRIC_START_TIMING();

      for( float iter=0;iter<iters; ++iter)
      {
         data[0] += 1.0f; data[1] += 2.0f; data[2] += 4.0f; data[3] += 8.0f;    // Just make sure data changes
         test_vec4.set(data);
         test_vec3.set(data);
         test_vec2.set(data);
         test_vec1.set(data);

         use_value = use_value + test_vec4[3] + test_vec3[2] + test_vec2[1] + test_vec1[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/SetPtrOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }


   void VecTest::testGetData()
   {
      float* data;
      gmtl::Vec<float, 4> test_vec4(1.0f, 2.0f, 3.0f, 4.0f);
      data = test_vec4.getData();
      CPPUNIT_ASSERT( data[0] == 1.0f);
      CPPUNIT_ASSERT( data[1] == 2.0f);
      CPPUNIT_ASSERT( data[2] == 3.0f);
      CPPUNIT_ASSERT( data[3] == 4.0f);

      gmtl::Vec<float, 3> test_vec3(1.0f, 2.0f, 3.0f);
      data = test_vec3.getData();
      CPPUNIT_ASSERT( data[0] == 1.0f);
      CPPUNIT_ASSERT( data[1] == 2.0f);
      CPPUNIT_ASSERT( data[2] == 3.0f);

      gmtl::Vec<float, 2> test_vec2(1.0f, 2.0f);
      data = test_vec2.getData();
      CPPUNIT_ASSERT( data[0] == 1.0f);
      CPPUNIT_ASSERT( data[1] == 2.0f);
   }


   // -- Test comparison -- //
   void VecTest::testEqualityCompare()
   {
      gmtl::Vec<float, 4> test_vec1(1.0f, 2.0f, 3.0f, 4.0f);
      gmtl::Vec<float, 4> test_vec2(test_vec1);

      CPPUNIT_ASSERT( test_vec1 == test_vec2);
      CPPUNIT_ASSERT(! (test_vec1 != test_vec2));

      test_vec2 = test_vec1;     // Set equal, vary elt 0
      test_vec2[0] = 21.10f;
      CPPUNIT_ASSERT( test_vec1 != test_vec2);
      CPPUNIT_ASSERT(! (test_vec1 == test_vec2));

      test_vec2 = test_vec1;     // Set equal, vary elt 0
      test_vec2[1] = 21.10f;
      CPPUNIT_ASSERT( test_vec1 != test_vec2);
      CPPUNIT_ASSERT(! (test_vec1 == test_vec2));

      test_vec2 = test_vec1;     // Set equal, vary elt 0
      test_vec2[2] = 21.10f;
      CPPUNIT_ASSERT( test_vec1 != test_vec2);
      CPPUNIT_ASSERT(! (test_vec1 == test_vec2));

      test_vec2 = test_vec1;     // Set equal, vary elt 0
      test_vec2[3] = 21.10f;
      CPPUNIT_ASSERT( test_vec1 != test_vec2);
      CPPUNIT_ASSERT(! (test_vec1 == test_vec2));
   }

   void VecMetricTest::testTimingEqualityCompare()
   {
      gmtl::Vec<float, 4> test_vec1(1.0f, 2.0f, 3.0f, 4.0f);
      gmtl::Vec<float, 4> test_vec2(test_vec1);

      // Test comparison performance
      // Test constructor
      const float iters(400000);
      unsigned true_count(0);
      unsigned false_count(0);

      // -- Equality
      CPPUNIT_METRIC_START_TIMING();
      test_vec1.set(0.0f, 0.0f, 0.0f, 2000.0f);
      test_vec2.set(0.0f, 0.0f, 0.0f, 1000.0f);

      for( float iter=0;iter<iters; ++iter)
      {
         test_vec1[3] += 1.0f;
         test_vec2[3] += 2.0f;
         if(test_vec1 == test_vec2)
            true_count++;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/EqualityCompareOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // -- Inequality
      CPPUNIT_METRIC_START_TIMING();
      test_vec1.set(0.0f, 0.0f, 0.0f, 2000.0f);
      test_vec2.set(0.0f, 0.0f, 0.0f, 1000.0f);

      for( float iter=0;iter<iters; ++iter)
      {
         test_vec1[3] += 1.0f;
         test_vec2[3] += 2.0f;
         if(test_vec1 != test_vec2)
            false_count++;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/InequalityCompareOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

   }

   // -- Test comparison -- //
   void VecTest::testIsEqual()
   {
      gmtl::Vec<float, 4> test_vec1(1.0f, 2.0f, 3.0f, 4.0f);
      gmtl::Vec<float, 4> test_vec2(test_vec1);
      float eps(0.0f);

      for(eps=0.0f;eps<10.0f;eps += 0.05f)
      {
         CPPUNIT_ASSERT( gmtl::isEqual(test_vec1, test_vec2, eps) );
      }

      test_vec1.set(1.0f, 1.0f, 1.0f, 1.0f);
      for(unsigned elt=0; elt<4; elt++)
      {
         test_vec2 = test_vec1;     // Set equal, vary elt 0
         test_vec2[elt] = 21.0f;
         CPPUNIT_ASSERT( !gmtl::isEqual(test_vec1, test_vec2, 10.0f) );
         CPPUNIT_ASSERT( !gmtl::isEqual(test_vec1, test_vec2, 19.9f) );
         CPPUNIT_ASSERT( gmtl::isEqual(test_vec1, test_vec2, 20.1f) );
         CPPUNIT_ASSERT( gmtl::isEqual(test_vec1, test_vec2, 22.0f) );
      }
   }

   void VecMetricTest::testTimingIsEqual()
   {
      gmtl::Vec<float, 4> test_vec1(1.0f, 2.0f, 3.0f, 4.0f);
      gmtl::Vec<float, 4> test_vec2(test_vec1);

      // Test comparison performance
      // Test constructor
      const float iters(400000);
      unsigned true_count(0);

      // -- Equality
      CPPUNIT_METRIC_START_TIMING();
      test_vec1.set(0.0f, 0.0f, 0.0f, 2000.0f);
      test_vec2.set(0.0f, 0.0f, 0.0f, 1000.0f);

      for( float iter=0;iter<iters; ++iter)
      {
         test_vec1[3] += 1.0f;
         test_vec2[3] += 2.0f;
         if(gmtl::isEqual(test_vec1, test_vec2, 1.0f) )
            true_count++;
         if(gmtl::isEqual(test_vec1, test_vec2, 0.1f) )
            true_count++;
         if(gmtl::isEqual(test_vec1, test_vec2, 100000.0f) )
            true_count++;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/isEqualOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

   }

   void VecTest::testOpNegate()
   {
      gmtl::Vec<float,3> test_vec1(1.0, 2.0, 3.0);
      gmtl::Vec<float,3> test_vec2;

      test_vec2 = -test_vec1;
      CPPUNIT_ASSERT( test_vec2[0] == -1.0f &&
                      test_vec2[1] == -2.0f &&
                      test_vec2[2] == -3.0f );
   }

   void VecMetricTest::testTimingOpNegate()
   {
      gmtl::Vec<float,3> test_vec1(1.0, 2.0, 3.0);
      gmtl::Vec<float,3> test_vec3(5.0, 7.0, 9.0);

      // -- test op+= performance
      const float iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      for( float iter=0;iter<iters; ++iter)
      {
         test_vec3.set(iter, iter+1, iter+2);
         test_vec1 = -test_vec3;
      }

      CPPUNIT_METRIC_STOP_TIMING();

      // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/OpNegateOverhead", iters,
                                      0.075f, 0.1f);
   }

   void VecTest::testOpPlusEq()
   {
      gmtl::Vec<float,3> test_vec1(1.0, 2.0, 3.0);
      gmtl::Vec<float,3> test_vec2(2.0, 2.0, 2.0);

      test_vec1 += test_vec2;
      CPPUNIT_ASSERT( test_vec1[0] == 3.0f &&
                      test_vec1[1] == 4.0f &&
                      test_vec1[2] == 5.0f );
   }

   void VecMetricTest::testTimingOpPlusEq()
   {
      gmtl::Vec<float,3> test_vec1(1.0, 2.0, 3.0);
      gmtl::Vec<float,3> test_vec2(2.0, 2.0, 2.0);
      gmtl::Vec<float,3> test_vec3(5.0, 7.0, 9.0);

      // -- test op+= performance
      const float iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      for( float iter=0;iter<iters; ++iter)
      {
         test_vec3.set(iter, iter+1, iter+2);
         test_vec1 += test_vec3;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/OpPlusEqOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      test_vec2 = test_vec1;
   }

   void VecTest::testOpPlus()
   {
      gmtl::Vec<float,3> test_vec1(1.0, 2.0, 3.0);
      gmtl::Vec<float,3> test_vec2(2.0, 2.0, 2.0);
      gmtl::Vec<float,3> test_vec3(1.0, 2.0, 3.0);

      test_vec1 = test_vec3 + test_vec2;
      CPPUNIT_ASSERT( test_vec1[0] == 3.0f &&
                      test_vec1[1] == 4.0f &&
                      test_vec1[2] == 5.0f );
   }

   void VecMetricTest::testTimingOpPlus()
   {
      gmtl::Vec<float,3> test_vec1(1.0, 2.0, 3.0);
      gmtl::Vec<float,3> test_vec2(2.0, 2.0, 2.0);
      gmtl::Vec<float,3> test_vec3(1.0, 2.0, 3.0);

      // -- test op+ performance
      const float iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      test_vec3.set(5.0, 7.0, 9.0);

      for( float iter=0;iter<iters; ++iter)
      {
         test_vec3.set(iter, iter+1, iter+2);
         test_vec1 = (test_vec3 + test_vec2);
      }

      test_vec2 = test_vec1;

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/OpPlusOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void VecTest::testOpMinusEq()
   {
      gmtl::Vec<float,3> test_vec1(1.0, 2.0, 3.0);
      gmtl::Vec<float,3> test_vec2(2.0, 2.0, 2.0);

      test_vec1 -= test_vec2;
      CPPUNIT_ASSERT( test_vec1[0] == -1.0f &&
                      test_vec1[1] == 0.0f &&
                      test_vec1[2] == 1.0f );
   }

   void VecMetricTest::testTimingOpMinusEq()
   {
      gmtl::Vec<float,3> test_vec1(1.0, 2.0, 3.0);
      gmtl::Vec<float,3> test_vec2(2.0, 2.0, 2.0);
      gmtl::Vec<float,3> test_vec3(5.0, 7.0, 9.0);

      // -- test op-= performance
      const float iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      for( float iter=0;iter<iters; ++iter)
      {
         test_vec3.set(iter, iter+1, iter+2);
         test_vec1 -= test_vec3;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/OpMinusEqOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      test_vec2 = test_vec1;
   }

   void VecTest::testOpMinus()
   {
      gmtl::Vec<float,3> test_vec1(1.0, 2.0, 3.0);
      gmtl::Vec<float,3> test_vec2(2.0, 2.0, 2.0);
      gmtl::Vec<float,3> test_vec3(1.0, 2.0, 3.0);

      test_vec1 = test_vec3 - test_vec2;
      CPPUNIT_ASSERT( test_vec1[0] == -1.0f &&
                      test_vec1[1] == 0.0f &&
                      test_vec1[2] == 1.0f );
   }

   void VecMetricTest::testTimingOpMinus()
   {
      gmtl::Vec<float,3> test_vec1(1.0, 2.0, 3.0);
      gmtl::Vec<float,3> test_vec2(2.0, 2.0, 2.0);
      gmtl::Vec<float,3> test_vec3(1.0, 2.0, 3.0);

      // -- test op- performance
      const float iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      test_vec3.set(5.0, 7.0, 9.0);

      for( float iter=0;iter<iters; ++iter)
      {
         test_vec3.set(iter, iter+1, iter+2);
         test_vec1 = (test_vec3 - test_vec2);
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/OpMinusOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      test_vec2 = test_vec1;
   }

   void VecTest::testOpMultScalarEq()
   {
      gmtl::Vec<float,3> test_vec1(1.0, 2.0, 3.0);

      test_vec1 *= 4.0f;
      CPPUNIT_ASSERT( test_vec1[0] == 4.0f &&
                      test_vec1[1] == 8.0f &&
                      test_vec1[2] == 12.0f );
   }

   void VecMetricTest::testTimingOpMultScalarEq()
   {
      gmtl::Vec<float,3> test_vec1(1.0, 2.0, 3.0);

      // -- test op-= performance
      const float iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      for( float iter=0;iter<iters; ++iter)
      {
         test_vec1 *= 1.05f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/OpMultScalarEqOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void VecTest::testOpMultScalar()
   {
      gmtl::Vec<float,3> test_vec1(1.0, 2.0, 3.0);
      gmtl::Vec<float,3> test_vec3(1.0, 2.0, 3.0);

      test_vec1 = test_vec3 * 4.0f;
      CPPUNIT_ASSERT( test_vec1[0] == 4.0f &&
                      test_vec1[1] == 8.0f &&
                      test_vec1[2] == 12.0f );
   }

   void VecMetricTest::testTimingOpMultScalar()
   {
      gmtl::Vec<float,3> test_vec1(1.0, 2.0, 3.0);
      gmtl::Vec<float,3> test_vec3(1.0, 2.0, 3.0);

      // -- test op- performance
      const float iters(400000);
      CPPUNIT_METRIC_START_TIMING();
      test_vec3.set(5.0, 7.0, 9.0);

      for( float iter=0;iter<iters; ++iter)
      {
         test_vec1 = test_vec3 * 1.05f;
         test_vec3 = test_vec1;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/OpVecMultScalarOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   /** Test scalar * vec */
   void VecTest::testOpScalarVecMult()
   {
      gmtl::Vec<float,3> test_vec1(1.0, 2.0, 3.0);
      gmtl::Vec<float,3> test_vec3(1.0, 2.0, 3.0);

      test_vec1 = 4.0f * test_vec3;
      CPPUNIT_ASSERT( test_vec1[0] == 4.0f &&
                      test_vec1[1] == 8.0f &&
                      test_vec1[2] == 12.0f );
   }

   void VecMetricTest::testTimingOpScalarVecMult()
   {
      gmtl::Vec<float,3> test_vec1(1.0, 2.0, 3.0);
      gmtl::Vec<float,3> test_vec3(5.0, 7.0, 9.0);

      // -- test op- performance
      const float iters(400000);
      float bogus_value(0.0f);
      CPPUNIT_METRIC_START_TIMING();

      for( float iter=0;iter<iters; ++iter)
      {
         test_vec1 = 1.05f * test_vec3;
         test_vec3 = test_vec1;
         bogus_value += test_vec1[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/OpScalarMultVecOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT(bogus_value > 5.0f);
   }


   void VecTest::testOpDivScalarEq()
   {
      gmtl::Vec<float,3> test_vec1(12.0, 8.0, 4.0);

      test_vec1 /= 4.0f;
      CPPUNIT_ASSERT( test_vec1[0] == 3.0f &&
                      test_vec1[1] == 2.0f &&
                      test_vec1[2] == 1.0f );
   }

   void VecMetricTest::testTimingOpDivScalarEq()
   {
      gmtl::Vec<float,3> test_vec1(12.0, 8.0, 4.0);

      // -- test op-= performance
      const float iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      for( float iter=0;iter<iters; ++iter)
      {
         test_vec1 /= 0.95f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/OpDivScalarEqOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void VecTest::testOpDivScalar()
   {
      gmtl::Vec<float,3> test_vec1(1.0, 2.0, 3.0);
      gmtl::Vec<float,3> test_vec3(12.0, 8.0, 4.0);

      test_vec1 = test_vec3 / 4.0f;
      CPPUNIT_ASSERT( test_vec1[0] == 3.0f &&
                      test_vec1[1] == 2.0f &&
                      test_vec1[2] == 1.0f );
   }

   void VecMetricTest::testTimingOpDivScalar()
   {
      gmtl::Vec<float,3> test_vec1(1.0, 2.0, 3.0);
      gmtl::Vec<float,3> test_vec3(5.0, 7.0, 9.0);

      // -- test op- performance
      const float iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      for( float iter=0;iter<iters; ++iter)
      {
         test_vec1 = test_vec3 / 0.95f;
         test_vec3 = test_vec1;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/OpDivScalarOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void VecMetricTest::testTimingGroupedOps()
   {
      gmtl::Vec<float,4> const_vec1(4.0f, 5.0f, 6.0f, 7.8f);
      gmtl::Vec<float,4> const_vec2(1.0f, 2.0f, 3.0f, 4.8f);
      gmtl::Vec<float,4> const_vec3(7.0f, 11.0f, 12.0f, 24.0f);
      gmtl::Vec<float,4> vec1, vec2, vec3;

      gmtl::Vec<float,4> res_vec, total_vec;

      const unsigned long iters(10000);

      // -- test vec = vec+vec+vec
      vec1.set(1.0, 2.0, 3.0, 4.0f);
      vec2.set(3.0, 3.0, 3.0, 3.0);
      vec3.set(12.0, 21.0, 75.0, 2.0f);
      total_vec.set(0,0,0,0);

      CPPUNIT_METRIC_START_TIMING();
      for( unsigned iter=0;iter<iters; ++iter)
      {
         // Do some work to make the vectors change a little
         vec1.set((float)iter, (float)iter+1, (float)iter+2, (float)iter+3);
         vec2 *= 0.00125f;
         vec3 *= (-0.000345f);

         // Do the actually operation of interest
         res_vec = vec1+vec2+vec3;
         total_vec += res_vec;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/vec+vec+vec:perf", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // -- test vec = vec-vec-vec
      vec1.set(1.0, 2.0, 3.0, 4.0f);
      vec2.set(3.0, 3.0, 3.0, 3.0);
      vec3.set(12.0, 21.0, 75.0, 2.0f);
      total_vec.set(0,0,0,0);

      CPPUNIT_METRIC_START_TIMING();
      for( unsigned iter=0;iter<iters; ++iter)
      {
         // Do some work to make the vectors change a little
         vec1.set((float)iter, (float)iter+1, (float)iter+2, (float)iter+3);
         vec2 *= 0.00125f;
         vec3 *= (-0.000345);

         // Do the actually operation of interest
         res_vec = vec1-vec2-vec3;
         total_vec += res_vec;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/vec-vec-vec:perf", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // -- test vec = const_vec1+const_vec2+const_vec3
      // Should be able to unroll this quite a bit
      total_vec.set(0,0,0,0);

      CPPUNIT_METRIC_START_TIMING();
      for( unsigned iter=0;iter<iters; ++iter)
      {
         // Do the actually operation of interest
         res_vec = const_vec1+const_vec2+const_vec3;
         total_vec += res_vec;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/const_vec+const_vec+const_vec:perf", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // -- test vec = const_vec1-const_vec2-const_vec3
      total_vec.set(0,0,0,0);

      CPPUNIT_METRIC_START_TIMING();
      for( unsigned iter=0;iter<iters; ++iter)
      {
         // Do the actually operation of interest
         res_vec = const_vec1-const_vec2-const_vec3;
         total_vec += res_vec;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/const_vec-const_vec-const_vec:perf", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // -- test vec = (vec-const_vec)+(vec+const_vec)-(const_vec*scalar)
      vec1.set(1.0, 2.0, 3.0, 4.0f);
      vec2.set(3.0, 3.0, 3.0, 3.0);
      vec3.set(12.0, 21.0, 75.0, 2.0f);
      total_vec.set(0,0,0,0);

      CPPUNIT_METRIC_START_TIMING();
      for( unsigned iter=0;iter<iters; ++iter)
      {
         // Do some work to make the vectors change a little
         vec1.set((float)iter, (float)iter+1, (float)iter+2, (float)iter+3);
         vec2 *= 0.00125f;

         // Do the actually operation of interest
         res_vec = (vec1-const_vec1)+(vec2+const_vec2)-(const_vec3*7.6f);
         total_vec += res_vec;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/(vec-const_vec)+(vec+const_vec)-(const_vec*scalar):perf", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // -- test vec = (vec*scalar)+(vec*scalar)
      vec1.set(1.0, 2.0, 3.0, 4.0f);
      vec2.set(3.0, 3.0, 3.0, 3.0);
      vec3.set(12.0, 21.0, 75.0, 2.0f);
      total_vec.set(0,0,0,0);

      CPPUNIT_METRIC_START_TIMING();
      for( unsigned iter=0;iter<iters; ++iter)
      {
         // Do some work to make the vectors change a little
         vec1.set((float)iter, (float)iter+1, (float)iter+2, (float)iter+3);
         vec2 *= 0.00125f;

         // Do the actually operation of interest
         res_vec = (vec1*7.0f)+(vec2*-1.0f);
         total_vec += res_vec;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/(vec*scalar)+(vec*scalar):perf", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // -- test vec = (const_vec*scalar)
      // Should be able to unroll this loop fairly well
      vec1.set(1.0, 2.0, 3.0, 4.0f);
      vec2.set(3.0, 3.0, 3.0, 3.0);
      vec3.set(12.0, 21.0, 75.0, 2.0f);
      total_vec.set(0,0,0,0);

      CPPUNIT_METRIC_START_TIMING();
      for( unsigned iter=0;iter<iters; ++iter)
      {
         // Do the actually operation of interest
         res_vec = (const_vec1*3.0f);
         total_vec += res_vec;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/(const_vec*scalar):perf", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // -- test vec = (vec*dot(const_vec,vec))
      // Should be able to unroll this loop fairly well
      vec1.set(1.0, 2.0, 3.0, 4.0f);
      vec2.set(3.0, 3.0, 3.0, 3.0);
      vec3.set(12.0, 21.0, 75.0, 2.0f);
      total_vec.set(0,0,0,0);

      CPPUNIT_METRIC_START_TIMING();
      for( unsigned iter=0;iter<iters; ++iter)
      {
         // Do some work to make the vectors change a little
         vec1.set((float)iter, (float)iter+1, (float)iter+2, (float)iter+3);
         vec2 *= 0.00125f;

         // Do the actually operation of interest
         res_vec = (vec1*gmtl::dot(const_vec1,vec2));
         total_vec += res_vec;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/(vec*dot(const_vec,vec)):perf", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // -- test vec = (scalar*cross(vec,vec))
      // Should be able to unroll this loop fairly well
      gmtl::Vec<float,3> vec5(3.0, 3.0, 3.0);
      gmtl::Vec<float,3> vec6(12.0, 21.0, 75.0);
      gmtl::Vec<float,3> total_vec2(0,0,0);
      gmtl::Vec<float,3> res_vec2;

      CPPUNIT_METRIC_START_TIMING();
      for( unsigned iter=0;iter<iters; ++iter)
      {
         // Do some work to make the vectors change a little
         vec5.set((float)iter+1, (float)iter+2, (float)iter+3);
         vec6 *= 0.00125f;

         // Do the actually operation of interest
         res_vec2 = (gmtl::makeCross(vec5,vec6)*21.0f);
         total_vec2 += res_vec2;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/(vec*cross(vec,vec)):perf", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

   }



   // ---- Vec specific functions --- //

   void VecTest::testReflect()
   {
      {
      gmtl::Point<float,3> v1(1,1,1);  // point or vec...
      gmtl::Point<float,3> v2(3,1,2);
      gmtl::Point<float,3> v3(4,5,1);
      gmtl::Vec<float,3> n1( 1,0,0 ); // normal of the surface/plane
      gmtl::Vec<float,3> n2( 0,1,0 );
      gmtl::Vec<float,3> n3( 0,0,1 );
      gmtl::Point<float,3> ex1( -1,1,1 ); // flipped about the surface
      gmtl::Point<float,3> ex2( 3,-1,2 );
      gmtl::Point<float,3> ex3( 4,5,-1 );
      gmtl::Point<float,3> res;

      const float eps = 0.001f;
      gmtl::reflect( res, v1, n1 );
      CPPUNIT_ASSERT( gmtl::isEqual( res, ex1, eps ) == true );
      gmtl::reflect( res, v2, n2 );
      CPPUNIT_ASSERT( gmtl::isEqual( res, ex2, eps ) == true );
      gmtl::reflect( res, v3, n3 );
      CPPUNIT_ASSERT( gmtl::isEqual( res, ex3, eps ) == true );
      }

      {
      gmtl::Vec<float,3> v1(1,1,1);  // point or vec...
      gmtl::Vec<float,3> v2(3,1,2);
      gmtl::Vec<float,3> v3(4,5,1);
      gmtl::Vec<float,3> n1( 1,0,0 ); // normal of the surface/plane
      gmtl::Vec<float,3> n2( 0,1,0 );
      gmtl::Vec<float,3> n3( 0,0,1 );
      gmtl::Vec<float,3> ex1( -1,1,1 ); // flipped about the surface
      gmtl::Vec<float,3> ex2( 3,-1,2 );
      gmtl::Vec<float,3> ex3( 4,5,-1 );
      gmtl::Vec<float,3> res;

      const float eps = 0.001f;
      gmtl::reflect( res, v1, n1 );
      CPPUNIT_ASSERT( gmtl::isEqual( res, ex1, eps ) == true );
      gmtl::reflect( res, v2, n2 );
      CPPUNIT_ASSERT( gmtl::isEqual( res, ex2, eps ) == true );
      gmtl::reflect( res, v3, n3 );
      CPPUNIT_ASSERT( gmtl::isEqual( res, ex3, eps ) == true );
      }
   }

   void VecTest::testDot()
   {
      gmtl::Vec<float,3> v1(1,0,0);
      gmtl::Vec<float,3> v2(0,1,0);
      gmtl::Vec<float,3> v3(0,0,1);
      float dot, ans;

      // Base Vectors
      dot = gmtl::dot(v1,v2);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, gmtl::dot(v1,v2), 0.05);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, gmtl::dot(v1,v3), 0.05);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0f, gmtl::dot(v2,v3), 0.05);

      // Other Vectors
      v1.set(13.45f, -7.8f, 0.056f);
      v2.set(0.777f, 5.333f,12.21f);
      v3.set(3.4f, -1.6f, 0.23f);

      ans = -30.463f;
      dot = gmtl::dot(v1,v2);
      CPPUNIT_ASSERT(GMTL_NEAR(dot,ans,0.01));
      dot = gmtl::dot(v2,v1);
      CPPUNIT_ASSERT(GMTL_NEAR(dot,ans,0.01));
      ans = -3.0827f;
      dot = gmtl::dot(v2,v3);
      CPPUNIT_ASSERT(GMTL_NEAR(dot,ans,0.01));
      dot = gmtl::dot(v3,v2);
      CPPUNIT_ASSERT(GMTL_NEAR(dot,ans,0.01));
   }

   void VecMetricTest::testTimingDot()
   {
      gmtl::Vec<float,3> v1(1,0,0);
      gmtl::Vec<float,3> v2(0,1,0);

      // -- test op- performance
      const float iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      float val(0);

      for( float iter=0;iter<iters; ++iter)
      {
         val += gmtl::dot(v1,v2);
         v1 *= 1.0025;                 // Make it grow a little
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/DotOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void VecTest::testLength()
   {
      gmtl::Vec<float,3> v1(1,0,0);
      gmtl::Vec<float,3> v2(0,1,0);
      gmtl::Vec<float,3> v3(0,0,1);
      float len, ans;

      // Base Vectors
      CPPUNIT_ASSERT_DOUBLES_EQUAL(gmtl::length(v1),1.0f, 0.05f);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(gmtl::length(v2),1.0f, 0.05f);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(gmtl::length(v3),1.0f, 0.05f);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(gmtl::lengthSquared(v1), 1.0f, 0.05f);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(gmtl::lengthSquared(v2), 1.0f, 0.05f);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(gmtl::lengthSquared(v3), 1.0f, 0.05f);

      // Other Vectors
      v1.set(2.0f, 4.0f, 5.0f);
      v2.set(12.0f, -2.0f, -4.0f);

      ans = 4.0f + 16.0f + 25.0f;
      len = gmtl::lengthSquared(v1);
      CPPUNIT_ASSERT(GMTL_NEAR(len,ans,0.01));

      ans = gmtl::Math::sqrt(ans);
      len = gmtl::length(v1);
      CPPUNIT_ASSERT(GMTL_NEAR(len,ans,0.01));

      ans = 144.0f + 4.0f + 16.0f;
      len = gmtl::lengthSquared(v2);
      CPPUNIT_ASSERT(GMTL_NEAR(len,ans,0.01));

      ans = gmtl::Math::sqrt(ans);
      len = gmtl::length(v2);
      CPPUNIT_ASSERT(GMTL_NEAR(len,ans,0.01));
   }

   void VecMetricTest::testTimingLength()
   {
      gmtl::Vec<float,3> v1(2.0f, 4.0f, 5.0f);

      // -- test length performance
      const float iters(100000);
      float val(0.0f);

      CPPUNIT_METRIC_START_TIMING();

      for( float iter=0;iter<iters; ++iter)
      {
         val += gmtl::length(v1);
         v1 *= 1.0025f;                 // Make it grow a little
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/LengthOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // -- test lengthSquared performance
      CPPUNIT_METRIC_START_TIMING();
      val = 0.0f;
      v1.set(1.0f, 2.0f, 4.0f);

      for( float iter=0;iter<iters; ++iter)
      {
         val += gmtl::lengthSquared(v1);
         v1 *= 1.0025f;                 // Make it grow a little
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/LengthSquaredOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }


   void VecTest::testNormalize()
   {
      gmtl::Vec<float,3> v1(1,0,0);
      gmtl::Vec<float,3> v2(0,1,0);

      // Other Vectors
      v1.set(2.0f, 4.0f, 5.0f);
      v2 = v1;
      gmtl::normalize(v1);
      gmtl::Vec<float,3> temp = (v1*gmtl::length(v2));
      CPPUNIT_ASSERT( gmtl::isEqual(v2, temp, 0.01f ) );

      v1.set(12.0f, -2.0f, -4.0f);
      v2 = v1;
      gmtl::normalize(v1);
      CPPUNIT_ASSERT( gmtl::isEqual(v2, gmtl::Vec3f(v1*gmtl::length(v2)),0.01f ) );
   }

   void VecMetricTest::testTimingNormalize()
   {
      gmtl::Vec<float,3> v1(12.0f, 21.0f, 75.0f);
      gmtl::Vec<float,3> v2(0,1,0);

      // -- test performance
      const float iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      float val(0.0f);

      for( float iter=0;iter<iters; ++iter)
      {
         v1 *= 1.0025f;                 // Make it grow a little
         v2 = v1;
         val += gmtl::normalize(v2);
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/NormalizeOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }


   void VecTest::testIsNormalized()
   {
      gmtl::Vec<float,3> v1(1,0,0);
      gmtl::Vec<float,3> v2(0,1,0);
      gmtl::Vec<float,3> v3(0,0,1);
      gmtl::Vec<float,3> v4(2,4,5);

      // no tolerance
      CPPUNIT_ASSERT( gmtl::isNormalized(v1) );
      CPPUNIT_ASSERT( gmtl::isNormalized(v2) );
      CPPUNIT_ASSERT( gmtl::isNormalized(v3) );

      CPPUNIT_ASSERT( ! gmtl::isNormalized(v4) );
   }

   void VecMetricTest::testTimingIsNormalized()
   {
      gmtl::Vec<float,3> v4(0.5f, 0.5f, 0.5f);

      // test performance
      const unsigned long iters(100000);
      long true_count(0);

      CPPUNIT_METRIC_START_TIMING();
      for ( unsigned long iter=0; iter<iters; ++iter )
      {
         v4 *= 1.0025f;
         if ( gmtl::isNormalized(v4) )
            ++true_count;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/IsNormalizedOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void VecTest::testIsNormalizedEps()
   {
      gmtl::Vec<float,3> v1(1,0,0);
      gmtl::Vec<float,3> v2(v1);

      // epsilon tolerance
      for ( float eps=0; eps<10; eps+=0.5 )
      {
         CPPUNIT_ASSERT( gmtl::isNormalized(v1, eps) );
      }

      v2.set(21,0,0);
      CPPUNIT_ASSERT( ! gmtl::isNormalized(v2, 15.0f * 15.0f) );
      CPPUNIT_ASSERT( ! gmtl::isNormalized(v2, 19.9f * 19.9f) );
      CPPUNIT_ASSERT( gmtl::isNormalized(v2, 21.0f * 21.0f - 0.9f) );
      CPPUNIT_ASSERT( gmtl::isNormalized(v2, 21.0f * 21.0f + 0.9f) );
   }

   void VecMetricTest::testTimingIsNormalizedEps()
   {
      gmtl::Vec<float,3> v2(0.5f, 0.5f, 0.5f);

      // test performance
      const unsigned long iters(100000);
      long true_count(0);
      float tol = 0.25f;

      CPPUNIT_METRIC_START_TIMING();
      for ( unsigned long iter=0; iter<iters; ++iter )
      {
         v2 *= 1.0025f;
         if ( gmtl::isNormalized(v2, tol) )
            ++true_count;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/IsNormalizedEpsOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }


   void VecTest::testCross()
   {
      gmtl::Vec<float,3> v1(1,0,0);
      gmtl::Vec<float,3> v2(0,1,0);
      gmtl::Vec<float,3> v3(0,0,1);
      gmtl::Vec<float,3> cross;

      // Base Vectors
      gmtl::cross(cross, v1,v2);
      CPPUNIT_ASSERT( gmtl::isEqual(cross, v3, 0.01f) );
      gmtl::cross(cross, v2,v1);
      CPPUNIT_ASSERT( gmtl::isEqual(cross, gmtl::Vec3f(-v3), 0.01f) );

      v1.set(13.45f, -7.8f, 0.056f);
      v2.set(0.777f, 5.333f,12.21f);
      v3.set(-95.537f, -164.181f, 77.789f);

      gmtl::cross(cross, v1,v2);
      CPPUNIT_ASSERT( gmtl::isEqual(cross, v3, 0.01f));
      gmtl::cross(cross, v2, v1);
      CPPUNIT_ASSERT(gmtl::isEqual(cross, gmtl::Vec3f(-v3), 0.01f));


      // Test for compilability
      //cross = gmtl::cross((v1+v2),(v2+v3));
   }

   void VecMetricTest::testTimingCross()
   {
      gmtl::Vec<float,3> v1(12.0f, 21.0f, 75.0f);
      gmtl::Vec<float,3> v2(0,1,0);
      gmtl::Vec<float,3> v3(0,0,1);
      gmtl::Vec<float,3> cross;

      // -- test performance
      const float iters(100000);
      CPPUNIT_METRIC_START_TIMING();

      for( float iter=0;iter<iters; ++iter)
      {
         gmtl::cross(cross, v2,v1);
         v1 *= 1.0025f;
         v3 += cross;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/CrossOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void VecTest::testLerp()
   {
      const float eps = 0.0001f;
      {
         gmtl::Vec<float, 2> q1( 2, 3 ), q2( 9.01f, 8.4f );
         gmtl::Vec<float, 2> expected_result1( q1 ), res1;
         gmtl::Vec<float, 2> expected_result2( q2 ), res2;

         gmtl::lerp( res1, 0.0f, q1, q2 );
         gmtl::lerp( res2, 1.0f, q1, q2 );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result1, res1, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result2, res2, eps ) );

         // test interpolated values...
         gmtl::Vec<float, 2> q3( 0, 0 ), q4( 1, 1 );
         gmtl::Vec<float, 2> expected_result3( 0.35f, 0.35f ), res3;
         gmtl::Vec<float, 2> expected_result4( 0.69f, 0.69f ), res4;

         gmtl::lerp( res3, 0.35f, q3, q4 );
         gmtl::lerp( res4, 0.69f, q3, q4 );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result3, res3, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result4, res4, eps ) );
      }
      {
         gmtl::Vec<float, 3> q1( 2, 3, 4 ), q2( 9.01f, 8.4f, 7.1f );
         gmtl::Vec<float, 3> expected_result1( q1 ), res1;
         gmtl::Vec<float, 3> expected_result2( q2 ), res2;

         gmtl::lerp( res1, 0.0f, q1, q2 );
         gmtl::lerp( res2, 1.0f, q1, q2 );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result1, res1, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result2, res2, eps ) );

         // test interpolated values...
         gmtl::Vec<float, 3> q3( 0, 0, 0 ), q4( 1, 1, 1 );
         gmtl::Vec<float, 3> expected_result3( 0.35f, 0.35f, 0.35f ), res3;
         gmtl::Vec<float, 3> expected_result4( 0.69f, 0.69f, 0.69f ), res4;

         gmtl::lerp( res3, 0.35f, q3, q4 );
         gmtl::lerp( res4, 0.69f, q3, q4 );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result3, res3, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result4, res4, eps ) );
      }
      {
         gmtl::Vec<float, 4> q1( 2, 3, 4, 5 ), q2( 9.01f, 8.4f, 7.1f, 10009 );
         gmtl::Vec<float, 4> expected_result1( q1 ), res1;
         gmtl::Vec<float, 4> expected_result2( q2 ), res2;

         gmtl::lerp( res1, 0.0f, q1, q2 );
         gmtl::lerp( res2, 1.0f, q1, q2 );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result1, res1, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result2, res2, eps ) );

         // test interpolated values...
         gmtl::Vec<float, 4> q3( 0, 0, 0, 0 ), q4( 1, 1, 1, 1 );
         gmtl::Vec<float, 4> expected_result3( 0.35f, 0.35f, 0.35f, 0.35f ), res3;
         gmtl::Vec<float, 4> expected_result4( 0.69f, 0.69f, 0.69f, 0.69f ), res4;

         gmtl::lerp( res3, 0.35f, q3, q4 );
         gmtl::lerp( res4, 0.69f, q3, q4 );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result3, res3, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result4, res4, eps ) );
      }
   }

   void VecMetricTest::testTimingLerp()
   {
      gmtl::Vec<float, 4> from, result;
      const long iters(10000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::lerp( result, ((float)iter) / ((float)iters), from, result );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecOpsTest/lerp()", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      // Make sure the compiler doesn't optimize out
      CPPUNIT_ASSERT( result[2] != 1234.5f );
   }

}

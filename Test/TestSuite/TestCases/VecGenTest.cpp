// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "VecGenTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <gmtl/Quat.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Generate.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(VecGenTest);
   CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(VecGenMetricTest, Suites::metric());

   //-- vec tests --//

   void VecGenTest::testMakeVecFromQuat()
   {
      gmtl::Quat<float> quat( 0.0f,21.0f,31.0f,1234.0f );
      gmtl::Vec<float, 3> vec( gmtl::makeVec( quat ) );
      CPPUNIT_ASSERT( vec[0] == 0.0f );
      CPPUNIT_ASSERT( vec[1] == 21.0f );
      CPPUNIT_ASSERT( vec[2] == 31.0f );
   }

   void VecGenTest::testMakeNormalVecFromVec()
   {
      {
         const float eps = 0.001f;
         const gmtl::Vec<float, 3> vec( 0.1f, 0.0f, 0.0f ), expected( 1, 0, 0 );
         gmtl::Vec<float, 3> result( gmtl::makeNormal( vec ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result, eps ) );
      }

      {
         const float eps = 0.001f;
         const gmtl::Vec<float, 3> vec( 0.1f, 128943139.0f, 0.0f ), expected( 0, 1, 0 );
         gmtl::Vec<float, 3> result( gmtl::makeNormal( vec ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result, eps ) );
      }

      {
         const float eps = 0.001f;
         const gmtl::Vec<float, 3> vec( 0.0f, 0.0f, 0.001f ), expected( 0, 0, 1 );
         gmtl::Vec<float, 3> result( gmtl::makeNormal( vec ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result, eps ) );
      }
   }

   template< typename T, unsigned ROWS, unsigned COLS >
   class RowTest
   {
   public:
      static void test()
      {
         // Create a matrix filled in linearly
         gmtl::Matrix<T, ROWS, COLS> mat;
         for (unsigned int i=0; i<(ROWS*COLS); ++i)
         {
            mat.mData[i] = T(i);
         }

         // Get each row and test it
         for (unsigned int i=0; i<ROWS; ++i)
         {
            gmtl::Vec<T, COLS> row = gmtl::makeRow(mat, i);
            // Test the row values
            for (unsigned int col=0; col<COLS; ++col)
            {
               CPPUNIT_ASSERT(unsigned(row[col]) == unsigned(col*ROWS + i));
            }
         }
      }
   };

   void VecGenTest::testMatrixRowAccess()
   {
      // Int
      RowTest<int, 2, 2>::test();
      RowTest<int, 2, 3>::test();
      RowTest<int, 2, 4>::test();
      RowTest<int, 3, 2>::test();
      RowTest<int, 3, 3>::test();
      RowTest<int, 3, 4>::test();
      RowTest<int, 4, 2>::test();
      RowTest<int, 4, 3>::test();
      RowTest<int, 4, 4>::test();
      // Float
      RowTest<float, 2, 2>::test();
      RowTest<float, 2, 3>::test();
      RowTest<float, 2, 4>::test();
      RowTest<float, 3, 2>::test();
      RowTest<float, 3, 3>::test();
      RowTest<float, 3, 4>::test();
      RowTest<float, 4, 2>::test();
      RowTest<float, 4, 3>::test();
      RowTest<float, 4, 4>::test();
   }

   template< typename T, unsigned ROWS, unsigned COLS >
   class ColumnTest
   {
   public:
      static void test()
      {
         // Create a matrix filled in linearly
         gmtl::Matrix<T, ROWS, COLS> mat;
         for (unsigned i=0; i<(unsigned)(ROWS*COLS); ++i)
         {
            mat.mData[i] = T(i);
         }

         // Get each column and test it
         for (unsigned i=0; i<unsigned(COLS); ++i)
         {
            gmtl::Vec<T, ROWS> col = gmtl::makeColumn(mat, i);
            // Test the row values
            for (unsigned row=0; row<unsigned(ROWS); ++row)
            {
               CPPUNIT_ASSERT(unsigned(col[row]) == unsigned(i*ROWS + row));
            }
         }
      }
   };

   void VecGenTest::testMatrixColumnAccess()
   {
      // Int
      ColumnTest<int, 2, 2>::test();
      ColumnTest<int, 2, 3>::test();
      ColumnTest<int, 2, 4>::test();
      ColumnTest<int, 3, 2>::test();
      ColumnTest<int, 3, 3>::test();
      ColumnTest<int, 3, 4>::test();
      ColumnTest<int, 4, 2>::test();
      ColumnTest<int, 4, 3>::test();
      ColumnTest<int, 4, 4>::test();
      // Float
      ColumnTest<float, 2, 2>::test();
      ColumnTest<float, 2, 3>::test();
      ColumnTest<float, 2, 4>::test();
      ColumnTest<float, 3, 2>::test();
      ColumnTest<float, 3, 3>::test();
      ColumnTest<float, 3, 4>::test();
      ColumnTest<float, 4, 2>::test();
      ColumnTest<float, 4, 3>::test();
      ColumnTest<float, 4, 4>::test();
   }


   //-- timing tests --//


   void VecGenMetricTest::testGenTimingMakeNormalVec1()
   {
      gmtl::Vec<double, 4> vec4d;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         vec4d = gmtl::makeNormal( vec4d );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "VecGenTest/makeNormal(vec4d)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( vec4d[0] != 10000.0f && vec4d[1] != 10000.0f && vec4d[2] != 10000.0f );
   }

   void VecGenMetricTest::testGenTimingMakeNormalVec2()
   {
      gmtl::Vec<float, 4> vec4f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         vec4f = gmtl::makeNormal( vec4f );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "VecGenTest/makeNormal(vec4f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( vec4f[0] != 10000.0f && vec4f[1] != 10000.0f && vec4f[2] != 10000.0f );
   }
   void VecGenMetricTest::testGenTimingMakeNormalVec3()
   {
      gmtl::Vec<double, 3> vec3d;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         vec3d = gmtl::makeNormal( vec3d );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "VecGenTest/makeNormal(vec3d)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( vec3d[0] != 10000.0f && vec3d[1] != 10000.0f && vec3d[2] != 10000.0f );
   }

   void VecGenMetricTest::testGenTimingMakeNormalVec4()
   {
      gmtl::Vec<float, 3> vec3f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         vec3f = gmtl::makeNormal( vec3f );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "VecGenTest/makeNormal(vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%


      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( vec3f[0] != 10000.0f && vec3f[1] != 10000.0f && vec3f[2] != 10000.0f );
   }

   void VecGenMetricTest::testGenTimingMakeVec()
   {
      gmtl::Quat<double> q1;
      gmtl::Vec<double, 3> v1;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter = 0; iter < iters; ++iter)
      {
         v1 = gmtl::makeVec( q1 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "VecGenTest/makeVec(quatd)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      gmtl::Quat<float> q2;
      gmtl::Vec<float, 3> v2;
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         v2 = gmtl::makeVec( q2 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "VecGenTest/makeVec(quatf)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( v2[0] != 10000.0f );
      CPPUNIT_ASSERT( v1[0] != 10000.0f );
   }
}

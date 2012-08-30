// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "MatrixCompareTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>

namespace gmtlTest
{
   template<typename T, int ROWS, int COLS>
   class testEqual
   {
   public:
      static void go()
      {
         CPPUNIT_ASSERT( ROWS <= 5 &&  COLS <= 5 );
         gmtl::Matrix<T, ROWS, COLS> mat1, mat2;
         T array[] = { (T)0.78, (T) 1.4,   (T) 2.9,  (T)3.45,
                       (T)4.21, (T)57.9,  (T) 65.9,  (T)74.6,
                       (T)89.2, (T)99.2,  (T) 10.9,  (T)11.9,
                       (T)12.5, (T)13.9,  (T)14.78,  (T)15.6,
                       (T)4.21, (T)57.9,  (T) 65.9,  (T)74.6,
                       (T)89.2, (T)99.2,  (T) 10.9,  (T)11.9,
                       (T)89.2, (T)99.2,  (T) 10.9,  (T)11.9 };
         mat1.set( array );
         mat1 = mat2;
         CPPUNIT_ASSERT( mat1 == mat2 );
         CPPUNIT_ASSERT( mat2 == mat1 );

         // Test that != works on all elements
         for (int i = 0; i < ROWS; ++i)
         {
            for (int j = 0; j < COLS; ++j)
            {
               mat2( i, j ) = (T)1221.0f;
               CPPUNIT_ASSERT(  (mat1 != mat2) );
               CPPUNIT_ASSERT( !(mat1 == mat2) );
               mat2( i, j ) = mat1( i, j ); // put it back
            }
         }

         // Test for epsilon equals working
         CPPUNIT_ASSERT( gmtl::isEqual( mat1, mat2 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( mat1, mat2, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( mat2, mat1, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( mat2, mat1, (T)100000.0f ) );
         T eps = (T)10.0;
         for (int i = 0; i < ROWS; ++i)
         {
            for (int j = 0; j < COLS; ++j)
            {
               mat2( i, j ) = mat1( i, j ) - (eps / (T)2.0);
               CPPUNIT_ASSERT(  gmtl::isEqual( mat1, mat2, eps ) );
               CPPUNIT_ASSERT( !gmtl::isEqual( mat1, mat2, (T)(eps / 3.0) ) );
               mat2( i, j ) = mat1( i, j ); // put it back
            }
         }
      }
   };

   void MatrixCompareTest::testMatEqualityFloatTest()
   {
      testEqual<float, 5, 5>::go();
      testEqual<float, 5, 4>::go();
      testEqual<float, 4, 5>::go();
      testEqual<float, 4, 4>::go();
      testEqual<float, 4, 3>::go();
      testEqual<float, 3, 4>::go();
      testEqual<float, 4, 3>::go();
      testEqual<float, 3, 3>::go();
      testEqual<float, 3, 2>::go();
      testEqual<float, 2, 3>::go();
      testEqual<float, 2, 2>::go();
      testEqual<float, 2, 1>::go();
      testEqual<float, 1, 2>::go();
      testEqual<float, 1, 1>::go();
   }

   void MatrixCompareTest::testMatEqualityDoubleTest()
   {
      testEqual<double, 5, 5>::go();
      testEqual<double, 5, 4>::go();
      testEqual<double, 4, 5>::go();
      testEqual<double, 4, 4>::go();
      testEqual<double, 4, 3>::go();
      testEqual<double, 3, 4>::go();
      testEqual<double, 4, 3>::go();
      testEqual<double, 3, 3>::go();
      testEqual<double, 3, 2>::go();
      testEqual<double, 2, 3>::go();
      testEqual<double, 2, 2>::go();
      testEqual<double, 2, 1>::go();
      testEqual<double, 1, 2>::go();
      testEqual<double, 1, 1>::go();
   }

   void MatrixCompareTest::testMatEqualityIntTest()
   {
      testEqual<int, 5, 5>::go();
      testEqual<int, 5, 4>::go();
      testEqual<int, 4, 5>::go();
      testEqual<int, 4, 4>::go();
      testEqual<int, 4, 3>::go();
      testEqual<int, 3, 4>::go();
      testEqual<int, 4, 3>::go();
      testEqual<int, 3, 3>::go();
      testEqual<int, 3, 2>::go();
      testEqual<int, 2, 3>::go();
      testEqual<int, 2, 2>::go();
      testEqual<int, 2, 1>::go();
      testEqual<int, 1, 2>::go();
      testEqual<int, 1, 1>::go();
   }

   void MatrixCompareMetricTest::testMatTimingOpEqualityTest()
   {
      // Test overhead of creation
      const long iters(25000);

      gmtl::Matrix<float, 1, 1> src_mat11;
      gmtl::Matrix<float, 2, 2> src_mat22;
      gmtl::Matrix<float, 3, 3> src_mat33;
      gmtl::Matrix<float, 3, 4> src_mat34;
      gmtl::Matrix<float, 4, 4> src_mat44;
      gmtl::Matrix<double, 10, 1> src_mat101;

      // half will be equal
      src_mat11.mData[0] = 1.0f;
      src_mat22.mData[0] = 1.0f;
      src_mat33.mData[4] = 2.0f;

      gmtl::Matrix<float, 1, 1> test_mat11( src_mat11 );
      gmtl::Matrix<float, 2, 2> test_mat22( src_mat22 );
      gmtl::Matrix<float, 3, 3> test_mat33( src_mat33 );
      gmtl::Matrix<float, 3, 4> test_mat34( src_mat34 );
      gmtl::Matrix<float, 4, 4> test_mat44( src_mat44 );
      gmtl::Matrix<double, 10, 1> test_mat101( src_mat101 );

      // half will be not equal
      src_mat34.mData[5] = 2.0f;
      src_mat44.mData[15] = 3.0f;
      src_mat101.mData[9] = 1.0f;

      unsigned true_count(0);

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         if (src_mat11 == test_mat11)
            ++true_count;
         if (src_mat22 == test_mat22)
            ++true_count;
         if (src_mat33 == test_mat33)
            ++true_count;
         if (src_mat34 == test_mat34)
            ++true_count;
         if (src_mat44 == test_mat44)
            ++true_count;
         if (src_mat101 == test_mat101)
            ++true_count;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixCompareTest/OpEqualityTest", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      // make sure compiler uses true_count
      CPPUNIT_ASSERT( true_count > 0 );
   }

   void MatrixCompareMetricTest::testMatTimingOpNotEqualityTest()
   {
      // Test overhead of creation
      const long iters(25000);

      gmtl::Matrix<float, 1, 1> src_mat11;
      gmtl::Matrix<float, 2, 2> src_mat22;
      gmtl::Matrix<float, 3, 3> src_mat33;
      gmtl::Matrix<float, 3, 4> src_mat34;
      gmtl::Matrix<float, 4, 4> src_mat44;
      gmtl::Matrix<double, 10, 1> src_mat101;

      // half will be equal
      src_mat11.mData[0] = 1.0f;
      src_mat22.mData[0] = 1.0f;
      src_mat33.mData[4] = 2.0f;

      gmtl::Matrix<float, 1, 1> test_mat11( src_mat11 );
      gmtl::Matrix<float, 2, 2> test_mat22( src_mat22 );
      gmtl::Matrix<float, 3, 3> test_mat33( src_mat33 );
      gmtl::Matrix<float, 3, 4> test_mat34( src_mat34 );
      gmtl::Matrix<float, 4, 4> test_mat44( src_mat44 );
      gmtl::Matrix<double, 10, 1> test_mat101( src_mat101 );

      // half will be not equal
      src_mat34.mData[5] = 2.0f;
      src_mat44.mData[15] = 3.0f;
      src_mat101.mData[9] = 1.0f;

      unsigned true_count(0);

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         if (src_mat11 != test_mat11)
            ++true_count;
         if (src_mat22 != test_mat22)
            ++true_count;
         if (src_mat33 != test_mat33)
            ++true_count;
         if (src_mat34 != test_mat34)
            ++true_count;
         if (src_mat44 != test_mat44)
            ++true_count;
         if (src_mat101 != test_mat101)
            ++true_count;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixCompareTest/OpNotEqualityTest", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      // make sure compiler uses true_count
      CPPUNIT_ASSERT( true_count > 0 );
   }

   void MatrixCompareMetricTest::testMatTimingIsEqualTest()
   {
      // Test overhead of creation
      const long iters(25000);

      gmtl::Matrix<float, 1, 1> src_mat11;
      gmtl::Matrix<float, 2, 2> src_mat22;
      gmtl::Matrix<float, 3, 3> src_mat33;
      gmtl::Matrix<float, 3, 4> src_mat34;
      gmtl::Matrix<float, 4, 4> src_mat44;
      gmtl::Matrix<double, 10, 1> src_mat101;

      // half will be equal
      src_mat11.mData[0] = 1.0f;
      src_mat22.mData[0] = 1.0f;
      src_mat33.mData[4] = 2.0f;

      gmtl::Matrix<float, 1, 1> test_mat11( src_mat11 );
      gmtl::Matrix<float, 2, 2> test_mat22( src_mat22 );
      gmtl::Matrix<float, 3, 3> test_mat33( src_mat33 );
      gmtl::Matrix<float, 3, 4> test_mat34( src_mat34 );
      gmtl::Matrix<float, 4, 4> test_mat44( src_mat44 );
      gmtl::Matrix<double, 10, 1> test_mat101( src_mat101 );

      // half will be not equal
      src_mat34.mData[5] = 2.0f;
      src_mat44.mData[15] = 3.0f;
      src_mat101.mData[9] = 1.0f;

      unsigned true_count(0);

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         if (gmtl::isEqual( src_mat11,  test_mat11, 0.0f ))
            ++true_count;
         if (gmtl::isEqual( src_mat22,  test_mat22, 0.2f ))
            ++true_count;
         if (gmtl::isEqual( src_mat33,  test_mat33, 0.3f ))
            ++true_count;
         if (gmtl::isEqual( src_mat34,  test_mat34, 0.6f ))
            ++true_count;
         if (gmtl::isEqual( src_mat44,  test_mat44, 0.8f ))
            ++true_count;
         if (gmtl::isEqual( src_mat101, test_mat101, double(111.1) ))
            ++true_count;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixCompareTest/IsEqualTest", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      // make sure compiler uses true_count
      CPPUNIT_ASSERT( true_count > 0 );
   }
}

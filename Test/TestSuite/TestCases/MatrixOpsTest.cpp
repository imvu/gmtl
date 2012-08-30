// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "MatrixOpsTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Math.h>
#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Output.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(MatrixOpsTest);
   CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(MatrixOpsMetricTest, Suites::metric());

   void MatrixOpsTest::testMatrixIdentity()
   {
      {
         gmtl::Matrix44f test_mat, ident_mat;
         test_mat.set( 0, 1, 2, 3,
                       0, 1, 2, 3,
                       0, 1, 2, 3,
                       0, 1, 2, 3);
         CPPUNIT_ASSERT(test_mat != ident_mat);
         gmtl::identity(test_mat);
         CPPUNIT_ASSERT(test_mat == ident_mat);
      }
   }

   void MatrixOpsMetricTest::testMatrixTimeIdentity44f()
   {
      gmtl::Matrix44f test_mat;
      float bogus_value(0.0f);

      const long iters(50000);
      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         test_mat.set( 0, (float)iter+1, (float)iter+2, (float)iter+3,
                       0, 1, 2, 3,
                       0, 1, 2, 3,
                       0, 1, 2, 3);
         gmtl::identity( test_mat );
         bogus_value += test_mat(1,1); // Should add 1 everytime
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/identity(mat44f)", iters, 0.095f, 0.125f);   // warn at 9.5%, error at 12.5%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT_DOUBLES_EQUAL( bogus_value, iters, 0.5f);
   }

   void MatrixOpsTest::testMatrixSetTrans()
   {
      float eps = 0.01f;

      // 3D trans
      {
         gmtl::Matrix34f mat34, expected_result34;
         gmtl::setRot( expected_result34, gmtl::EulerAngleXYZf( 0.5f, 1.0f, -1.0f ) );
         expected_result34(0,3) = 21;
         expected_result34(1,3) = 22;
         expected_result34(2,3) = 23;

         gmtl::setRot(mat34, gmtl::EulerAngleXYZf( 0.5f, 1.0f, -1.0f ) );
         gmtl::setTrans( mat34, gmtl::Vec3f( 21, 22, 23 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat34, eps ) );
      }
      // 3D rot/trans set by homogeneous vector
      {
         gmtl::Matrix34f mat34, expected_result34;
         gmtl::setRot(expected_result34, gmtl::EulerAngleXYZf( 0.5f, 1.0f, -1.0f ) );
         expected_result34(0,3) = 42;
         expected_result34(1,3) = 44;
         expected_result34(2,3) = 46;

         gmtl::setRot(mat34, gmtl::EulerAngleXYZf( 0.5f, 1.0f, -1.0f ) );
         gmtl::setTrans( mat34, gmtl::Vec4f( 21, 22, 23, 0.5f ) );

         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat34, eps ) );
      }
      // 3D trans
      {
         gmtl::Matrix44f mat44, expected_result44;
         gmtl::setRot(expected_result44, gmtl::EulerAngleXYZf( 0.5f, 1.0f, -1.0f ) );
         expected_result44(0,3) = 21;
         expected_result44(1,3) = 22;
         expected_result44(2,3) = 23;

         gmtl::setRot( mat44, gmtl::EulerAngleXYZf( 0.5f, 1.0f, -1.0f ) );
         gmtl::setTrans( mat44, gmtl::Vec3f( 21.0f, 22.0f, 23.0f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat44, eps ) );
      }
      // 3D rot/trans/skew set by homogeneous vector...
      {
         gmtl::Matrix44f mat44, expected_result44;

         gmtl::setRot(expected_result44, gmtl::EulerAngleXYZf( 0.5f, 1.0f, -1.0f ) );
         expected_result44(0,3) = 42;
         expected_result44(1,3) = 44;
         expected_result44(2,3) = 46;

         gmtl::setRot( mat44, gmtl::EulerAngleXYZf( 0.5f, 1.0f, -1.0f ) );
         gmtl::setTrans( mat44, gmtl::Vec4f( 21, 22, 23, 0.5f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat44, eps ) );
      }
   }

   void MatrixOpsMetricTest::testTimingMakeTrans()
   {
      gmtl::Matrix33f mat33;
      gmtl::Matrix34f mat34;
      gmtl::Matrix44f mat44;
      float a = 1.0f;

      const long iters(100000);

      // 2D translation
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setTrans( mat33, gmtl::Vec2f( a, 2 ) );
         a += mat33.mData[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/setTrans(mat33f,vec2f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat33.mData[3] != 1234.0456f && a != 987654.321f  );


      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setTrans( mat33, gmtl::Vec3f( 1, a, 1.0f ) ); // homogeneous
         a += mat33.mData[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/setTrans(mat33f,vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat33.mData[3] != 1234.0456f && a != 987654.321f  );


      // 3D translation
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setTrans( mat34, gmtl::Vec3f( a, 32, 121 ) );
         a += mat34.mData[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/setTrans(mat34f,vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat34.mData[3] != 1234.0456f && a != 987654.321f  );


      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setTrans( mat44, gmtl::Vec3f( 30, a, 121 ) );
         a += mat44.mData[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/setTrans(mat44f,vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat44.mData[3] != 1234.0456f && a != 987654.321f  );


      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setTrans( mat44, gmtl::Vec4f( 30, 32, a, 1.0f ) ); // homogeneous
         a += mat44.mData[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/setTrans(mat44f,vec4f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat44.mData[3] != 1234.0456f && a != 987654.321f  );
   }


   void MatrixOpsMetricTest::testMatrixTimeTranspose44f()
   {
      gmtl::Matrix<float, 4, 4> test_mat1;
      test_mat1.set( 0,  1,  2,  3,
                     4,  5,  6,  7,
                     8,  9, 10, 11,
                    12, 13, 14, 15 );

      const long iters(50000);
      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::transpose( test_mat1 );
         test_mat1.mData[2] += test_mat1.mData[3];
         test_mat1.mData[3] -= test_mat1.mData[1];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/transpose(mat44f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( test_mat1.mData[2] != test_mat1.mData[0] );
   }


   void MatrixOpsMetricTest::testMatrixTimeTranspose33d()
   {
      gmtl::Matrix<double, 3, 3> test_mat2;
      test_mat2.set( 0,  1,  2,
                    4,  5,  6,
                    8,  9,  10 );

      const long iters(50000);
      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::transpose( test_mat2 );
         test_mat2.mData[2] += test_mat2.mData[3];
         test_mat2.mData[3] -= test_mat2.mData[1];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/transpose(mat33d)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( test_mat2.mData[2] != test_mat2.mData[0] );
   }

   void MatrixOpsMetricTest::testMatrixTimeMult44_mult()
   {
      gmtl::Matrix<float, 4, 4> test_mat1, test_mat2, res_mat;
      test_mat1.set( 0,  1,  2,  3,
                     4,  5,  6,  7,
                     8,  9, 10, 11,
                    12, 13, 14, 15 );
      res_mat = test_mat2 = test_mat1;

      const long iters(50000);
      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::mult( res_mat, res_mat, test_mat1 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/mult(res,mat44f,mat44f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( test_mat1.mData[2] != test_mat2.mData[0] );
      CPPUNIT_ASSERT( res_mat.mData[2] != 1000.0f );
   }

   void MatrixOpsMetricTest::testMatrixTimeMult44_operatorStar()
   {
      gmtl::Matrix<float, 4, 4> test_mat1, test_mat2, res_mat;
      test_mat1.set( 0,  1,  2,  3,
                     4,  5,  6,  7,
                     8,  9, 10, 11,
                    12, 13, 14, 15 );
      res_mat = test_mat2 = test_mat1;

      const long iters(50000);
      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         res_mat = test_mat1 * res_mat;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/operator*(mat44f,mat44f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( test_mat1.mData[2] != test_mat2.mData[0] );
      CPPUNIT_ASSERT( res_mat.mData[2] != 1000.0f );
   }

   void MatrixOpsMetricTest::testMatrixTimeMult44f_operatorStarStar()
   {
      gmtl::Matrix<float, 4, 4> test_mat1, test_mat2, res_mat;
      test_mat1.set( 0,  1,  2,  3,
                     4,  5,  6,  7,
                     8,  9, 10, 11,
                    12, 13, 14, 15 );
      res_mat = test_mat2 = test_mat1;

      const long iters(5000);
      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         res_mat = test_mat1 * res_mat * test_mat2;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/mat44f*mat44f*mat44f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( test_mat1.mData[2] != test_mat2.mData[0] );
      CPPUNIT_ASSERT( res_mat.mData[2] != 1000.0f );
   }

   void MatrixOpsMetricTest::testMatrixTimeMult44d_operatorStarStar()
   {
      gmtl::Matrix<double, 4, 4> test_mat1, test_mat2, res_mat;
      test_mat1.set( 0,  1,  2,  3,
                     4,  5,  6,  7,
                     8,  9, 10, 11,
                    12, 13, 14, 15 );
      res_mat = test_mat2 = test_mat1;

      const long iters(5000);
      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         res_mat = test_mat1 * res_mat * test_mat2;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/mat44d*mat44d*mat44d", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( test_mat1.mData[2] != test_mat2.mData[0] );
      CPPUNIT_ASSERT( res_mat.mData[2] != 1000.0f );
   }

   void MatrixOpsMetricTest::testMatrixTimeMult33f_operatorStarStar()
   {
      gmtl::Matrix<float, 3, 3> test_mat1, test_mat2, res_mat;
      test_mat1.set( 0,  1,  2,
                     4,  5,  6,
                     8,  9, 10 );
      res_mat = test_mat2 = test_mat1;

      const long iters(50000);
      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         res_mat = test_mat1 * res_mat * test_mat2;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/mat33f*mat33f*mat33f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( test_mat1.mData[2] != test_mat2.mData[0] );
      CPPUNIT_ASSERT( res_mat.mData[2] != 1000.0f );
   }

   void MatrixOpsMetricTest::testMatrixTimeMult33d_operatorStarStar()
   {
      gmtl::Matrix<double, 3, 3> test_mat1, test_mat2, res_mat;
      test_mat1.set( 0,  1,  2,
                     4,  5,  6,
                     8,  9, 10 );
      res_mat = test_mat2 = test_mat1;

      const long iters(50000);
      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         res_mat = test_mat1 * res_mat * test_mat2;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/mat33d*mat33d*mat33d", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( test_mat1.mData[2] != test_mat2.mData[0] );
      CPPUNIT_ASSERT( res_mat.mData[2] != 1000.0f );
   }


   void MatrixOpsMetricTest::testMatrixTimeAdd44()
   {
      gmtl::Matrix<float, 4, 4> test_mat1, test_mat2, res_mat;
      test_mat1.set( 0,  1,  2,  3,
                     4,  5,  6,  7,
                     8,  9, 10, 11,
                    12, 13, 14, 15 );
      res_mat = test_mat2 = test_mat1;

      const long iters(50000);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::add( res_mat, res_mat, test_mat2 );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/add(res,mat44f,mat44f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( res_mat.mData[2] != 1000.0f );
   }


   void MatrixOpsMetricTest::testMatrixTimeSub44()
   {
      gmtl::Matrix<float, 4, 4> test_mat1, test_mat2, res_mat;
      test_mat1.set( 0,  1,  2,  3,
                     4,  5,  6,  7,
                     8,  9, 10, 11,
                    12, 13, 14, 15 );
      res_mat = test_mat2 = test_mat1;

      const long iters(50000);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::sub( res_mat, test_mat1, res_mat );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/sub(res,mat44f,mat44f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( res_mat.mData[2] != 1000.0f );
   }



   ///////////////////////////////////////////////////
   // op tests:



   template<typename T, int SIZE, bool TEST>
   class transposeTest
   {
   public:
      static void go()
      {
         gmtl::Matrix<T, SIZE, SIZE> test_mat, res_mat;
         test_mat( SIZE - 1, 0 ) = 9;
         res_mat( 0, SIZE - 1 ) = 9;
         test_mat( 1, 0 ) = 2;
         res_mat( 0, 1 ) = 2;
         gmtl::transpose( res_mat );
         if (TEST == true)
         { CPPUNIT_ASSERT( res_mat == test_mat ); }
         gmtl::transpose( res_mat );

         // test the other transpose op
         gmtl::transpose( res_mat, res_mat );
         if (TEST == true)
         { CPPUNIT_ASSERT( res_mat == test_mat ); }
      }
   };

   void MatrixOpsTest::testMatrixTranspose()
   {
      // this can use transposeTest::go() if we
      // can figure out how to generically pass in init values.
      {
         gmtl::Matrix<float, 2, 2> test_mat, res_mat;
         test_mat.set( 0,  1,
                       4,  5 );
         res_mat.set( 0,   4,
                      1,   5 );
         gmtl::transpose( res_mat );
         CPPUNIT_ASSERT( res_mat == test_mat );
         gmtl::transpose( res_mat );

         // test the other transpose op
         gmtl::transpose( res_mat, res_mat );
         CPPUNIT_ASSERT( res_mat == test_mat );
      }

      {
         gmtl::Matrix<float, 3, 3> test_mat, res_mat;
         test_mat.set( 0,  1,  2,
                       4,  5,  6,
                       8,  9,  10 );
         res_mat.set( 0,   4,   8,
                      1,   5,   9,
                      2,   6,  10 );
         gmtl::transpose( res_mat );
         CPPUNIT_ASSERT( res_mat == test_mat );
         gmtl::transpose( res_mat );

         // test the other transpose op
         gmtl::transpose( res_mat, res_mat );
         CPPUNIT_ASSERT( res_mat == test_mat );
      }
      {
         gmtl::Matrix<float, 4, 4> test_mat, res_mat;
         test_mat.set( 0,  1,  2,  3,
                       4,  5,  6,  7,
                       8,  9,  10, 11,
                       12, 13, 14, 15 );
         res_mat.set( 0,   4,   8,  12,
                      1,   5,   9,  13,
                      2,   6,  10,  14,
                      3,   7,  11,  15 );
         gmtl::transpose( res_mat );
         CPPUNIT_ASSERT( res_mat == test_mat );
         gmtl::transpose( res_mat );

         // test the other transpose op
         gmtl::transpose( res_mat, res_mat );
         CPPUNIT_ASSERT( res_mat == test_mat );
      }

      transposeTest<float, 2, true>::go();
      transposeTest<float, 3, true>::go();
      transposeTest<float, 4, true>::go();
      transposeTest<float, 5, true>::go();
      transposeTest<float, 6, true>::go();
      transposeTest<float, 7, true>::go();
      transposeTest<float, 8, true>::go();
      transposeTest<float, 9, true>::go();
      transposeTest<float, 10, true>::go();
      transposeTest<double, 2, true>::go();
      transposeTest<double, 3, true>::go();
      transposeTest<double, 4, true>::go();
      transposeTest<double, 5, true>::go();
      transposeTest<double, 6, true>::go();
      transposeTest<double, 7, true>::go();
      transposeTest<double, 8, true>::go();
      transposeTest<double, 9, true>::go();
      transposeTest<double, 10, true>::go();

      // test the case where we convert between different degrees (3x4 to 4x3)
      {
         gmtl::Matrix<float, 4, 3> source_mat;
         gmtl::Matrix<float, 3, 4> result_mat, expected_answer;
         float v1[] = { 0,  4,  8,
                        1,  5,  9,
                        2,  6,  10,
                        3,  7,  11 };
         source_mat.setTranspose( v1 );
         float v2[] = { 0,  1,  2, 3,
                        4,  5,  6, 7,
                        8,  9,  10, 11 };
         expected_answer.setTranspose( v2 );
         gmtl::transpose( result_mat, source_mat );
         CPPUNIT_ASSERT( result_mat == expected_answer );
      }
      {
         gmtl::Matrix<float, 3, 4> source_mat;
         gmtl::Matrix<float, 4, 3> result_mat, expected_answer;
         float v1[] = { 0,  1,  2, 3,
                        4,  5,  6, 7,
                        8,  9,  10, 11 };
         source_mat.setTranspose( v1 );
         float v2[] = { 0,  4,  8,
                        1,  5,  9,
                        2,  6,  10,
                        3,  7,  11 };
         expected_answer.setTranspose( v2 );
         gmtl::transpose( result_mat, source_mat );
         CPPUNIT_ASSERT( result_mat == expected_answer );
      }
   }


   template <typename DATA_TYPE>
   class matrixAddSub
   {
   public:
      static void go()
      {
         {
            gmtl::Matrix<DATA_TYPE, 2, 2> test_mat1, test_mat2, res_mat, ans_mat;
            test_mat1.set( 0,  1,
                           4,  5 );
            test_mat2 = test_mat1;
            ans_mat.set( 0,  2,
                         8, 10  );
            gmtl::add( res_mat, test_mat1, test_mat2 );    // rm = m1 + m2
            CPPUNIT_ASSERT(res_mat == ans_mat);


            gmtl::Matrix<DATA_TYPE, 2, 2> diff_mat;
            gmtl::sub( diff_mat, res_mat, test_mat1 );    // rm = m1 - m2
            CPPUNIT_ASSERT(diff_mat != res_mat);
            CPPUNIT_ASSERT(diff_mat == test_mat2);
         }
         {
            gmtl::Matrix<DATA_TYPE, 3, 3> test_mat1, test_mat2, res_mat, ans_mat;
            test_mat1.set( 0,  1,  2,
                           4,  5,  6,
                           8,  9, 10 );
            test_mat2 = test_mat1;
            ans_mat.set( 0,  2,  4,
                         8, 10, 12,
                        16, 18, 20 );
            gmtl::add( res_mat, test_mat1, test_mat2 );    // rm = m1 + m2
            CPPUNIT_ASSERT(res_mat == ans_mat);


            gmtl::Matrix<DATA_TYPE, 3, 3> diff_mat;
            gmtl::sub( diff_mat, res_mat, test_mat1 );    // rm = m1 - m2
            CPPUNIT_ASSERT(diff_mat != res_mat);
            CPPUNIT_ASSERT(diff_mat == test_mat2);
         }
         {
            gmtl::Matrix<DATA_TYPE, 3, 4> test_mat1, test_mat2, res_mat, ans_mat;
            test_mat1.set( 0,  1,  2,  3,
                           4,  5,  6,  7,
                           8,  9, 10, 11 );
            test_mat2 = test_mat1;
            ans_mat.set( 0,  2,  4,  6,
                         8, 10, 12, 14,
                        16, 18, 20, 22 );
            gmtl::add( res_mat, test_mat1, test_mat2 );    // rm = m1 + m2
            CPPUNIT_ASSERT(res_mat == ans_mat);


            gmtl::Matrix<DATA_TYPE, 3, 4> diff_mat;
            gmtl::sub( diff_mat, res_mat, test_mat1 );    // rm = m1 - m2
            CPPUNIT_ASSERT(diff_mat != res_mat);
            CPPUNIT_ASSERT(diff_mat == test_mat2);
         }
         {
            gmtl::Matrix<DATA_TYPE, 4, 3> test_mat1, test_mat2, res_mat, ans_mat;
            DATA_TYPE v1[] = { 0,  1,  2,
                               4,  5,  6,
                               8,  9, 10,
                              12, 13, 14 };
            test_mat1.setTranspose( v1 );
            test_mat2 = test_mat1;
            DATA_TYPE v2[] = { 0,  2,  4,
                               8, 10, 12,
                              16, 18, 20,
                              24, 26, 28 };
            ans_mat.setTranspose( v2 );
            gmtl::add( res_mat, test_mat1, test_mat2 );    // rm = m1 + m2
            CPPUNIT_ASSERT(res_mat == ans_mat);


            gmtl::Matrix<DATA_TYPE, 4, 3> diff_mat;
            gmtl::sub( diff_mat, res_mat, test_mat1 );    // rm = m1 - m2
            CPPUNIT_ASSERT(diff_mat != res_mat);
            CPPUNIT_ASSERT(diff_mat == test_mat2);
         }
         {
            gmtl::Matrix<DATA_TYPE, 4, 4> test_mat1, test_mat2, res_mat, ans_mat;
            test_mat1.set( 0,  1,  2,  3,
                           4,  5,  6,  7,
                           8,  9, 10, 11,
                          12, 13, 14, 15 );
            test_mat2 = test_mat1;
            ans_mat.set( 0,  2,  4,  6,
                         8, 10, 12, 14,
                        16, 18, 20, 22,
                        24, 26, 28, 30 );
            gmtl::add( res_mat, test_mat1, test_mat2 );    // rm = m1 + m2
            CPPUNIT_ASSERT(res_mat == ans_mat);


            gmtl::Matrix<DATA_TYPE, 4, 4> diff_mat;
            gmtl::sub( diff_mat, res_mat, test_mat1 );    // rm = m1 - m2
            CPPUNIT_ASSERT(diff_mat != res_mat);
            CPPUNIT_ASSERT(diff_mat == test_mat2);
         }
      }
   };

   void MatrixOpsTest::testMatrixAddSub()
   {
      matrixAddSub<float>::go();
      matrixAddSub<double>::go();
      matrixAddSub<int>::go();
      matrixAddSub<short>::go();
      matrixAddSub<char>::go();
   }


   template <typename T>
   class matrixMult33
   {
   public:
      static void go()
      {
         gmtl::Matrix<T, 3, 3> mat1, mat2, mat3, res_mat;

         T eps = (T)0.001;

         mat1.set((T) 1.1000, (T)2.2000,  (T) 3.3000,
                  (T) 5.5000, (T)6.6000,  (T) 7.7000,
                  (T) 9.9000, (T)10.1000, (T)11.1100 );
         mat2.set((T) 43,  (T) -8,  (T) -4,
                  (T) 23,  (T) 22,  (T) 72,
                  (T)-34,  (T)-23,  (T) 99 );

         // make sure mat3 = mat1 * mat2 yields the correct result
         gmtl::mult( mat3, mat1, mat2 );
         res_mat.set( (T)-14.300,   (T) -36.300,   (T) 480.700,
                      (T)126.500,   (T) -75.900,   (T)1215.500,
                      (T)280.260,   (T)-112.530,   (T)1787.490 );
         CPPUNIT_ASSERT( gmtl::isEqual( res_mat, mat3, eps ) );

         // test post and pre mult operators...
         {
            gmtl::Matrix<T, 3, 3> m1( mat1 );
            const gmtl::Matrix<T, 3, 3> m2( mat2 );
            gmtl::postMult( m1, m2 );
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m1, eps ) );
         }
         {
            gmtl::Matrix<T, 3, 3> m1( mat1 );
            const gmtl::Matrix<T, 3, 3> m2( mat2 );
            m1 *= m2;
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m1, eps ) );
         }
         {
            const gmtl::Matrix<T, 3, 3> m1( mat1 );
            gmtl::Matrix<T, 3, 3> m2( mat2 );
            gmtl::preMult( m2, m1 );
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m2, eps ) );
         }
         {
            gmtl::Matrix<T, 3, 3> result;
            result = mat1 * mat2;
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, result, eps ) );
         }

         // make sure mult is not commutitive
         gmtl::mult( mat3, mat2, mat1 );
         CPPUNIT_ASSERT( !gmtl::isEqual( res_mat, mat3, eps ) );

         // make sure mat3 = mat2 * mat1 yields the correct result
         res_mat.set((T)-36.3000,    (T)  1.4000,   (T)  35.8600,
                     (T)859.1000,    (T)923.0000,   (T)1045.2200,
                     (T)816.2000,    (T)773.3000,   (T) 810.5900 );
         CPPUNIT_ASSERT( gmtl::isEqual( res_mat, mat3, eps ) );

         // test post and pre mult operators...
         {
            const gmtl::Matrix<T, 3, 3> m1( mat1 );
            gmtl::Matrix<T, 3, 3> m2( mat2 );
            gmtl::postMult( m2, m1 );
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m2, eps ) );
         }
         {
            const gmtl::Matrix<T, 3, 3> m1( mat1 );
            gmtl::Matrix<T, 3, 3> m2( mat2 );
            m2 *=m1;
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m2, eps ) );
         }
         {
            gmtl::Matrix<T, 3, 3> m1( mat1 );
            const gmtl::Matrix<T, 3, 3> m2( mat2 );
            gmtl::preMult( m1, m2 );
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m1, eps ) );
         }
         {
            gmtl::Matrix<T, 3, 3> result;
            result = mat2 * mat1;
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, result, eps ) );
         }
      }
   };

   template <typename T>
   class matrixMultUnlike
   {
   public:
      static void go()
      {
         gmtl::Matrix<T, 3, 4> lhs34;
         gmtl::Matrix<T, 4, 3> rhs43;
         gmtl::Matrix<T, 4, 4> res44, expected_answer44;
         gmtl::Matrix<T, 3, 3> res33, expected_answer33;


         T eps = (T)0.01;

         T v1[] = { (T)1.1000, (T)2.2000, (T)3.3000, (T)4.4000,
                    (T)5.5000, (T)6.6000, (T)7.7000, (T)8.8000,
                    (T)9.9000, (T)10.1000, (T)11.1100, (T)12.1200 };
         lhs34.setTranspose( v1 );
         T v2[] = { (T)13.100, (T)14.200, (T)15.300,
                    (T)16.400, (T)17.500, (T)18.600,
                    (T)19.700, (T)20.800, (T)21.900,
                    (T)22.100, (T)23.110, (T)24.120  };
         rhs43.setTranspose( v2 );

         // make sure mat3 = mat2 * mat1 yields the correct result
         T v3[] = {  (T)243.98, (T)277.07, (T)322.55, (T)368.04,
                     (T)298.43, (T)339.44, (T)395.52, (T)451.59,
                     (T)352.88, (T)401.81, (T)468.48, (T)535.15,
                     (T)390.20, (T)444.76, (T)518.85, (T)592.94  };
         expected_answer44.setTranspose( v3 );
         gmtl::mult( res44, rhs43, lhs34 );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_answer44, res44, eps ) );
         {
            gmtl::Matrix<T, 4, 4> result;
            result = rhs43 * lhs34;
            CPPUNIT_ASSERT( gmtl::isEqual( expected_answer44, result, eps ) );
         }

         // make sure mat3 = mat1 * mat2 yields the correct result
         T v4[] = {  (T)212.74,  (T)224.44,  (T)236.15,
                     (T)526.46,  (T)557.13,  (T)587.80,
                     (T)782.05,  (T)828.51,  (T)874.97   };
         expected_answer33.setTranspose( v4 );
         gmtl::mult( res33, lhs34, rhs43 );
         CPPUNIT_ASSERT( gmtl::isEqual( res33, expected_answer33, eps ) );
         {
            gmtl::Matrix<T, 3, 3> result;
            result = lhs34 * rhs43;
            CPPUNIT_ASSERT( gmtl::isEqual( expected_answer33, result, eps ) );
         }


         gmtl::Matrix<T, 5, 3> lhs53;
         gmtl::Matrix<T, 5, 4> res54, expected_answer54;
         T v5[] = { (T)13.100, (T)14.200, (T)15.300,
                    (T)16.400, (T)17.500, (T)18.600,
                    (T)19.700, (T)20.800, (T)21.900,
                    (T)22.100, (T)23.110, (T)24.120,
                    (T)25.000, (T)26.000, (T)27.000  };
         lhs53.setTranspose( v5 );
         gmtl::mult( res54, lhs53, lhs34 );
         T v6[] = { (T)243.98, (T)277.07, (T)322.55, (T)368.04, (T)298.43,
                    (T)339.44, (T)395.52, (T)451.59, (T)352.88, (T)401.81,
                    (T)468.48, (T)535.15, (T)390.20, (T)444.76, (T)518.85,
                    (T)592.94, (T)437.80, (T)499.30, (T)582.67, (T)666.04  };
         expected_answer54.setTranspose( v6 );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_answer54, res54, eps ) );
         {
            gmtl::Matrix<T, 5, 4> result;
            result = lhs53 * lhs34;
            CPPUNIT_ASSERT( gmtl::isEqual( expected_answer54, result, eps ) );
         }
      }
   };

   template <typename T>
   class matrixMult44
   {
   public:
      static void go()
      {
         gmtl::Matrix<T, 4, 4> mat1, mat2, mat3, res_mat;

         T eps = (T)0.001;

         mat1.set((T) 1.1000, (T)2.2000,  (T) 3.3000, (T) 4.4000,
                  (T) 5.5000, (T)6.6000,  (T) 7.7000, (T) 8.8000,
                  (T) 9.9000, (T)10.1000, (T)11.1100, (T)12.1200,
                  (T)13.1300, (T)14.1400, (T)15.1500, (T)16.1600 );
         mat2.set((T) 43,  (T) -8,  (T) -4, (T)   7,
                  (T) 23,  (T) 22,  (T) 72, (T)  69,
                  (T)-34,  (T)-23,  (T) 99, (T) -48,
                  (T) 12,  (T) 16,  (T) 21, (T)  18);

         // make sure mat3 = mat1 * mat2 yields the correct result
         gmtl::mult( mat3, mat1, mat2 );
         res_mat.set((T) 38.500,   (T) 34.100,  (T) 573.100,   (T) 80.300,
                     (T)232.100,   (T) 64.900,  (T)1400.300,   (T)282.700,
                     (T)425.700,   (T) 81.390,  (T)2042.010,   (T)451.080,
                     (T)568.630,   (T)116.150,  (T)2804.770,   (T)631.250 );
         CPPUNIT_ASSERT( gmtl::isEqual( res_mat, mat3, eps ) );

         // test post and pre mult operators...
         {
            gmtl::Matrix<T, 4, 4> m1( mat1 );
            const gmtl::Matrix<T, 4, 4> m2( mat2 );
            gmtl::postMult( m1, m2 );
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m1, eps ) );
         }
         {
            gmtl::Matrix<T, 4, 4> m1( mat1 );
            const gmtl::Matrix<T, 4, 4> m2( mat2 );
            m1 *= m2;
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m1, eps ) );
         }
         {
            const gmtl::Matrix<T, 4, 4> m1( mat1 );
            gmtl::Matrix<T, 4, 4> m2( mat2 );
            gmtl::preMult( m2, m1 );
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m2, eps ) );
         }
         {
            gmtl::Matrix<T, 4, 4> result;
            result = mat1 * mat2;
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, result, eps ) );
         }

         // make sure mult is not commutitive
         gmtl::mult( mat3, mat2, mat1 );
         CPPUNIT_ASSERT( !gmtl::isEqual( res_mat, mat3, eps ) );

         // make sure mat3 = mat2 * mat1 yields the correct result
         res_mat.set(  (T)55.610,   (T)100.380,   (T)141.910,   (T)183.440,
                     (T)1765.070,  (T)1898.660,  (T)2090.570,  (T)2282.480,
                      (T)185.960,    (T)94.580,    (T)83.390,    (T)72.200,
                      (T)545.440,   (T)598.620,   (T)668.810,   (T)739.000 );
         CPPUNIT_ASSERT( gmtl::isEqual( res_mat, mat3, eps ) );

         // test post and pre mult operators...
         {
            const gmtl::Matrix<T, 4, 4> m1( mat1 );
            gmtl::Matrix<T, 4, 4> m2( mat2 );
            gmtl::postMult( m2, m1 );
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m2, eps ) );
         }
         {
            const gmtl::Matrix<T, 4, 4> m1( mat1 );
            gmtl::Matrix<T, 4, 4> m2( mat2 );
            m2 *= m1;
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m2, eps ) );
         }
         {
            gmtl::Matrix<T, 4, 4> m1( mat1 );
            const gmtl::Matrix<T, 4, 4> m2( mat2 );
            gmtl::preMult( m1, m2 );
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m1, eps ) );
         }
         {
            gmtl::Matrix<T, 4, 4> result;
            result = mat2 * mat1;
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, result, eps ) );
         }
      }
   };

   void MatrixOpsTest::testMatrixMult()
   {
      matrixMult33<float>::go();
      matrixMult33<double>::go();
      matrixMult44<float>::go();
      matrixMult44<double>::go();
      matrixMultUnlike<float>::go();
      matrixMultUnlike<double>::go();
   }

   template <typename T>
   class matrixScalarMult
   {
   public:
      static void go()
      {
         gmtl::Matrix<T, 4, 4> mat1, res_mat, expected_result;

         T eps = (T)0.001;

         mat1.set((T) 1.1000, (T)2.2000,  (T) 3.3000, (T) 4.4000,
                  (T) 5.5000, (T)6.6000,  (T) 7.7000, (T) 8.8000,
                  (T) 9.9000, (T)10.1000, (T)11.1100, (T)12.1200,
                  (T)13.1300, (T)14.1400, (T)15.1500, (T)16.1600 );
         expected_result.set(  (T)3.3000,   (T)6.6000,   (T)9.9000,  (T)13.2000,
                              (T)16.5000,  (T)19.8000,  (T)23.1000,  (T)26.4000,
                              (T)29.7000,  (T)30.3000,  (T)33.3300,  (T)36.3600,
                              (T)39.3900,  (T)42.4200,  (T)45.4500,  (T)48.4800  );

         // result = mat * scalar
         gmtl::mult( res_mat, mat1, (T)3 );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result, res_mat, eps ) );

         // result *= scalar
         res_mat = mat1;
         gmtl::mult( res_mat, (T)3 );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result, res_mat, eps ) );

         // result *= scalar
         res_mat = mat1;
         res_mat *= (T)3;
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result, res_mat, eps ) );
      }
   };

   void MatrixOpsTest::testMatrixScalarMult()
   {
      matrixScalarMult<float>::go();
      matrixScalarMult<double>::go();
   }

   template <typename DATA_TYPE>
   class matInvertKnownFull
   {
      typedef DATA_TYPE T;
   public:
      static void go()
      {
         gmtl::Matrix<DATA_TYPE, 4, 4> mat1, expected_value, result, identity;
         DATA_TYPE eps = (T)0.001;
         mat1.set( (T)0.78,  (T)1.4,   (T)2.9, (T)3.45,
                   (T)4.21, (T)57.9,  (T)65.9, (T)74.6,
                   (T)89.2, (T)99.2,  (T)10.9, (T)11.9,
                   (T)12.5, (T)13.9, (T)14.78, (T)15.6  );
         expected_value.set( (T)0.3071733,  (T)-0.0239700,   (T)0.0034853,   (T)0.0440345,
                            (T)-0.2891106,   (T)0.0216826,   (T)0.0079218,  (T)-0.0457924,
                            (T)-3.0532152,   (T)0.0305681,  (T)-0.0547335,   (T)0.5708037,
                             (T)2.9041982,  (T)-0.0290744,   (T)0.0420053,  (T)-0.4711792 );

         // Make sure our pre-computed answer is right
         gmtl::mult( result, mat1, expected_value );
         CPPUNIT_ASSERT( gmtl::isEqual( result, identity, eps ) );

         // Test inversion
         result = gmtl::Matrix<DATA_TYPE, 4, 4>();
         gmtl::invert( result, mat1 );
         CPPUNIT_ASSERT( gmtl::isEqual( result, expected_value, eps ) );

         // Test inversion in place
         result = gmtl::Matrix<DATA_TYPE, 4, 4>();
         gmtl::invert( mat1 );
         CPPUNIT_ASSERT( gmtl::isEqual( mat1, expected_value, eps ) );
      }
   };

   template <typename DATA_TYPE, unsigned SIZE>
   class matInvertFull
   {
   public:
      static void go()
      {
         unsigned const iters(100);
         float eps(0.01f);

         gmtl::Matrix<DATA_TYPE, SIZE, SIZE> mat, inv_mat, mult_mat, expected_mat;

         for(unsigned i=0;i<iters;++i)
         {
            // Fill matrix with random values in range 0.1 to 1.0;
            for(unsigned r=0;r<SIZE;++r)
            {
               for(unsigned c=0;c<SIZE;++c)
               { mat(r,c) = gmtl::Math::rangeRandom(0.1,1.0); }
            }
            mat.setState(gmtl::Matrix<DATA_TYPE,SIZE,SIZE>::FULL);

            gmtl::invert(inv_mat, mat);
            mult_mat = mat * inv_mat;
            CPPUNIT_ASSERT( gmtl::isEqual(mult_mat, expected_mat, DATA_TYPE(eps)));

            inv_mat = mat;
            gmtl::invert(inv_mat);
            CPPUNIT_ASSERT( gmtl::isEqual(mult_mat, expected_mat, DATA_TYPE(eps)));
         }
      }
   };

   void MatrixOpsTest::testMatInvert()
   {
      matInvertKnownFull<float>::go();
      matInvertKnownFull<double>::go();

      float eps(0.001f);

      // -- Test translation creation and inversion -- //
      const float trans_range(100), trans_inc(20);
      for(float x=-trans_range;x<trans_range;x+=trans_inc)
      {
         for(float y=-trans_range;y<trans_range;y+=trans_inc)
         {
            for(float z=-trans_range;z<trans_range;z+=trans_inc)
            {
               gmtl::Matrix44f expected_inv;
               expected_inv.set(1, 0, 0, -x,
                                0, 1, 0, -y,
                                0, 0, 1, -z,
                                0, 0, 0, 1);
               gmtl::Matrix44f src_mat, inv_mat;
               gmtl::setTrans(src_mat,gmtl::Vec3f(x,y,z));
               gmtl::invertFull_orig(inv_mat, src_mat);
               CPPUNIT_ASSERT( gmtl::isEqual(inv_mat, expected_inv, eps));
               gmtl::identity(inv_mat);
               gmtl::invertFull_GJ(inv_mat, src_mat);
               CPPUNIT_ASSERT( gmtl::isEqual(inv_mat, expected_inv, eps));
               gmtl::identity(inv_mat);
               gmtl::invert(inv_mat, src_mat);
               CPPUNIT_ASSERT( gmtl::isEqual(inv_mat, expected_inv, eps));
            }
         }
      }

      // -- Test rotation matrix creation and inversion -- //
      /*
      {
         const float trans_range(360), trans_inc(30);
         for(float x=-trans_range;x<trans_range;x+=trans_inc)
         {
            for(float y=-trans_range;y<trans_range;y+=trans_inc)
            {
               for(float z=-trans_range;z<trans_range;z+=trans_inc)
               {
                  std::cout << "-------- x:" << x << " y:" << y << " z:" << z << std::endl;

                  gmtl::Matrix44f inv_mat, rot_mat, expected_mult, mult_mat;

                  gmtl::setRot( rot_mat, gmtl::EulerAngleXYZf(
                                         gmtl::Math::deg2Rad( x ),
                                         gmtl::Math::deg2Rad( y ),
                                         gmtl::Math::deg2Rad( z ) ) );

                  std::cout << "rot_mat: \n" << rot_mat << std::endl;

                  gmtl::invertFull_orig(inv_mat, rot_mat);
                  mult_mat = inv_mat * rot_mat;
                  std::cout << "inv_mat orig: \n" << inv_mat << std::endl
                            << "mult_mat orig: \n" << mult_mat << std::endl;
                  CPPUNIT_ASSERT( gmtl::isEqual(mult_mat, expected_mult, eps));

                  gmtl::identity(inv_mat);
                  gmtl::invertFull_GJ(inv_mat, rot_mat);
                  mult_mat = inv_mat * rot_mat;
                  std::cout << "inv_mat gj: \n" << inv_mat << std::endl
                            << "mult_mat gj: \n" << mult_mat << std::endl;

                  CPPUNIT_ASSERT( gmtl::isEqual(mult_mat, expected_mult, eps));

                  gmtl::identity(inv_mat);
                  gmtl::invert(inv_mat, rot_mat);
                  mult_mat = inv_mat * rot_mat;
                  CPPUNIT_ASSERT( gmtl::isEqual(mult_mat, expected_mult, eps));
               }
            }
         }
      }
      */


      /*
      // Test rotation inversions
      gmtl::Matrix<DATA_TYPE, 4, 4> rot_mat1, rot_mat1_inv; // rot_mat2, rot_mat2_inv;
      rot_mat1.makeXYZEuler( 30.0f, 45.0f, 60.0f );
      rot_mat1_inv.invert(rot_mat1);
      result = rot_mat1*rot_mat1_inv;
      CPPUNIT_ASSERT(result.equal(identity));

      // Test translation matrix inversion
      gmtl::Matrix<DATA_TYPE, 4, 4> trans_mat1, trans_mat1_inv;
      trans_mat1.makeTrans(21.0f, -23.45f, 0.045f);
      trans_mat1_inv.invert(trans_mat1);
      result = trans_mat1*trans_mat1_inv;
      CPPUNIT_ASSERT(result.equal(identity));
      */

      matInvertFull<float,2>::go();
      matInvertFull<float,3>::go();
      matInvertFull<float,4>::go();
      matInvertFull<float,5>::go();
      matInvertFull<float,8>::go();

      matInvertFull<double,2>::go();
      matInvertFull<double,3>::go();
      matInvertFull<double,4>::go();
      matInvertFull<double,5>::go();
      matInvertFull<double,8>::go();
   }

   /*
   void MatrixOpsTest::testGetSetAxes()
   {
      gmtl::Matrix mat1, mat2;
      gmtl::Vec3 xAxis1,yAxis1,zAxis1;
      gmtl::Vec3 xAxis2,yAxis2,zAxis2;

      // Simple rotation around X axis
      mat1.setRot(90,gmtl::XUnitVec3);
      mat1.getAxes(xAxis1,yAxis1,zAxis1);
      mat2.makeAxes(xAxis1,yAxis1,zAxis1);
      mat2.getAxes(xAxis2,yAxis2,zAxis2);

      CPPUNIT_ASSERT(xAxis1.equal(xAxis2,0.01));
      CPPUNIT_ASSERT(yAxis1.equal(yAxis2,0.01));
      CPPUNIT_ASSERT(zAxis1.equal(zAxis2,0.01));

      // More complex Euler rotation
      mat1.makeXYZEuler(45.0f, -35.0f, 13.0f);
      mat1.getAxes(xAxis1,yAxis1,zAxis1);
      mat2.makeAxes(xAxis1,yAxis1,zAxis1);
      mat2.getAxes(xAxis2,yAxis2,zAxis2);

      CPPUNIT_ASSERT(xAxis1.equal(xAxis2,0.01));
      CPPUNIT_ASSERT(yAxis1.equal(yAxis2,0.01));
      CPPUNIT_ASSERT(zAxis1.equal(zAxis2,0.01));

      // Use orthonormal axis
      xAxis1.set(7, 11, 21);     xAxis1.normalize();
      yAxis1.set(12, 21, 75);    yAxis1.normalize();
      zAxis1 = xAxis1.cross(yAxis1);   zAxis1.normalize();

      mat2.makeAxes(xAxis1,yAxis1,zAxis1);
      mat2.getAxes(xAxis2,yAxis2,zAxis2);

      CPPUNIT_ASSERT(xAxis1.equal(xAxis2,0.01));
      CPPUNIT_ASSERT(yAxis1.equal(yAxis2,0.01));
      CPPUNIT_ASSERT(zAxis1.equal(zAxis2,0.01));
   }
   */
}

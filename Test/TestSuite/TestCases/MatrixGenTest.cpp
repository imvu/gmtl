// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "MatrixGenTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Output.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(MatrixGenTest);
   CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(MatrixGenMetricTest, Suites::metric());

   void MatrixGenTest::testMatrixsetViewing()
   {
      // check against results from gluPerspective, and glFrustum.
      {
         gmtl::Matrix44f mat;
         gmtl::setFrustum( mat, -1.0f, 1.0f, 1.0f, -1.0f, 0.02f, 100.0f );
         //std::cout << "frus: " << mat << std::endl;
         float data[] = { 0.02, 0, 0, 0,
                        0, 0.02, 0, 0,
                        0, 0, -1.0004, -0.040008,
                        0, 0, -1, 0 };
         gmtl::Matrix44f expected;
         expected.setTranspose( data );

         CPPUNIT_ASSERT( gmtl::isEqual( expected, mat, 0.001f ) );
      }

      {
         gmtl::Matrix44f mat;
         gmtl::setPerspective( mat, 89.0f, 1.33f, 0.001f, 1000.0f );
         //std::cout << "per: " << mat << std::endl;

         float data[] = { 0.765118, 0, 0, 0,
                           0, 1.01761, 0, 0,
                           0, 0, -1.0, -0.002,
                           0, 0, -1, 0 };
         gmtl::Matrix44f expected;
         expected.setTranspose( data );

         CPPUNIT_ASSERT( gmtl::isEqual( expected, mat, 0.001f ) );
      }
   }

   void MatrixGenTest::testMatrixsetTrans()
   {
      float eps = 0.001f;
      // 2D rot/trans
      {
         gmtl::Matrix<float, 2, 3> mat23, expected_result23;
         gmtl::Vec2f trans_vec( 32, 33 );
         expected_result23.set( 1, 0, 32,
                                0, 1, 33 );
         gmtl::setTrans( mat23, trans_vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result23, mat23, eps ) );
         CPPUNIT_ASSERT( gmtl::makeTrans<gmtl::Vec2f>(mat23) == trans_vec );

         // make sure that make and set return the same...
         CPPUNIT_ASSERT( expected_result23 == gmtl::makeTrans<gmtl::Matrix23f>( gmtl::Vec2f( 32, 33 ) ) );
      }
      // 2D rot/trans/skew
      {
         gmtl::Matrix33f mat33, expected_result33;
         gmtl::Vec2f trans_vec( 32, 33 );
         expected_result33.set( 1, 0, 32,
                                0, 1, 33,
                                0, 0, 1 );
         gmtl::setTrans( mat33, trans_vec);
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat33, eps ) );
         CPPUNIT_ASSERT( gmtl::makeTrans<gmtl::Vec2f>(mat33) == trans_vec);

         // make sure that make and set return the same...
         CPPUNIT_ASSERT( expected_result33 == gmtl::makeTrans<gmtl::Matrix33f>( gmtl::Vec2f( 32, 33 ) ) );
      }
      // 2D rot/trans/skew set by homogeneous vector
      {
         gmtl::Matrix33f mat33, expected_result33;
         gmtl::Vec3f trans_vec( 32, 33, 0.5f );
         expected_result33.set( 1, 0, 64,
                                0, 1, 66,
                                0, 0, 1 );
         gmtl::setTrans( mat33, trans_vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat33, eps ) );
         CPPUNIT_ASSERT( gmtl::makeTrans<gmtl::Vec3f>(mat33) == gmtl::Vec3f(64.0f, 66.0f, 1.0f) );
      }
      // 3D rot/trans
      {
         gmtl::Matrix34f mat34, expected_result34;
         gmtl::Vec3f trans_vec( 32, 33, 34 );
         expected_result34.set( 1, 0, 0, 32,
                                0, 1, 0, 33,
                                0, 0, 1, 34 );
         gmtl::setTrans( mat34, trans_vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat34, eps ) );
         CPPUNIT_ASSERT( gmtl::makeTrans<gmtl::Vec3f>(mat34) == trans_vec );
      }
      // 3D rot/trans set by homogeneous vector
      {
         gmtl::Matrix34f mat34, expected_result34;
         gmtl::Vec4f trans_vec( 32, 33, 34, 0.5f );
         expected_result34.set( 1, 0, 0, 64,
                                0, 1, 0, 66,
                                0, 0, 1, 68 );
         gmtl::setTrans( mat34, trans_vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat34, eps ) );
         CPPUNIT_ASSERT( gmtl::makeTrans<gmtl::Vec3f>(mat34) == gmtl::Vec3f(64.0f, 66.0f, 68.0f) );
      }
      // 3D rot/trans/skew
      {
         gmtl::Matrix44f mat44, expected_result44;
         expected_result44.set( 1, 0, 0, 32,
                                0, 1, 0, 33,
                                0, 0, 1, 34,
                                0, 0, 0, 1  );
         gmtl::setTrans( mat44, gmtl::Vec3f( 32, 33, 34 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat44, eps ) );
      }
      // 3D rot/trans/skew set by homogeneous vector...
      {
         gmtl::Matrix44f mat44, expected_result44;
         expected_result44.set( 1, 0, 0, 64,
                                0, 1, 0, 66,
                                0, 0, 1, 68,
                                0, 0, 0, 1  );
         gmtl::setTrans( mat44, gmtl::Vec4f( 32, 33, 34, 0.5f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat44, eps ) );
      }

      // --- Test standalone makeTrans(trans) against setTrans(mat,trans) -- //
      {
         gmtl::Matrix44f expected_mat;
         gmtl::Vec3f trans3(1.0, 2.0, 3.0f);
         gmtl::setTrans(expected_mat, trans3);
         CPPUNIT_ASSERT( gmtl::isEqual( gmtl::makeTrans<gmtl::Matrix44f>(trans3),
                                        expected_mat, eps ) );

      }
   }

   void MatrixGenTest::testMatrixsetAxes()
   {
      const float eps = 0.001f;
      const float a = 98234576.0f;
      {
         gmtl::Matrix33f mat33, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat33.mData[x] = a;
         expected_result33.set( 0, 1, 0,
                                1, 0, 0,
                                0, 0, -1  );
         gmtl::setAxes( mat33, gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,0,-1 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat33, eps ) );
         CPPUNIT_ASSERT( gmtl::makeAxes<gmtl::Matrix33f>( gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,0,-1 ) ) == mat33 );
      }
      {
         gmtl::Matrix44f mat44, expected_result44;
         for (int x = 0; x < 16; ++x)
            mat44.mData[x] = a;
         expected_result44.set( 0, 1, 0, a,
                                1, 0, 0, a,
                                0, 0, -1, a,
                                a, a, a, a  );
         gmtl::setAxes( mat44, gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,0,-1 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat44, eps ) );

         // make sure set and make are the same...
         gmtl::Matrix44f new_mat;
         gmtl::setAxes( new_mat, gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,0,-1 ) );
         CPPUNIT_ASSERT( gmtl::makeAxes<gmtl::Matrix44f>( gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,0,-1 ) ) == new_mat );
      }
   }

   // Test for direction cosines
   // Coordinate frames: I - Identity (base frame), T - transformed frame
   //
   // Compute tranformation to new frame. Convert known points back and forth to see if they match
   //
   void MatrixGenTest::testMatrixsetDirCos()
   {
      const float       eps(0.01f);       // Should be close enough
      gmtl::Matrix44f   i_M_t;            // Transform from identity to the transform.

      // Two points that should match in different frames
      const gmtl::Point3f     pt_I(1.0f, 0.0f, 0.0f);      // Point in identity frame
      const gmtl::Point3f     pt_T(0.0f, 0.0f, 1.0f);      // Point in the transformed frame

      // Basis vectors of the T coordinate frame in the I coordinate frame
      const gmtl::Vec3f x_axis(0,1,0), y_axis(0,0,1), z_axis(1,0,0);

      // Build the transform matrix
      i_M_t = gmtl::makeDirCos<gmtl::Matrix44f>(x_axis, y_axis, z_axis);
      gmtl::Point3f    result_pt;

      // Test point going from T to I
      result_pt = i_M_t * pt_T;
      //std::cout << "result_pt:1: " << result_pt << std::endl;
      CPPUNIT_ASSERT( gmtl::isEqual(result_pt, pt_I, eps));

      // Test point going from I to T
      result_pt = gmtl::makeInvert<float,4,4>(i_M_t) * pt_I;
      CPPUNIT_ASSERT( gmtl::isEqual(result_pt, pt_T, eps));
   }


   void MatrixGenTest::testMatrixsetScale()
   {
      const float eps = 0.001f;
      const float a = 98234576.0f;
      // 2D rot/trans
      {
         gmtl::Matrix<float, 2, 3> mat23, expected_result23;
         for (int x = 0; x < 6; ++x)
            mat23.mData[x] = a;
         expected_result23.set( 32, a, a,
                                a, 33, a );
         gmtl::setScale( mat23, gmtl::Vec2f( 32, 33 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result23, mat23, eps ) );

         // make sure set and make are the same...
         gmtl::Matrix23f new_mat;
         gmtl::setScale( new_mat, gmtl::Vec2f( 32, 33 ) );
         CPPUNIT_ASSERT( gmtl::makeScale<gmtl::Matrix23f >( gmtl::Vec2f( 32, 33 ) ) == new_mat );
      }
      // 2D rot/trans/skew
      {
         gmtl::Matrix33f mat33, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat33.mData[x] = a;
         expected_result33.set( 32, a, a,
                                a, 33, a,
                                a, a, a );
         gmtl::setScale( mat33, gmtl::Vec2f( 32, 33 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat33, eps ) );

         // make sure set and make are the same...
         gmtl::Matrix33f new_mat;
         gmtl::setScale( new_mat, gmtl::Vec2f( 32, 33 ) );
         CPPUNIT_ASSERT( gmtl::makeScale<gmtl::Matrix33f >( gmtl::Vec2f( 32, 33 ) ) == new_mat );
      }
      // 3D rot/trans
      {
         gmtl::Matrix34f mat34, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat34.mData[x] = a;
         expected_result34.set( 32, a, a, a,
                                a, 33, a, a,
                                a, a, 34, a );
         gmtl::setScale( mat34, gmtl::Vec3f( 32, 33, 34 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat34, eps ) );

         // make sure set and make are the same...
         gmtl::Matrix34f new_mat;
         gmtl::setScale( new_mat, gmtl::Vec3f( 32, 33, 34 ) );
         CPPUNIT_ASSERT( gmtl::makeScale<gmtl::Matrix34f >( gmtl::Vec3f( 32, 33, 34 ) ) == new_mat );
      }
      // 3D rot/trans/skew
      {
         gmtl::Matrix44f mat44, expected_result44;
         for (int x = 0; x < 16; ++x)
            mat44.mData[x] = a;
         expected_result44.set( 32, a, a, a,
                                a, 33, a, a,
                                a, a, 34, a,
                                a, a, a, a  );
         gmtl::setScale( mat44, gmtl::Vec3f( 32, 33, 34 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat44, eps ) );

         // make sure set and make are the same...
         gmtl::Matrix44f new_mat;
         gmtl::setScale( new_mat, gmtl::Vec3f( 32, 33, 34 ) );
         CPPUNIT_ASSERT( gmtl::makeScale<gmtl::Matrix44f >( gmtl::Vec3f( 32, 33, 34 ) ) == new_mat );
      }



      // 2D rot/trans
      {
         gmtl::Matrix<float, 2, 3> mat23, expected_result23;
         for (int x = 0; x < 6; ++x)
            mat23.mData[x] = a;
         expected_result23.set( 32, a, a,
                                a, 32, a );
         gmtl::setScale( mat23, 32.0f );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result23, mat23, eps ) );

         // make sure set and make are the same...
         gmtl::Matrix23f new_mat;
         gmtl::setScale( new_mat, 32.0f );
         CPPUNIT_ASSERT( gmtl::makeScale<gmtl::Matrix23f >( 32.0f ) == new_mat );
      }
      // 2D rot/trans/skew
      {
         gmtl::Matrix33f mat33, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat33.mData[x] = a;
         expected_result33.set( 32, a, a,
                                a, 32, a,
                                a, a, a );
         gmtl::setScale( mat33, 32.0f );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat33, eps ) );

         // make sure set and make are the same...
         gmtl::Matrix33f new_mat;
         gmtl::setScale( new_mat, 32.0f );
         CPPUNIT_ASSERT( gmtl::makeScale<gmtl::Matrix33f >( 32.0f ) == new_mat );
      }
      // 3D rot/trans
      {
         gmtl::Matrix34f mat34, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat34.mData[x] = a;
         expected_result34.set( 32, a, a, a,
                                a, 32, a, a,
                                a, a, 32, a );
         gmtl::setScale( mat34, 32.0f );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat34, eps ) );

         // make sure set and make are the same...
         gmtl::Matrix34f new_mat;
         gmtl::setScale( new_mat, 32.0f );
         CPPUNIT_ASSERT( gmtl::makeScale<gmtl::Matrix34f >( 32.0f ) == new_mat );
      }
      // 3D rot/trans/skew
      {
         gmtl::Matrix44f mat44, expected_result44;
         for (int x = 0; x < 16; ++x)
            mat44.mData[x] = a;
         expected_result44.set( 32, a, a, a,
                                a, 32, a, a,
                                a, a, 32, a,
                                a, a, a, a  );
         gmtl::setScale( mat44, 32.0f );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat44, eps ) );

         // make sure set and make are the same...
         gmtl::Matrix44f new_mat;
         gmtl::setScale( new_mat, 32.0f );
         CPPUNIT_ASSERT( gmtl::makeScale<gmtl::Matrix44f >( 32.0f ) == new_mat );
      }
      {
         // make sure this compiles, and runs without internal assert.
         gmtl::Matrix<float, 4, 8> mat48;
         gmtl::setScale( mat48, 32.0f );

         gmtl::Matrix<float, 8, 4> mat84;
         gmtl::setScale( mat84, 32.0f );
      }
   }

   /// @todo test out getRot (just like this set rot function, but reversed)...

   void MatrixGenTest::testMatrixsetRot()
   {
      const float eps = 0.01f;
      const float a = 98234576.0f;
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat.mData[x] = a;
         expected_result33.set( 1, 0, 0,
                                0, 0, -1,
                                0, 1, 0 );
         gmtl::Vec3f vec( 1.0f, 0.0f, 0.0f );
         gmtl::normalize( vec );
         gmtl::setRot( mat, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), vec ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );

         // make sure that the other version works the same...
         gmtl::Matrix33f mat2;
         gmtl::setRot( mat2, gmtl::makeNormal( gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), 1.0f, 0.0f, 0.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( mat2, mat, eps ) );

         // make sure set and make are the same...
         CPPUNIT_ASSERT( gmtl::makeRot<gmtl::Matrix33f>( gmtl::makeNormal( gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), 1.0f, 0.0f, 0.0f ) ) ) == mat2 );
         CPPUNIT_ASSERT( gmtl::makeRot<gmtl::Matrix33f>( gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), vec ) ) == mat2 );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat.mData[x] = a;
         expected_result33.set( 1, 0, 0,
                                0, 1, 0,
                                0, 0, 1 );
         gmtl::Vec3f vec( -1.0f, 1.0f, -1.0f );
         gmtl::normalize( vec );
         gmtl::setRot( mat, gmtl::AxisAnglef( gmtl::Math::deg2Rad( -360.0f ), vec ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );

         // make sure that the other version works the same...
         gmtl::Matrix33f mat2;
         gmtl::setRot( mat2, gmtl::makeNormal( gmtl::AxisAnglef( gmtl::Math::deg2Rad( -360.0f ), -1.0f, 1.0f, -1.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( mat2, mat, eps ) );

         // make sure set and make are the same...
         CPPUNIT_ASSERT( gmtl::makeRot<gmtl::Matrix33f>( gmtl::makeNormal( gmtl::AxisAnglef( gmtl::Math::deg2Rad( -360.0f ), -1.0f, 1.0f, -1.0f ) ) ) == mat2 );
         CPPUNIT_ASSERT( gmtl::makeRot<gmtl::Matrix33f>( gmtl::AxisAnglef( gmtl::Math::deg2Rad( -360.0f ), vec ) ) == mat2 );
      }

      {
         gmtl::Matrix34f mat, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat.mData[x] = a;
         expected_result34.set( 1, 0, 0, a,
                                0, 0, 1, a,
                                0, -1, 0, a );
         gmtl::Vec3f vec( 1.0f, 0.0f, 0.0f );
         gmtl::normalize( vec );
         gmtl::setRot( mat, gmtl::AxisAnglef( gmtl::Math::deg2Rad( -90.0f ), vec ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );

         // make sure that the other version works the same...
         gmtl::Matrix34f mat2;
         for (int x = 0; x < 12; ++x)
            mat2.mData[x] = a;
         gmtl::setRot( mat2, gmtl::makeNormal( gmtl::AxisAnglef( gmtl::Math::deg2Rad( -90.0f ), 1.0f, 0.0f, 0.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( mat2, mat, eps ) );

         // make sure set and make are the same...
         gmtl::Matrix34f new_mat;
         gmtl::setRot( new_mat, gmtl::makeNormal( gmtl::AxisAnglef( gmtl::Math::deg2Rad( -90.0f ), 1.0f, 0.0f, 0.0f ) ) );
         CPPUNIT_ASSERT( gmtl::makeRot<gmtl::Matrix34f>( gmtl::makeNormal( gmtl::AxisAnglef( gmtl::Math::deg2Rad( -90.0f ), 1.0f, 0.0f, 0.0f ) ) ) == new_mat );
         gmtl::setRot( new_mat, gmtl::AxisAnglef( gmtl::Math::deg2Rad( -90.0f ), vec ) );
         CPPUNIT_ASSERT( gmtl::makeRot<gmtl::Matrix34f>( gmtl::AxisAnglef( gmtl::Math::deg2Rad( -90.0f ), vec ) ) == new_mat );
      }
      {
         gmtl::Matrix34f mat, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat.mData[x] = a;
         expected_result34.set( 0.804738f, 0.310617f, -0.505879f, a,
                                -0.505879f, 0.804738f, -0.310617f, a,
                                0.310617f, 0.505879f, 0.804738f, a  );
         gmtl::Vec3f vec( 0.7f, -0.7f, -0.7f );
         gmtl::normalize( vec );
         gmtl::setRot( mat, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 45.0f ), vec ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );

         // make sure that the other version works the same...
         gmtl::Matrix34f mat2;
         for (int x = 0; x < 12; ++x)
            mat2.mData[x] = a;
         gmtl::setRot( mat2, gmtl::makeNormal( gmtl::AxisAnglef( gmtl::Math::deg2Rad( 45.0f ), 0.7f, -0.7f, -0.7f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( mat2, mat, eps ) );

         // make sure set and make are the same...
         gmtl::Matrix34f new_mat;
         gmtl::setRot( new_mat, gmtl::makeNormal( gmtl::AxisAnglef( gmtl::Math::deg2Rad( 45.0f ), 0.7f, -0.7f, -0.7f ) ) );
         CPPUNIT_ASSERT( gmtl::makeRot<gmtl::Matrix34f>( gmtl::makeNormal( gmtl::AxisAnglef( gmtl::Math::deg2Rad( 45.0f ), 0.7f, -0.7f, -0.7f ) ) ) == new_mat );
         gmtl::setRot( new_mat, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 45.0f ), vec ) );
         CPPUNIT_ASSERT( gmtl::makeRot<gmtl::Matrix34f>( gmtl::AxisAnglef( gmtl::Math::deg2Rad( 45.0f ), vec ) ) == new_mat );
      }
      // test that unnormalized vec works...
      {
         gmtl::Matrix44f mat, expected_result44;
         for (int x = 0; x < 16; ++x)
            mat.mData[x] = a;
         expected_result44.set( 0.804738f, -0.310617f, 0.505879f, a,
                                0.505879f, 0.804738f, -0.310617f, a,
                                -0.310617f, 0.505879f, 0.804738f, a,
                                a, a, a, a );
         gmtl::Vec3f vec( 1.7f, 1.7f, 1.7f );
         gmtl::normalize( vec );
         gmtl::setRot( mat, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 45.0f ), vec ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat, eps ) );

         // make sure that the other version works the same...
         gmtl::Matrix44f mat2;
         for (int x = 0; x < 16; ++x)
            mat2.mData[x] = a;
         gmtl::setRot( mat2, gmtl::makeNormal( gmtl::AxisAnglef( gmtl::Math::deg2Rad( 45.0f ), 1.7f, 1.7f, 1.7f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( mat2, mat, eps ) );

         // make sure set and make are the same...
         gmtl::Matrix44f new_mat;
         gmtl::setRot( new_mat, gmtl::makeNormal( gmtl::AxisAnglef( gmtl::Math::deg2Rad( 45.0f ), 1.7f, 1.7f, 1.7f ) ) );
         CPPUNIT_ASSERT( gmtl::makeRot<gmtl::Matrix44f>( gmtl::makeNormal( gmtl::AxisAnglef( gmtl::Math::deg2Rad( 45.0f ), 1.7f, 1.7f, 1.7f ) ) ) == new_mat );
         gmtl::setRot( new_mat, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 45.0f ), vec ) );
         CPPUNIT_ASSERT( gmtl::makeRot<gmtl::Matrix44f>( gmtl::AxisAnglef( gmtl::Math::deg2Rad( 45.0f ), vec ) ) == new_mat );
      }

      // ---- Test standalone one ---- //
      {
         gmtl::Matrix44f mat, expected_mat;
         gmtl::Vec3f rot_axis(1.0f, 2.0f, 3.0f);
         gmtl::normalize( rot_axis );
         gmtl::AxisAnglef axisAngle( 1.1f, rot_axis );
         gmtl::setRot( expected_mat, axisAngle );
         mat = gmtl::makeRot<gmtl::Matrix44f>( axisAngle );
         CPPUNIT_ASSERT( gmtl::isEqual( mat, expected_mat, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( gmtl::makeRot<gmtl::Matrix44f>( axisAngle ), expected_mat, eps ) );
      }

      {
         gmtl::Matrix34f mat, expected_mat;
         gmtl::Vec3f rot_axis(1.0f, 2.0f, 3.0f);
         gmtl::normalize(rot_axis);
         gmtl::AxisAnglef axisAngle( 1.1f, rot_axis );
         gmtl::setRot(expected_mat, axisAngle);
         mat = gmtl::makeRot<gmtl::Matrix34f>( axisAngle );
         CPPUNIT_ASSERT( gmtl::isEqual( mat, expected_mat, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( gmtl::makeRot<gmtl::Matrix34f>( axisAngle ), expected_mat, eps ) );
      }

   }

   void MatrixGenTest::testMatrixgetRotEuler()
   {
      float eps = 0.01f;
      gmtl::Matrix44f matrix;
      // XYZ
      {
         gmtl::EulerAngleXYZf euler;
         gmtl::set( matrix, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), 1.0f, 0.0f, 0.0f ) );
         gmtl::set( euler, matrix );
         //std::cout<<gmtl::Math::rad2Deg( euler[0] )<<" "
         //         <<gmtl::Math::rad2Deg( euler[1] )<<" "
         //         <<gmtl::Math::rad2Deg( euler[2] )<<" "<<std::endl;
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[0] ), 90.0f, eps ) );
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[1] ), 0.0f, eps ) );
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[2] ), 0.0f, eps ) );

         gmtl::set( matrix, gmtl::AxisAnglef( gmtl::Math::deg2Rad( -90.0f ), 1.0f, 0.0f, 0.0f ) );
         gmtl::set( euler, matrix );
         //std::cout<<gmtl::Math::rad2Deg( euler[0] )<<" "
         //         <<gmtl::Math::rad2Deg( euler[1] )<<" "
         //         <<gmtl::Math::rad2Deg( euler[2] )<<" "<<std::endl;
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[0] ), -90.0f, eps ) );
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[1] ), 0.0f, eps ) );
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[2] ), 0.0f, eps ) );

         gmtl::set( matrix, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 35.0f ), 0.0f, 1.0f, 0.0f ) );
         gmtl::set( euler, matrix );
         //std::cout<<gmtl::Math::rad2Deg( euler[0] )<<" "
         //         <<gmtl::Math::rad2Deg( euler[1] )<<" "
         //         <<gmtl::Math::rad2Deg( euler[2] )<<" "<<std::endl;
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[0] ), 0.0f, eps ) );
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[1] ), 35.0f, eps ) );
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[2] ), 0.0f, eps ) );

         // test cos y = 0 singularity
         gmtl::set( matrix, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), 0.0f, 1.0f, 0.0f ) );
         gmtl::set( euler, matrix );
         //std::cout<<gmtl::Math::rad2Deg( euler[0] )<<" "
         //         <<gmtl::Math::rad2Deg( euler[1] )<<" "
         //         <<gmtl::Math::rad2Deg( euler[2] )<<" "<<std::endl;
         /* XXX: FIX ME
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[0] ), 0.0f, eps ) );
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[1] ), 90.0f, eps ) );
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[2] ), 0.0f, eps ) );
         */

         // test cos z = 0 singularity
         gmtl::set( matrix, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), 0.0f, 0.0f, 1.0f ) );
         gmtl::set( euler, matrix );
         //std::cout<<gmtl::Math::rad2Deg( euler[0] )<<" "
         //         <<gmtl::Math::rad2Deg( euler[1] )<<" "
         //         <<gmtl::Math::rad2Deg( euler[2] )<<" "<<std::endl;
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[0] ), 0.0f, eps ) );
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[1] ), 0.0f, eps ) );
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[2] ), 90.0f, eps ) );
      }

      // ZYX
      {
         gmtl::EulerAngleZYXf euler;
         gmtl::set( matrix, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), 1.0f, 0.0f, 0.0f ) );
         gmtl::set( euler, matrix );
         //std::cout<<gmtl::Math::rad2Deg( euler[0] )<<" "
         //         <<gmtl::Math::rad2Deg( euler[1] )<<" "
         //         <<gmtl::Math::rad2Deg( euler[2] )<<" "<<std::endl;
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[0] ), 0.0f, eps ) );
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[1] ), 0.0f, eps ) );
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[2] ), 90.0f, eps ) );

         gmtl::set( matrix, gmtl::AxisAnglef( gmtl::Math::deg2Rad( -90.0f ), 1.0f, 0.0f, 0.0f ) );
         gmtl::set( euler, matrix );
         //std::cout<<gmtl::Math::rad2Deg( euler[0] )<<" "
         //         <<gmtl::Math::rad2Deg( euler[1] )<<" "
         //         <<gmtl::Math::rad2Deg( euler[2] )<<" "<<std::endl;
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[0] ), 0.0f, eps ) );
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[1] ), 0.0f, eps ) );
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[2] ), -90.0f, eps ) );

         // test sin x = 0 singularity
         gmtl::set( matrix, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 35.0f ), 0.0f, 1.0f, 0.0f ) );
         gmtl::set( euler, matrix );
         //std::cout<<gmtl::Math::rad2Deg( euler[0] )<<" "
         //         <<gmtl::Math::rad2Deg( euler[1] )<<" "
         //         <<gmtl::Math::rad2Deg( euler[2] )<<" "<<std::endl;
         /* XXX: FIX ME
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[0] ), 0.0f, eps ) );
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[1] ), 35.0f, eps ) );
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[2] ), 0.0f, eps ) );
         */

         // test cos y = 0 singularity
         gmtl::set( matrix, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 35.0f ), 0.0f, 1.0f, 0.0f ) );
         gmtl::set( euler, matrix );
         //std::cout<<gmtl::Math::rad2Deg( euler[0] )<<" "
         //         <<gmtl::Math::rad2Deg( euler[1] )<<" "
         //         <<gmtl::Math::rad2Deg( euler[2] )<<" "<<std::endl;
         /* XXX: FIX ME
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[0] ), 0.0f, eps ) );
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[1] ), 90.0f, eps ) );
         CPPUNIT_ASSERT( gmtl::Math::isEqual( gmtl::Math::rad2Deg( euler[2] ), 0.0f, eps ) );
         */
      }
   }

   void MatrixGenTest::testMatrixsetRotEuler()
   {
      const float eps = 0.001f;
      const float a = 98234576.0f;
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat.mData[x] = a;
         expected_result33.set( 0.683013f, -0.183013f, 0.707107f,
                                0.683013f, -0.183013f, -0.707107f,
                                0.258819f, 0.965926f, 0.0f );
         gmtl::setRot( mat, gmtl::EulerAngleXYZf(
                             gmtl::Math::deg2Rad( 90.0f ),
                             gmtl::Math::deg2Rad( 45.0f ),
                             gmtl::Math::deg2Rad( 15.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat.mData[x] = a;
         expected_result33.set( 1, 0,  0,
                                0, 0, -1,
                                0, 1,  0  );
         gmtl::setRot( mat, gmtl::EulerAngleXYZf( gmtl::Math::deg2Rad( 90.0f ),
                                               gmtl::Math::deg2Rad( 0.0f ),
                                               gmtl::Math::deg2Rad( 0.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );

         // make sure set and make are the same...
         CPPUNIT_ASSERT( gmtl::makeRot<gmtl::Matrix33f>( gmtl::EulerAngleXYZf( gmtl::Math::deg2Rad( 90.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 0.0f ) ) ) == mat );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat.mData[x] = a;
         expected_result33.set( 0, 0, 1,
                                0, 1, 0,
                                -1, 0, 0  );
         gmtl::setRot( mat, gmtl::EulerAngleXYZf( gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 90.0f ), gmtl::Math::deg2Rad( 0.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );

         // make sure set and make are the same...
         CPPUNIT_ASSERT( gmtl::makeRot<gmtl::Matrix33f>( gmtl::EulerAngleXYZf( gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 90.0f ), gmtl::Math::deg2Rad( 0.0f ) ) ) == mat );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat.mData[x] = a;
         expected_result33.set( 0, -1, 0,
                                1, 0, 0,
                                0, 0, 1  );
         gmtl::setRot( mat, gmtl::EulerAngleXYZf( gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 90.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );

         // make sure set and make are the same...
         CPPUNIT_ASSERT( gmtl::makeRot<gmtl::Matrix33f>( gmtl::EulerAngleXYZf( gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 90.0f ) ) ) == mat );
      }

      {
         gmtl::Matrix34f mat, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat.mData[x] = a;
         expected_result34.set( 0.683013f, 0.183013f, -0.707107f, a,
                               -0.0413633f, -0.956855f, -0.287606f, a,
                               -0.729234f, 0.225687f, -0.645974f, a   );
         gmtl::setRot( mat, gmtl::EulerAngleXYZf( gmtl::Math::deg2Rad( 156.0f ), gmtl::Math::deg2Rad( -45.0f ), gmtl::Math::deg2Rad( -15.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );

         // make sure set and make are the same...
         gmtl::Matrix34f new_mat;
         gmtl::setRot( new_mat, gmtl::EulerAngleXYZf( gmtl::Math::deg2Rad( 156.0f ), gmtl::Math::deg2Rad( -45.0f ), gmtl::Math::deg2Rad( -15.0f ) ) );
         CPPUNIT_ASSERT( gmtl::makeRot<gmtl::Matrix34f>( gmtl::EulerAngleXYZf( gmtl::Math::deg2Rad( 156.0f ), gmtl::Math::deg2Rad( -45.0f ), gmtl::Math::deg2Rad( -15.0f ) ) ) == new_mat );
      }
      {
         gmtl::Matrix34f mat, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat.mData[x] = a;
         expected_result34.set( 0, 0, 1, a,
                                0, 1, 0, a,
                                -1, 0, 0, a );
         gmtl::setRot( mat, gmtl::EulerAngleXYZf( gmtl::Math::deg2Rad( 0.0f ),
                             gmtl::Math::deg2Rad( 90.0f ),
                             gmtl::Math::deg2Rad( 0.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );

         // make sure set and make are the same...
         gmtl::Matrix34f new_mat;
         gmtl::setRot( new_mat, gmtl::EulerAngleXYZf( gmtl::Math::deg2Rad( 0.0f ),
                             gmtl::Math::deg2Rad( 90.0f ),
                             gmtl::Math::deg2Rad( 0.0f ) ) );
         CPPUNIT_ASSERT( gmtl::makeRot<gmtl::Matrix34f>( gmtl::EulerAngleXYZf( gmtl::Math::deg2Rad( 0.0f ),
                             gmtl::Math::deg2Rad( 90.0f ),
                             gmtl::Math::deg2Rad( 0.0f ) ) ) == new_mat );
      }

      {
         gmtl::Matrix44f mat, expected_result44;
         for (int x = 0; x < 16; ++x)
            mat.mData[x] = a;
         expected_result44.set( 0.697193f, 0.0121696f, 0.71678f, a,
                               -0.275553f, -0.918494f, 0.283617f, a,
                                0.66181f, -0.395247f, -0.637014f, a,
                                a, a, a, a );
         gmtl::setRot( mat, gmtl::EulerAngleXYZf( gmtl::Math::deg2Rad( -156.0f ), gmtl::Math::deg2Rad( 45.7892892f ), gmtl::Math::deg2Rad( -361.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat, eps ) );

         // make sure set and make are the same...
         gmtl::Matrix44f new_mat;
         gmtl::setRot( new_mat, gmtl::EulerAngleXYZf( gmtl::Math::deg2Rad( -156.0f ), gmtl::Math::deg2Rad( 45.7892892f ), gmtl::Math::deg2Rad( -361.0f ) ) );
         CPPUNIT_ASSERT( gmtl::makeRot<gmtl::Matrix44f>( gmtl::EulerAngleXYZf( gmtl::Math::deg2Rad( -156.0f ), gmtl::Math::deg2Rad( 45.7892892f ), gmtl::Math::deg2Rad( -361.0f ) ) ) == new_mat );
      }


      // ZYX
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat.mData[x] = a;
         expected_result33.set( 0.0f, -0.965926f, 0.258819f,
                                0.707107f, 0.183013f, 0.683013f,
                                -0.707107f, 0.183013f, 0.683013f );
         gmtl::setRot( mat, gmtl::EulerAngleZYXf( gmtl::Math::deg2Rad( 90.0f ),
                             gmtl::Math::deg2Rad( 45.0f ),
                             gmtl::Math::deg2Rad( 15.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );

         // make sure set and make are the same...
         gmtl::Matrix33f new_mat;
         gmtl::setRot( new_mat, gmtl::EulerAngleZYXf( gmtl::Math::deg2Rad( 90.0f ),
                             gmtl::Math::deg2Rad( 45.0f ),
                             gmtl::Math::deg2Rad( 15.0f ) ) );
         CPPUNIT_ASSERT( gmtl::makeRot<gmtl::Matrix33f>( gmtl::EulerAngleZYXf(
                             gmtl::Math::deg2Rad( 90.0f ), gmtl::Math::deg2Rad( 45.0f ),
                             gmtl::Math::deg2Rad( 15.0f ) ) ) == new_mat );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat.mData[x] = a;
         expected_result33.set( 0, -1, 0,
                                1, 0, 0,
                                0, 0, 1  );
         gmtl::setRot( mat, gmtl::EulerAngleZYXf( gmtl::Math::deg2Rad( 90.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 0.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );

         // make sure set and make are the same...
         gmtl::Matrix33f new_mat;
         gmtl::setRot( new_mat, gmtl::EulerAngleZYXf( gmtl::Math::deg2Rad( 90.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 0.0f ) ) );
         CPPUNIT_ASSERT( gmtl::makeRot<gmtl::Matrix33f>( gmtl::EulerAngleZYXf( gmtl::Math::deg2Rad( 90.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 0.0f ) ) ) == new_mat );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat.mData[x] = a;
         expected_result33.set( 0, 0, 1,
                                0, 1, 0,
                                -1, 0, 0  );
         gmtl::setRot( mat, gmtl::EulerAngleZYXf( gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 90.0f ), gmtl::Math::deg2Rad( 0.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );

         // make sure set and make are the same...
         gmtl::Matrix33f new_mat;
         gmtl::setRot( new_mat, gmtl::EulerAngleZYXf( gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 90.0f ), gmtl::Math::deg2Rad( 0.0f ) ) );
         CPPUNIT_ASSERT( gmtl::makeRot<gmtl::Matrix33f>( gmtl::EulerAngleZYXf( gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 90.0f ), gmtl::Math::deg2Rad( 0.0f ) ) ) == new_mat );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat.mData[x] = a;
         expected_result33.set( 1, 0, 0,
                                0, 0, -1,
                                0, 1, 0  );
         gmtl::setRot( mat, gmtl::EulerAngleZYXf( gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 90.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }

      {
         gmtl::Matrix34f mat, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat.mData[x] = a;
         expected_result34.set( -0.645974f, -0.560068f, 0.518692f, a,
                                 0.287606f, -0.807979f, -0.514249f, a,
                                 0.707107f, -0.183013f, 0.683013f, a  );
         gmtl::setRot( mat, gmtl::EulerAngleZYXf( gmtl::Math::deg2Rad( 156.0f ), gmtl::Math::deg2Rad( -45.0f ), gmtl::Math::deg2Rad( -15.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );
      }
      {
         gmtl::Matrix34f mat, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat.mData[x] = a;
         expected_result34.set( 0, 0, 1, a,
                                0, 1, 0, a,
                                -1, 0, 0, a );
         gmtl::setRot( mat, gmtl::EulerAngleZYXf( gmtl::Math::deg2Rad( 0.0f ), gmtl::Math::deg2Rad( 90.0f ), gmtl::Math::deg2Rad( 0.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );
      }

      {
         gmtl::Matrix44f mat, expected_result44;
         for (int x = 0; x < 16; ++x)
            mat.mData[x] = a;
         expected_result44.set( -0.637014f, 0.418103f, -0.647613f, a,
                                -0.283617f, -0.908318f, -0.30744f, a,
                                -0.71678f, -0.0121696f, 0.697193f, a,
                                 a, a, a, a );
         gmtl::setRot( mat, gmtl::EulerAngleZYXf( gmtl::Math::deg2Rad( -156.0f ), gmtl::Math::deg2Rad( 45.7892892f ), gmtl::Math::deg2Rad( -361.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat, eps ) );
      }


      // ZXY
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat.mData[x] = a;
         expected_result33.set( -0.183013f, -0.707107f, 0.683013f,
                                 0.965926f, 0.0f,       0.258819f,
                                -0.183013f, 0.707107f,  0.683013f );
         gmtl::setRot( mat, gmtl::EulerAngleZXYf( gmtl::Math::deg2Rad( 90.0f ),
                             gmtl::Math::deg2Rad( 45.0f ),
                             gmtl::Math::deg2Rad( 15.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat.mData[x] = a;
         expected_result33.set( 0, -1, 0,
                                1, 0, 0,
                                0, 0, 1  );
         gmtl::setRot( mat, gmtl::EulerAngleZXYf( gmtl::Math::deg2Rad( 90.0f ),
                             gmtl::Math::deg2Rad( 0.0f ),
                             gmtl::Math::deg2Rad( 0.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat.mData[x] = a;
         expected_result33.set( 1, 0,  0,
                                0, 0, -1,
                                0, 1,  0  );
         gmtl::setRot( mat, gmtl::EulerAngleZXYf( gmtl::Math::deg2Rad( 0.0f ),
                             gmtl::Math::deg2Rad( 90.0f ),
                             gmtl::Math::deg2Rad( 0.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }
      {
         gmtl::Matrix33f mat, expected_result33;
         for (int x = 0; x < 9; ++x)
            mat.mData[x] = a;
         expected_result33.set(  0, 0, 1,
                                 0, 1, 0,
                                -1, 0, 0  );
         gmtl::setRot( mat, gmtl::EulerAngleZXYf( gmtl::Math::deg2Rad( 0.0f ),
                             gmtl::Math::deg2Rad( 0.0f ),
                             gmtl::Math::deg2Rad( 90.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result33, mat, eps ) );
      }

      {
         gmtl::Matrix34f mat, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat.mData[x] = a;
         expected_result34.set( -0.956855f, -0.287606f, -0.0413633f, a,
                                 0.225687f, -0.645974f, -0.729234f,  a,
                                 0.183013f, -0.707107f,  0.683013f,  a  );
         gmtl::setRot( mat, gmtl::EulerAngleZXYf( gmtl::Math::deg2Rad( 156.0f ),
                             gmtl::Math::deg2Rad( -45.0f ),
                             gmtl::Math::deg2Rad( -15.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );
      }
      {
         gmtl::Matrix34f mat, expected_result34;
         for (int x = 0; x < 12; ++x)
            mat.mData[x] = a;
         expected_result34.set( 1, 0,  0, a,
                                0, 0, -1, a,
                                0, 1,  0, a );
         gmtl::setRot( mat, gmtl::EulerAngleZXYf( gmtl::Math::deg2Rad( 0.0f ),
                             gmtl::Math::deg2Rad( 90.0f ),
                             gmtl::Math::deg2Rad( 0.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat, eps ) );
      }

      {
         gmtl::Matrix44f mat, expected_result44;
         for (int x = 0; x < 16; ++x)
            mat.mData[x] = a;
         expected_result44.set( -0.918494f, 0.283617f, -0.275553f, a,
                                -0.395247f, -0.637014f, 0.66181f, a,
                                 0.0121696f, 0.71678f, 0.697193f, a,
                                 a, a, a, a );
         gmtl::setRot( mat, gmtl::EulerAngleZXYf( gmtl::Math::deg2Rad( -156.0f ),
                             gmtl::Math::deg2Rad( 45.7892892f ),
                             gmtl::Math::deg2Rad( -361.0f ) ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat, eps ) );
      }


      // --- Test standalone setRot(val,val,val) against setRot(mat,val,val,val) -- //
      {
         gmtl::Matrix44f mat, expected_mat;
         gmtl::setRot(expected_mat, gmtl::EulerAngleXYZf( 0.1f, 2.3f, -2.1f ) );
         mat = gmtl::makeRot<gmtl::Matrix44f>( gmtl::EulerAngleXYZf( 0.1f, 2.3f, -2.1f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( mat, expected_mat, eps ) );

         gmtl::setRot(expected_mat, gmtl::EulerAngleZXYf( 0.1f, 2.3f, -2.1f ) );
         mat = gmtl::makeRot<gmtl::Matrix44f>( gmtl::EulerAngleZXYf( 0.1f, 2.3f, -2.1f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( mat, expected_mat, eps ) );

         gmtl::setRot(expected_mat, gmtl::EulerAngleZYXf( 0.1f, 2.3f, -2.1f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( gmtl::makeRot<gmtl::Matrix44f>(
                                        gmtl::EulerAngleZYXf( 0.1f, 2.3f, -2.1f ) ),
                                        expected_mat, eps ) );
      }

      {
         gmtl::Matrix33f mat, expected_mat;
         gmtl::setRot(expected_mat, gmtl::EulerAngleXYZf( 0.1f, 2.3f, -2.1f));
         mat = gmtl::makeRot<gmtl::Matrix33f>( gmtl::EulerAngleXYZf( 0.1f, 2.3f, -2.1f));
         CPPUNIT_ASSERT( gmtl::isEqual( mat, expected_mat, eps ) );

         gmtl::setRot(expected_mat, gmtl::EulerAngleZXYf( 0.1f, 2.3f, -2.1f ) );
         mat = gmtl::makeRot<gmtl::Matrix33f>( gmtl::EulerAngleZXYf( 0.1f, 2.3f, -2.1f ));
         CPPUNIT_ASSERT( gmtl::isEqual( mat, expected_mat, eps ) );

         gmtl::setRot(expected_mat, gmtl::EulerAngleZYXf( 0.1f, 2.3f, -2.1f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( gmtl::makeRot<gmtl::Matrix33f>( gmtl::EulerAngleZYXf( 0.1f, 2.3f, -2.1f ) ),
                                        expected_mat, eps ) );
      }

      {
         gmtl::Matrix34f mat, expected_mat;
         gmtl::setRot(expected_mat, gmtl::EulerAngleXYZf( 0.1f, 2.3f, -2.1f ));
         mat = gmtl::makeRot<gmtl::Matrix34f>( gmtl::EulerAngleXYZf( 0.1f, 2.3f, -2.1f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( mat, expected_mat, eps ) );

         gmtl::setRot(expected_mat, gmtl::EulerAngleZXYf( 0.1f, 2.3f, -2.1f ) );
         mat = gmtl::makeRot<gmtl::Matrix34f>( gmtl::EulerAngleZXYf( 0.1f, 2.3f, -2.1f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( mat, expected_mat, eps ) );

         gmtl::setRot(expected_mat, gmtl::EulerAngleZYXf( 0.1f, 2.3f, -2.1f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( gmtl::makeRot<gmtl::Matrix34f>( gmtl::EulerAngleZYXf( 0.1f, 2.3f, -2.1f ) ),
                                        expected_mat, eps ) );
      }
   }

   template <typename EulerType>
   class exhaustiveEulerGetSet
   {
   public:
      /** Systematically set all possible euler angles and convert to matrix and back to check
       * for "good" get of the values from the euler.
       */
      static void go()
      {
         const float eps = 0.01f;
         const float angle_inc = 10.0f;
         const float angle_range = 190.0f;

         for(float a = -angle_range; a != angle_range; a += angle_inc)
         {
            for(float b = -angle_range; b != angle_range; b += angle_inc)
            {
               for(float c = -angle_range; c != angle_range; c += angle_inc)
               {
                  gmtl::Matrix44f mat1, mat2;
                  EulerType euler2;

                  EulerType euler1( gmtl::Math::deg2Rad(a), gmtl::Math::deg2Rad(b), gmtl::Math::deg2Rad(c));
                  gmtl::set( mat1, euler1);

                  gmtl::set( euler2, mat1);
                  gmtl::set( mat2, euler2);

                  if(!gmtl::isEqual(mat1,mat2,eps))
                  {
                     // CPPUNIT_ASSERT(gmtl::isEqual(mat1,mat2,eps));
                     std::cout << "Failed euler get set: [" << typeid(EulerType).name()
                               << "]: (" << a << "," << "," << b << "," << c << ")" << std::endl;
                  }
               }
            }
         }
      }
   };

   void MatrixGenTest::testMatrixGetSetRotEuler()
   {
      exhaustiveEulerGetSet<gmtl::EulerAngleXYZf>::go();
      exhaustiveEulerGetSet<gmtl::EulerAngleZXYf>::go();
      exhaustiveEulerGetSet<gmtl::EulerAngleZYXf>::go();
   }


   template <typename DATA_TYPE>
   class matMakeInverse
   {
   public:
      static void go()
      {
         gmtl::Matrix<DATA_TYPE, 4, 4> mat1, expected_value, result, identity;
         DATA_TYPE eps = 0.001;
         mat1.set( 0.78,  1.4,   2.9, 3.45,
                   4.21, 57.9,  65.9, 74.6,
                   89.2, 99.2,  10.9, 11.9,
                   12.5, 13.9, 14.78, 15.6 );
         expected_value.set( 0.3071733,  -0.0239700,   0.0034853,   0.0440345,
                            -0.2891106,   0.0216826,   0.0079218,  -0.0457924,
                            -3.0532152,   0.0305681,  -0.0547335,   0.5708037,
                             2.9041982,  -0.0290744,   0.0420053,  -0.4711792 );

         // Make sure our pre-computed answer is right
         gmtl::mult( result, mat1, expected_value );
         CPPUNIT_ASSERT( gmtl::isEqual( result, identity, eps ) );

         // Test inversion
         result = gmtl::makeInvert( mat1 );
         CPPUNIT_ASSERT( gmtl::isEqual( result, expected_value, eps ) );
      }
   };

   void MatrixGenTest::testMatrixmakeInverse()
   {
      matMakeInverse<float>::go();
      matMakeInverse<double>::go();
   }

   void MatrixGenMetricTest::testTimingsetTrans()
   {
      gmtl::Matrix33f mat33;
      gmtl::Matrix34f mat34;
      gmtl::Matrix44f mat44;
      float a = 1.0f;

      const long iters(25000);

      // 2D translation
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setTrans( mat33, gmtl::Vec2f( a, 2 ) );
         a += mat33.mData[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setTrans(mat33f,vec2f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat33.mData[3] != 1234.0456f && a != 987654.321f  );


      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setTrans( mat33, gmtl::Vec3f( 1, a, 1.0f ) ); // homogeneous
         a += mat33.mData[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setTrans(mat33f,vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat33.mData[3] != 1234.0456f && a != 987654.321f  );


      // 3D translation
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setTrans( mat34, gmtl::Vec3f( a, 32, 121 ) );
         a += mat34.mData[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setTrans(mat34f,vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat34.mData[3] != 1234.0456f && a != 987654.321f  );


      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setTrans( mat44, gmtl::Vec3f( 30, a, 121 ) );
         a += mat44.mData[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setTrans(mat44f,vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat44.mData[3] != 1234.0456f && a != 987654.321f  );


      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setTrans( mat44, gmtl::Vec4f( 30, 32, a, 1.0f ) ); // homogeneous
         a += mat44.mData[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setTrans(mat44f,vec4f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat44.mData[3] != 1234.0456f && a != 987654.321f  );
   }
   /*
   void MatrixGenMetricTest::testTimingMakeTransStatic()
   {
      gmtl::Matrix22f mat22;
      gmtl::Matrix33f mat33;
      gmtl::Matrix34f mat34;
      gmtl::Matrix44f mat44;
      gmtl::Matrix43f mat43;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeTrans( mat22, Vec2f( 1, 2 ) );
         gmtl::makeTrans( mat33, Vec3f( 30, 32, 121 ) );
         gmtl::makeTrans( mat34, Vec3f( 30, 32, 121 ) );
         gmtl::makeTrans( mat43, Vec3f( 30, 32, 121 ) );
         gmtl::makeTrans( mat44, Vec3f( 30, 32, 121 ) );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeScale", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   */

   void MatrixGenMetricTest::testTimingsetScale()
   {
      float a = 2.1f;
      gmtl::Matrix33f mat33;
      gmtl::Matrix34f mat34;
      gmtl::Matrix44f mat44;
      gmtl::Matrix<float, 4, 3> mat43;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setScale( mat33, gmtl::Vec2f( a, 2 ) );
         a += mat33.mData[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setScale(mat33f,vec2f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat33.mData[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setScale( mat34, gmtl::Vec3f( 30, 32, a ) );
         a += mat34.mData[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setScale(mat34f,vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat34.mData[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setScale( mat43, gmtl::Vec3f( 30, 32, a ) );
         a += mat43.mData[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setScale(mat43f,vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat43.mData[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setScale( mat44, gmtl::Vec3f( 30, 32, a ) );
         a += mat44.mData[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setScale(mat44f,vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat44.mData[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setScale( mat33, a );
         a += mat33.mData[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setScale(mat33f,f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat33.mData[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setScale( mat34, a );
         a += mat34.mData[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setScale(mat34f,f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat34.mData[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setScale( mat43, a );
         a += mat43.mData[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setScale(mat43f,f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat43.mData[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setScale( mat44, a );
         a += mat44.mData[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setScale(mat44f,f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat44.mData[3] != 1234.0456f && a != 987654.321f  );
   }

   /*
   void MatrixGenMetricTest::testTimingMakeScaleStatic()
   {
      gmtl::Matrix22f mat22;
      gmtl::Matrix33f mat33;
      gmtl::Matrix34f mat34;
      gmtl::Matrix44f mat44;
      gmtl::Matrix43f mat43;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::makeScale( mat22, Vec2f( 1, 2 ) );
         gmtl::makeScale( mat33, Vec3f( 30, 32, 121 ) );
         gmtl::makeScale( mat34, Vec3f( 30, 32, 121 ) );
         gmtl::makeScale( mat43, Vec3f( 30, 32, 121 ) );
         gmtl::makeScale( mat44, Vec3f( 30, 32, 121 ) );
         gmtl::makeScale( mat33, 2.0f );
         gmtl::makeScale( mat34, 3.0f );
         gmtl::makeScale( mat43, 4.0f );
         gmtl::makeScale( mat44, 5.0f );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeScale", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   */

   void MatrixGenMetricTest::testTimingsetRot33()
   {
      gmtl::Matrix33f mat;
      float a = 0.0f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setRot( mat, gmtl::AxisAnglef( gmtl::Math::deg2Rad( a ), 1.0f, 0.0f, 0.0f ) );
         a += mat.mData[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setRot33f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( mat.mData[3] != 1234.0456f && a != 987654.321f  );
   }

   void MatrixGenMetricTest::testTimingsetRot34()
   {
      gmtl::Matrix34f mat;
      float a = 0.0f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setRot( mat, gmtl::AxisAnglef( gmtl::Math::deg2Rad( a ), 1.0f, 0.0f, 0.0f ) );
         a += mat.mData[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setRot34f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat.mData[3] != 1234.0456f && a != 987654.321f  );
   }

   void MatrixGenMetricTest::testTimingsetRot44()
   {
      gmtl::Matrix44f mat;
      float a = 0.0f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setRot( mat, gmtl::AxisAnglef( gmtl::Math::deg2Rad( a ), 1.0f, 0.0f, 0.0f ) );
         a += mat.mData[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setRot44f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat.mData[3] != 1234.0456f && a != 987654.321f  );
   }

   /*
   void MatrixGenMetricTest::testTimingMakeRot33Static()
   {
      gmtl::bok<gmtl::Matrix33f>( (float)1.0f );
      gmtl::Matrix<float, 3, 3> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix33f>( 90.0f, 1.0f, 0.0f, 0.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRot33Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void MatrixGenMetricTest::testTimingMakeRot34Static()
   {
      gmtl::Matrix<float, 3, 4> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix34f>( 90.0f, 1.0f, 0.0f, 0.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRot34Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void MatrixGenMetricTest::testTimingMakeRot44Static()
   {
      gmtl::Matrix<float, 4, 4> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix44f>( 90.0f, 1.0f, 0.0f, 0.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRot44Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   */


   void MatrixGenMetricTest::testTimingGetRot()
   {
      /// @todo ... write a setRot( rad, axis, mat ) test here....
      CPPUNIT_ASSERT(false);
   }


   // makeRot Euler tests...

   void MatrixGenMetricTest::testTimingsetRotEuler33()
   {
      gmtl::Matrix33f mat;
      float a = 0;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setRot( mat, gmtl::EulerAngleZXYf( a, 45.0f, 35.0f ) );
         a -= mat.mData[4];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setRotEuler(mat33f,ZXY)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat.mData[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setRot( mat, gmtl::EulerAngleZYXf( a, 45.0f, 35.0f ) );
         a += mat.mData[4];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setRotEuler(mat33f,ZYX)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat.mData[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setRot( mat, gmtl::EulerAngleXYZf( a, 45.0f, 35.0f ) );
         a -= mat.mData[4];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setRotEuler(mat33f,XYZ)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat.mData[3] != 1234.0456f && a != 987654.321f  );
   }

   void MatrixGenMetricTest::testTimingsetRotEuler34()
   {
      gmtl::Matrix34f mat;
      float a = 0;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setRot( mat, gmtl::EulerAngleZXYf( a, 45.0f, 35.0f ) );
         a -= mat.mData[4];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setRotEuler(mat34f,ZXY)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat.mData[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setRot( mat, gmtl::EulerAngleZYXf( a, 45.0f, 35.0f ) );
         a += mat.mData[4];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setRotEuler(mat34f,ZYX)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat.mData[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setRot( mat, gmtl::EulerAngleXYZf( a, 45.0f, 35.0f ) );
         a -= mat.mData[4];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setRotEuler(mat34f,XYZ)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat.mData[3] != 1234.0456f && a != 987654.321f  );
   }

   void MatrixGenMetricTest::testTimingsetRotEuler44()
   {
      gmtl::Matrix44f mat;
      float a = 0;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setRot( mat, gmtl::EulerAngleZXYf( a, 45.0f, 35.0f ) );
         a -= mat.mData[4];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setRotEuler(mat44f,ZXY)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat.mData[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setRot( mat, gmtl::EulerAngleZYXf( a, 45.0f, 35.0f ) );
         a += mat.mData[4];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setRotEuler(mat44f,ZYX)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat.mData[3] != 1234.0456f && a != 987654.321f  );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setRot( mat, gmtl::EulerAngleXYZf( a, 45.0f, 35.0f ) );
         a -= mat.mData[4];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setRotEuler(mat44f,XYZ)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat.mData[3] != 1234.0456f && a != 987654.321f  );
   }
   /*
   void MatrixGenMetricTest::testTimingMakeRotEuler33Static()
   {
      gmtl::Matrix<float, 3, 3> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix33f>( 90.0f, 45.0f, 35.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRotEuler33Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void MatrixGenMetricTest::testTimingMakeRotEuler34Static()
   {
      gmtl::Matrix<float, 3, 4> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix34f>( 90.0f, 45.0f, 35.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRotEuler34Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void MatrixGenMetricTest::testTimingMakeRotEuler44Static()
   {
      gmtl::Matrix44f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix44f>( 90.0f, 45.0f, 35.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeRotEuler44Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   */

   void MatrixGenMetricTest::testTimingsetDirCos33()
   {
      gmtl::Matrix33f mat;
      float a = 0.0f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setDirCos( mat, gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( a,1,0 ), gmtl::Vec3f( 0,0,1 ) );
         a += mat.mData[1];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setDirCos33f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat.mData[3] != 1234.0456f && a != 987654.321f  );
   }

   void MatrixGenMetricTest::testTimingsetDirCos34()
   {
      gmtl::Matrix34f mat;
      float a = 0.0f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setDirCos( mat, gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( a,1,0 ), gmtl::Vec3f( 0,0,1 ) );
         a += mat.mData[1];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setDirCos34f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat.mData[3] != 1234.0456f && a != 987654.321f  );
   }

   void MatrixGenMetricTest::testTimingsetDirCos44()
   {
      gmtl::Matrix44f mat;
      float a = 0.0f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setDirCos( mat, gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( a,1,0 ), gmtl::Vec3f( 0,0,1 ) );
         a += mat.mData[1];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setDirCos44f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat.mData[3] != 1234.0456f && a != 987654.321f );
   }
   /*
   void MatrixGenMetricTest::testTimingMakeDirCos33Static()
   {
      gmtl::Matrix<float, 3, 3> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix33f>( 90.0f, 45.0f, 35.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeDirCos33Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void MatrixGenMetricTest::testTimingMakeDirCos34Static()
   {
      gmtl::Matrix<float, 3, 4> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix34f>( 90.0f, 45.0f, 35.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeDirCos34Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void MatrixGenMetricTest::testTimingMakeDirCos44Static()
   {
      gmtl::Matrix44f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeRot<gmtl::Matrix44f>( 90.0f, 45.0f, 35.0f );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeDirCos44Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   */

   void MatrixGenMetricTest::testTimingsetAxes33()
   {
      gmtl::Matrix33f mat;
      float a = 0.0f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setAxes( mat, gmtl::Vec3f( 1,a,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
         a += mat.mData[1];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setAxes33f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat.mData[3] != 1234.0456f && a != 987654.321f );
   }

   void MatrixGenMetricTest::testTimingsetAxes34()
   {
      gmtl::Matrix34f mat;
      float a = 0.0f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setAxes( mat, gmtl::Vec3f( 1,a,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
         a += mat.mData[1];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setAxes34f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat.mData[3] != 1234.0456f && a != 987654.321f );
   }

   void MatrixGenMetricTest::testTimingsetAxes44()
   {
      gmtl::Matrix44f mat;
      float a = 0.0f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setAxes( mat, gmtl::Vec3f( 1,a,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
         a += mat.mData[1];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/setAxes44f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat.mData[3] != 1234.0456f && a != 987654.321f );
   }
   /*
   void MatrixGenMetricTest::testTimingMakeAxes33Static()
   {
      gmtl::Matrix<float, 3, 3> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeAxes<gmtl::Matrix33f>( gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeAxes33Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void MatrixGenMetricTest::testTimingMakeAxes34Static()
   {
      gmtl::Matrix<float, 3, 4> mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeAxes<gmtl::Matrix34f>( gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeAxes34Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void MatrixGenMetricTest::testTimingMakeAxes44Static()
   {
      gmtl::Matrix44f mat;
      const long iters(100000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
         mat = gmtl::makeAxes<gmtl::Matrix44f>( gmtl::Vec3f( 1,0,0 ), gmtl::Vec3f( 0,1,0 ), gmtl::Vec3f( 0,0,1 ) );
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixGenTest/MakeAxes44Static", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   */

   // is this a convert test?
   void MatrixGenMetricTest::testTimingsetAxes()
   {
      CPPUNIT_ASSERT(false);
//      gmtl::Matrix44f mat1, mat2;
//      gmtl::Vec3f xAxis1,yAxis1,zAxis1;
//      gmtl::Vec3f xAxis2,yAxis2,zAxis2;



      /*
      // Simple rotation around X axis
      mat1.makeRot(90,gmtl::XUnitVec3);
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
      */
   }
}

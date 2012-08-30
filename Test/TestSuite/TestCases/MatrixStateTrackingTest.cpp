// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "MatrixStateTrackingTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Matrix.h>
#include <gmtl/EulerAngle.h>
#include <gmtl/AxisAngle.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Generate.h>
#include <gmtl/Xforms.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION( MatrixStateTrackingTest );

   void MatrixStateTrackingTest::testMatrixStateTracking()
   {
      /*
      const int num_states = 7;
      gmtl::Matrix44f::XformState all_states[num_states] = {
         gmtl::Matrix44f::IDENTITY,
         gmtl::Matrix44f::TRANS,
         gmtl::Matrix44f::ORTHOGONAL,
         gmtl::Matrix44f::AFFINE,
         gmtl::Matrix44f::NON_UNISCALE,
         gmtl::Matrix44f::FULL,
         gmtl::Matrix44f::XFORM_ERROR
      };
      */

      const int num_teststates = 8;
      int test_states[num_teststates] = {
         gmtl::Matrix44f::IDENTITY,
         gmtl::Matrix44f::TRANS,
         gmtl::Matrix44f::ORTHOGONAL,
         gmtl::Matrix44f::AFFINE,
         gmtl::Matrix44f::NON_UNISCALE,
         gmtl::Matrix44f::AFFINE | gmtl::Matrix44f::NON_UNISCALE,
         gmtl::Matrix44f::FULL,
         gmtl::Matrix44f::XFORM_ERROR
      };

      // test combine utility func
      {
         int expected[num_teststates * num_teststates] = {
            gmtl::Matrix44f::IDENTITY, // ident
            gmtl::Matrix44f::TRANS,
            gmtl::Matrix44f::ORTHOGONAL,
            gmtl::Matrix44f::AFFINE,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::AFFINE | gmtl::Matrix44f::NON_UNISCALE,
            gmtl::Matrix44f::FULL,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::TRANS,    // trans
            gmtl::Matrix44f::TRANS,
            gmtl::Matrix44f::AFFINE,
            gmtl::Matrix44f::AFFINE,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::AFFINE | gmtl::Matrix44f::NON_UNISCALE,
            gmtl::Matrix44f::FULL,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::ORTHOGONAL,    // ORTHOGONAL
            gmtl::Matrix44f::AFFINE,
            gmtl::Matrix44f::ORTHOGONAL,
            gmtl::Matrix44f::AFFINE,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::AFFINE | gmtl::Matrix44f::NON_UNISCALE,
            gmtl::Matrix44f::FULL,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::AFFINE,    // AFFINE
            gmtl::Matrix44f::AFFINE,
            gmtl::Matrix44f::AFFINE,
            gmtl::Matrix44f::AFFINE,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::AFFINE | gmtl::Matrix44f::NON_UNISCALE,
            gmtl::Matrix44f::FULL,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::XFORM_ERROR,    // NON_UNISCALE
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::AFFINE | gmtl::Matrix44f::NON_UNISCALE,    // AFFINE | NON_UNISCALE
            gmtl::Matrix44f::AFFINE | gmtl::Matrix44f::NON_UNISCALE,
            gmtl::Matrix44f::AFFINE | gmtl::Matrix44f::NON_UNISCALE,
            gmtl::Matrix44f::AFFINE | gmtl::Matrix44f::NON_UNISCALE,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::AFFINE | gmtl::Matrix44f::NON_UNISCALE,
            gmtl::Matrix44f::FULL,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::FULL,    // FULL
            gmtl::Matrix44f::FULL,
            gmtl::Matrix44f::FULL,
            gmtl::Matrix44f::FULL,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::FULL,
            gmtl::Matrix44f::FULL,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::XFORM_ERROR,    // XFORM_ERROR
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::XFORM_ERROR,
            gmtl::Matrix44f::XFORM_ERROR
         };

         int total = 0;
         for (int x = 0; x < num_teststates; ++x)
         for (int y = 0; y < num_teststates; ++y)
         {
            CPPUNIT_ASSERT( gmtl::combineMatrixStates( test_states[x], test_states[y] ) == expected[total] );
            ++total;
         }
      }

   // test core matrix class
      // test default constructor
      {
         gmtl::Matrix44f mat;
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::IDENTITY );
      }

      // test copy constructor
      {
         gmtl::Matrix44f mat1;
         mat1.mState = gmtl::Matrix44f::FULL;
         gmtl::Matrix44f mat2( mat1 );
         CPPUNIT_ASSERT( mat2.mState == gmtl::Matrix44f::FULL );
      }

      // test set
      {
         gmtl::Matrix44f mat;
         mat.set( 0,1,2,3, 4,5,6,7, 8,9,10,11, 12,13,14,15 );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::FULL );
      }

      // test setTranspose
      {
         gmtl::Matrix44f mat;
         float data[16];
         mat.setTranspose( data );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::FULL );
      }

   // matrix ops

      // test Identity
      {
         gmtl::Matrix44f mat;
         gmtl::identity( mat );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::IDENTITY );

         // make sure identity() sets the flag when matrix wasn't originally identity
         mat.mState = gmtl::Matrix44f::FULL;
         gmtl::identity( mat );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::IDENTITY );
      }

      // test zero
      {
         gmtl::Matrix44f mat;
         gmtl::zero( mat );
      }

      // test composing two mats
      {
         for (int x = 0; x < num_teststates; ++x)
         for (int y = 0; y < num_teststates; ++y)
         {
            // operator*(mat, mat)
            {
               gmtl::Matrix44f mat1, mat2, result;
               mat1.mState = test_states[x];
               mat2.mState = test_states[y];
               result = mat1 * mat2;
               CPPUNIT_ASSERT( result.mState == gmtl::combineMatrixStates( test_states[x], test_states[y] ) && "operator*( mat, mat ) does not combine matrix states properly" );
               result = mat2 * mat1;
               CPPUNIT_ASSERT( result.mState == gmtl::combineMatrixStates( test_states[x], test_states[y] ) && "operator*( mat, mat ) does not combine matrix states properly" );
            }

            // mult(res, mat, mat)
            {
               gmtl::Matrix44f mat1, mat2, result;
               mat1.mState = test_states[x];
               mat2.mState = test_states[y];
               gmtl::mult( result, mat1, mat2 );
               CPPUNIT_ASSERT( result.mState == gmtl::combineMatrixStates( test_states[x], test_states[y] ) && "mult(res, mat, mat) does not combine matrix states properly" );
               gmtl::mult( result, mat2, mat1 );
               CPPUNIT_ASSERT( result.mState == gmtl::combineMatrixStates( test_states[x], test_states[y] ) && "mult(res, mat, mat) does not combine matrix states properly" );
            }

            // preMult(res, mat)
            {
               gmtl::Matrix44f mat1, result;
               mat1.mState = test_states[x];
               result.mState = test_states[y];
               gmtl::preMult( result, mat1 );
               CPPUNIT_ASSERT( result.mState == gmtl::combineMatrixStates( test_states[x], test_states[y] ) && "preMult(res, mat) does not combine matrix states properly" );
               gmtl::preMult( result, mat1 );
               CPPUNIT_ASSERT( result.mState == gmtl::combineMatrixStates( test_states[x], test_states[y] ) && "preMult(res, mat) does not combine matrix states properly" );
            }

            // postMult(res, mat)
            {
               gmtl::Matrix44f mat1, result;
               mat1.mState = test_states[x];
               result.mState = test_states[y];
               gmtl::postMult( result, mat1 );
               CPPUNIT_ASSERT( result.mState == gmtl::combineMatrixStates( test_states[x], test_states[y] ) && "postMult(res, mat) does not combine matrix states properly" );
               gmtl::postMult( result, mat1 );
               CPPUNIT_ASSERT( result.mState == gmtl::combineMatrixStates( test_states[x], test_states[y] ) && "postMult(res, mat) does not combine matrix states properly" );
            }

            // add(res, mat, mat), sub(res, mat, mat)
            {
               gmtl::Matrix44f mat1, mat2, result;
               mat1.mState = test_states[x];
               mat2.mState = test_states[y];
               gmtl::add( result, mat1, mat2 );
               CPPUNIT_ASSERT( result.mState == gmtl::combineMatrixStates( test_states[x], test_states[y] ) && "postMult(res, mat, mat) does not combine matrix states properly" );
               gmtl::add( result, mat2, mat1 );
               CPPUNIT_ASSERT( result.mState == gmtl::combineMatrixStates( test_states[x], test_states[y] ) && "postMult(res, mat, mat) does not combine matrix states properly" );

               gmtl::sub( result, mat1, mat2 );
               CPPUNIT_ASSERT( result.mState == gmtl::combineMatrixStates( test_states[x], test_states[y] ) && "sub(res, mat, mat) does not combine matrix states properly" );
               gmtl::sub( result, mat2, mat1 );
               CPPUNIT_ASSERT( result.mState == gmtl::combineMatrixStates( test_states[x], test_states[y] ) && "sub(res, mat, mat) does not combine matrix states properly" );
            }

            // mult(res, mat, scalar)
            {
               gmtl::Matrix44f mat1, result;
               mat1.mState = test_states[x];
               gmtl::mult( result, mat1, 45.0f );
               CPPUNIT_ASSERT( result.mState == mat1.mState && "mult(res, mat, scalar) does not propogate matrix states properly" );
            }

            // mult(res, scalar)
            {
               gmtl::Matrix44f result;
               result.mState = test_states[x];
               gmtl::mult( result, 45.0f );
               CPPUNIT_ASSERT( result.mState == test_states[x] && "mult(res, scalar) does not set matrix state properly" );
            }

            // operator*=(mat, mat)
            {
               gmtl::Matrix44f mat1, result;

               mat1.mState = test_states[x];
               result.mState = test_states[y];
               result *= mat1;
               CPPUNIT_ASSERT( result.mState == gmtl::combineMatrixStates( test_states[x], test_states[y] ) && "operator*=( mat, mat ) does not combine matrix states properly" );

               mat1.mState = test_states[x];
               result.mState = test_states[y];
               mat1 *= result;
               CPPUNIT_ASSERT( mat1.mState == gmtl::combineMatrixStates( test_states[x], test_states[y] ) && "operator*=( mat, mat ) does not combine matrix states properly" );
            }
         }
      }

   // test =, ==, !=, isEqual
      {
         gmtl::Matrix44f mat1, result;
         mat1.mState = gmtl::Matrix44f::ORTHOGONAL;

         result.mState = gmtl::Matrix44f::FULL;
         result = mat1;
         CPPUNIT_ASSERT( result.mState == gmtl::Matrix44f::ORTHOGONAL );

         // make sure they are still equal (== and != shouldn't observe the mState)
         result.mState = gmtl::Matrix44f::FULL;
         CPPUNIT_ASSERT( !(result != mat1) );

         result.mState = gmtl::Matrix44f::ORTHOGONAL;
         CPPUNIT_ASSERT( result == mat1 );

         result.mState = gmtl::Matrix44f::FULL;
         CPPUNIT_ASSERT( gmtl::isEqual( result, mat1, 0.0001f ) );
      }

   // generators

      // test setScale
      {
         gmtl::Matrix44f mat, mat2;
         gmtl::setScale( mat, 2345.0f );
         //int bok1 = (gmtl::Matrix44f::AFFINE);
         //int bok2 = (gmtl::Matrix44f::NON_UNISCALE);
         //int bok = (gmtl::Matrix44f::AFFINE | gmtl::Matrix44f::NON_UNISCALE);
         CPPUNIT_ASSERT( mat.mState == (gmtl::Matrix44f::AFFINE | gmtl::Matrix44f::NON_UNISCALE) );

         mat2 = gmtl::makeScale<gmtl::Matrix44f>( 2345.0f );
         CPPUNIT_ASSERT( mat2.mState == (gmtl::Matrix44f::AFFINE | gmtl::Matrix44f::NON_UNISCALE) );
      }

      // test setScale
      {
         gmtl::Matrix44f mat, mat2;
         gmtl::setScale( mat, gmtl::Vec3f( 983.0f, 234.0f, 1.0f ) );
         CPPUNIT_ASSERT( mat.mState == (gmtl::Matrix44f::AFFINE | gmtl::Matrix44f::NON_UNISCALE) );

         mat2 = gmtl::makeScale<gmtl::Matrix44f>( gmtl::Vec3f( 983.0f, 234.0f, 1.0f ) );
         CPPUNIT_ASSERT( mat2.mState == (gmtl::Matrix44f::AFFINE | gmtl::Matrix44f::NON_UNISCALE) );
      }

      // test setTrans
      {
         gmtl::Matrix44f mat, mat2;

         // set
         gmtl::setTrans( mat, gmtl::Vec3f( 983.0f, 234.0f, 1.0f ) );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::TRANS );

         mat.mState = gmtl::Matrix44f::FULL;
         gmtl::setTrans( mat, gmtl::Vec3f( 983.0f, 234.0f, 1.0f ) );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::FULL );

         mat.mState = gmtl::Matrix44f::ORTHOGONAL;
         gmtl::setTrans( mat, gmtl::Vec3f( 983.0f, 234.0f, 1.0f ) );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         mat.mState = gmtl::Matrix44f::AFFINE;
         gmtl::setTrans( mat, gmtl::Vec3f( 983.0f, 234.0f, 1.0f ) );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         // make
         mat2 = gmtl::makeTrans<gmtl::Matrix44f>( gmtl::Vec3f( 983.0f, 234.0f, 1.0f ) );
         CPPUNIT_ASSERT( mat2.mState == gmtl::Matrix44f::TRANS );
      }


      // test setRot( axisangle )
      {
         gmtl::AxisAnglef rot( 90, gmtl::Vec3f( 0.0f, 1.0f, 0.0f ) );
         gmtl::Matrix44f mat, mat2;

         // set
         gmtl::setRot( mat, rot );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::ORTHOGONAL );

         mat.mState = gmtl::Matrix44f::ORTHOGONAL;
         gmtl::setRot( mat, rot );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::ORTHOGONAL );

         mat.mState = gmtl::Matrix44f::TRANS;
         gmtl::setRot( mat, rot );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         mat.mState = gmtl::Matrix44f::AFFINE;
         gmtl::setRot( mat, rot );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         mat.mState = gmtl::Matrix44f::FULL;
         gmtl::setRot( mat, rot );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::FULL );

         // make
         mat2 = gmtl::makeRot<gmtl::Matrix44f>( rot );
         CPPUNIT_ASSERT( mat2.mState == gmtl::Matrix44f::ORTHOGONAL );
      }

      // test setRot( eulerangle )
      {
         gmtl::EulerAngleXYZf rot;
         gmtl::Matrix44f mat, mat2;

         // set
         gmtl::setRot( mat, rot );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::ORTHOGONAL );

         mat.mState = gmtl::Matrix44f::ORTHOGONAL;
         gmtl::setRot( mat, rot );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::ORTHOGONAL );

         mat.mState = gmtl::Matrix44f::TRANS;
         gmtl::setRot( mat, rot );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         mat.mState = gmtl::Matrix44f::AFFINE;
         gmtl::setRot( mat, rot );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         mat.mState = gmtl::Matrix44f::FULL;
         gmtl::setRot( mat, rot );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::FULL );

         // make
         mat2 = gmtl::makeRot<gmtl::Matrix44f>( rot );
         CPPUNIT_ASSERT( mat2.mState == gmtl::Matrix44f::ORTHOGONAL );
      }

      // test setRot( Quatf )
      {
         gmtl::Quatf rot;
         gmtl::Matrix44f mat, mat2;

         // set
         gmtl::setRot( mat, rot );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::ORTHOGONAL );

         mat.mState = gmtl::Matrix44f::ORTHOGONAL;
         gmtl::setRot( mat, rot );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::ORTHOGONAL );

         mat.mState = gmtl::Matrix44f::TRANS;
         gmtl::setRot( mat, rot );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         mat.mState = gmtl::Matrix44f::AFFINE;
         gmtl::setRot( mat, rot );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         mat.mState = gmtl::Matrix44f::FULL;
         gmtl::setRot( mat, rot );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::FULL );

         // make
         mat2 = gmtl::makeRot<gmtl::Matrix44f>( rot );
         CPPUNIT_ASSERT( mat2.mState == gmtl::Matrix44f::ORTHOGONAL );
      }

      // test setFrustum()
      {
         gmtl::Matrix44f mat;

         gmtl::setFrustum( mat,  1.0f,2.0f,3.0f,4.0f,5.0f,6.0f );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::FULL );

         mat.mState = gmtl::Matrix44f::ORTHOGONAL;
         gmtl::setFrustum( mat, 1.0f,2.0f,3.0f,4.0f,5.0f,6.0f );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::FULL );
      }

      // test setPerspective()
      {
         gmtl::Matrix44f mat;

         gmtl::setPerspective( mat, 60.0f, 1.33f, 0.0004f, 100.0f );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::FULL );

         mat.mState = gmtl::Matrix44f::ORTHOGONAL;
         gmtl::setPerspective( mat, 60.0f, 1.33f, 0.0004f, 100.0f );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::FULL );
      }

      // test setRot( matrix )
      /*
      {
         gmtl::Matrix44f rot;
         gmtl::Matrix44f mat, mat2;

         // set
         gmtl::setRot( mat, rot );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::ORTHOGONAL );

         mat.mState = gmtl::Matrix44f::ORTHOGONAL;
         gmtl::setRot( mat, rot );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::ORTHOGONAL );

         mat.mState = gmtl::Matrix44f::TRANS;
         gmtl::setRot( mat, rot );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         mat.mState = gmtl::Matrix44f::AFFINE;
         gmtl::setRot( mat, rot );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         mat.mState = gmtl::Matrix44f::FULL;
         gmtl::setRot( mat, rot );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::FULL );

         // make
         mat2 = gmtl::makeRot<gmtl::Matrix44f>( rot );
         CPPUNIT_ASSERT( mat2.mState == gmtl::Matrix44f::ORTHOGONAL );
      }
      */

      // test set( coordveceuler )
      {
         gmtl::Coord3fXYZ xform;
         gmtl::Matrix44f mat, mat2;

         // set
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         mat.mState = gmtl::Matrix44f::ORTHOGONAL;
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         mat.mState = gmtl::Matrix44f::TRANS;
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         mat.mState = gmtl::Matrix44f::AFFINE;
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         mat.mState = gmtl::Matrix44f::FULL;
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         // make
         mat2 = gmtl::make<gmtl::Matrix44f>( xform );
         CPPUNIT_ASSERT( mat2.mState == gmtl::Matrix44f::AFFINE );
      }

      // test set( coordvecquat )
      {
         gmtl::Coord3fQuat xform;
         gmtl::Matrix44f mat, mat2;

         // set
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         mat.mState = gmtl::Matrix44f::ORTHOGONAL;
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         mat.mState = gmtl::Matrix44f::TRANS;
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         mat.mState = gmtl::Matrix44f::AFFINE;
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         mat.mState = gmtl::Matrix44f::FULL;
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         // make
         mat2 = gmtl::make<gmtl::Matrix44f>( xform );
         CPPUNIT_ASSERT( mat2.mState == gmtl::Matrix44f::AFFINE );
      }

      // test set( coordvecquat )
      {
         gmtl::Coord3fAxisAngle xform;
         gmtl::Matrix44f mat, mat2;

         // set
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         mat.mState = gmtl::Matrix44f::ORTHOGONAL;
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         mat.mState = gmtl::Matrix44f::TRANS;
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         mat.mState = gmtl::Matrix44f::AFFINE;
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         mat.mState = gmtl::Matrix44f::FULL;
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::AFFINE );

         // make
         mat2 = gmtl::make<gmtl::Matrix44f>( xform );
         CPPUNIT_ASSERT( mat2.mState == gmtl::Matrix44f::AFFINE );
      }

      // test set( quat )
      {
         gmtl::Quatf xform;
         gmtl::Matrix44f mat, mat2;

         // set
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::ORTHOGONAL );

         mat.mState = gmtl::Matrix44f::ORTHOGONAL;
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::ORTHOGONAL );

         mat.mState = gmtl::Matrix44f::TRANS;
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::ORTHOGONAL );

         mat.mState = gmtl::Matrix44f::AFFINE;
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::ORTHOGONAL );

         mat.mState = gmtl::Matrix44f::FULL;
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::ORTHOGONAL );

         // make
         mat2 = gmtl::make<gmtl::Matrix44f>( xform );
         CPPUNIT_ASSERT( mat2.mState == gmtl::Matrix44f::ORTHOGONAL );
      }

      // test set( AxisAnglef )
      {
         gmtl::AxisAnglef xform;
         gmtl::Matrix44f mat, mat2;

         // set
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::ORTHOGONAL );

         mat.mState = gmtl::Matrix44f::ORTHOGONAL;
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::ORTHOGONAL );

         mat.mState = gmtl::Matrix44f::TRANS;
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::ORTHOGONAL );

         mat.mState = gmtl::Matrix44f::AFFINE;
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::ORTHOGONAL );

         mat.mState = gmtl::Matrix44f::FULL;
         gmtl::set( mat, xform );
         CPPUNIT_ASSERT( mat.mState == gmtl::Matrix44f::ORTHOGONAL );

         // make
         mat2 = gmtl::make<gmtl::Matrix44f>( xform );
         CPPUNIT_ASSERT( mat2.mState == gmtl::Matrix44f::ORTHOGONAL );
      }


   // test invert()
      {
         for (int x = 0; x < num_teststates; ++x)
         {
            // invertFull(result, mat)
            {
               gmtl::Matrix44f result, mat;
               mat.mState = test_states[x];
               gmtl::invertFull( result, mat );
               CPPUNIT_ASSERT( result.mState == mat.mState && "invertFull(result, mat) does not transfer matrix state properly" );
            }
            // invertTrans(result, mat)
            {
               gmtl::Matrix44f result, mat;
               mat.mState = test_states[x];
               gmtl::invertTrans( result, mat );
               CPPUNIT_ASSERT( result.mState == mat.mState && "invertTrans(result, mat) does not transfer matrix state properly" );
            }
            // invertOrthogonal(result, mat)
            {
               gmtl::Matrix44f result, mat;
               mat.mState = test_states[x];
               gmtl::invertOrthogonal( result, mat );
               CPPUNIT_ASSERT( result.mState == mat.mState && "invertOrthogonal(result, mat) does not transfer matrix state properly" );
            }
            // invertAffine(result, mat)
            {
               gmtl::Matrix44f result, mat;
               mat.mState = test_states[x];
               gmtl::invertAffine( result, mat );
               CPPUNIT_ASSERT( result.mState == mat.mState && "invertAffine(result, mat) does not transfer matrix state properly" );
            }
         }

         gmtl::Matrix44f mat;
         float eps = 0.0001f;
      // gmtl::Matrix44f::IDENTITY:
         {
            mat.set( 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 );
            mat.mState = gmtl::Matrix44f::IDENTITY;
            gmtl::Matrix44f iv( mat ), iv_full( mat ), iv_affine( mat ), iv_trans( mat ), iv_ortho( mat ), iv_nochange( mat );
            gmtl::invert( iv );
            gmtl::invertFull( iv_full, iv_full );
            CPPUNIT_ASSERT( gmtl::isEqual( iv, iv_nochange, eps ) && gmtl::isEqual( iv, iv_full, eps ) && "invert(IDENTITY) funcs do not match" );
         }
      // gmtl::Matrix44f::TRANS:
         {
            mat.set( 1,0,0,4,
                     0,1,0,5,
                     0,0,1,6,
                     0,0,0,1 );
            mat.mState = gmtl::Matrix44f::TRANS;
            gmtl::Matrix44f iv( mat ), iv_full( mat ), iv_affine( mat ), iv_trans( mat ), iv_ortho( mat ), iv_nochange( mat );
            gmtl::invert( iv );
            gmtl::invertFull( iv_full, iv_full );
            gmtl::invertTrans( iv_trans, iv_trans );
            CPPUNIT_ASSERT( gmtl::isEqual( iv, iv_trans, eps ) && gmtl::isEqual( iv, iv_full, eps ) && "invert(TRANS 4x4) funcs do not match" );
         }
         // TODO: invertFull only works with nxn matrices (fix!!!!!)
         /*
         {
            gmtl::Matrix34f mat;
            mat.set( 1,0,0,4,
                     0,1,0,5,
                     0,0,1,6 );
            mat.mState = gmtl::Matrix44f::TRANS;
            gmtl::Matrix34f iv( mat ), iv_full( mat ), iv_affine( mat ), iv_trans( mat ), iv_ortho( mat ), iv_nochange( mat );
            gmtl::invert( iv );
            gmtl::invertFull( iv_full, iv_full );
            gmtl::invertTrans( iv_trans, iv_trans );
            CPPUNIT_ASSERT( gmtl::isEqual( iv, iv_trans, eps ) && gmtl::isEqual( iv, iv_full, eps ) && "invert(TRANS 3x4) funcs do not match" );
         }
         */
      // gmtl::Matrix44f::ORTHOGONAL:
         {
            mat.set( 0,0,-1,0,
                     1,0,0,0,
                     0,-1,0,0,
                     0,0,0,1 );
            mat.mState = gmtl::Matrix44f::ORTHOGONAL;
            gmtl::Matrix44f iv( mat ), iv_full( mat ), iv_affine( mat ), iv_trans( mat ), iv_ortho( mat ), iv_nochange( mat );
            gmtl::invert( iv );
            gmtl::invertFull( iv_full, iv_full );
            gmtl::invertOrthogonal( iv_ortho, iv_ortho );
            CPPUNIT_ASSERT( gmtl::isEqual( iv, iv_ortho, eps ) && gmtl::isEqual( iv, iv_full, eps ) && "invert(ORTHOGONAL) funcs do not match" );
         }
      // gmtl::Matrix44f::AFFINE:
         {
            mat.set( 0,1,0, 10,
                     0,0,-1,11,
                     -1,0,0,12,
                     0,0,0,1 );
            mat.mState = gmtl::Matrix44f::AFFINE;
            gmtl::Matrix44f iv( mat ), iv_full( mat ), iv_affine( mat ), iv_trans( mat ), iv_ortho( mat ), iv_nochange( mat );
            gmtl::invert( iv );
            gmtl::invertFull( iv_full, iv_full );
            gmtl::invertAffine( iv_affine, iv_affine );
            CPPUNIT_ASSERT( gmtl::isEqual( iv, iv_affine, eps ) && gmtl::isEqual( iv, iv_full, eps ) && "invert(AFFINE) funcs do not match" );
         }
         {
            mat.set( 0,1,0, 10,
                     0,0,-1,11,
                     -1,0,0,12,
                     0,0,0,20057 );
            mat.mState = gmtl::Matrix44f::AFFINE;
            gmtl::Matrix44f iv( mat ), iv_full( mat ), iv_affine( mat ), iv_trans( mat ), iv_ortho( mat ), iv_nochange( mat );
            gmtl::invert( iv );
            gmtl::invertFull( iv_full, iv_full );
            gmtl::invertAffine( iv_affine, iv_affine );
            CPPUNIT_ASSERT( gmtl::isEqual( iv, iv_affine, eps ) && gmtl::isEqual( iv, iv_full, eps ) && "invert(AFFINE with uniform scale) funcs do not match" );
         }
      // gmtl::Matrix44f::AFFINE | gmtl::Matrix44f::NON_UNISCALE:
         {
            mat.set( 0,2,0, 10,
                     0,0,-8,11,
                     -3,0,0,12,
                     0,0,0,1 );
            mat.mState = gmtl::Matrix44f::AFFINE | gmtl::Matrix44f::NON_UNISCALE;
            gmtl::Matrix44f iv( mat ), iv_full( mat ), iv_affine( mat ), iv_trans( mat ), iv_ortho( mat ), iv_nochange( mat );
            gmtl::invert( iv );
            gmtl::invertFull( iv_full, iv_full );
            gmtl::invertAffine( iv_affine, iv_affine );
            CPPUNIT_ASSERT( gmtl::isEqual( iv, iv_affine, eps ) && gmtl::isEqual( iv, iv_full, eps ) && "invert(AFFINE with NON_UNISCALE) funcs do not match" );
         }
         {
            mat.set( 0,2,0, 10,
                     0,0,-8,11,
                     -3,0,0,12,
                     0,0,0,23489 );
            mat.mState = gmtl::Matrix44f::AFFINE | gmtl::Matrix44f::NON_UNISCALE;
            gmtl::Matrix44f iv( mat ), iv_full( mat ), iv_affine( mat ), iv_trans( mat ), iv_ortho( mat ), iv_nochange( mat );
            gmtl::invert( iv );
            gmtl::invertFull( iv_full, iv_full );
            gmtl::invertAffine( iv_affine, iv_affine );
            CPPUNIT_ASSERT( gmtl::isEqual( iv, iv_affine, eps ) && gmtl::isEqual( iv, iv_full, eps ) && "invert(AFFINE with NON_UNISCALE and uniform scale) funcs do not match" );
         }
      // gmtl::Matrix44f::FULL:
         {
            mat.set( 1,2,3,13,
                     4,5,6,14,
                     7,8,9,15,
                     10,11,12,16 );
            mat.mState = gmtl::Matrix44f::FULL;
            gmtl::Matrix44f iv( mat ), iv_full( mat ), iv_affine( mat ), iv_trans( mat ), iv_ortho( mat ), iv_nochange( mat );
            gmtl::invert( iv );
            gmtl::invertFull( iv_full, iv_full );
            CPPUNIT_ASSERT( gmtl::isEqual( iv, iv_full, eps ) && "invert(AFFINE|NON_UNISCALE) funcs do not match" );
         }
      }
   }
}

// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "ConvertTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>

#include <gmtl/QuatOps.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Generate.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(ConvertTest);

   void ConvertTest::testConvertVecToPureQuat()
   {
      const float eps = 0.0001f;
      gmtl::Vec<float, 3> vec( 1.0f, 2.0f, 3.0f );
      gmtl::Quat<float> quat( 4.0f, 5.0f, 6.0f, 1.0f ), bok, expected( 1.0f, 2.0f, 3.0f, 0.0f );

      bok = gmtl::setPure( quat, vec );
      CPPUNIT_ASSERT( gmtl::isEqual( expected, quat, eps ) );
      CPPUNIT_ASSERT( gmtl::isEqual( expected, bok, eps ) );
   }

   void ConvertTest::testConvertQuatMat_MatQuat()
   {
      float eps = 0.0001f;
//      gmtl::Vec3f xAxis1, yAxis1, zAxis1;
      gmtl::Matrix44f mat1, mat2;
      gmtl::Quatf quat0, quat1;

      // identity, quat0 -> mat1 -> quat1 -> mat2
      quat0 = gmtl::Quatf();
      gmtl::set( mat1, quat0 ); // mat1 = quat0
      gmtl::set( quat1, mat1 ); // quat1 = mat1
      CPPUNIT_ASSERT( gmtl::isEqual( quat0, quat1, eps ) );
      // make sure we get the same mat as we started
      gmtl::set( mat2, quat1  ); // mat2 = quat1
      CPPUNIT_ASSERT( gmtl::isEqual( mat2, mat1, eps ) );

      // identity, mat1 -> quat0 -> mat2 -> quat1
      mat1 = gmtl::MAT_IDENTITY44F;
      gmtl::set( quat0, mat1 ); // quat0 = mat1
      gmtl::set( mat2, quat0 ); // mat2 = quat0
      CPPUNIT_ASSERT( gmtl::isEqual( mat1, mat2, eps ) );
      // make sure we get the same quat as we started
      gmtl::set( quat1, mat2 ); // quat1 = mat2
      CPPUNIT_ASSERT( gmtl::isEqual( quat0, quat1, eps ) );

      // Simple rotation around XAxis
      mat1 = gmtl::make<gmtl::Matrix44f>( gmtl::makeNormal( gmtl::AxisAnglef(
                                                gmtl::Math::deg2Rad( 90.0f ), 1.0f, 0.0f, 0.0f) ) );
      gmtl::set( quat0, mat1 ); // quat0 = mat1
      gmtl::set( mat2, quat0 ); // mat2 = quat0
      CPPUNIT_ASSERT( gmtl::isEqual( mat1, mat2, eps ) );
      // make sure we get the same quat as we started
      gmtl::set( quat1, mat2 ); // quat1 = mat2
      CPPUNIT_ASSERT( gmtl::isEqual( quat0, quat1, eps ) );

      // more complex rotation  mat1 -> quat0 -> mat2 -> quat1
      mat1 = gmtl::make<gmtl::Matrix44f>( gmtl::makeNormal( gmtl::AxisAnglef(
                                                gmtl::Math::deg2Rad( 123.4f ), 1.0f, 1.0f, -1.0f ) ) );
      gmtl::set( quat0, mat1 ); // quat0 = mat1
      gmtl::set( mat2, quat0 ); // mat2 = quat0
      CPPUNIT_ASSERT( gmtl::isEqual( mat1, mat2, eps ) );
      // make sure we get the same quat as we started
      gmtl::set( quat1, mat2 ); // quat1 = mat2
      CPPUNIT_ASSERT( gmtl::isEqual( quat0, quat1, eps ) );

      // more complex rotation  quat0 -> mat1 -> quat1 -> mat2
      quat0 = gmtl::make<gmtl::Quatf>( gmtl::makeNormal( gmtl::AxisAnglef(
                                                gmtl::Math::deg2Rad( 123.4f ), 1.0f, 1.0f, -1.0f ) ) );
      CPPUNIT_ASSERT( gmtl::isEqual( quat0, quat1, eps ) );
      gmtl::set( mat1, quat0 ); // mat1 = quat0
      gmtl::set( quat1, mat1 ); // quat1 = mat1
      CPPUNIT_ASSERT( gmtl::isEqual( quat0, quat1, eps ) );
      // make sure we get the same quat as we started
      gmtl::set( mat2, quat1  ); // mat2 = quat1
      CPPUNIT_ASSERT( gmtl::isEqual( mat2, mat1, eps ) );

      // more complex rotation
      mat1 = gmtl::make<gmtl::Matrix44f>( gmtl::EulerAngleXYZf( 45.0f, -89.0f, 32.45f ) );
      gmtl::set( quat0, mat1 ); // quat0 = mat1
      gmtl::set( mat2, quat0 ); // mat2 = quat0
      CPPUNIT_ASSERT( gmtl::isEqual( mat1, mat2, eps ) );
      // make sure we get the same quat as we started
      gmtl::set( quat1, mat2 ); // quat1 = mat2
      CPPUNIT_ASSERT( gmtl::isEqual( quat0, quat1, eps ) );

      // really test it out...  mat1 -> quat0 -> mat2 -> quat1
      for (float x = -gmtl::Math::PI; x < gmtl::Math::PI; x += 0.2)
      for (float y = -gmtl::Math::PI; y < gmtl::Math::PI; y += 0.2)
      for (float z = -gmtl::Math::PI; z < gmtl::Math::PI; z += 0.2)
      {
         // more complex rotation
         mat1 = gmtl::make<gmtl::Matrix44f>( gmtl::EulerAngleXYZf( x, y, z ) );
         gmtl::set( quat0, mat1 ); // quat0 = mat1
         gmtl::set( mat2, quat0 ); // mat2 = quat0
         CPPUNIT_ASSERT( gmtl::isEqual( mat1, mat2, eps ) );
         // make sure we get the same quat as we started
         gmtl::set( quat1, mat2 ); // quat1 = mat2
         CPPUNIT_ASSERT( gmtl::isEquiv( quat0, quat1, eps ) );
      }

      // really test it out...  quat0 -> mat1 -> quat1 -> mat2
      for (float x = -gmtl::Math::PI; x < gmtl::Math::PI; x += 0.2)
      for (float y = -gmtl::Math::PI; y < gmtl::Math::PI; y += 0.2)
      for (float z = -gmtl::Math::PI; z < gmtl::Math::PI; z += 0.2)
      {
         // more complex rotation
         quat0 = gmtl::make<gmtl::Quatf>( gmtl::EulerAngleXYZf( x, y, z ) );
         gmtl::set( mat1, quat0 ); // quat0 = mat1
         gmtl::set( quat1, mat1 ); // mat2 = quat0
         CPPUNIT_ASSERT( gmtl::isEquiv( quat0, quat1, eps ) );
         // make sure we get the same quat as we started
         gmtl::set( mat2, quat1 ); // quat1 = mat2
         CPPUNIT_ASSERT( gmtl::isEqual( mat1, mat2, eps ) );
      }

      // make a 44 matrix by hand... (with positive 3x3 diagonal)
      gmtl::Matrix44f mat44a, mat44b;
      mat44a.set( 0.0f, 1.0f, 0.0f, 0.0f,
                 -1.0f, 0.0f, 0.0f, 0.0f,
                  0.0f, 0.0f, 1.0f, 0.0f,
                  0.0f, 0.0f, 0.0f, 1.0f );
      gmtl::set( quat0, mat44a ); // quat0 = mat44a
      gmtl::set( mat44b, quat0 ); // mat44b = quat0
      CPPUNIT_ASSERT( gmtl::isEqual( mat44a, mat44b, eps ) );
      // make sure we get the same quat as we started
      gmtl::set( quat1, mat44b ); // quat1 = mat2
      CPPUNIT_ASSERT( gmtl::isEqual( quat0, quat1, eps ) );

      // make a 44 matrix by hand... (with negative 3x3 diagonal)
      mat44a.set( 0.0f, -1.0f, 0.0f, 0.0f,
                 -1.0f, 0.0f, 0.0f, 0.0f,
                  0.0f, 0.0f, -1.0f, 0.0f,
                  0.0f, 0.0f, 0.0f, 1.0f );
      gmtl::set( quat0, mat44a ); // quat0 = mat44a
      gmtl::set( mat44b, quat0 ); // mat44b = quat0
      CPPUNIT_ASSERT( gmtl::isEqual( mat44a, mat44b, eps ) );
      // make sure we get the same quat as we started
      gmtl::set( quat1, mat44b ); // quat1 = mat2
      CPPUNIT_ASSERT( gmtl::isEqual( quat0, quat1, eps ) );

      // make a 34 matrix by hand... (with negative diag)
      gmtl::Matrix34f mat34a, mat34b;
      mat34a.set( 0.0f, -1.0f, 0.0f, 0.0f,
                 -1.0f, 0.0f, 0.0f, 0.0f,
                  0.0f, 0.0f, -1.0f, 0.0f  );
      gmtl::set( quat0, mat34a ); // quat0 = mat34a
      gmtl::set( mat34b, quat0 ); // mat34b = quat0
      CPPUNIT_ASSERT( gmtl::isEqual( mat34a, mat34b, eps ) );
      // make sure we get the same quat as we started
      gmtl::set( quat1, mat34b ); // quat1 = mat2
      CPPUNIT_ASSERT( gmtl::isEqual( quat0, quat1, eps ) );

      // make a 33 matrix by hand... (with positive diag)
      gmtl::Matrix33f mat33a, mat33b;
      mat33a.set( 0.0f, 1.0f, 0.0f,
                 -1.0f, 0.0f, 0.0f,
                  0.0f, 0.0f, 1.0f );
      gmtl::set( quat0, mat33a ); // quat0 = mat33a
      gmtl::set( mat33b, quat0 ); // mat33b = quat0
      CPPUNIT_ASSERT( gmtl::isEqual( mat33a, mat33b, eps ) );
      // make sure we get the same quat as we started
      gmtl::set( quat1, mat33b ); // quat1 = mat2
      CPPUNIT_ASSERT( gmtl::isEqual( quat0, quat1, eps ) );

      /// @todo allen, you need to look at this (you wrote it), it doesn't pass the test, Im guessing it is because the 3 coordinate axes are not square...

      // Make orthonormal matrix
      /*
      xAxis1.set( 7.0f, 11.0f, 21.0f );
      yAxis1.set( 12.0f, 21.0f, 75.0f );
      zAxis1 = gmtl::cross( xAxis1, yAxis1 );
      gmtl::normalize( xAxis1 );
      gmtl::normalize( yAxis1 );
      gmtl::normalize( zAxis1 );
      gmtl::makeAxes( mat1, xAxis1, yAxis1, zAxis1 );
      gmtl::set( quat0, mat1 ); // quat0 = mat1
      gmtl::set( mat2, quat0 ); // mat2 = quat0
      CPPUNIT_ASSERT( gmtl::isEqual( mat1, mat2, eps ) );
      // make sure we get the same quat as we started
      gmtl::set( quat1, mat2 ); // quat1 = mat2
      CPPUNIT_ASSERT( gmtl::isEquiv( quat0, quat1, eps ) );
      */
   }
}

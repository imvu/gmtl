// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include <sstream>
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include "OutputTest.h"

#include <gmtl/Vec.h>
#include <gmtl/Tri.h>
#include <gmtl/Matrix.h>
#include <gmtl/Plane.h>
#include <gmtl/Point.h>
#include <gmtl/Quat.h>
#include <gmtl/Sphere.h>
#include <gmtl/Output.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(OutputTest);

   void OutputTest::testVec()
   {
      std::ostringstream out1;
      gmtl::Vec<int, 1> v1;
      v1.set( 1 );
      out1 << v1;
      CPPUNIT_ASSERT( out1.str() == "(1)" );

      std::ostringstream out2;
      gmtl::Vec<int, 2> v2( 1, 2 );
      out2 << v2;
      CPPUNIT_ASSERT( out2.str() == "(1, 2)" );

      std::ostringstream out3;
      gmtl::Vec<int, 3> v3( 1, 2, 3 );
      out3 << v3;
      CPPUNIT_ASSERT( out3.str() == "(1, 2, 3)" );

      std::ostringstream out4;
      gmtl::Vec<int,3> v4(1,1,1);
      out4 << (v3+v4);
      CPPUNIT_ASSERT( out4.str() == "(2, 3, 4)" );
   }

   void OutputTest::testPoint()
   {
      std::ostringstream out1;
      gmtl::Point<int, 1> p1;
      p1.set( 1 );
      out1 << p1;
      CPPUNIT_ASSERT( out1.str() == "(1)" );

      std::ostringstream out2;
      gmtl::Point<int, 2> p2( 1, 2 );
      out2 << p2;
      CPPUNIT_ASSERT( out2.str() == "(1, 2)" );

      std::ostringstream out3;
      gmtl::Point<int, 3> p3( 1, 2, 3 );
      out3 << p3;
      CPPUNIT_ASSERT( out3.str() == "(1, 2, 3)" );
   }

   void OutputTest::testMatrix()
   {
      std::stringstream out1;
      gmtl::Matrix<int, 1, 1> m11;
      m11(0,0) = 1;
      out1 << m11;
      CPPUNIT_ASSERT( out1.str() == "| 1 |\n" );

      std::stringstream out2;
      gmtl::Matrix<int, 2, 2> m22;
      m22.set( 1, 2,
               3, 4 );
      out2 << m22;
      CPPUNIT_ASSERT( out2.str() == "| 1 2 |\n| 3 4 |\n" );

      std::stringstream out3;
      gmtl::Matrix<int, 3, 4> m34;
      m34.set( 1,  2,  3,  4,
               5,  6,  7,  8,
               9, 10, 11, 12 );
      out3 << m34;
      CPPUNIT_ASSERT( out3.str() == "| 1 2 3 4 |\n| 5 6 7 8 |\n| 9 10 11 12 |\n" );
   }

   void OutputTest::testQuat()
   {
      std::stringstream out1;
      gmtl::Quat<int> q1( 1, 2, 3, 4 );
      out1 << q1;
      CPPUNIT_ASSERT( out1.str() == "(1, 2, 3, 4)" );
   }

   void OutputTest::testTri()
   {
      std::stringstream out1;
      gmtl::Tri<int> t1(
            gmtl::Point<int, 3>(1, 2, 3),
            gmtl::Point<int, 3>(4, 5, 6),
            gmtl::Point<int, 3>(7, 8, 9)
      );
      out1 << t1;
      CPPUNIT_ASSERT( out1.str() == "(1, 2, 3), (4, 5, 6), (7, 8, 9)" );
   }

   void OutputTest::testPlane()
   {
      std::stringstream out1;
      gmtl::Plane<int> p1(
            gmtl::Vec<int, 3>(1, 2, 3),
            4
      );
      out1 << p1;
      CPPUNIT_ASSERT( out1.str() == "(1, 2, 3), 4" );
   }

   void OutputTest::testSphere()
   {
      std::stringstream out1;
      gmtl::Sphere<int> s1(
            gmtl::Point<int, 3>(1, 2, 3),
            4
      );
      out1 << s1;
      CPPUNIT_ASSERT( out1.str() == "(1, 2, 3), 4" );
   }

   void OutputTest::testAABox()
   {
      std::stringstream out1;
      gmtl::AABox<int> b1(
            gmtl::Point<int, 3>(1, 2, 3),
            gmtl::Point<int, 3>(4, 5, 6)
      );
      out1 << b1;
      CPPUNIT_ASSERT( out1.str() == "(1, 2, 3) (4, 5, 6) false" );
   }
}

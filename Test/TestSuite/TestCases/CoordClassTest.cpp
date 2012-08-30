// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "CoordClassTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Coord.h>
#include <gmtl/CoordOps.h>
#include <gmtl/EulerAngle.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(CoordClassTest);
   CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(CoordClassMetricTest, Suites::metric());

   void CoordClassTest::testCoordClassTestCreation()
   {
      // test that it initializes to the multiplication identity
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > q;
      CPPUNIT_ASSERT( q.pos()[0] == 0.0f );
      CPPUNIT_ASSERT( q.pos()[1] == 0.0f );
      CPPUNIT_ASSERT( q.pos()[2] == 0.0f );
      CPPUNIT_ASSERT( q.rot()[0] == 0.0f );
      CPPUNIT_ASSERT( q.rot()[1] == 0.0f );
      CPPUNIT_ASSERT( q.rot()[2] == 0.0f );

      // try out element constructor
      gmtl::Vec3f p( 1, 2, 3 );
      gmtl::EulerAngle<float, gmtl::XYZ> r( 4, 5, 6 );
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > q2( p, r );
      CPPUNIT_ASSERT( q2.pos()[0] == 1.0f );
      CPPUNIT_ASSERT( q2.pos()[1] == 2.0f );
      CPPUNIT_ASSERT( q2.pos()[2] == 3.0f );
      CPPUNIT_ASSERT( q2.rot()[0] == 4.0f );
      CPPUNIT_ASSERT( q2.rot()[1] == 5.0f );
      CPPUNIT_ASSERT( q2.rot()[2] == 6.0f );

      // try out copy constructor
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > q3( q2 );
      CPPUNIT_ASSERT( q3.pos()[0] == 1.0f );
      CPPUNIT_ASSERT( q3.pos()[1] == 2.0f );
      CPPUNIT_ASSERT( q3.pos()[2] == 3.0f );
      CPPUNIT_ASSERT( q3.rot()[0] == 4.0f );
      CPPUNIT_ASSERT( q3.rot()[1] == 5.0f );
      CPPUNIT_ASSERT( q3.rot()[2] == 6.0f );

      // try out operator=() function
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > q4;
      CPPUNIT_ASSERT( q4.pos()[0] == 0.0f );
      CPPUNIT_ASSERT( q4.pos()[1] == 0.0f );
      CPPUNIT_ASSERT( q4.pos()[2] == 0.0f );
      CPPUNIT_ASSERT( q4.rot()[0] == 0.0f );
      CPPUNIT_ASSERT( q4.rot()[1] == 0.0f );
      CPPUNIT_ASSERT( q4.rot()[2] == 0.0f );
      q4 = q3;
      CPPUNIT_ASSERT( q4.pos()[0] == 1.0f );
      CPPUNIT_ASSERT( q4.pos()[1] == 2.0f );
      CPPUNIT_ASSERT( q4.pos()[2] == 3.0f );
      CPPUNIT_ASSERT( q4.rot()[0] == 4.0f );
      CPPUNIT_ASSERT( q4.rot()[1] == 5.0f );
      CPPUNIT_ASSERT( q4.rot()[2] == 6.0f );

      // Instantiate one copy of all the types that we are supposed to support
      gmtl::CoordVec3EulerAngleXYZd CoordVec3EulerAngleXYZd_test();
      gmtl::CoordVec3EulerAngleXYZf CoordVec3EulerAngleXYZf_test();
      gmtl::CoordVec4EulerAngleXYZd CoordVec4EulerAngleXYZd_test();
      gmtl::CoordVec4EulerAngleXYZf CoordVec4EulerAngleXYZf_test();

      gmtl::CoordVec3EulerAngleZYXd CoordVec3EulerAngleZYXd_test();
      gmtl::CoordVec3EulerAngleZYXf CoordVec3EulerAngleZYXf_test();
      gmtl::CoordVec4EulerAngleZYXd CoordVec4EulerAngleZYXd_test();
      gmtl::CoordVec4EulerAngleZYXf CoordVec4EulerAngleZYXf_test();

      gmtl::CoordVec3EulerAngleZXYd CoordVec3EulerAngleZXYd_test();
      gmtl::CoordVec3EulerAngleZXYf CoordVec3EulerAngleZXYf_test();
      gmtl::CoordVec4EulerAngleZXYd CoordVec4EulerAngleZXYd_test();
      gmtl::CoordVec4EulerAngleZXYf CoordVec4EulerAngleZXYf_test();

      gmtl::CoordVec3AxisAngled CoordVec3AxisAngled_test();
      gmtl::CoordVec3AxisAnglef CoordVec3AxisAnglef_test();
      gmtl::CoordVec4AxisAngled CoordVec4AxisAngled_test();
      gmtl::CoordVec4AxisAnglef CoordVec4AxisAnglef_test();

      /** 3 elt types */
      gmtl::Coord3fXYZ Coord3fXYZ_test();
      gmtl::Coord3fZYX Coord3fZYX_test();
      gmtl::Coord3fZXY Coord3fZXY_test();
      gmtl::Coord3dXYZ Coord3dXYZ_test();
      gmtl::Coord3dZYX Coord3dZYX_test();
      gmtl::Coord3dZXY Coord3dZXY_test();

      /** 4 elt types */
      gmtl::Coord4fXYZ Coord4fXYZ_test();
      gmtl::Coord4fZYX Coord4fZYX_test();
      gmtl::Coord4fZXY Coord4fZXY_test();
      gmtl::Coord4dXYZ Coord4dXYZ_test();
      gmtl::Coord4dZYX Coord4dZYX_test();
      gmtl::Coord4dZXY Coord4dZXY_test();

      /** 3 elt types */
      gmtl::Coord3fQuat Coord3fQuat_test();
      gmtl::Coord3dQuat Coord3dQuat_test();

      /** 4 elt types */
      gmtl::Coord4fQuat Coord4fQuat_test();
      gmtl::Coord4dQuat Coord4dQuat_test();

      /** 3 elt types */
      gmtl::Coord3fAxisAngle Coord3fAxisAngle_test();
      gmtl::Coord3dAxisAngle Coord3dAxisAngle_test();

      /** 4 elt types */
      gmtl::Coord4fAxisAngle Coord4fAxisAngle_test();
      gmtl::Coord4dAxisAngle Coord4dAxisAngle_test();
   }

   void CoordClassTest::testMultiArgConstructors()
   {
      {
         gmtl::Coord3fXYZ coord(1, 2, 3, 4, 5, 6);
         CPPUNIT_ASSERT( coord.pos()[0] == 1 );
         CPPUNIT_ASSERT( coord.pos()[1] == 2 );
         CPPUNIT_ASSERT( coord.pos()[2] == 3 );
         CPPUNIT_ASSERT( coord.rot()[0] == 4 );
         CPPUNIT_ASSERT( coord.rot()[1] == 5 );
         CPPUNIT_ASSERT( coord.rot()[2] == 6 );
      }

      {
         gmtl::Coord4fXYZ coord(1, 2, 3, 4, 5, 6, 7);
         CPPUNIT_ASSERT( coord.pos()[0] == 1 );
         CPPUNIT_ASSERT( coord.pos()[1] == 2 );
         CPPUNIT_ASSERT( coord.pos()[2] == 3 );
         CPPUNIT_ASSERT( coord.pos()[3] == 4 );
         CPPUNIT_ASSERT( coord.rot()[0] == 5 );
         CPPUNIT_ASSERT( coord.rot()[1] == 6 );
         CPPUNIT_ASSERT( coord.rot()[2] == 7 );
      }
      
      {
         gmtl::CoordVec4AxisAnglef coord(1, 2, 3, 4, 5, 6, 7, 8);
         CPPUNIT_ASSERT( coord.pos()[0] == 1 );
         CPPUNIT_ASSERT( coord.pos()[1] == 2 );
         CPPUNIT_ASSERT( coord.pos()[2] == 3 );
         CPPUNIT_ASSERT( coord.pos()[3] == 4 );
         CPPUNIT_ASSERT( coord.rot()[0] == 5 );
         CPPUNIT_ASSERT( coord.rot()[1] == 6 );
         CPPUNIT_ASSERT( coord.rot()[2] == 7 );
         CPPUNIT_ASSERT( coord.rot()[3] == 8 );
      }

   }

   void CoordClassMetricTest::testCoordTimingDefaultConstructor()
   {
      const long iters( 400000 );
      float use_value(1);

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of def constructor
         gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > q;
         use_value += q.mPos[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("CoordTest/DefaultConstructor", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value != 0 );
   }

   void CoordClassMetricTest::testCoordTimingElementConstructor()
   {
      const long iters( 400000 );
      float use_value(1);

      gmtl::Vec3f p( 1, 2, 3 );
      gmtl::EulerAngle<float, gmtl::XYZ> r( 4, 5, 6 );
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of element constructor
         gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > q2( p, r );
         use_value += q2.mPos[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("CoordTest/ElementConstructor", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value != 0 );
   }

   void CoordClassMetricTest::testCoordTimingCopyConstructor()
   {
      const long iters( 400000 );
      float use_value(1);
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > q;

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of copy constructor
         gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > q3( q );
         use_value += q3.mPos[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("CoordTest/CopyConstructor", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value != 0 );
   }


   void CoordClassMetricTest::testCoordTimingGet()
   {
      const long iters( 400000 );
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > q;
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of get...
         use_value += use_value + q.pos()[0];
         use_value += use_value + q.rot()[0];
         q.rot()[0] -= use_value;
         q.pos()[0] -= use_value;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("CoordTest/get()", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value != 8324908723.0f );
   }

   void CoordClassMetricTest::testCoordTimingOpEqual()
   {
      const long iters( 400000 );
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > q4, q2;
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of operator=() function
         q4 = q2;
         q2.pos()[2] += q4.pos()[1];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("CoordTest/operator=()", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( q4.pos()[0] != 3498.0f );
   }
}

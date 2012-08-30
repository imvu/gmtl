// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "CoordCompareTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Coord.h>
#include <gmtl/CoordOps.h>
#include <gmtl/EulerAngle.h>
#include <gmtl/EulerAngleOps.h>
#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(CoordCompareTest);
   CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(CoordCompareMetricTest, Suites::metric());

   template<typename T>
   class testEqual
   {
   public:
      static void go()
      {
         gmtl::Vec<T, 3> p( 1, 2, 3 );
         gmtl::EulerAngle<T, gmtl::XYZ> r( 4, 5, 6 );
         gmtl::Coord<gmtl::Vec<T,3>, gmtl::EulerAngle<T, gmtl::XYZ> > coord1(p,r), coord2;
         coord1 = coord2;
         CPPUNIT_ASSERT( coord1 == coord2 );
         CPPUNIT_ASSERT( coord2 == coord1 );

         // Test that != works on all elements
         for (int j = 0; j < 3; ++j)
         {
            coord2.pos()[j] = (T)1221.0f;
            CPPUNIT_ASSERT(  (coord1 != coord2) );
            CPPUNIT_ASSERT( !(coord1 == coord2) );
            coord2.pos()[j] = coord1.pos()[j]; // put it back
            
            coord2.rot()[j] = (T)1221.0f;
            CPPUNIT_ASSERT(  (coord1 != coord2) );
            CPPUNIT_ASSERT( !(coord1 == coord2) );
            coord2.rot()[j] = coord1.rot()[j]; // put it back
         }

         // Test for epsilon equals working
         CPPUNIT_ASSERT( gmtl::isEqual( coord1, coord2 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( coord1, coord2, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( coord2, coord1, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( coord2, coord1, (T)100000.0f ) );
         T eps = (T)10.0;
         for (int j = 0; j < 3; ++j)
         {
               coord2.pos()[j] = coord1.pos()[j] - (eps / (T)2.0);
               CPPUNIT_ASSERT(  gmtl::isEqual( coord1, coord2, eps ) );
               CPPUNIT_ASSERT( !gmtl::isEqual( coord1, coord2, (T)(eps / 3.0) ) );
               coord2.pos()[j] = coord1.pos()[j]; // put it back
               
               coord2.rot()[j] = coord1.rot()[j] - (eps / (T)2.0);
               CPPUNIT_ASSERT(  gmtl::isEqual( coord1, coord2, eps ) );
               CPPUNIT_ASSERT( !gmtl::isEqual( coord1, coord2, (T)(eps / 3.0) ) );
               coord2.rot()[j] = coord1.rot()[j]; // put it back
         }
      }
   };

   void CoordCompareTest::testCoordEqualityFloatTest()
   {
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
   }

   void CoordCompareTest::testCoordEqualityDoubleTest()
   {
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
   }

   void CoordCompareMetricTest::testCoordTimingOpEqualityTest()
   {
      // Test overhead of creation
      const long iters(400000);

      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > src_coord11;
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > src_coord22;
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > src_coord33;
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > src_coord34;
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > src_coord44;
      gmtl::Coord<gmtl::Vec<double,3>, gmtl::EulerAngle<double, gmtl::XYZ> > src_coord101;

      // half of them will be equal
      src_coord11.pos()[0] = 1.0f;
      src_coord22.pos()[1] = 1.0f;
      src_coord33.pos()[2] = 2.0f;

      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > test_coord11( src_coord11 );
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > test_coord22( src_coord22 );
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > test_coord33( src_coord33 );
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > test_coord34( src_coord34 );
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > test_coord44( src_coord44 );
      gmtl::Coord<gmtl::Vec<double,3>, gmtl::EulerAngle<double, gmtl::XYZ> > test_coord101( src_coord101 );

      // half will be not equal
      src_coord34.pos()[0] = 2.0f;
      src_coord44.pos()[1] = 3.0f;
      src_coord101.pos()[2] = 1.0;

      unsigned true_count(0);

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         if (src_coord11 == test_coord11)
            ++true_count;
         if (src_coord22 == test_coord22)
            ++true_count;
         if (src_coord33 == test_coord33)
            ++true_count;
         if (src_coord34 == test_coord34)
            ++true_count;
         if (src_coord44 == test_coord44)
            ++true_count;
         if (src_coord101 == test_coord101)
            ++true_count;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("CoordCompareTest/operator==", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // Make sure the compiler doesn't optimize out true_count
      CPPUNIT_ASSERT( true_count > 0 );
   }

   void CoordCompareMetricTest::testCoordTimingOpNotEqualityTest()
   {
      // Test overhead of creation
      const long iters(400000);

      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > src_coord11;
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > src_coord22;
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > src_coord33;
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > src_coord34;
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > src_coord44;
      gmtl::Coord<gmtl::Vec<double,3>, gmtl::EulerAngle<double, gmtl::XYZ> > src_coord101;

      // half will be equal
      src_coord11.pos()[0] = 1.0f;
      src_coord22.pos()[1] = 1.0f;
      src_coord33.pos()[2] = 2.0f;

      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > test_coord11( src_coord11 );
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > test_coord22( src_coord22 );
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > test_coord33( src_coord33 );
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > test_coord34( src_coord34 );
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > test_coord44( src_coord44 );
      gmtl::Coord<gmtl::Vec<double,3>, gmtl::EulerAngle<double, gmtl::XYZ> > test_coord101( src_coord101 );

      // half will be not equal
      src_coord34.pos()[0] = 2.0f;
      src_coord44.pos()[1] = 3.0f;
      src_coord101.pos()[2] = 1.0f;

      unsigned true_count(0);

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         if (src_coord11 != test_coord11)
            ++true_count;
         if (src_coord22 != test_coord22)
            ++true_count;
         if (src_coord33 != test_coord33)
            ++true_count;
         if (src_coord34 != test_coord34)
            ++true_count;
         if (src_coord44 != test_coord44)
            ++true_count;
         if (src_coord101 != test_coord101)
            ++true_count;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("CoordCompareTest/operator!=", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // Make sure the compiler doesn't optimize out true_count
      CPPUNIT_ASSERT( true_count > 0 );
   }

   void CoordCompareMetricTest::testCoordTimingIsEqualTest()
   {
      // Test overhead of creation
      const long iters(400000);

      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > src_coord11;
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > src_coord22;
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > src_coord33;
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > src_coord34;
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > src_coord44;
      gmtl::Coord<gmtl::Vec<double,3>, gmtl::EulerAngle<double, gmtl::XYZ> > src_coord101;

      // half will be equal
      src_coord11.pos()[0] = 1.0f;
      src_coord22.pos()[1] = 1.0f;
      src_coord33.pos()[2] = 2.0f;

      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > test_coord11( src_coord11 );
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > test_coord22( src_coord22 );
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > test_coord33( src_coord33 );
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > test_coord34( src_coord34 );
      gmtl::Coord<gmtl::Vec<float,3>, gmtl::EulerAngle<float, gmtl::XYZ> > test_coord44( src_coord44 );
      gmtl::Coord<gmtl::Vec<double,3>, gmtl::EulerAngle<double, gmtl::XYZ> > test_coord101( src_coord101 );

      // half will be not equal
      src_coord34.pos()[0] = 23.0f;
      src_coord44.pos()[2] = 234.0f;
      src_coord101.pos()[1] = 1234.0f;

      unsigned true_count(0);

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         if (gmtl::isEqual( src_coord11,  test_coord11, 0.0f ))
            ++true_count;
         if (gmtl::isEqual( src_coord22,  test_coord22, 0.2f ))
            ++true_count;
         if (gmtl::isEqual( src_coord33,  test_coord33, 0.3f ))
            ++true_count;
         if (gmtl::isEqual( src_coord34,  test_coord34, 0.6f ))
            ++true_count;
         if (gmtl::isEqual( src_coord44,  test_coord44, 0.8f ))
            ++true_count;
         if (gmtl::isEqual( src_coord101, test_coord101, 111.1 ))
            ++true_count;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("CoordCompareTest/isEqual(...)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // Make sure the compiler doesn't optimize out true_count
      CPPUNIT_ASSERT( true_count > 0 );
   }
}

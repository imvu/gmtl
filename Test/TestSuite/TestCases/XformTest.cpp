// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "XformTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Generate.h>
#include <gmtl/Xforms.h>
#include <gmtl/LineSegOps.h>
#include <gmtl/RayOps.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(XformTest);
   CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(XformMetricTest, Suites::metric());

   template <typename T>
   class XformQuatVec3
   {
   public:
      static void go( char* name )
      {
         std::string n = "XformTest/operator*(quat4,vec3)";
         n += name;
         gmtl::Quat<T> q1( gmtl::makeNormal( gmtl::Quat<T>( (T)1, (T)2, (T)3, (T)4 ) ) );
         gmtl::Vec<T, 3> v2;
         v2[0] = (T)1;
         const long iters(25000);
         CPPUNIT_METRIC_START_TIMING();
         for (long iter = 0; iter < iters; ++iter)
         {
            v2 = q1 * v2;
         }
         CPPUNIT_METRIC_STOP_TIMING();
         CPPUNIT_ASSERT_METRIC_TIMING_LE( n.c_str(), iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

         n = "XformTest/xform(vec,quat4,vec3)";
         n += name;
         CPPUNIT_METRIC_START_TIMING();
         for (long iter = 0; iter < iters; ++iter)
         {
            gmtl::xform( v2, q1, v2 );
         }
         CPPUNIT_METRIC_STOP_TIMING();
         CPPUNIT_ASSERT_METRIC_TIMING_LE( n.c_str(), iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
         CPPUNIT_ASSERT( v2[0] != 13.045 );
      }
   };

// mips pro and VC7 can't handle template template params
#ifdef __GNUC__
   /** @todo Get XformMatByVecType to work outside gcc */
   template <
         template <typename, unsigned> class VEC_TYPE,
         typename T,
         unsigned VEC_SIZE,
         unsigned ROWS,
         unsigned COLS
   >
   class XformMatByVecType
   {
   public:
      static void go( char* vectype  )
      {
         char buf[20]; int rows( ROWS ), cols( COLS ), vecsize( VEC_SIZE );
         std::string n = "XformTest/operator*(mat";
         sprintf( buf, "%d", rows ); n += buf;
         sprintf( buf, "%d", cols ); n += buf;
         n += ",";
         n += vectype;
         sprintf( buf, "%d", vecsize ); n += buf;
         n += ")";
         n += typeid( T ).name();
         gmtl::Matrix<T, ROWS, COLS> q1;
         VEC_TYPE<T, VEC_SIZE> v2;
         const long iters(25000);
         CPPUNIT_METRIC_START_TIMING();
         for (long iter = 0; iter < iters; ++iter)
         {
            v2 = q1 * v2;
         }
         CPPUNIT_METRIC_STOP_TIMING();
         CPPUNIT_ASSERT_METRIC_TIMING_LE( n.c_str(), iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

         n = "XformTest/xform(";
         n += vectype;
         sprintf( buf, "%d", vecsize ); n += buf;
         n += ",mat";
         sprintf( buf, "%d", rows ); n += buf;
         sprintf( buf, "%d", cols ); n += buf;
         n += ",";
         n += vectype;
         sprintf( buf, "%d", vecsize ); n += buf;
         n += ")";
         n += typeid( T ).name();
         CPPUNIT_METRIC_START_TIMING();
         for (long iter = 0; iter < iters; ++iter)
         {
            gmtl::xform( v2, q1, v2 );
         }
         CPPUNIT_METRIC_STOP_TIMING();
         CPPUNIT_ASSERT_METRIC_TIMING_LE( n.c_str(), iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

         CPPUNIT_ASSERT( v2[0] != 1.0 );
      }
   };
#endif // __GNUC__

   void XformMetricTest::testTimingXformQuatVec3()
   {
      XformQuatVec3<float>::go( "f" );
      XformQuatVec3<double>::go( "d" );
   }

   /** @todo Get testTimingXformMatVecComplete to work outside gcc */
   void XformMetricTest::testTimingXformMatVecComplete()
   {
// mips pro and VC7 can't handle template template params
#ifdef __GNUC__
      XformMatByVecType<gmtl::Vec, float, 2, 2, 2>::go( "vec" );
      XformMatByVecType<gmtl::Vec, float, 3, 2, 3>::go( "vec" );
      XformMatByVecType<gmtl::Vec, float, 3, 3, 3>::go( "vec" );
      XformMatByVecType<gmtl::Vec, float, 4, 3, 4>::go( "vec" );
      XformMatByVecType<gmtl::Vec, float, 4, 4, 4>::go( "vec" );

      XformMatByVecType<gmtl::Vec, double, 2, 2, 2>::go( "vec" );
      XformMatByVecType<gmtl::Vec, double, 3, 2, 3>::go( "vec" );
      XformMatByVecType<gmtl::Vec, double, 3, 3, 3>::go( "vec" );
      XformMatByVecType<gmtl::Vec, double, 4, 3, 4>::go( "vec" );
      XformMatByVecType<gmtl::Vec, double, 4, 4, 4>::go( "vec" );

      XformMatByVecType<gmtl::Vec, short, 4, 4, 4>::go( "vec" );
      XformMatByVecType<gmtl::Vec, int, 4, 4, 4>::go( "vec" );
      XformMatByVecType<gmtl::Vec, long, 4, 4, 4>::go( "vec" );
#endif // __GNUC__
   }

   /** @todo Get testTimingXformMatVecPartial to work outside gcc */
   void XformMetricTest::testTimingXformMatVecPartial()
   {
// mips pro and VC7 can't handle template template params
#ifdef __GNUC__
      XformMatByVecType<gmtl::Vec, float, 2, 2, 3>::go( "vec" );
      XformMatByVecType<gmtl::Vec, float, 2, 3, 3>::go( "vec" );
      XformMatByVecType<gmtl::Vec, float, 3, 3, 4>::go( "vec" );
      XformMatByVecType<gmtl::Vec, float, 3, 4, 4>::go( "vec" );

      XformMatByVecType<gmtl::Vec, double, 2, 2, 3>::go( "vec" );
      XformMatByVecType<gmtl::Vec, double, 2, 3, 3>::go( "vec" );
      XformMatByVecType<gmtl::Vec, double, 3, 3, 4>::go( "vec" );
      XformMatByVecType<gmtl::Vec, double, 3, 4, 4>::go( "vec" );

      XformMatByVecType<gmtl::Vec, short, 3, 4, 4>::go( "vec" );
      XformMatByVecType<gmtl::Vec, int, 3, 4, 4>::go( "vec" );
      XformMatByVecType<gmtl::Vec, long, 3, 4, 4>::go( "vec" );
#endif // __GNUC__
   }

   /** @todo Get testTimingXformMatPointComplete to work outside gcc */
   void XformMetricTest::testTimingXformMatPointComplete()
   {
// mips pro and VC7 can't handle template template params
#ifdef __GNUC__
      XformMatByVecType<gmtl::Point, float, 2, 2, 2>::go( "pnt" );
      XformMatByVecType<gmtl::Point, float, 3, 2, 3>::go( "pnt" );
      XformMatByVecType<gmtl::Point, float, 3, 3, 3>::go( "pnt" );
      XformMatByVecType<gmtl::Point, float, 4, 3, 4>::go( "pnt" );
      XformMatByVecType<gmtl::Point, float, 4, 4, 4>::go( "pnt" );

      XformMatByVecType<gmtl::Point, double, 2, 2, 2>::go( "pnt" );
      XformMatByVecType<gmtl::Point, double, 3, 2, 3>::go( "pnt" );
      XformMatByVecType<gmtl::Point, double, 3, 3, 3>::go( "pnt" );
      XformMatByVecType<gmtl::Point, double, 4, 3, 4>::go( "pnt" );
      XformMatByVecType<gmtl::Point, double, 4, 4, 4>::go( "pnt" );

      XformMatByVecType<gmtl::Point, short, 4, 4, 4>::go( "pnt" );
      XformMatByVecType<gmtl::Point, int, 4, 4, 4>::go( "pnt" );
      XformMatByVecType<gmtl::Point, long, 4, 4, 4>::go( "pnt" );
#endif // __GNUC__
   }
   /** @todo Get testTimingXformMatPointPartial to work outside gcc */
   void XformMetricTest::testTimingXformMatPointPartial()
   {
// mips pro and VC7 can't handle template template params
#ifdef __GNUC__
      XformMatByVecType<gmtl::Point, float, 2, 2, 3>::go( "pnt" );
      XformMatByVecType<gmtl::Point, float, 2, 3, 3>::go( "pnt" );
      XformMatByVecType<gmtl::Point, float, 3, 3, 4>::go( "pnt" );
      XformMatByVecType<gmtl::Point, float, 3, 4, 4>::go( "pnt" );

      XformMatByVecType<gmtl::Point, double, 2, 2, 3>::go( "pnt" );
      XformMatByVecType<gmtl::Point, double, 2, 3, 3>::go( "pnt" );
      XformMatByVecType<gmtl::Point, double, 3, 3, 4>::go( "pnt" );
      XformMatByVecType<gmtl::Point, double, 3, 4, 4>::go( "pnt" );

      XformMatByVecType<gmtl::Point, short, 3, 4, 4>::go( "pnt" );
      XformMatByVecType<gmtl::Point, int, 3, 4, 4>::go( "pnt" );
      XformMatByVecType<gmtl::Point, long, 3, 4, 4>::go( "pnt" );
#endif // __GNUC__
   }

   void XformTest::testQuatVecXform()
   {
      {
         // xform() vector quat.  verify xform works...
         const float eps = 0.0001f;
         gmtl::Quat<float> q1, q2, q3, qident;
         gmtl::Vec<float, 3> vec( 0.0f, 0.0f, 1.0f ), res1, res2, res3, res4, resi, vec2( 2.0f, 5.0f, 10.0f );
         gmtl::setRot( q1, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), 0.0f, 1.0f, 0.0f ) );
         gmtl::setRot( q2, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), 1.0f, 0.0f, 0.0f ) );
         gmtl::setRot( q3, gmtl::makeNormal( gmtl::AxisAnglef( gmtl::Math::deg2Rad( 35.0f ), 1.0f, 1.0f, 0.0f ) ) );

         gmtl::Vec<float, 3> ex1( 1.0f, 0.0f, 0.0f );
         gmtl::Vec<float, 3> ex2( 0.0f, -1.0f, 0.0f );
         gmtl::Vec<float, 3> ex3( 0.40558f, -0.40558f, 0.819152f ); // this also matches xform(mat,vec)
         gmtl::Vec<float, 3> ex4( 6.32707f, 0.67293f, 9.40826f ); // this also matches xform(mat,vec)

         gmtl::xform( res1, q1, vec );
         gmtl::xform( res2, q2, vec );
         gmtl::xform( res3, q3, vec );
         gmtl::xform( res4, q3, vec2 );
         gmtl::xform( resi, qident, vec );

         CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex1, res1, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex2, res2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex3, res3, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res4, eps ) );

         // operator*() should be same as xform()
         gmtl::Vec<float, 3> res5, res6, res7, res8;
         res5 = q1 * vec;
         res6 = q2 * vec;
         res7 = q3 * vec;
         res8 = q3 * vec2;
         resi = qident * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex1, res5, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex2, res6, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex3, res7, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res8, eps ) );

         // make sure that xform(quat) yields same result as xform(mat).
         gmtl::Matrix<float, 4,4> mat;
         gmtl::setRot( mat, gmtl::makeNormal( gmtl::AxisAnglef( gmtl::Math::deg2Rad( 35.0f ), 1.0f, 1.0f, 0.0f ) ) );
         res8 = mat * vec2;
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res8, eps ) );
      }

      // make sure non unit length vectors work...
      {
         float eps = 0.001f;
         const gmtl::Vec3f vec( 10.0f,100.0f,200.0f ), expected( 10.0f, -200.0f, 100.0f );
         gmtl::Quatf rot;
         gmtl::setRot( rot, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), 1.0f,0.0f,0.0f ) );

         gmtl::Vec3f result;
         gmtl::xform( result, rot, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result, eps ) );
      }
   }

   void XformTest::weird_XformQuatVec_InvConj_SanityCheck()
   {
      // just for sanity check, inv and conj should both work
      // for the implementation of quat*vec (but conj is actually faster so we usually choose that.)
      // they both will work only in the case where quat is already normalized (a rotation quat).
      {
         float eps = 0.001f;
         const gmtl::Vec3f vec( 10.0f,-100.0f,-2000.0f ), expected( 10.0f, 2000.0f, -100.0f );
         gmtl::Quatf rot;
         gmtl::setRot( rot, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), 1.0f,0.0f,0.0f ) );

         gmtl::Vec3f result1, result2;
         result1 = gmtl::makeVec( rot * gmtl::makePure( vec ) * gmtl::makeConj( rot ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );
         result2 = gmtl::makeVec( rot * gmtl::makePure( vec ) * gmtl::makeInvert( rot ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( result1, result2, eps ) );

         // should be equal because the rotation is normalized
		 CPPUNIT_ASSERT( gmtl::isEqual( gmtl::makeConj( rot ), gmtl::makeInvert( rot ), eps ) );
      }

      // same, but without the expected value (just check that the two are equal)
      {
         float eps = 0.001f;
         const gmtl::Vec3f vec( 123.0f, -4.56f, 78.910f );
         gmtl::Quatf rot;
         gmtl::setRot( rot, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 123.4556f ), gmtl::makeNormal( gmtl::Vec3f( -79.0f,1000.0f,234.0f ) ) ) );

         gmtl::Vec3f result1, result2;
         result1 = gmtl::makeVec( rot * gmtl::makePure( vec ) * gmtl::makeConj( rot ) );
         result2 = gmtl::makeVec( rot * gmtl::makePure( vec ) * gmtl::makeInvert( rot ) );
         CPPUNIT_ASSERT( gmtl::isEqual( result1, result2, eps ) );

         // should be equal because the rotation is normalized
		 CPPUNIT_ASSERT( gmtl::isEqual( gmtl::makeConj( rot ), gmtl::makeInvert( rot ), eps ) );
      }
   }

   void XformTest::testMatLineSegXform()
   {
      gmtl::LineSegf seg;
      seg.setOrigin( gmtl::Point3f( 1.0f, 2.0f, 3.0f ) );
      seg.setDir( gmtl::Vec3f( 3.0f, 95.0f, 1.0f ) );

      gmtl::Matrix44f matrix;
      gmtl::setTrans( matrix, gmtl::Vec3f( 9.0f, 8.0f, 7.0f ) );
      gmtl::setRot( matrix, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ),
      gmtl::Vec3f( 0.0f, 1.0f, 0.0f ) ) );
      
      gmtl::LineSegf expected( gmtl::Point3f( 12, 10, 6 ), gmtl::Vec3f( 1, 95, -3 ) );
      // test xform
      gmtl::LineSegf result;
      gmtl::xform( result, matrix, seg );
      CPPUNIT_ASSERT( gmtl::isEqual( expected, result, 0.0001f ) );
      
      // test operator*
      result = matrix * seg;
      CPPUNIT_ASSERT( gmtl::isEqual( expected, result, 0.0001f ) );
      
      // test operator*=
      result = seg;
      result *= matrix;
      CPPUNIT_ASSERT( gmtl::isEqual( expected, result, 0.0001f ) );
   }
   
   void XformTest::testMatRayXform()
   {
      gmtl::Rayf seg;
      seg.setOrigin( gmtl::Point3f( 1.0f, 2.0f, 3.0f ) );
      seg.setDir( gmtl::Vec3f( 3.0f, 95.0f, 1.0f ) );

      gmtl::Matrix44f matrix;
      gmtl::setTrans( matrix, gmtl::Vec3f( 9.0f, 8.0f, 7.0f ) );
      gmtl::setRot( matrix, gmtl::AxisAnglef( gmtl::Math::deg2Rad( 90.0f ), gmtl::Vec3f( 0.0f, 1.0f, 0.0f ) ) );
      
      gmtl::Rayf expected( gmtl::Point3f( 12, 10, 6 ), gmtl::Vec3f( 1, 95, -3 ) );
      // test xform
      gmtl::Rayf result;
      gmtl::xform( result, matrix, seg );
      CPPUNIT_ASSERT( gmtl::isEqual( expected, result, 0.0001f ) );
      
      // test operator*
      result = matrix * seg;
      CPPUNIT_ASSERT( gmtl::isEqual( expected, result, 0.0001f ) );
      
      // test operator*=
      result = seg;
      result *= matrix;
      CPPUNIT_ASSERT( gmtl::isEqual( expected, result, 0.0001f ) );
   }

   void XformTest::testMatVecXform()
   {
      // really simple mat44*vec4 rotations (hard coded matrix rot)
      {
         // xform a vector by a mat.  verify the rotation worked...
         const float eps = 0.0001f;
         gmtl::Matrix<float, 4, 4> q1, q2, q3, qident;
         q1.set( 0.0f, -1.0f, 0.0f, 0.0f,  // twist 90 about Z
              1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 1.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         q2.set( 0.0f, 0.0f, 1.0f, 0.0f,   // twist 90 about Y
              0.0f, 1.0f, 0.0f, 0.0f,
              -1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         q3.set( 1.0f, 0.0f, 0.0f, 0.0f,   // twist -90 about X
              0.0f, 0.0f, 1.0f, 0.0f,
              0.0f, -1.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         gmtl::Vec<float, 4> vec( 0.0f, 0.0f, 1.0f, 0.0f ), res1, res2, res3, res4, resi, vec2( 1.0f, 1.0f, -10.0f, 0.0f );
         gmtl::Vec<float, 4> ex1( 0.0f, 0.0f, 1.0f, 0.0f );
         gmtl::Vec<float, 4> ex2( 1.0f, 0.0f, 0.0f, 0.0f );
         gmtl::Vec<float, 4> ex3( 0.0f, 1.0f, 0.0f, 0.0f );
         gmtl::Vec<float, 4> ex4( 1.0f, -10.0f, -1.0f, 0.0f );

         gmtl::xform( resi, qident, vec );
         gmtl::xform( res1, q1, vec );
         gmtl::xform( res2, q2, vec );
         gmtl::xform( res3, q3, vec );
         gmtl::xform( res4, q3, vec2 );

         CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex1, res1, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex2, res2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex3, res3, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res4, eps ) );

         resi = qident * vec;
         res1 = q1 * vec;
         res2 = q2 * vec;
         res3 = q3 * vec;
         res4 = q3 * vec2;

         CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex1, res1, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex2, res2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex3, res3, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res4, eps ) );
      }

      // really simple mat44*vec3 rotations (hard coded matrix rot)
      {
         // xform a vector by a mat.  verify the rotation worked...
         const float eps = 0.0001f;
         gmtl::Matrix<float, 4, 4> q1, q2, q3, qident;
         q1.set( 0.0f, -1.0f, 0.0f, 0.0f,  // twist 90 about Z
              1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 1.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         q2.set( 0.0f, 0.0f, 1.0f, 0.0f,   // twist 90 about Y
              0.0f, 1.0f, 0.0f, 0.0f,
              -1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         q3.set( 1.0f, 0.0f, 0.0f, 0.0f,   // twist -90 about X
              0.0f, 0.0f, 1.0f, 0.0f,
              0.0f, -1.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         gmtl::Vec<float, 3> vec( 0.0f, 0.0f, 1.0f ), res1, res2, res3, res4, resi, vec2( 1.0f, 1.0f, -10.0f );
         gmtl::Vec<float, 3> ex1( 0.0f, 0.0f, 1.0f );
         gmtl::Vec<float, 3> ex2( 1.0f, 0.0f, 0.0f );
         gmtl::Vec<float, 3> ex3( 0.0f, 1.0f, 0.0f );
         gmtl::Vec<float, 3> ex4( 1.0f, -10.0f, -1.0f );

         gmtl::xform( resi, qident, vec );
         gmtl::xform( res1, q1, vec );
         gmtl::xform( res2, q2, vec );
         gmtl::xform( res3, q3, vec );
         gmtl::xform( res4, q3, vec2 );

         CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex1, res1, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex2, res2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex3, res3, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res4, eps ) );

         resi = qident * vec;
         res1 = q1 * vec;
         res2 = q2 * vec;
         res3 = q3 * vec;
         res4 = q3 * vec2;

         CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex1, res1, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex2, res2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex3, res3, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res4, eps ) );
      }

      // more "interesting" rotations...
      {
         const float eps = 0.0001f;
         const gmtl::Vec<float, 3> vec( 2.0f, 5.0f, 10.0f ), expected( 6.32707f, 0.67293f, 9.40826f );
         gmtl::Matrix<float, 4, 4> mat;
         gmtl::setRot( mat, gmtl::makeNormal( gmtl::AxisAnglef( gmtl::Math::deg2Rad( 35.0f ), 1.0f, 1.0f, 0.0f ) ) );
         

         // xform a vector by a mat.  verify the rotation worked...
         gmtl::Vec<float, 3> result1;
         gmtl::xform( result1, mat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );

         // operator* should be same
         gmtl::Vec<float, 3> result2;
         result2 = mat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );

         // make sure that xform by quat yields same result as xform by mat.
         gmtl::Quat<float> quat;
         gmtl::setRot( quat, gmtl::makeNormal( gmtl::AxisAnglef( gmtl::Math::deg2Rad( 35.0f ), 1.0f, 1.0f, 0.0f ) ) );

         gmtl::Vec<float, 3> result3;
         gmtl::xform( result3, quat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result3, eps ) );

         gmtl::Vec<float, 3> result4;
         result4 = quat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result4, eps ) );
      }



      // 4x4 matrix: test out complete transforms with a weird vector
      {
         const float eps = 0.0001f;
         const gmtl::Vec<float, 4> vec( -100.0f, 334.0f, 455.0f, -568.0f ), expected( -339.0f, 145.0f, 629.0f, 1113.0f );
         gmtl::Matrix<float, 4, 4> mat;
         mat.set( 1.0f, 2.0f, 3.0f, 4.0f,
                  5.0f, 6.0f, 7.0f, 8.0f,
                  9.0f, 10.0f, 11.0f, 12.0f,
                  13.0f, 14.0f, 15.0f, 16.0f );

         // xform a vector by a mat.  verify the xform worked...
         gmtl::Vec<float, 4> result1;
         gmtl::xform( result1, mat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );

         // operator* should be same
         gmtl::Vec<float, 4> result2;
         result2 = mat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );
      }

      // 3x4 matrix: test out complete transforms with a weird vector
      /// @todo: maybe change this to return size 3: todo, xform doesn't support uneven matrices, but should it??? need to resolve..
      {
         const float eps = 0.0001f;
         const gmtl::Vec<float, 4> vec( -100.0f, 334.0f, 455.0f, -568.0f );
         const gmtl::Vec<float, 4> expected( -339.0f, 145.0f, 629.0f, 0.0f );
         gmtl::Matrix<float, 3, 4> mat;
         mat.set( 1.0f, 2.0f, 3.0f, 4.0f,
                  5.0f, 6.0f, 7.0f, 8.0f,
                  9.0f, 10.0f, 11.0f, 12.0f );

         // xform a vector by a mat.  verify the xform worked...
         gmtl::Vec<float, 4> result1;
         gmtl::xform( result1, mat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );

         // operator* should be same
         gmtl::Vec<float, 4> result2;
         result2 = mat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );
      }


      // 3x3 matrix: test out complete transforms with a weird vector
      {
         const float eps = 0.0001f;
         const gmtl::Vec<float, 3> vec( -100.0f, 334.0f, 455.0f ), expected( 1933.0f, 4689.0f, 7445.0f );
         gmtl::Matrix<float, 3, 3> mat;
         mat.set( 1.0f, 2.0f, 3.0f,
                  5.0f, 6.0f, 7.0f,
                  9.0f, 10.0f, 11.0f );

         // xform a vector by a mat.  verify the xform worked...
         gmtl::Vec<float, 3> result1;
         gmtl::xform( result1, mat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );

         // operator* should be same
         gmtl::Vec<float, 3> result2;
         result2 = mat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );
      }

      // 4x4 matrix: test out complete transforms with standard vector
      {
         const float eps = 0.0001f;
         const gmtl::Vec<float, 4> vec( -100.0f, 334.0f, 455.0f, 0.0f ), expected( 1933.0f, 4689.0f, 7445.0f, 10201.0f );
         const gmtl::Vec<float, 3> partial_vec( -100.0f, 334.0f, 455.0f ), expected2( 1933.0f/10201.0f, 4689.0f/10201.0f, 7445.0f/10201.0f );
         gmtl::Matrix<float, 4, 4> mat;
         mat.set( 1.0f, 2.0f, 3.0f, 4.0f,
                  5.0f, 6.0f, 7.0f, 8.0f,
                  9.0f, 10.0f, 11.0f, 12.0f,
                  13.0f, 14.0f, 15.0f, 16.0f );

         // xform a vector by a mat.  verify the xform worked...
         gmtl::Vec<float, 4> result1;
         gmtl::xform( result1, mat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );

         // operator* should be same
         gmtl::Vec<float, 4> result2;
         result2 = mat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );

         // xform a partially specified vector by a mat.  verify the xform worked...
         gmtl::Vec<float, 3> result3;
         gmtl::xform( result3, mat, partial_vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected2, result3, eps ) );

         // operator* should be same
         gmtl::Vec<float, 3> result4;
         result4 = mat * partial_vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected2, result4, eps ) );
      }

      // 3x4 matrix: test out complete transforms with standard vector
      /// @todo: maybe change this to return size 3: todo, xform doesn't support uneven matrices, but should it??? need to resolve..
      {
         const float eps = 0.0001f;
         const gmtl::Vec<float, 4> vec( -100.0f, 334.0f, 455.0f, 0.0f ), expected( 1933.0f, 4689.0f, 7445.0f, 0.0f );
         const gmtl::Vec<float, 3> partial_vec( -100.0f, 334.0f, 455.0f ), expected2( 1933.0f, 4689.0f, 7445.0f );
         gmtl::Matrix<float, 3, 4> mat;
         mat.set( 1.0f, 2.0f, 3.0f, 4.0f,
                  5.0f, 6.0f, 7.0f, 8.0f,
                  9.0f, 10.0f, 11.0f, 12.0f );

         // xform a vector by a mat.  verify the xform worked...
         gmtl::Vec<float, 4> result1;
         gmtl::xform( result1, mat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );

         // operator* should be same
         gmtl::Vec<float, 4> result2;
         result2 = mat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );

         // xform a partially specified vector by a mat.  verify the xform worked...
         gmtl::Vec<float, 3> result3;
         gmtl::xform( result3, mat, partial_vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected2, result3, eps ) );

         // operator* should be same
         gmtl::Vec<float, 3> result4;
         result4 = mat * partial_vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected2, result4, eps ) );
      }

      // 3x3 matrix: test out complete transforms with standard vector
      {
         const float eps = 0.0001f;
         const gmtl::Vec<float, 3> vec( -100.0f, 334.0f, 0.0f ), expected( 568.0f, 1504.0f, 2440.0f );
         const gmtl::Vec<float, 2> partial_vec( -100.0f, 334.0f ), expected2( 568.0f/2440.0f, 1504.0f/2440.0f );
         gmtl::Matrix<float, 3, 3> mat;
         mat.set( 1.0f, 2.0f, 3.0f,
                  5.0f, 6.0f, 7.0f,
                  9.0f, 10.0f, 11.0f );

         // xform a vector by a mat.  verify the xform worked...
         gmtl::Vec<float, 3> result1;
         gmtl::xform( result1, mat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );

         // operator* should be same
         gmtl::Vec<float, 3> result2;
         result2 = mat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );

         // xform a partially specified vector by a mat.  verify the xform worked...
         gmtl::Vec<float, 2> result3;
         gmtl::xform( result3, mat, partial_vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected2, result3, eps ) );

         // operator* should be same
         gmtl::Vec<float, 2> result4;
         result4 = mat * partial_vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected2, result4, eps ) );
      }
   }

   void XformTest::testMatPointXform()
   {
      // really simple mat44*pnt4 rotations (hard coded matrix rot)
      {
         // xform a vector by a mat.  verify the rotation worked...
         const float eps = 0.0001f;
         gmtl::Matrix<float, 4, 4> q1, q2, q3, qident;
         q1.set( 0.0f, -1.0f, 0.0f, 0.0f,  // twist 90 about Z
              1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 1.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         q2.set( 0.0f, 0.0f, 1.0f, 0.0f,   // twist 90 about Y
              0.0f, 1.0f, 0.0f, 0.0f,
              -1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         q3.set( 1.0f, 0.0f, 0.0f, 0.0f,   // twist -90 about X
              0.0f, 0.0f, 1.0f, 0.0f,
              0.0f, -1.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         gmtl::Point<float, 4> vec( 0.0f, 0.0f, 1.0f, 1.0f ), res1, res2, res3, res4, resi, vec2( 1.0f, 1.0f, -10.0f, 1.0f );
         gmtl::Point<float, 4> ex1( 0.0f, 0.0f, 1.0f, 1.0f );
         gmtl::Point<float, 4> ex2( 1.0f, 0.0f, 0.0f, 1.0f );
         gmtl::Point<float, 4> ex3( 0.0f, 1.0f, 0.0f, 1.0f );
         gmtl::Point<float, 4> ex4( 1.0f, -10.0f, -1.0f, 1.0f );

         gmtl::xform( resi, qident, vec );
         gmtl::xform( res1, q1, vec );
         gmtl::xform( res2, q2, vec );
         gmtl::xform( res3, q3, vec );
         gmtl::xform( res4, q3, vec2 );

         CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex1, res1, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex2, res2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex3, res3, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res4, eps ) );

         resi = qident * vec;
         res1 = q1 * vec;
         res2 = q2 * vec;
         res3 = q3 * vec;
         res4 = q3 * vec2;

         CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex1, res1, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex2, res2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex3, res3, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res4, eps ) );
      }

      // really simple mat44*pnt3 rotations (hard coded matrix rot)
      {
         // xform a vector by a mat.  verify the rotation worked...
         const float eps = 0.0001f;
         gmtl::Matrix<float, 4, 4> q1, q2, q3, qident;
         q1.set( 0.0f, -1.0f, 0.0f, 0.0f,  // twist 90 about Z
              1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 1.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         q2.set( 0.0f, 0.0f, 1.0f, 0.0f,   // twist 90 about Y
              0.0f, 1.0f, 0.0f, 0.0f,
              -1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         q3.set( 1.0f, 0.0f, 0.0f, 0.0f,   // twist -90 about X
              0.0f, 0.0f, 1.0f, 0.0f,
              0.0f, -1.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         gmtl::Point<float, 3> vec( 0.0f, 0.0f, 1.0f ), res1, res2, res3, res4, resi, vec2( 1.0f, 1.0f, -10.0f );
         gmtl::Point<float, 3> ex1( 0.0f, 0.0f, 1.0f );
         gmtl::Point<float, 3> ex2( 1.0f, 0.0f, 0.0f );
         gmtl::Point<float, 3> ex3( 0.0f, 1.0f, 0.0f );
         gmtl::Point<float, 3> ex4( 1.0f, -10.0f, -1.0f );

         gmtl::xform( resi, qident, vec );
         gmtl::xform( res1, q1, vec );
         gmtl::xform( res2, q2, vec );
         gmtl::xform( res3, q3, vec );
         gmtl::xform( res4, q3, vec2 );

         CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex1, res1, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex2, res2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex3, res3, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res4, eps ) );

         resi = qident * vec;
         res1 = q1 * vec;
         res2 = q2 * vec;
         res3 = q3 * vec;
         res4 = q3 * vec2;

         CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex1, res1, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex2, res2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex3, res3, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res4, eps ) );
      }

      // more "interesting" rotations...  pnt3 = mat44 * pnt3
      {
         const float eps = 0.0001f;
         const gmtl::Point<float, 3> vec( 2.0f, 5.0f, 10.0f ), expected( 6.32707f, 0.67293f, 9.40826f );
         gmtl::Matrix<float, 4, 4> mat;
         gmtl::setRot( mat, gmtl::makeNormal(  gmtl::AxisAnglef( gmtl::Math::deg2Rad( 35.0f ), 1.0f, 1.0f, 0.0f ) ) );

         // xform a vector by a mat.  verify the rotation worked...
         gmtl::Point<float, 3> result1;
         gmtl::xform( result1, mat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );

         // operator* should be same
         gmtl::Point<float, 3> result2;
         result2 = mat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );
      }

      // 4x4 matrix: test out complete transforms with a weird vector (last elt non 1)
      {
         const float eps = 0.0001f;
         const gmtl::Point<float, 4> vec( -100.0f, 334.0f, 455.0f, -568.0f ), expected( -339.0f, 145.0f, 629.0f, 1113.0f );
         gmtl::Matrix<float, 4, 4> mat;
         mat.set( 1.0f, 2.0f, 3.0f, 4.0f,
                  5.0f, 6.0f, 7.0f, 8.0f,
                  9.0f, 10.0f, 11.0f, 12.0f,
                  13.0f, 14.0f, 15.0f, 16.0f );

         // xform a vector by a mat.  verify the xform worked...
         gmtl::Point<float, 4> result1;
         gmtl::xform( result1, mat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );

         // operator* should be same
         gmtl::Point<float, 4> result2;
         result2 = mat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );
      }

      // 3x4 matrix: test out complete transforms with a weird vector  (last elt non 1)
      /// @todo: maybe change this to return size 3: todo, xform doesn't support uneven matrices, but should it??? need to resolve..
      {
         const float eps = 0.0001f;
         const gmtl::Point<float, 4> vec( -100.0f, 334.0f, 455.0f, -568.0f );
         const gmtl::Point<float, 4> expected( -339.0f, 145.0f, 629.0f, 0.0f );
         gmtl::Matrix<float, 3, 4> mat;
         mat.set( 1.0f, 2.0f, 3.0f, 4.0f,
                  5.0f, 6.0f, 7.0f, 8.0f,
                  9.0f, 10.0f, 11.0f, 12.0f );

         // xform a vector by a mat.  verify the xform worked...
         gmtl::Point<float, 4> result1;
         gmtl::xform( result1, mat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );

         // operator* should be same
         gmtl::Point<float, 4> result2;
         result2 = mat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );
      }


      // 3x3 matrix: test out complete transforms with a weird vector  (last elt non 1)
      {
         const float eps = 0.0001f;
         const gmtl::Point<float, 3> vec( -100.0f, 334.0f, 455.0f ), expected( 1933.0f, 4689.0f, 7445.0f );
         gmtl::Matrix<float, 3, 3> mat;
         mat.set( 1.0f, 2.0f, 3.0f,
                  5.0f, 6.0f, 7.0f,
                  9.0f, 10.0f, 11.0f );

         // xform a vector by a mat.  verify the xform worked...
         gmtl::Point<float, 3> result1;
         gmtl::xform( result1, mat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );

         // operator* should be same
         gmtl::Point<float, 3> result2;
         result2 = mat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );
      }

      // 4x4 matrix: test out complete transforms with standard vector
      {
         const float eps = 0.0001f;
         const gmtl::Point<float, 4> vec( -100.0f, 334.0f, 455.0f, 1.0f ), expected( 1937.0f, 4697.0f, 7457.0f, 10217.0f );
         const gmtl::Point<float, 3> partial_vec( -100.0f, 334.0f, 455.0f ), expected2( 1937.0f/10217.0f, 4697.0f/10217.0f, 7457.0f/10217.0f );
         gmtl::Matrix<float, 4, 4> mat;
         mat.set( 1.0f, 2.0f, 3.0f, 4.0f,
                  5.0f, 6.0f, 7.0f, 8.0f,
                  9.0f, 10.0f, 11.0f, 12.0f,
                  13.0f, 14.0f, 15.0f, 16.0f );

         // xform a vector by a mat.  verify the xform worked...
         gmtl::Point<float, 4> result1;
         gmtl::xform( result1, mat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );

         // operator* should be same
         gmtl::Point<float, 4> result2;
         result2 = mat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );

         // xform a partially specified vector by a mat.  verify the xform worked...
         gmtl::Point<float, 3> result3;
         gmtl::xform( result3, mat, partial_vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected2, result3, eps ) );

         // operator* should be same
         gmtl::Point<float, 3> result4;
         result4 = mat * partial_vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected2, result4, eps ) );
      }

      // 3x4 matrix: test out complete transforms with standard vector
      /// @todo: maybe change this to return size 3: todo, xform doesn't support uneven matrices, but should it??? need to resolve..
      {
         const float eps = 0.0001f;
         const gmtl::Point<float, 4> vec( -100.0f, 334.0f, 455.0f, 1.0f ), expected( 1937.0f, 4697.0f, 7457.0f, 0.0f );
         const gmtl::Point<float, 3> partial_vec( -100.0f, 334.0f, 455.0f ), expected2( 1937.0f, 4697.0f, 7457.0f );
         gmtl::Matrix<float, 3, 4> mat;
         mat.set( 1.0f, 2.0f, 3.0f, 4.0f,
                  5.0f, 6.0f, 7.0f, 8.0f,
                  9.0f, 10.0f, 11.0f, 12.0f );

         // xform a vector by a mat.  verify the xform worked...
         gmtl::Point<float, 4> result1;
         gmtl::xform( result1, mat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );

         // operator* should be same
         gmtl::Point<float, 4> result2;
         result2 = mat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );

         // xform a partially specified vector by a mat.  verify the xform worked...
         gmtl::Point<float, 3> result3;
         gmtl::xform( result3, mat, partial_vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected2, result3, eps ) );

         // operator* should be same
         gmtl::Point<float, 3> result4;
         result4 = mat * partial_vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected2, result4, eps ) );
      }

      // 3x3 matrix: test out complete transforms with standard vector
      {
         const float eps = 0.0001f;
         const gmtl::Point<float, 3> vec( -100.0f, 334.0f, 1.0f ), expected( 571.0f, 1511.0f, 2451.0f );
         const gmtl::Point<float, 2> partial_vec( -100.0f, 334.0f ), expected2( 571.0f/2451.0f, 1511.0f/2451.0f );
         gmtl::Matrix<float, 3, 3> mat;
         mat.set( 1.0f, 2.0f, 3.0f,
                  5.0f, 6.0f, 7.0f,
                  9.0f, 10.0f, 11.0f );

         // xform a vector by a mat.  verify the xform worked...
         gmtl::Point<float, 3> result1;
         gmtl::xform( result1, mat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );

         // operator* should be same
         gmtl::Point<float, 3> result2;
         result2 = mat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );

         // xform a partially specified vector by a mat.  verify the xform worked...
         gmtl::Point<float, 2> result3;
         gmtl::xform( result3, mat, partial_vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected2, result3, eps ) );

         // operator* should be same
         gmtl::Point<float, 2> result4;
         result4 = mat * partial_vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected2, result4, eps ) );
      }
   }
}

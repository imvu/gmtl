// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include "IntersectionTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Intersection.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(IntersectionTest);
   CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(IntersectionMetricTest, Suites::metric());

   void IntersectionTest::testIntersectAABoxAABox()
   {
      // Test overlapping boxes
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(1,1,1));
         gmtl::AABoxf box2(gmtl::Point3f(0,0,0), gmtl::Point3f(2,2,2));
         CPPUNIT_ASSERT(gmtl::intersect(box1, box2));
      }

      // Test boxes with shared edge
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::AABoxf box2(gmtl::Point3f(0,0,0), gmtl::Point3f(-1,-1,-1));
         CPPUNIT_ASSERT(gmtl::intersect(box1, box2));
      }

      // Test non-overlapping boxes
      {
         gmtl::AABoxf box1(gmtl::Point3f(-2,-2,-2), gmtl::Point3f(-1,-1,-1));
         gmtl::AABoxf box2(gmtl::Point3f(1,1,1), gmtl::Point3f(2,2,2));
         CPPUNIT_ASSERT(! gmtl::intersect(box1, box2));
      }
   }

   void IntersectionMetricTest::testTimingIntersectAABoxAABox()
   {
      gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(1,1,1));
      gmtl::AABoxf box2(gmtl::Point3f(0,0,0), gmtl::Point3f(2,2,2));
      const long iters(400000);
      unsigned true_count(0);
      CPPUNIT_METRIC_START_TIMING();

      for(long iter=0;iter<iters; ++iter)
      {
         if (gmtl::intersect(box1, box2))
         {
            ++true_count;
         }
         box2.mMax[0] += 0.01;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("IntersectionTest/IntersectAABoxAABox", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT(true_count > 0.0f);
   }



   void IntersectionTest::testIntersectAABoxPoint()
   {
      // Test point in box
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(1,1,1));
         gmtl::Point3f point(gmtl::Point3f(0,0,0));
         CPPUNIT_ASSERT(gmtl::intersect(box1, point));
      }

      //////////

      // test point on edge (bottom face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(-0.5f,-1,-0.5f));
         CPPUNIT_ASSERT(gmtl::intersect(box1, point));
      }
      // test point on edge (top face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(-0.5f,0,-0.5f));
         CPPUNIT_ASSERT(gmtl::intersect(box1, point));
      }
      // test point on edge (left face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(-1.0f,-0.5,-0.5f));
         CPPUNIT_ASSERT(gmtl::intersect(box1, point));
      }
      // test point on edge (right face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(0.0f,-0.5,-0.5f));
         CPPUNIT_ASSERT(gmtl::intersect(box1, point));
      }
      // test point on edge (near face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(-0.5f,-0.5,0.0f));
         CPPUNIT_ASSERT(gmtl::intersect(box1, point));
      }
      // test point on edge (far face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(-0.5f,-0.5,-1.0f));
         CPPUNIT_ASSERT(gmtl::intersect(box1, point));
      }

      /////////

      // test point outside (bottom face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(-0.5f,-1.01,-0.5f));
         CPPUNIT_ASSERT(!gmtl::intersect(box1, point));
      }
      // test point outside (top face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(-0.5f,0.01,-0.5f));
         CPPUNIT_ASSERT(!gmtl::intersect(box1, point));
      }
      // test point outside (left face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(-1.01f,-0.5,-0.5f));
         CPPUNIT_ASSERT(!gmtl::intersect(box1, point));
      }
      // test point outside (right face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(0.01f,-0.5,-0.5f));
         CPPUNIT_ASSERT(!gmtl::intersect(box1, point));
      }
      // test point outside (near face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(-0.5f,-0.5,0.01f));
         CPPUNIT_ASSERT(!gmtl::intersect(box1, point));
      }
      // test point outside (far face)
      {
         gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Point3f point(gmtl::Point3f(-0.5f,-0.5,-1.01f));
         CPPUNIT_ASSERT(!gmtl::intersect(box1, point));
      }

      // @todo, could use more rigorous testing here, test all sides of the box,
      //        in and out and on the edges...
   }

   void IntersectionTest::testIntersectAABoxLineSeg()
   {
      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment at the origin and pointing along the positive
         // X-axis.
         gmtl::LineSegf seg(gmtl::Point3f(0.0f, 0.0f, 0.0f),
                            gmtl::Vec3f(1.0f, 0.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, seg, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 1);
         CPPUNIT_ASSERT(t_in == 0.5f);
         CPPUNIT_ASSERT(t_in == t_out);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment at the origin and pointing along the negative
         // X-axis.
         gmtl::LineSegf seg(gmtl::Point3f(0.0f, 0.0f, 0.0f),
                            gmtl::Vec3f(-1.0f, 0.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, seg, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 1);
         CPPUNIT_ASSERT(t_in == 0.5f);
         CPPUNIT_ASSERT(t_in == t_out);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment at the origin and pointing along the positive
         // Y-axis.
         gmtl::LineSegf seg(gmtl::Point3f(0.0f, 0.0f, 0.0f),
                            gmtl::Vec3f(0.0f, 1.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, seg, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 1);
         CPPUNIT_ASSERT(t_in == 0.5f);
         CPPUNIT_ASSERT(t_in == t_out);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment at the origin and pointing along the negative
         // Y-axis.
         gmtl::LineSegf seg(gmtl::Point3f(0.0f, 0.0f, 0.0f),
                            gmtl::Vec3f(0.0f, -1.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, seg, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 1);
         CPPUNIT_ASSERT(t_in == 0.5f);
         CPPUNIT_ASSERT(t_in == t_out);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment at the origin and pointing along the positive
         // Z-axis.
         gmtl::LineSegf seg(gmtl::Point3f(0.0f, 0.0f, 0.0f),
                            gmtl::Vec3f(0.0f, 0.0f, 1.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, seg, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 1);
         CPPUNIT_ASSERT(t_in == 0.5f);
         CPPUNIT_ASSERT(t_in == t_out);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment at the origin and pointing along the negative
         // Z-axis.
         gmtl::LineSegf seg(gmtl::Point3f(0.0f, 0.0f, 0.0f),
                            gmtl::Vec3f(0.0f, 0.0f, -1.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, seg, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 1);
         CPPUNIT_ASSERT(t_in == 0.5f);
         CPPUNIT_ASSERT(t_in == t_out);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment with its origin on the right side of the box
         // pointing away from the box perpendicular to the right side (along
         // the positive X-axis).
         gmtl::LineSegf seg(gmtl::Point3f(0.5f, 0.0f, 0.0f),
                            gmtl::Vec3f(1.0f, 0.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, seg, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 1);
         CPPUNIT_ASSERT(t_in == 0.0f);
         CPPUNIT_ASSERT(t_in == t_out);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment with its origin on the right side of the box
         // pointing into the box perpendicular to the right side (along the
         // negative X-axis).
         gmtl::LineSegf seg(gmtl::Point3f(0.5f, 0.0f, 0.0f),
                            gmtl::Vec3f(-1.0f, 0.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, seg, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 2);
         CPPUNIT_ASSERT(t_in == 0.0f);
         CPPUNIT_ASSERT(t_out == 1.0f);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment with its origin on the top side of the box
         // pointing away from the box perpendicular to the top side (along
         // the positive Y-axis).
         gmtl::LineSegf seg(gmtl::Point3f(0.0f, 0.5f, 0.0f),
                            gmtl::Vec3f(0.0f, 1.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, seg, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 1);
         CPPUNIT_ASSERT(t_in == 0.0f);
         CPPUNIT_ASSERT(t_in == t_out);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment with its origin on the top side of the box
         // pointing into the box perpendicular to the top side (along the
         // negative Y-axis).
         gmtl::LineSegf seg(gmtl::Point3f(0.0f, 0.5f, 0.0f),
                            gmtl::Vec3f(0.0f, -1.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, seg, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 2);
         CPPUNIT_ASSERT(t_in == 0.0f);
         CPPUNIT_ASSERT(t_out == 1.0f);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment with its origin on the front side of the box
         // pointing away from the box perpendicular to the front side (along
         // the positive Z-axis).
         gmtl::LineSegf seg(gmtl::Point3f(0.0f, 0.0f, 0.5f),
                            gmtl::Vec3f(0.0f, 0.0f, 1.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, seg, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 1);
         CPPUNIT_ASSERT(t_in == 0.0f);
         CPPUNIT_ASSERT(t_in == t_out);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment with its origin on the front side of the box
         // pointing into the box perpendicular to the front side (along the
         // negative Z-axis).
         gmtl::LineSegf seg(gmtl::Point3f(0.0f, 0.0f, 0.5f),
                            gmtl::Vec3f(0.0f, 0.0f, -1.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, seg, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 2);
         CPPUNIT_ASSERT(t_in == 0.0f);
         CPPUNIT_ASSERT(t_out == 1.0f);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment with its origin outside the box on its right
         // side pointing away from the box perpendicular to the right side
         // (along the positive X-axis).
         gmtl::LineSegf seg(gmtl::Point3f(1.0f, 0.0f, 0.0f),
                            gmtl::Vec3f(1.0f, 0.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(! gmtl::intersect(box, seg, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 0);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment with its origin outside the box on its right
         // side pointing into the box perpendicular to the right side (along
         // the positive X-axis).
         gmtl::LineSegf seg(gmtl::Point3f(1.0f, 0.0f, 0.0f),
                            gmtl::Vec3f(-1.0f, 0.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, seg, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 1);
         CPPUNIT_ASSERT(t_in == 0.5f);
         CPPUNIT_ASSERT(t_out == t_in);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment with its origin above the box pointing away from
         // the box perpendicular to the top side (along the positive Y-axis).
         gmtl::LineSegf seg(gmtl::Point3f(0.0f, 1.0f, 0.0f),
                            gmtl::Vec3f(0.0f, 1.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(! gmtl::intersect(box, seg, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 0);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment with its origin above the box pointing into the
         // box perpendicular to the top side (along the positive Y-axis).
         gmtl::LineSegf seg(gmtl::Point3f(0.0f, 1.0f, 0.0f),
                            gmtl::Vec3f(0.0f, -1.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, seg, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 1);
         CPPUNIT_ASSERT(t_in == 0.5f);
         CPPUNIT_ASSERT(t_out == t_in);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment with its origin in front of the box pointing
         // away from the box perpendicular to the front side (along the
         // positive Z-axis).
         gmtl::LineSegf seg(gmtl::Point3f(0.0f, 0.0f, 1.0f),
                            gmtl::Vec3f(0.0f, 0.0f, 1.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(! gmtl::intersect(box, seg, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 0);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment with its origin in front of the box pointing
         // into the box perpendicular to the front side (along the positive
         // Z-axis).
         gmtl::LineSegf seg(gmtl::Point3f(0.0f, 0.0f, 1.0f),
                        gmtl::Vec3f(0.0f, 0.0f, -1.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, seg, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 1);
         CPPUNIT_ASSERT(t_in == 0.5f);
         CPPUNIT_ASSERT(t_out == t_in);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment with its origin on the right edge of the box
         // and its endpoint on the left edge of the box.
         gmtl::LineSegf seg(gmtl::Point3f(0.5f, 0.0f, 0.0f),
                            gmtl::Point3f(-0.5f, 0.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, seg, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 2);
         CPPUNIT_ASSERT(t_in == 0.0f);
         CPPUNIT_ASSERT(t_out == 1.0f);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment with its origin on the top edge of the box
         // and its endpoint on the bottom edge of the box.
         gmtl::LineSegf seg(gmtl::Point3f(0.0f, 0.5f, 0.0f),
                            gmtl::Point3f(0.0f, -0.5f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, seg, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 2);
         CPPUNIT_ASSERT(t_in == 0.0f);
         CPPUNIT_ASSERT(t_out == 1.0f);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment with its origin on the front edge of the box
         // and its endpoint on the back edge of the box.
         gmtl::LineSegf seg(gmtl::Point3f(0.0f, 0.0f, 0.5f),
                            gmtl::Point3f(0.0f, 0.0f, -0.5f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, seg, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 2);
         CPPUNIT_ASSERT(t_in == 0.0f);
         CPPUNIT_ASSERT(t_out == 1.0f);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
         gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Unit line segment with its origin on the front edge of the box
         // and its endpoint on the back edge of the box.
         gmtl::LineSegf seg(gmtl::Point3f(0.0f, 0.0f, 0.0f),
         gmtl::Point3f(0.1f, 0.0f, -0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(!gmtl::intersect(box, seg, num_hits, t_in, t_out));
      }
   }

   void IntersectionTest::testIntersectAABoxRay()
   {
      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Ray at the origin and pointing along the positive X-axis.
         gmtl::Rayf ray(gmtl::Point3f(0.0f, 0.0f, 0.0f),
                        gmtl::Vec3f(1.0f, 0.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, ray, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 1);
         CPPUNIT_ASSERT(t_in == 0.5f);
         CPPUNIT_ASSERT(t_in == t_out);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Ray at the origin and pointing along the negative X-axis.
         gmtl::Rayf ray(gmtl::Point3f(0.0f, 0.0f, 0.0f),
                        gmtl::Vec3f(-1.0f, 0.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, ray, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 1);
         CPPUNIT_ASSERT(t_in == 0.5f);
         CPPUNIT_ASSERT(t_in == t_out);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Ray at the origin and pointing along the positive Y-axis.
         gmtl::Rayf ray(gmtl::Point3f(0.0f, 0.0f, 0.0f),
                        gmtl::Vec3f(0.0f, 1.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, ray, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 1);
         CPPUNIT_ASSERT(t_in == 0.5f);
         CPPUNIT_ASSERT(t_in == t_out);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Ray at the origin and pointing along the negative Y-axis.
         gmtl::Rayf ray(gmtl::Point3f(0.0f, 0.0f, 0.0f),
                        gmtl::Vec3f(0.0f, -1.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, ray, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 1);
         CPPUNIT_ASSERT(t_in == 0.5f);
         CPPUNIT_ASSERT(t_in == t_out);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Ray at the origin and pointing along the positive Z-axis.
         gmtl::Rayf ray(gmtl::Point3f(0.0f, 0.0f, 0.0f),
                        gmtl::Vec3f(0.0f, 0.0f, 1.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, ray, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 1);
         CPPUNIT_ASSERT(t_in == 0.5f);
         CPPUNIT_ASSERT(t_in == t_out);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Ray at the origin and pointing along the negative Z-axis.
         gmtl::Rayf ray(gmtl::Point3f(0.0f, 0.0f, 0.0f),
                        gmtl::Vec3f(0.0f, 0.0f, -1.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, ray, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 1);
         CPPUNIT_ASSERT(t_in == 0.5f);
         CPPUNIT_ASSERT(t_in == t_out);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Ray with its origin on the right side of the box pointing away
         // from the box perpendicular to the right side (along the positive
         // X-axis).
         gmtl::Rayf ray(gmtl::Point3f(0.5f, 0.0f, 0.0f),
                        gmtl::Vec3f(1.0f, 0.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, ray, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 1);
         CPPUNIT_ASSERT(t_in == 0.0f);
         CPPUNIT_ASSERT(t_in == t_out);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Ray with its origin on the right side of the box pointing into
         // the box perpendicular to the right side (along the negative
         // X-axis).
         gmtl::Rayf ray(gmtl::Point3f(0.5f, 0.0f, 0.0f),
                        gmtl::Vec3f(-1.0f, 0.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, ray, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 2);
         CPPUNIT_ASSERT(t_in == 0.0f);
         CPPUNIT_ASSERT(t_out == 1.0f);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Ray with its origin on the top side of the box pointing away
         // from the box perpendicular to the top side (along the positive
         // Y-axis).
         gmtl::Rayf ray(gmtl::Point3f(0.0f, 0.5f, 0.0f),
                        gmtl::Vec3f(0.0f, 1.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, ray, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 1);
         CPPUNIT_ASSERT(t_in == 0.0f);
         CPPUNIT_ASSERT(t_in == t_out);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Ray with its origin on the top side of the box pointing into
         // the box perpendicular to the top side (along the negative Y-axis).
         gmtl::Rayf ray(gmtl::Point3f(0.0f, 0.5f, 0.0f),
                        gmtl::Vec3f(0.0f, -1.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, ray, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 2);
         CPPUNIT_ASSERT(t_in == 0.0f);
         CPPUNIT_ASSERT(t_out == 1.0f);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Ray with its origin on the front side of the box pointing away
         // from the box perpendicular to the front side (along the positive
         // Z-axis).
         gmtl::Rayf ray(gmtl::Point3f(0.0f, 0.0f, 0.5f),
                        gmtl::Vec3f(0.0f, 0.0f, 1.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, ray, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 1);
         CPPUNIT_ASSERT(t_in == 0.0f);
         CPPUNIT_ASSERT(t_in == t_out);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Ray with its origin on the front side of the box pointing into
         // the box perpendicular to the front side (along the negative
         // Z-axis).
         gmtl::Rayf ray(gmtl::Point3f(0.0f, 0.0f, 0.5f),
                        gmtl::Vec3f(0.0f, 0.0f, -1.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, ray, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 2);
         CPPUNIT_ASSERT(t_in == 0.0f);
         CPPUNIT_ASSERT(t_out == 1.0f);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Ray with its origin outside the box on its right side pointing away
         // from the box perpendicular to the right side (along the positive
         // X-axis).
         gmtl::Rayf ray(gmtl::Point3f(1.0f, 0.0f, 0.0f),
                        gmtl::Vec3f(1.0f, 0.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(! gmtl::intersect(box, ray, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 0);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Ray with its origin outside the box on its right side pointing into
         // the box perpendicular to the right side (along the positive
         // X-axis).
         gmtl::Rayf ray(gmtl::Point3f(1.0f, 0.0f, 0.0f),
                        gmtl::Vec3f(-1.0f, 0.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, ray, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 2);
         CPPUNIT_ASSERT(t_in == 0.5f);
         CPPUNIT_ASSERT(t_out == 1.5f);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Ray with its origin above the box pointing away from the box
         // perpendicular to the top side (along the positive Y-axis).
         gmtl::Rayf ray(gmtl::Point3f(0.0f, 1.0f, 0.0f),
                        gmtl::Vec3f(0.0f, 1.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(! gmtl::intersect(box, ray, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 0);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Ray with its origin above the box pointing into the box
         // perpendicular to the top side (along the positive Y-axis).
         gmtl::Rayf ray(gmtl::Point3f(0.0f, 1.0f, 0.0f),
                        gmtl::Vec3f(0.0f, -1.0f, 0.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, ray, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 2);
         CPPUNIT_ASSERT(t_in == 0.5f);
         CPPUNIT_ASSERT(t_out == 1.5f);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Ray with its origin in front of the box pointing away from the
         // box perpendicular to the front side (along the positive Z-axis).
         gmtl::Rayf ray(gmtl::Point3f(0.0f, 0.0f, 1.0f),
                        gmtl::Vec3f(0.0f, 0.0f, 1.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(! gmtl::intersect(box, ray, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 0);
      }

      {
         // Unit box centered at the origin.
         gmtl::AABoxf box(gmtl::Point3f(-0.5f, -0.5f, -0.5f),
                          gmtl::Point3f(0.5f, 0.5f, 0.5f));
         // Ray with its origin in front of the box pointing into the box
         // perpendicular to the front side (along the positive Z-axis).
         gmtl::Rayf ray(gmtl::Point3f(0.0f, 0.0f, 1.0f),
                        gmtl::Vec3f(0.0f, 0.0f, -1.0f));
         unsigned int num_hits;
         float t_in, t_out;
         CPPUNIT_ASSERT(gmtl::intersect(box, ray, num_hits, t_in, t_out));
         CPPUNIT_ASSERT(num_hits == 2);
         CPPUNIT_ASSERT(t_in == 0.5f);
         CPPUNIT_ASSERT(t_out == 1.5f);
      }
   }

   void IntersectionTest::testIntersectLineSegPlane()
   {
      gmtl::Planef plane( gmtl::Vec3f( 0,1,0 ), 0 );
      
      float d;
      bool res;
      const float eps(0.0001f);
      // behind
      {
         gmtl::LineSegf seg( gmtl::Point3f( 0,-1,0 ), gmtl::Vec3f( 0,-1,0 ) );
         res = gmtl::intersect( plane, seg, d );
         CPPUNIT_ASSERT( res == false );
      }
      // not long enough
      {
         gmtl::LineSegf seg( gmtl::Point3f( 0,5,0 ), gmtl::Vec3f( 0,-2.5,0 ) );
         res = gmtl::intersect( plane, seg, d );
         CPPUNIT_ASSERT( res == false );
         CPPUNIT_ASSERT( d == 2.0f );
      }
      // through
      {
         gmtl::LineSegf seg( gmtl::Point3f( 0,5,0 ), gmtl::Vec3f( 0,-10,0 ) );
         res = gmtl::intersect( plane, seg, d );
         CPPUNIT_ASSERT( res == true );
         CPPUNIT_ASSERT( d == 0.5f );
      }
      // parallel - Shoot seg parallel to plane
      {
         gmtl::Rayf ray( gmtl::Point3f(0,1,0), gmtl::Vec3f(1,0,0));
         res = gmtl::intersect(plane, ray, d);
         CPPUNIT_ASSERT( res == false);
         CPPUNIT_ASSERT_DOUBLES_EQUAL(d,0,eps);
      }
      // parallel - On plane - Shoot ray parallel to plane on plane
      {
         gmtl::LineSegf seg( gmtl::Point3f(0,0,0), gmtl::Vec3f(1,0,0));
         res = gmtl::intersect(plane, seg, d);
         CPPUNIT_ASSERT( res == true);
         CPPUNIT_ASSERT_DOUBLES_EQUAL(d,0,eps);
      }
   }

   void IntersectionTest::testIntersectRayPlane()
   {
      float d(0.0f);
      const float eps(0.0001f);
      bool res(false);

      // Plane at origin
      {
         gmtl::Planef plane( gmtl::Vec3f( 0,1,0 ), 0 );     // Define plane on origin pointing up

         // through - Shoot ray from +5y straight down at plane
         //       should hit with t = 5
         {
            gmtl::Rayf ray( gmtl::Point3f( 0,5,0 ), gmtl::Vec3f( 0,-1,0 ) );
            res = gmtl::intersect( plane, ray, d );
            CPPUNIT_ASSERT( res == true );
            CPPUNIT_ASSERT( d == 5.0f );
         }
         // behind - Shoot ray from -1y straight down.  Should miss
         {
            gmtl::Rayf ray( gmtl::Point3f( 0,-1,0 ), gmtl::Vec3f( 0,-1,0 ) );
            res = gmtl::intersect( plane, ray, d );
            CPPUNIT_ASSERT( res == false );
         }
         // parallel - Shoot ray parallel to plane
         {
            gmtl::Rayf ray( gmtl::Point3f(0,1,0), gmtl::Vec3f(1,0,0));
            res = gmtl::intersect(plane, ray, d);
            CPPUNIT_ASSERT( res == false);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(d,0,eps);
         }
         // parallel - On plane - Shoot ray parallel to plane on plane
         {
            gmtl::Rayf ray( gmtl::Point3f(0,0,0), gmtl::Vec3f(1,0,0));
            res = gmtl::intersect(plane, ray, d);
            CPPUNIT_ASSERT( res == true);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(d,0,eps);
         }
      }

      // Plane off origin - 45 degree angle off
      {
         gmtl::Planef plane( gmtl::Point3f(1,0,0), gmtl::Point3f(0,1,0), gmtl::Point3f(0,0,1));

         // send ray from origin orthogonal
         {
            gmtl::Rayf ray( gmtl::Point3f(0,0,0), gmtl::Vec3f(1,1,1));
            res = gmtl::intersect( plane, ray, d);
            CPPUNIT_ASSERT( res == true);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(d,0.3333, 0.01);

            gmtl::Rayf miss_ray(gmtl::Point3f(0,0,0), gmtl::Vec3f(-1,-1,-1));
            res = gmtl::intersect( plane, miss_ray, d);
            CPPUNIT_ASSERT( res == false);
         }
      }

   }

   void IntersectionMetricTest::testTimingIntersectAABoxPoint()
   {
      gmtl::AABoxf box1(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(1,1,1));
      gmtl::Point3f point(gmtl::Point3f(-0.5f,-0.5,-1.01f));
      const long iters(400000);
      unsigned true_count(0);
      CPPUNIT_METRIC_START_TIMING();

      for(long iter=0;iter<iters; ++iter)
      {
         if (gmtl::intersect(box1, point))
         {
            ++true_count;
         }
         point[0] += 0.01;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("IntersectionTest/IntersectAABoxPoint", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT(true_count == 0);
   }

   void IntersectionTest::testIntersectAABoxSphere()
   {
      // Overlapping
      {
         gmtl::AABoxf box(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Spheref sph(gmtl::Point3f(0,0,0), 2);
         CPPUNIT_ASSERT(gmtl::intersect(box, sph));
         CPPUNIT_ASSERT(gmtl::intersect(sph, box));
      }
      // Shared edge
      {
         gmtl::AABoxf box(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Spheref sph(gmtl::Point3f(2,0,0), 2);
         CPPUNIT_ASSERT(gmtl::intersect(box, sph));
         CPPUNIT_ASSERT(gmtl::intersect(sph, box));
      }
      // Non-overlapping
      {
         gmtl::AABoxf box(gmtl::Point3f(-1,-1,-1), gmtl::Point3f(0,0,0));
         gmtl::Spheref sph(gmtl::Point3f(3,3,3), 2);
         CPPUNIT_ASSERT(! gmtl::intersect(box, sph));
         CPPUNIT_ASSERT(! gmtl::intersect(sph, box));
      }
   }

   void IntersectionTest::testIntersectAABoxSweep()
   {
      gmtl::AABoxf box1(gmtl::Point3f(-3,1,-3), gmtl::Point3f(-2,2,-2));
      gmtl::AABoxf box2(gmtl::Point3f( 2,1,-3), gmtl::Point3f( 3,3,-2));
      gmtl::Vec3f path1(5,0,0);
      gmtl::Vec3f path2(-5,0,0);

      float first, second;
      bool result = gmtl::intersect(box1, path1, box2, path2, first, second);
      CPPUNIT_ASSERT(result);
      CPPUNIT_ASSERT(first == 0.4f);
      CPPUNIT_ASSERT(second == 0.6f);
   }

   void IntersectionMetricTest::testTimingIntersectAABoxSweep()
   {
      gmtl::AABoxf box1(gmtl::Point3f(-3,1,-3), gmtl::Point3f(-2,2,-2));
      gmtl::AABoxf box2(gmtl::Point3f( 2,1,-3), gmtl::Point3f( 3,3,-2));
      gmtl::Vec3f path1(1,0,0);
      gmtl::Vec3f path2(-5,0,0);
      float first, second;

      const long iters(400000);
      unsigned true_count(0);
      CPPUNIT_METRIC_START_TIMING();

      for(long iter=0;iter<iters; ++iter)
      {
         if (gmtl::intersect(box1, path1, box2, path2, first, second))
         {
            ++true_count;
         }
         path1[0] += 0.1f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("IntersectionTest/IntersectAABoxSweep", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT(true_count > 0);
   }

   void IntersectionTest::testIntersectSphereSweep()
   {
      gmtl::Spheref sph1(gmtl::Point3f(-3,1,-3), 2);
      gmtl::Spheref sph2(gmtl::Point3f( 2,1,-3), 1);
      gmtl::Vec3f path1(5,0,0);
      gmtl::Vec3f path2(-5,0,0);

      float first, second;
      bool result = gmtl::intersect(sph1, path1, sph2, path2, first, second);
      CPPUNIT_ASSERT(result);
      CPPUNIT_ASSERT(gmtl::Math::isEqual(first, 0.2f, 0.001f));
      CPPUNIT_ASSERT(gmtl::Math::isEqual(second, 0.8f, 0.001f));
   }

   void IntersectionMetricTest::testTimingIntersectSphereSweep()
   {
      gmtl::Spheref sph1(gmtl::Point3f(-3,1,-3), 2);
      gmtl::Spheref sph2(gmtl::Point3f( 2,1,-3), 1);
      gmtl::Vec3f path1(1,0,0);
      gmtl::Vec3f path2(-5,0,0);
      float first, second;

      const long iters(400000);
      unsigned true_count(0);
      CPPUNIT_METRIC_START_TIMING();

      for(long iter=0;iter<iters; ++iter)
      {
         if (gmtl::intersect(sph1, path1, sph2, path2, first, second))
         {
            ++true_count;
         }
         path1[0] += 0.1f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("IntersectionTest/IntersectSphereSweep", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT(true_count > 0);
   }
}

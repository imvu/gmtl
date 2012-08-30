// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <gmtl/Vec3.h>
#include <gmtl/Point3.h>
#include <gmtl/OOBox.h>
#include <gmtl/Containment.h>
#include <gmtl/gmtlOutput.h>

namespace gmtlTest
{

   using namespace gmtl;

class ContainmentTest : public CppUnit::TestFixture
{
public:
   ContainmentTest( std::string name = "ContainmentTest")
   : TestCase (name)
   {;}

   virtual ~ContainmentTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {;}

   void testComputePtsAreInOBB()
   {
      // Known pts
      std::vector<gmtl::Point3> points;
      points.push_back(Point3(0,0,0));
      points.push_back(Point3(1,0,0));
      points.push_back(Point3(0,1,0));
      points.push_back(Point3(0,0,1));

      OOBox box;
      box.center() = Vec3(0,0,0);
      box.halfLen(0) = 1.5f; box.halfLen(1) = 1.5f; box.halfLen(2) = 1.5f;
      box.axis(0) = XUnitVec3; box.axis(1) = YUnitVec3; box.axis(2) = ZUnitVec3;

      //CPPUNIT_ASSERT(ptsAreInOOB(box,points));

      points.push_back(Point3(5.0f,0.0f,0.0f));
      //CPPUNIT_ASSERT(!ptsAreInOOB(box,points));

      box.halfLen(0) = 7.0f;
      //CPPUNIT_ASSERT(ptsAreInOOB(box,points));

   }


   void testComputeContainmentOOB_PointVec()
   {
      // Known pts
      Vec3 xAxis, yAxis, zAxis, cross;

      std::vector<gmtl::Point3> points;
      points.push_back(Point3(0,0,0));
      points.push_back(Point3(1,0,0));
      points.push_back(Point3(0,1,0));
      points.push_back(Point3(0,0,1));

      OOBox box;

      computeContainment(box,points);
      xAxis = box.axis(0); yAxis = box.axis(1); zAxis = box.axis(2);
      cross = xAxis.cross(yAxis);
      CPPUNIT_ASSERT(cross.equal(zAxis));

      //std::cout << "daBox\n" << box << std::endl;

      CPPUNIT_ASSERT(ptsAreInOOB(box,points));

      // Get random cloud of points
      for(long r=0;r<100;r++)
      {
         points.erase(points.begin(), points.end());
         for(int i=0;i<(r%30)+3;i++)
         {
            float scale = (Math::unitRandom()-0.5f)*10.0f;
            points.push_back(Point3(Math::unitRandom()*scale, Math::unitRandom()*scale, Math::unitRandom()*scale));
         }
         computeContainment(box, points);
         CPPUNIT_ASSERT(ptsAreInOOB(box,points));
      }

   }

   void testComputeContainmentOOB_MergeOOB()
   {
      // Known boxes
      std::vector<gmtl::Point3> vert_points, points;
      gmtl::Point3 verts[8];
      OOBox box1;
      OOBox box2;
      OOBox combined_box;

      box1.center().set(-1,-1,-1);
      box1.axis(0) = XUnitVec3; box1.axis(1) = YUnitVec3; box1.axis(2) = ZUnitVec3;
      box1.halfLen(0) = 0.5; box1.halfLen(1) = 0.5; box1.halfLen(2) = 0.5;
      box2.center().set(1,1,1);
      box2.axis(0) = XUnitVec3; box2.axis(1) = YUnitVec3; box2.axis(2) = ZUnitVec3;
      box2.halfLen(0) = 0.5; box2.halfLen(1) = 0.5; box2.halfLen(2) = 0.5;

      box1.getVerts(verts);
      for(unsigned i=0;i<8;i++) vert_points.push_back(verts[i]);
      box2.getVerts(verts);
      for(unsigned i=0;i<8;i++) vert_points.push_back(verts[i]);

      computeContainment(combined_box, box1, box2, true);
      CPPUNIT_ASSERT(ptsAreInOOB(combined_box,vert_points));
      computeContainment(combined_box, box1, box2, false);
      CPPUNIT_ASSERT(ptsAreInOOB(combined_box,vert_points));


      // Known pts
      points.erase(points.begin(), points.end());
      points.push_back(Point3(0,0,0));
      points.push_back(Point3(1,0,0));
      points.push_back(Point3(0,1,0));
      points.push_back(Point3(0,0,1));

      std::vector<gmtl::Point3> more_points;
      more_points.push_back(Point3(5,0,0));
      more_points.push_back(Point3(7,0,0));
      more_points.push_back(Point3(0,5,0));
      more_points.push_back(Point3(0,0,21));

      computeContainment(box1,points);
      computeContainment(box2,more_points);
      computeContainment(combined_box,box1, box2);
      //std::cout << "daBox\n" << box << std::endl;

      vert_points.erase(vert_points.begin(), vert_points.end());
      box1.getVerts(verts);
      for(unsigned i=0;i<8;i++) vert_points.push_back(verts[i]);
      box2.getVerts(verts);
      for(unsigned i=0;i<8;i++) vert_points.push_back(verts[i]);

      CPPUNIT_ASSERT(ptsAreInOOB(box1, points));
      CPPUNIT_ASSERT(ptsAreInOOB(box2, more_points));
      CPPUNIT_ASSERT(ptsAreInOOB(combined_box, vert_points));
      CPPUNIT_ASSERT(ptsAreInOOB(combined_box, points));
      CPPUNIT_ASSERT(ptsAreInOOB(combined_box, more_points));

      // Get random cloud of points
      for(long r=0;r<50;r++)
      {
         points.erase(points.begin(), points.end());
         more_points.erase(more_points.begin(), more_points.end());
         for(int i=0;i<(r%20)+3;i++)
         {
            float scale = (Math::unitRandom()-0.5f)*10.0f;
            points.push_back(Point3(Math::unitRandom()*scale, Math::unitRandom()*scale, Math::unitRandom()*scale));
            more_points.push_back(Point3(Math::unitRandom()*scale, Math::unitRandom()*scale, Math::unitRandom()*scale));
         }
         computeContainment(box1, points);
         computeContainment(box2, more_points);
         CPPUNIT_ASSERT(ptsAreInOOB(box1,points));
         CPPUNIT_ASSERT(ptsAreInOOB(box2,more_points));

         computeContainment(combined_box,box1, box2, true);
         CPPUNIT_ASSERT(ptsAreInOOB(combined_box,points));
         CPPUNIT_ASSERT(ptsAreInOOB(combined_box,more_points));

         computeContainment(combined_box,box1, box2, false);
         CPPUNIT_ASSERT(ptsAreInOOB(combined_box,points));
         CPPUNIT_ASSERT(ptsAreInOOB(combined_box,more_points));
      }
   }

   // Helpers - test points against and OOB
   bool ptsAreInOOB(const OOBox& box, const std::vector<Point3> points)
   {
      if(points.empty())
         return true;

      Point3 box_verts[8];
      box.getVerts(&box_verts[0]);

      // Build the boxes eight planes that point OUT!!!
      std::vector<Plane> test_planes;

      test_planes.push_back( Plane(box_verts[5], box_verts[1], box_verts[6]));  // right
      test_planes.push_back( Plane(box_verts[4], box_verts[7], box_verts[0]));  // left

      test_planes.push_back( Plane(box_verts[6], box_verts[2], box_verts[7]));  // Top
      test_planes.push_back( Plane(box_verts[5], box_verts[4], box_verts[1]));  // Bottom

      test_planes.push_back( Plane(box_verts[6], box_verts[7], box_verts[5]));  // front
      test_planes.push_back( Plane(box_verts[0], box_verts[3], box_verts[1]));  // back

      for(unsigned i=0;i<points.size();i++)
      {
         for(unsigned j=0;j<test_planes.size();j++)
         {
            if( test_planes[j].whichSide(points[i],0.001) == Plane::POS_SIDE)    // Allow NEG and ON_PLANE
            {
               float dist = test_planes[j].distanceToPt(points[i]);
               std::cout << "Fail dist: " << dist << std::endl;
               std::cout << "Failed plane: " << j << "  point: " << i << std::endl;
               return false;
            }
         }
      }

      return true;
   }



   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("ContainmentTest");
      test_suite->addTest( new CppUnit::TestCaller<ContainmentTest>("testComputePtsAreInOBB", &ContainmentTest::testComputePtsAreInOBB));
      test_suite->addTest( new CppUnit::TestCaller<ContainmentTest>("testComputeContainmentOOB_PointVec", &ContainmentTest::testComputeContainmentOOB_PointVec));
      test_suite->addTest( new CppUnit::TestCaller<ContainmentTest>("testComputeContainmentOOB_MergeOOB", &ContainmentTest::testComputeContainmentOOB_MergeOOB));
      return test_suite;
   }

   static CppUnit::Test* perfSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("ContainmentTiming");
      return test_suite;
   }
   
   static CppUnit::Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("ContainmentTestInteractive");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};

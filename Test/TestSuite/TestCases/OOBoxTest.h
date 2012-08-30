// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <gmtl/OOBox.h>

namespace gmtlTest
{

class OOBoxTest : public CppUnit::TestFixture
{
public:
   OOBoxTest( std::string name = "OOBoxTest")
   : TestCase (name)
   {;}

   virtual ~OOBoxTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {;}

   void testBoxCreation()
   {
      gmtl::OOBox box1;
      gmtl::OOBox box2;

      box1.center().set(0.0, 1.0f, -2.0f);
      box1.axis(0) = gmtl::XUnitVec3;
      box1.axis(1) = gmtl::YUnitVec3;
      box1.axis(2) = gmtl::ZUnitVec3;

      box2 = box1;

      CPPUNIT_ASSERT(box2.center() == gmtl::Point3(0.0, 1.0f, -2.0f));
      CPPUNIT_ASSERT(box2 == box1);
      CPPUNIT_ASSERT(box1 == box2);
   }

   void testGetBoxVerts()
   {
      gmtl::OOBox box1;

      // Create box centered on origin
      // Aligned with major axes
      // with half lens 1,2,3
      box1.center().set(0.0, 0.0f, 0.0f);
      box1.axis(0) = gmtl::XUnitVec3;
      box1.axis(1) = gmtl::YUnitVec3;
      box1.axis(2) = gmtl::ZUnitVec3;
      box1.halfLen(0) = 1.0f;
      box1.halfLen(1) = 2.0f;
      box1.halfLen(2) = 3.0f;

      gmtl::Point3 verts[8];
      box1.getVerts(verts);

      CPPUNIT_ASSERT(verts[0] == gmtl::Point3(-1.0f,-2.0f,-3.0f));   // 000
      CPPUNIT_ASSERT(verts[1] == gmtl::Point3(1.0f,-2.0f,-3.0f));   // 100
      CPPUNIT_ASSERT(verts[2] == gmtl::Point3(1.0f,2.0f,-3.0f));   // 110
      CPPUNIT_ASSERT(verts[3] == gmtl::Point3(-1.0f,2.0f,-3.0f));   // 010

      CPPUNIT_ASSERT(verts[4] == gmtl::Point3(-1.0f,-2.0f,3.0f));   // 001
      CPPUNIT_ASSERT(verts[5] == gmtl::Point3(1.0f,-2.0f,3.0f));   // 101
      CPPUNIT_ASSERT(verts[6] == gmtl::Point3(1.0f,2.0f,3.0f));   // 111
      CPPUNIT_ASSERT(verts[7] == gmtl::Point3(-1.0f,2.0f,3.0f));   // 011
   }


   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("OOBoxTest");
      test_suite->addTest( new CppUnit::TestCaller<OOBoxTest>("testBoxCreation", &OOBoxTest::testBoxCreation));
      test_suite->addTest( new CppUnit::TestCaller<OOBoxTest>("testGetBoxVerts", &OOBoxTest::testGetBoxVerts));

      return test_suite;
   }

   static CppUnit::Test* perfSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("OOBoxTiming");
      return test_suite;
   }
   
   static CppUnit::Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("OOBoxTestInteractive");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};

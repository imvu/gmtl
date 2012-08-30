// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/extensions/MetricRegistry.h>

namespace gmtlTest
{

   const int TIMES_TO_RUN = 9999999;

   template< class T >
   void passByVal( T val )
   {
      static T i = 0;
      i += val;
   }

   template< class T >
   void passByRef( T& val )
   {
      static T i = 0;
      i += val;
   }

   template< class T >
   void passByConstRef( const T& val )
   {
      static T i =0;
      i += val;
   }


class OptTest : public CppUnit::TestCase
{
public:
   OptTest( std::string name = "OptTest" );

   virtual ~OptTest();

   virtual void setUp();

   virtual void tearDown();

   // this simulates the invert or normalize func
   // two possibilities:
   //    invert( srcAndResult )
   //    invert( result, source )
   //
   void testInPlace();

   // test perf of copy ops
   void testSetEqual();

   // test perf of returning result by reference (no temporary)
   void testRetByReference();

   // test perf of returning internal temporary by value
   void testRetValTemp();

   // test perf of the the return value optimization when returning a temporary by value
   void testRetValOpt();

   // test performance of loop unrolling
   void testLoopUnrolling();


   // test perf of passing a primitive by value/ref/const ref
   // test the performance of passing primitives into functions
   template< class T >
   void testPassPrimitiveTypes()
   {
      T prim = 24;
      std::cout << std::endl << "test performance of passing "<<(typeid(T).name())<<" into funcs" << std::endl;

      // pass by value
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            prim = 12;
            passByVal( prim );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "["<<(typeid(T).name())<<"]testPassPrimitive (value):     " << avg << std::endl;
      }

      // pass by ref
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            prim = 12;
            passByRef( prim );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "["<<(typeid(T).name())<<"]testPassPrimitive (ref):       " << avg << std::endl;
      }

      // pass by const ref
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            prim = 12;
            passByConstRef( prim );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "["<<(typeid(T).name())<<"]testPassPrimitive (const ref): " << avg << std::endl;
      }
   }

   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("OptTest");
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testInPlace", &OptTest::testInPlace));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testSetEqual", &OptTest::testSetEqual));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testRetByReference", &OptTest::testRetByReference));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testRetValTemp", &OptTest::testRetValTemp));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testRetValOpt", &OptTest::testRetValOpt));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testLoopUnrolling", &OptTest::testLoopUnrolling));

      // passing primitives
// work around buggy VC7
#ifndef _WIN32
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testPassPrimitiveTypes<char>", &OptTest::testPassPrimitiveTypes<char>));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testPassPrimitiveTypes<short>", &OptTest::testPassPrimitiveTypes<short>));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testPassPrimitiveTypes<int>", &OptTest::testPassPrimitiveTypes<int>));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testPassPrimitiveTypes<long>", &OptTest::testPassPrimitiveTypes<long>));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testPassPrimitiveTypes<float>", &OptTest::testPassPrimitiveTypes<float>));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testPassPrimitiveTypes<double>", &OptTest::testPassPrimitiveTypes<double>));
#else
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testPassPrimitiveTypes<char>", OptTest::testPassPrimitiveTypes<char>));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testPassPrimitiveTypes<short>", OptTest::testPassPrimitiveTypes<short>));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testPassPrimitiveTypes<int>", OptTest::testPassPrimitiveTypes<int>));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testPassPrimitiveTypes<long>", OptTest::testPassPrimitiveTypes<long>));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testPassPrimitiveTypes<float>", OptTest::testPassPrimitiveTypes<float>));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testPassPrimitiveTypes<double>", OptTest::testPassPrimitiveTypes<double>));
#endif // ! _WIN32
      return test_suite;
   }

   static CppUnit::Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveThreadTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }
private:

};

};

// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#include <math.h>
#include <TestCases/InfoTests/OptTest.h>

namespace gmtlTest
{
   inline double simpleRetValOpt( double myval )
   {
      return double( ::fabs( myval ) );
   }
   inline double simpleRetVal( double myval )
   {
      return ::fabs( myval );
   }
   
   class Mat44
   {
   public:
      Mat44()
      {
         mat[1]  = mat[2]  = mat[3]  = mat[5]  = mat[6]  = mat[7]  = mat[9] =
         mat[10] = mat[11] = mat[13] = mat[14] = mat[15] = mat[16] = 0.0f;
         mat[0]  = mat[4]  = mat[8]  = mat[12] = 1.0f;
      }
      Mat44( const Mat44& v )
      {
         mat[0]  = v.mat[0];
         mat[1]  = v.mat[1];
         mat[2]  = v.mat[2];
         mat[3]  = v.mat[3];
         mat[4]  = v.mat[4];
         mat[5]  = v.mat[5];
         mat[6]  = v.mat[6];
         mat[7]  = v.mat[7];
         mat[8]  = v.mat[8];
         mat[9]  = v.mat[9];
         mat[10] = v.mat[10];
         mat[11] = v.mat[11];
         mat[12] = v.mat[12];
         mat[13] = v.mat[13];
         mat[14] = v.mat[14];
         mat[15] = v.mat[15];
         mat[16] = v.mat[16];
      }

      float mat[16];
   };

   inline Mat44& setEqual( Mat44& lhs, const Mat44& rhs )
   {
      lhs.mat[0]  = rhs.mat[0];
      lhs.mat[1]  = rhs.mat[1];
      lhs.mat[2]  = rhs.mat[2];
      lhs.mat[3]  = rhs.mat[3];
      lhs.mat[4]  = rhs.mat[4];
      lhs.mat[5]  = rhs.mat[5];
      lhs.mat[6]  = rhs.mat[6];
      lhs.mat[7]  = rhs.mat[7];
      lhs.mat[8]  = rhs.mat[8];
      lhs.mat[9]  = rhs.mat[9];
      lhs.mat[10] = rhs.mat[10];
      lhs.mat[11] = rhs.mat[11];
      lhs.mat[12] = rhs.mat[12];
      lhs.mat[13] = rhs.mat[13];
      lhs.mat[14] = rhs.mat[14];
      lhs.mat[15] = rhs.mat[15];
      lhs.mat[16] = rhs.mat[16];
      return lhs;
   }
   inline Mat44& setEqualConst( Mat44& lhs )
   {
      lhs.mat[0]  = 0.0f;
      lhs.mat[1]  = 1.0f;
      lhs.mat[2]  = 0.0f;
      lhs.mat[3]  = 1.0f;
      lhs.mat[4]  = 0.0f;
      lhs.mat[5]  = 0.0f;
      lhs.mat[6]  = 0.0f;
      lhs.mat[7]  = 1.0f;
      lhs.mat[8]  = 0.0f;
      lhs.mat[9]  = 0.0f;
      lhs.mat[10] = 0.0f;
      lhs.mat[11] = 1.0f;
      lhs.mat[12] = 1.0f;
      lhs.mat[13] = 1.0f;
      lhs.mat[14] = 0.0f;
      lhs.mat[15] = 1.0f;
      lhs.mat[16] = 0.0f;
      return lhs;
   }

   inline Mat44 retvalopt( const Mat44& lhs, const Mat44& rhs )
   {
      return Mat44( lhs );
   }
   inline Mat44 retvalInternalTemporary( const Mat44& lhs, const Mat44& rhs )
   {
      Mat44 temporary;
      temporary = lhs;
      return temporary;
   }
   inline void retbyref( Mat44& result, const Mat44& lhs, const Mat44& rhs )
   {
      result = lhs;
   }
   
   class ArrayVec3
   {
   public:
      ArrayVec3()
      {
         vec[0] = 0.0f;
         vec[1] = 0.0f;
         vec[2] = 0.0f;
      }
      ArrayVec3( const ArrayVec3& v )
      {
         vec[0] = v.vec[0];
         vec[1] = v.vec[1];
         vec[2] = v.vec[2];
      }
      ArrayVec3( float x, float y, float z )
      {
         vec[0] = x;
         vec[1] = y;
         vec[2] = z;
      }
      float vec[3];
   };

   inline ArrayVec3& operator+=( ArrayVec3& lhs, const ArrayVec3& rhs )
   {
      lhs.vec[0] += rhs.vec[0];
      lhs.vec[1] += rhs.vec[1];
      lhs.vec[2] += rhs.vec[2];
      return lhs;
   }
   inline ArrayVec3& inplaceModify( ArrayVec3& lhs )
   {
      lhs.vec[0] += lhs.vec[0];
      lhs.vec[1] += lhs.vec[1];
      lhs.vec[2] += lhs.vec[2];
      return lhs;
   }
   inline ArrayVec3& setEqual( ArrayVec3& lhs, const ArrayVec3& rhs )
   {
      lhs.vec[0] = rhs.vec[0];
      lhs.vec[1] = rhs.vec[1];
      lhs.vec[2] = rhs.vec[2];
      return lhs;
   }
   inline ArrayVec3& setEqualConst( ArrayVec3& lhs )
   {
      lhs.vec[0] = 0.0f;
      lhs.vec[1] = 0.0f;
      lhs.vec[2] = 0.0f;
      return lhs;
   }
   inline ArrayVec3 retvalopt( const ArrayVec3& lhs, const ArrayVec3& rhs )
   {
      return ArrayVec3( lhs.vec[0] + rhs.vec[0], lhs.vec[1] + rhs.vec[1], lhs.vec[2] + rhs.vec[2] );
   }
   inline void retbyref( ArrayVec3& result, const ArrayVec3& lhs, const ArrayVec3& rhs )
   {
      result.vec[0] = lhs.vec[0] + rhs.vec[0];
      result.vec[1] = lhs.vec[1] + rhs.vec[1];
      result.vec[2] = lhs.vec[2] + rhs.vec[2];
   }
   inline ArrayVec3 retvalInternalTemporary( const ArrayVec3& lhs, const ArrayVec3& rhs )
   {
      ArrayVec3 temporary;
      temporary.vec[0] = lhs.vec[0] + rhs.vec[0];
      temporary.vec[1] = lhs.vec[1] + rhs.vec[1];
      temporary.vec[2] = lhs.vec[2] + rhs.vec[2];
      return temporary;
   }

   class SeparateVec3
   {
   public:
      SeparateVec3()
      {
         vec1 = 0.0f;
         vec2 = 0.0f;
         vec0 = 0.0f;
      }
      SeparateVec3( const SeparateVec3& v )
      {
         vec0 = v.vec0;
         vec1 = v.vec1;
         vec2 = v.vec2;
      }
      SeparateVec3( float x, float y, float z )
      {
         vec0 = x;
         vec1 = y;
         vec2 = z;
      }
      float vec0, vec1, vec2;
   };

   inline SeparateVec3& setEqual( SeparateVec3& lhs, const SeparateVec3& rhs )
   {
      lhs.vec0 = rhs.vec0;
      lhs.vec1 = rhs.vec1;
      lhs.vec2 = rhs.vec2;
      return lhs;
   }
   inline SeparateVec3& setEqualConst( SeparateVec3& lhs )
   {
      lhs.vec0 = 0.0f;
      lhs.vec1 = 0.0f;
      lhs.vec2 = 0.0f;
      return lhs;
   }
   inline SeparateVec3& inplaceModify( SeparateVec3& lhs )
   {
      lhs.vec0 += lhs.vec0;
      lhs.vec1 += lhs.vec1;
      lhs.vec2 += lhs.vec2;
      return lhs;
   }
   inline SeparateVec3& operator+=( SeparateVec3& lhs, const SeparateVec3& rhs )
   {
      lhs.vec0 += rhs.vec0;
      lhs.vec1 += rhs.vec1;
      lhs.vec2 += rhs.vec2;
      return lhs;
   }

   // listed in More Effective C++
   inline SeparateVec3 retvalopt( const SeparateVec3& lhs, const SeparateVec3& rhs )
   {
      return SeparateVec3( lhs.vec0 + rhs.vec0, lhs.vec1 + rhs.vec1, lhs.vec2 + rhs.vec2 );
   }
   inline SeparateVec3 retvalInternalTemporary( const SeparateVec3& lhs, const SeparateVec3& rhs )
   {
      SeparateVec3 temporary;
      temporary.vec0 = lhs.vec0 + rhs.vec0;
      temporary.vec1 = lhs.vec1 + rhs.vec1;
      temporary.vec2 = lhs.vec2 + rhs.vec2;
      return temporary;
   }
   inline void retbyref( SeparateVec3& result, const SeparateVec3& lhs, const SeparateVec3& rhs )
   {
      result.vec0 = lhs.vec0 + rhs.vec0;
      result.vec1 = lhs.vec1 + rhs.vec1;
      result.vec2 = lhs.vec2 + rhs.vec2;
   }

   // listed in More Effective C++ p 107
   // this might be better, but it wont compile under gcc... :(
   /*
      const SeparateVec3 retvalopt2( const SeparateVec3& lhs, const SeparateVec3& rhs )
      {
         return SeparateVec3( lhs ) -= rhs;
      }
   */

   OptTest::OptTest( std::string name )
   : CppUnit::TestCase (name)
   {;}

   OptTest::~OptTest()
   {}

   void OptTest::setUp()
   {;}

   void OptTest::tearDown()
   {
   }

   // this simulates the invert or normalize func
   // two possibilities:
   //    invert( srcAndResult )
   //    invert( result, source )
   //
   void OptTest::testInPlace()
   {
      SeparateVec3 destvec;
      std::cout << std::endl << "test perf of in-place modification of destvec param (no temporary)" << std::endl;

      // operate on some value in place (uses = and +
      // inplaceModify( result );
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            inplaceModify( destvec );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "\n[s]testInPlace (inplaceModify( destvec );): " << avg << std::endl;
      }
      {
         ArrayVec3 destvec;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            inplaceModify( destvec );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "[a]testInPlace (inplaceModify( destvec );): " << avg << std::endl;
      }

      // do operation to temp
      // operator+=( result, v1 );
      {
         SeparateVec3 srcvec;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            operator+=( destvec, srcvec );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "\n[s]testInPlace (operator+=( destvec, srcvec );): " << avg << std::endl;
      }
      {
         ArrayVec3 destvec;
         ArrayVec3 srcvec;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            operator+=( destvec, srcvec );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "[a]testInPlace (operator+=( destvec, srcvec );): " << avg << std::endl;
      }
   }

   // test perf of copy ops
   void OptTest::testSetEqual()
   {
      SeparateVec3 destvec;
      SeparateVec3 srcvec1;
      std::cout << std::endl << "test perf of copy ops" << std::endl;

      // use our setEqual func to copy
      // setEqual( result, v1 )
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            setEqual( destvec, srcvec1 );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "\n[s]testSetEqual (setEqual( destvec, srcvec1 ) ): " << avg << std::endl;
      }
      {
         ArrayVec3 destvec;
         ArrayVec3 srcvec1;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            setEqual( destvec, srcvec1 );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "[a]testSetEqual (setEqual( destvec, srcvec1 ) ): " << avg << std::endl;
      }
      {
         Mat44 destmat, srcmat;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            setEqual( destmat, srcmat );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "[m]testSetEqual (setEqual( destmat, srcmat ) ): " << avg << std::endl;
      }

      // set destvec from const values
      // setEqualConst( result );
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            setEqualConst( destvec );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "\n[s]testSetEqual (setEqualConst( destvec );): " << avg << std::endl;
      }
      {
         ArrayVec3 destvec;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            setEqualConst( destvec );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "[a]testSetEqual (setEqualConst( destvec );): " << avg << std::endl;
      }
      {
         Mat44 destmat;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            setEqualConst( destmat );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "[m]testSetEqual (setEqualConst( destmat );): " << avg << std::endl;
      }

      // let compiler make the operator=
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec = srcvec1;
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "\n[s]testSetEqual (destvec = srcvec1 from compiler): " << avg << std::endl;
      }
      {
         ArrayVec3 destvec;
         ArrayVec3 srcvec1;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec = srcvec1;
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "[a]testSetEqual (destvec = srcvec1 from compiler): " << avg << std::endl;
      }
      {
         Mat44 destmat, srcmat;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destmat = srcmat;
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "[m]testSetEqual (destmat = srcmat from compiler): " << avg << std::endl;
      }
   }

   // test perf of returning result by reference (no temporary)
   void OptTest::testRetByReference()
   {
      SeparateVec3 destvec;
      SeparateVec3 srcvec1, srcvec2;
      std::cout << std::endl << "test perf of returning result by reference (no temporary)" << std::endl;

      // return by reference
      // retbyref( result, v1, v2 );
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            retbyref( destvec, srcvec1, srcvec2 );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "\n[s]testRetByReference retbyref( destvec, srcvec1, srcvec2 ): " << avg << std::endl;
      }
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            retbyref( destvec, destvec, destvec );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "[s]testRetByReference retbyref( destvec, destvec, srcvec2 ): " << avg << std::endl;
      }
      {
         ArrayVec3 destvec;
         ArrayVec3 srcvec1, srcvec2;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            retbyref( destvec, srcvec1, srcvec2 );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "[a]testRetByReference retbyref( destvec, srcvec1, srcvec2 ): " << avg << std::endl;
      }
      {
         Mat44 destmat;
         Mat44 srcmat1, srcmat2;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            retbyref( destmat, srcmat1, srcmat2 );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "[m]testRetByReference retbyref( destmat, srcmat1, srcmat2 ): " << avg << std::endl;
      }

      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec += srcvec1;
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "\n[s]testRetByReference (destvec += srcvec1): " << avg << std::endl;
      }
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec = srcvec1; destvec += srcvec2;
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "[s]testRetByReference (destvec = srcvec1; destvec += srcvec2): " << avg << std::endl;
      }
      {
         ArrayVec3 destvec;
         ArrayVec3 srcvec1, srcvec2;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec = srcvec1; destvec += srcvec2;
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "[a]testRetByReference (destvec = srcvec1; destvec += srcvec2): " << avg << std::endl;
      }
   }

   // test perf of returning internal temporary by value
   void OptTest::testRetValTemp()
   {
      SeparateVec3 destvec;
      SeparateVec3 srcvec1, srcvec2;
      std::cout << std::endl << "test perf of returning internal temporary by value" << std::endl;

      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec = retvalInternalTemporary( srcvec1, srcvec2 );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "\n[s]testRetValTemp v = retvalInternalTemporary( s1, s2 ): " << avg << std::endl;
      }
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec = retvalInternalTemporary( destvec, srcvec1 );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "[s]testRetValTemp v = retvalInternalTemporary( v, s1 ): " << avg << std::endl;
      }
      {
         ArrayVec3 destvec;
         ArrayVec3 srcvec1, srcvec2;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec = retvalInternalTemporary( srcvec1, srcvec2 );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "[a]testRetValTemp v = retvalInternalTemporary( s1, s2 ): " << avg << std::endl;
      }
      {
         Mat44 destmat;
         Mat44 srcmat1, srcmat2;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destmat = retvalInternalTemporary( srcmat1, srcmat2 );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "[m]testRetValTemp m = retvalInternalTemporary( s1, s2 ): " << avg << std::endl;
      }
   }

   // test perf of the the return value optimization when returning a temporary by value
   void OptTest::testRetValOpt()
   {
      SeparateVec3 destvec;
      SeparateVec3 srcvec1, srcvec2;
      std::cout << std::endl << "test perf of ret val opt when returning a temporary by value" << std::endl;

      // return by value
      // result = retvalopt( v1, v2 );
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec = retvalopt( srcvec1, srcvec2 );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "\n[s]testRetValOpt v = retvalopt( s1, s2 ): " << avg << std::endl;
      }
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec = retvalopt( destvec, destvec );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "[s]testRetValOpt v = retvalopt( v, v ): " << avg << std::endl;
      }
      {
         ArrayVec3 destvec;
         ArrayVec3 srcvec2;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec = retvalopt( destvec, srcvec2 );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "[a]testRetValOpt v = retvalopt( v, s2 ): " << avg << std::endl;
      }
      {
         Mat44 dest;
         Mat44 src1, src2;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            dest = retvalopt( src1, src2 );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "[m]testRetValOpt m = retvalopt( s1, s2 ): " << avg << std::endl;
      }
      
      {
         double myval = -4;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            myval = simpleRetValOpt( -myval );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "[d]testRetValOpt simpleRetValOpt( -4 ): " << end_t - start_t << std::endl;
      }
      {
         double myval = -4;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            myval = simpleRetValOpt( -myval );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "[d]testRetValOpt simpleRetVal( -4 ): " << end_t - start_t << std::endl;
      }
   }



   // test performance of loop unrolling
   void OptTest::testLoopUnrolling()
   {
      ArrayVec3 destvec;
      ArrayVec3 srcvec;
      std::cout << std::endl << "test performance of manual loop unrolling" << std::endl;

      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            for (int y = 0; y < 3; ++y)
            {
               destvec.vec[y] += srcvec.vec[y];
            }
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "\n[a]testLoopUnrolling (forloop ++y): " << avg << std::endl;
      }

      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            for (int y = 0; y < 3; y++)
            {
               destvec.vec[y] += srcvec.vec[y];
            }
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "[a]testLoopUnrolling (forloop y++): " << avg << std::endl;
      }

      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec.vec[0] += srcvec.vec[0];
            destvec.vec[1] += srcvec.vec[1];
            destvec.vec[2] += srcvec.vec[2];
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         double avg = ((double)end_t - (double)start_t) / ((double)TIMES_TO_RUN);
         std::cout << "[a]testLoopUnrolling (unrolled): " << avg << std::endl;
      }
   }

};

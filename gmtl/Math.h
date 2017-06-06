// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _GMTL_MATH_H_
#define _GMTL_MATH_H_

#include <cmath>
#include <cstdlib>
#include <gmtl/Defines.h>
#include <gmtl/Util/Assert.h>
#include <gmtl/Util/StaticAssert.h>

namespace gmtl
{

/** Base class for Rotation orders
 *  @ingroup Defines
 * @see XYZ, ZYX, ZXY
 */
struct RotationOrderBase { enum { IS_ROTORDER = 1 }; };

/** XYZ Rotation order
 *  @ingroup Defines */
struct XYZ : public RotationOrderBase { enum { ID = 0 }; };

/** ZYX Rotation order
 *  @ingroup Defines */
struct ZYX : public RotationOrderBase { enum { ID = 1 }; };

/** ZXY Rotation order
 *  @ingroup Defines */
struct ZXY : public RotationOrderBase { enum { ID = 2 }; };

namespace Math
{
   /** @ingroup Math
    *  @name Mathematical constants
    *  @{
    */
   const float TWO_PI = 6.28318530717958647692f;
   const float PI = 3.14159265358979323846f; //3.14159265358979323846264338327950288419716939937510;
   const float PI_OVER_2 = 1.57079632679489661923f;
   const float PI_OVER_4 = 0.78539816339744830962f;
   /** @} */

   /** @ingroup Math
    *  @name C Math Abstraction
    *  @{
    */
using std::abs;
using std::ceil;
using std::floor;
using std::acos;
using std::asin;
using std::atan;
using std::atan2;
using std::cos;
using std::exp;
using std::log;
using std::pow;
using std::sin;
using std::tan;
using std::sqrt;

//----------------------------------------------------------------------------
template <typename T>
inline int sign( T iValue )
{
   if (iValue > static_cast<T>(0))
   {
      return 1;
   }
   else
   {
      if (iValue < static_cast<T>(0))
      {
         return -1;
      }
      else
      {
         return 0;
      }
   }
}
//----------------------------------------------------------------------------
/**
 * Clamps the given value down to zero if it is within epsilon of zero.
 *
 * @param value      the value to clamp
 * @param eps        the epsilon tolerance or zero by default
 *
 * @return  zero if the value is close to 0, the value otherwise
 */
template <typename T>
inline T zeroClamp( T value, T eps = static_cast<T>(0) )
{
   return ( (gmtl::Math::abs(value) <= eps) ? static_cast<T>(0) : value );
}

//----------------------------------------------------------------------------
// don't allow non-float types, because their ret val wont be correct
// i.e. with int, the int retval will be rounded up or down.
//      we'd need a float retval to do it right, but we can't specialize by ret
template <typename T>
inline T aCos( T fValue );
inline float aCos( float fValue )
{
    if ( -1.0f < fValue )
    {
        if ( fValue < 1.0f )
        {
            return ::acosf(fValue);
        }
        else
            return 0.0f;
    }
    else
    {
        return static_cast<float>(gmtl::Math::PI);
    }
}
inline double aCos( double fValue )
{
    if ( -1.0 < fValue )
    {
        if ( fValue < 1.0 )
            return static_cast<double>(::acos(fValue));
        else
            return 0.0;
    }
    else
    {
        return static_cast<double>(gmtl::Math::PI);
    }
}
//----------------------------------------------------------------------------
template <typename T>
inline T aSin( T fValue );
inline float aSin( float fValue )
{
    if ( -1.0f < fValue )
    {
        if ( fValue < 1.0f )
        {
            return ::asinf(fValue);
        }
        else
            return static_cast<float>(-gmtl::Math::PI_OVER_2);
    }
    else
    {
        return static_cast<float>(gmtl::Math::PI_OVER_2);
    }
}
inline double aSin( double fValue )
{
    if ( -1.0 < fValue )
    {
        if ( fValue < 1.0 )
            return static_cast<double>(::asin(fValue));
        else
            return static_cast<double>(-gmtl::Math::PI_OVER_2);
    }
    else
    {
        return static_cast<double>(gmtl::Math::PI_OVER_2);
    }
}
//----------------------------------------------------------------------------
template <typename T>
inline T aTan(T fValue)
{
    return std::atan(fValue);
}
//----------------------------------------------------------------------------
template <typename T>
inline T aTan2(T fY, T fX)
{
    return std::atan2(fY, fX);
}
//----------------------------------------------------------------------------
template <typename T>
inline T sqr( T fValue )
{
    return static_cast<T>(fValue * fValue);
}

/** Fast inverse square root.
 */
inline float fastInvSqrt(float x)
{
   GMTL_STATIC_ASSERT(sizeof(float) == sizeof(int),
                      Union_type_sizes_do_not_match);

   // Use an approach to data type reinterpretation that is safe with GCC
   // strict aliasing enabled. This is called type-punning, and it is valid
   // when done with a union where the value read (int_value) is different
   // than the one most recently written to (float_value).
   union
   {
      float float_value;
      int   int_value;
   } data;

   const float xhalf(0.5f*x);
   data.float_value = x;
   // This hides a good amount of math
   data.int_value = 0x5f3759df - (data.int_value >> 1);
   x = data.float_value;
   x = x*(1.5f - xhalf*x*x);   // Repeat for more accuracy
   return x;
}

inline float fastInvSqrt2(float x)
{
   GMTL_STATIC_ASSERT(sizeof(float) == sizeof(int),
                      Union_type_sizes_do_not_match);

   // Use an approach to data type reinterpretation that is safe with GCC
   // strict aliasing enabled. This is called type-punning, and it is valid
   // when done with a union where the value read (int_value) is different
   // than the one most recently written to (float_value).
   union
   {
      float float_value;
      int   int_value;
   } data;

   const float xhalf(0.5f*x);
   data.float_value = x;
   // This hides a good amount of math
   data.int_value = 0x5f3759df - (data.int_value >> 1);
   x = data.float_value;
   x = x*(1.5f - xhalf*x*x);   // Repeat for more accuracy
   x = x*(1.5f - xhalf*x*x);
   return x;
}

inline float fastInvSqrt3(float x)
{
   GMTL_STATIC_ASSERT(sizeof(float) == sizeof(int),
                      Union_type_sizes_do_not_match);

   // Use an approach to data type reinterpretation that is safe with GCC
   // strict aliasing enabled. This is called type-punning, and it is valid
   // when done with a union where the value read (int_value) is different
   // than the one most recently written to (float_value).
   union
   {
      float float_value;
      int   int_value;
   } data;

   const float xhalf(0.5f*x);
   data.float_value = x;
   // This hides a good amount of math
   data.int_value = 0x5f3759df - (data.int_value >> 1);
   x = data.float_value;
   x = x*(1.5f - xhalf*x*x);   // Repeat for more accuracy
   x = x*(1.5f - xhalf*x*x);
   x = x*(1.5f - xhalf*x*x);
   return x;
}


//----------------------------------------------------------------------------
/**
 * Seeds the pseudorandom number generator with the given seed.
 *
 * @param seed  the seed for the pseudorandom number generator.
 */
inline void seedRandom(unsigned int seed)
{
   ::srand(seed);
}

/** get a random number between 0 and 1
 * @post returns number between 0 and 1
 */
inline float unitRandom()
{
   return static_cast<float>(::rand()) / static_cast<float>(RAND_MAX);
}

/** return a random number between x1 and x2
 * RETURNS: random number between x1 and x2
 */
inline float rangeRandom( float x1, float x2 )
{
   float r = gmtl::Math::unitRandom();
   float size = x2 - x1;
   return static_cast<float>(r * size + x1);
}

/*
float SymmetricRandom ()
{
    return 2.0 * static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 1.0;
}
*/
//----------------------------------------------------------------------------

inline float deg2Rad( float fVal )
{
   return static_cast<float>(fVal * static_cast<float>(gmtl::Math::PI / 180.0));
}
inline double deg2Rad( double fVal )
{
   return static_cast<double>(fVal * static_cast<double>(gmtl::Math::PI / 180.0));
}

inline float rad2Deg( float fVal )
{
   return static_cast<float>(fVal * static_cast<float>(180.0 / gmtl::Math::PI));
}
inline double rad2Deg( double fVal )
{
   return static_cast<float>(fVal * static_cast<double>(180.0 / gmtl::Math::PI));
}
//----------------------------------------------------------------------------

/** Is almost equal?
 * test for equality within some tolerance...
 * @PRE: tolerance must be >= 0
 */
template <class T>
inline bool isEqual( const T& a, const T& b, const T& tolerance )
{
   gmtlASSERT(tolerance >= static_cast<T>(0));
   return gmtl::Math::abs( a - b ) <= tolerance;
}
//----------------------------------------------------------------------------
/** cut off the digits after the decimal place */
template <class T>
inline T trunc( T val )
{
   return static_cast<T>((val < static_cast<T>(0)) ?
                         gmtl::Math::ceil(val)     :
                         gmtl::Math::floor(val));
}
/** round to nearest integer */
template <class T>
inline T round( T p )
{
   return static_cast<T>(gmtl::Math::floor(p + static_cast<T>(0.5)));
}
//----------------------------------------------------------------------------
/** min returns the minimum of 2 values */
template <class T>
inline T Min( const T& x, const T& y )
{
   return ( x > y ) ? y : x;
}
/** min returns the minimum of 3 values */
template <class T>
inline T Min( const T& x, const T& y, const T& z )
{
   return Min( gmtl::Math::Min( x, y ), z );
}
/** min returns the minimum of 4 values */
template <class T>
inline T Min( const T& w, const T& x, const T& y, const T& z )
{
   return gmtl::Math::Min( gmtl::Math::Min( w, x ), gmtl::Math::Min( y, z ) );
}

/** max returns the maximum of 2 values */
template <class T>
inline T Max( const T& x, const T& y )
{
   return ( x > y ) ? x : y;
}
/** max returns the maximum of 3 values */
template <class T>
inline T Max( const T& x, const T& y, const T& z )
{
   return Max( gmtl::Math::Max( x, y ), z );
}
/** max returns the maximum of 4 values */
template <class T>
inline T Max( const T& w, const T& x, const T& y, const T& z )
{
   return gmtl::Math::Max( gmtl::Math::Max( w, x ), gmtl::Math::Max( y, z ) );
}
//----------------------------------------------------------------------------
/** Compute the factorial.
 * give - an object who's type has operator++, operator=, operator<=, and operator*= defined.
 *        it should be a single valued scalar type such as an int, float, double etc....
 * NOTE: This could be faster with a lookup table, but then wouldn't work templated : kevin
 */
template<class T>
inline T factorial(T rhs)
{
   T lhs = static_cast<T>(1);

   for( T x = static_cast<T>(1); x <= rhs; ++x )
   {
      lhs *= x;
   }

   return lhs;
}
/** @} */

/**
 * clamp "number" to a range between lo and hi
 */
template <class T>
inline T clamp( T number, T lo, T hi )
{
   if (number > hi) number = hi;
   else if (number < lo) number = lo;
   return number;
}

/** @ingroup Interp
 * @name Scalar type interpolation (for doubles, floats, etc...)
 * @{
 */

/** Linear Interpolation between number [a] and [b].
 *  lerp=0.0 returns a, lerp=1.0 returns b
 *  @pre use double or float only...
 */
template <class T, typename U>
inline void lerp( T& result, const U& lerp, const T& a, const T& b )
{
    T size = b - a;
    result = static_cast<U>(a) + (static_cast<U>(size) * lerp);
}
/** @} */

/**
 * Uses the quadratic formula to compute the 2 roots of the given 2nd degree
 * polynomial in the form of Ax^2 + Bx + C.
 *
 * @param r1   set to the first root
 * @param r2   set to the second root
 * @param a    the coefficient to x^2
 * @param b    the coefficient to x^1
 * @param c    the coefficient to x^0
 *
 * @return  true if both r1 and r2 are real; false otherwise
 */
template <class T>
inline bool quadraticFormula(T& r1, T& r2, const T& a, const T& b, const T& c)
{
   const T q = b * b - static_cast<T>(4) * a * c;

   // the result has real roots
   if (q >= 0)
   {
      const T sq = gmtl::Math::sqrt(q);
      const T d = static_cast<T>(1) / (static_cast<T>(2) * a);
      r1 = (-b + sq) * d;
      r2 = (-b - sq) * d;
      return true;
   }
   // the result has complex roots
   else
   {
      return false;
   }
}

} // end namespace Math
} // end namespace gmtl

#endif

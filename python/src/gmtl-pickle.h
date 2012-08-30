// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _PYGMTL_PICKLE_H_
#define _PYGMTL_PICKLE_H_

#include <boost/python.hpp>

#include <gmtl/AABox.h>
#include <gmtl/AxisAngle.h>
#include <gmtl/Coord.h>
#include <gmtl/EulerAngle.h>
#include <gmtl/Frustum.h>
#include <gmtl/LineSeg.h>
#include <gmtl/Matrix.h>
#include <gmtl/Plane.h>
#include <gmtl/Point.h>
#include <gmtl/Quat.h>
#include <gmtl/Ray.h>
#include <gmtl/Sphere.h>
#include <gmtl/Tri.h>
#include <gmtl/Vec.h>


namespace gmtlPickle
{

template<typename T>
struct AABox_pickle : boost::python::pickle_suite
{
   static boost::python::tuple getstate(const gmtl::AABox<T>& b)
   {
      return boost::python::make_tuple(b.mMin, b.mMax);
   }

   static void setstate(gmtl::AABox<T>& b, boost::python::tuple state)
   {
      // Work around a GCC 3.2 bug.
#if defined(__GNUC__) && __GNUC__ == 3 && __GNUC_MINOR__ == 2
      gmtl::Point<T, 3> temp_pt0 = boost::python::extract< gmtl::Point<T, 3> >(state[0]);
      gmtl::Point<T, 3> temp_pt1 = boost::python::extract< gmtl::Point<T, 3> >(state[1]);
      b.mMin = temp_pt0;
      b.mMax = temp_pt1;
#else
      b.mMin = boost::python::extract< gmtl::Point<T, 3> >(state[0]);
      b.mMax = boost::python::extract< gmtl::Point<T, 3> >(state[1]);
#endif
   }
};

template<typename T>
struct AxisAngle_pickle : boost::python::pickle_suite
{
   static boost::python::tuple getstate(const gmtl::AxisAngle<T>& a)
   {
      return boost::python::make_tuple(a[0], a[1], a[2], a[3]);
   }

   static void setstate(gmtl::AxisAngle<T>& a, boost::python::tuple state)
   {
      a[0] = boost::python::extract<T>(state[0]);
      a[1] = boost::python::extract<T>(state[1]);
      a[2] = boost::python::extract<T>(state[2]);
      a[3] = boost::python::extract<T>(state[3]);
   }
};

template<typename POS_TYPE, typename ROT_TYPE>
struct Coord_pickle : boost::python::pickle_suite
{
   static boost::python::tuple getstate(const gmtl::Coord<POS_TYPE, ROT_TYPE>& c)
   {
      return boost::python::make_tuple(c.mPos, c.mRot);
   }

   static void setstate(gmtl::Coord<POS_TYPE, ROT_TYPE>& c,
                        boost::python::tuple state)
   {
      // Work around a GCC 3.2 bug.
#if defined(__GNUC__) && __GNUC__ == 3 && __GNUC_MINOR__ == 2
      POS_TYPE temp = boost::python::extract<POS_TYPE>(state[0]);
      c.mPos = temp;
#else
      c.mPos = boost::python::extract<POS_TYPE>(state[0]);
#endif
      c.mRot = boost::python::extract<ROT_TYPE>(state[1]);
   }
};

template<typename T, typename ROTATION_ORDER>
struct EulerAngle_pickle : boost::python::pickle_suite
{
   static boost::python::tuple getstate(const gmtl::EulerAngle<T, ROTATION_ORDER>& e)
   {
      return boost::python::make_tuple(e[0], e[1], e[2]);
   }

   static void setstate(gmtl::EulerAngle<T, ROTATION_ORDER>& e,
                        boost::python::tuple state)
   {
      e[0] = boost::python::extract<T>(state[0]);
      e[1] = boost::python::extract<T>(state[1]);
      e[2] = boost::python::extract<T>(state[2]);
   }
};

template<typename T>
struct LineSeg_pickle : boost::python::pickle_suite
{
   static boost::python::tuple getstate(const gmtl::LineSeg<T>& l)
   {
      return boost::python::make_tuple(l.mOrigin, l.mDir);
   }

   static void setstate(gmtl::LineSeg<T>& l, boost::python::tuple state)
   {
      // Work around a GCC 3.2 bug.
#if defined(__GNUC__) && __GNUC__ == 3 && __GNUC_MINOR__ == 2
      gmtl::Point<T, 3> temp_pt = boost::python::extract< gmtl::Point<T, 3> >(state[0]);
      gmtl::Vec<T, 3> temp_vec  = boost::python::extract< gmtl::Vec<T, 3> >(state[1]);
      l.mOrigin = temp_pt;
      l.mDir    = temp_vec;
#else
      l.mOrigin = boost::python::extract< gmtl::Point<T, 3> >(state[0]);
      l.mDir    = boost::python::extract< gmtl::Vec<T, 3> >(state[1]);
#endif
   }
};

template<typename T>
struct Matrix33_pickle : boost::python::pickle_suite
{
   static boost::python::tuple getstate(const gmtl::Matrix<T, 3, 3>& m)
   {
      return boost::python::make_tuple(m.mData[0], m.mData[1], m.mData[2],
                                       m.mData[3], m.mData[4], m.mData[5],
                                       m.mData[6], m.mData[7], m.mData[8]);
   }

   static void setstate(gmtl::Matrix<T, 3, 3>& m, boost::python::tuple state)
   {
      for ( unsigned int i = 0; i < 9; ++i )
      {
         m.mData[i] = boost::python::extract<T>(state[i]);
      }
   }
};

template<typename T>
struct Matrix44_pickle : boost::python::pickle_suite
{
   static boost::python::tuple getstate(const gmtl::Matrix<T, 4, 4>& m)
   {
      return boost::python::make_tuple( m.mData[0],  m.mData[1],  m.mData[2],
                                        m.mData[3],  m.mData[4],  m.mData[5],
                                        m.mData[6],  m.mData[7],  m.mData[8],
                                        m.mData[9], m.mData[10], m.mData[11],
                                       m.mData[12], m.mData[13], m.mData[14],
                                       m.mData[15]);
   }

   static void setstate(gmtl::Matrix<T, 4, 4>& m, boost::python::tuple state)
   {
      for ( unsigned int i = 0; i < 16; ++i )
      {
         m.mData[i] = boost::python::extract<T>(state[i]);
      }
   }
};

template<typename T>
struct Plane_pickle : boost::python::pickle_suite
{
   static boost::python::tuple getstate(const gmtl::Plane<T>& p)
   {
      return boost::python::make_tuple(p.mNorm, p.mOffset);
   }

   static void setstate(gmtl::Plane<T>& p, boost::python::tuple state)
   {
      // Work around a GCC 3.2 bug.
#if defined(__GNUC__) && __GNUC__ == 3 && __GNUC_MINOR__ == 2
      gmtl::Vec<T, 3> temp = boost::python::extract< gmtl::Vec<T, 3> >(state[0]);
      p.mNorm   = temp;
#else
      p.mNorm   = boost::python::extract< gmtl::Vec<T, 3> >(state[0]);
#endif
      p.mOffset = boost::python::extract<T>(state[1]);
   }
};

template<typename T>
struct Point2_pickle : boost::python::pickle_suite
{
   static boost::python::tuple getstate(const gmtl::Point<T, 2>& p)
   {
      return boost::python::make_tuple(p[0], p[1]);
   }

   static void setstate(gmtl::Point<T, 2>& p, boost::python::tuple state)
   {
      p[0] = boost::python::extract<T>(state[0]);
      p[1] = boost::python::extract<T>(state[1]);
   }
};

template<typename T>
struct Point3_pickle : boost::python::pickle_suite
{
   static boost::python::tuple getstate(const gmtl::Point<T, 3>& p)
   {
      return boost::python::make_tuple(p[0], p[1], p[2]);
   }

   static void setstate(gmtl::Point<T, 3>& p, boost::python::tuple state)
   {
      p[0] = boost::python::extract<T>(state[0]);
      p[1] = boost::python::extract<T>(state[1]);
      p[2] = boost::python::extract<T>(state[2]);
   }
};

template<typename T>
struct Quat_pickle : boost::python::pickle_suite
{
   static boost::python::tuple getstate(const gmtl::Quat<T>& q)
   {
      return boost::python::make_tuple(q[0], q[1], q[2], q[3]);
   }

   static void setstate(gmtl::Quat<T>& q, boost::python::tuple state)
   {
      q[0] = boost::python::extract<T>(state[0]);
      q[1] = boost::python::extract<T>(state[1]);
      q[2] = boost::python::extract<T>(state[2]);
      q[3] = boost::python::extract<T>(state[3]);
   }
};

template<typename T>
struct Ray_pickle : boost::python::pickle_suite
{
   static boost::python::tuple getstate(const gmtl::Ray<T>& r)
   {
      return boost::python::make_tuple(r.mOrigin, r.mDir);
   }

   static void setstate(gmtl::Ray<T>& r, boost::python::tuple state)
   {
      // Work around a GCC 3.2 bug.
#if defined(__GNUC__) && __GNUC__ == 3 && __GNUC_MINOR__ == 2
      gmtl::Point<T, 3> temp_pt = boost::python::extract< gmtl::Point<T, 3> >(state[0]);
      gmtl::Vec<T, 3> temp_vec = boost::python::extract< gmtl::Vec<T, 3> >(state[1]);
      r.mOrigin = temp_pt;
      r.mDir    = temp_vec;
#else
      r.mOrigin = boost::python::extract< gmtl::Point<T, 3> >(state[0]);
      r.mDir    = boost::python::extract< gmtl::Vec<T, 3> >(state[1]);
#endif
   }
};

template<typename T>
struct Sphere_pickle : boost::python::pickle_suite
{
   static boost::python::tuple getstate(const gmtl::Sphere<T>& s)
   {
      return boost::python::make_tuple(s.mCenter, s.mRadius);
   }

   static void setstate(gmtl::Sphere<T>& s, boost::python::tuple state)
   {
      // Work around a GCC 3.2 bug.
#if defined(__GNUC__) && __GNUC__ == 3 && __GNUC_MINOR__ == 2
      gmtl::Point<T, 3> temp = boost::python::extract< gmtl::Point<T, 3> >(state[0]);
      s.mCenter = temp;
#else
      s.mCenter = boost::python::extract< gmtl::Point<T, 3> >(state[0]);
#endif
      s.mRadius = boost::python::extract<T>(state[1]);
   }
};

template<typename T>
struct Tri_pickle : boost::python::pickle_suite
{
   static boost::python::tuple getstate(const gmtl::Tri<T>& t)
   {
      return boost::python::make_tuple(t[0], t[1], t[2]);
   }

   static void setstate(gmtl::Tri<T>& t, boost::python::tuple state)
   {
      // Work around a GCC 3.2 bug.
#if defined(__GNUC__) && __GNUC__ == 3 && __GNUC_MINOR__ == 2
      gmtl::Point<T, 3> temp0 = boost::python::extract< gmtl::Point<T, 3> >(state[0]);
      gmtl::Point<T, 3> temp1 = boost::python::extract< gmtl::Point<T, 3> >(state[1]);
      gmtl::Point<T, 3> temp2 = boost::python::extract< gmtl::Point<T, 3> >(state[2]);
      t[0] = temp0;
      t[1] = temp1;
      t[2] = temp2;
#else
      t[0] = boost::python::extract< gmtl::Point<T, 3> >(state[0]);
      t[1] = boost::python::extract< gmtl::Point<T, 3> >(state[1]);
      t[2] = boost::python::extract< gmtl::Point<T, 3> >(state[2]);
#endif
   }
};

template<typename T>
struct VecBase2_pickle : boost::python::pickle_suite
{
   static boost::python::tuple getstate(const gmtl::VecBase<T, 2>& v)
   {
      return boost::python::make_tuple(v[0], v[1]);
   }

   static void setstate(gmtl::VecBase<T, 2>& v, boost::python::tuple state)
   {
      v[0] = boost::python::extract<T>(state[0]);
      v[1] = boost::python::extract<T>(state[1]);
   }
};

template<typename T>
struct VecBase3_pickle : boost::python::pickle_suite
{
   static boost::python::tuple getstate(const gmtl::VecBase<T, 3>& v)
   {
      return boost::python::make_tuple(v[0], v[1], v[2]);
   }

   static void setstate(gmtl::VecBase<T, 3>& v, boost::python::tuple state)
   {
      v[0] = boost::python::extract<T>(state[0]);
      v[1] = boost::python::extract<T>(state[1]);
      v[2] = boost::python::extract<T>(state[2]);
   }
};

template<typename T>
struct VecBase4_pickle : boost::python::pickle_suite
{
   static boost::python::tuple getstate(const gmtl::VecBase<T, 4>& v)
   {
      return boost::python::make_tuple(v[0], v[1], v[2], v[3]);
   }

   static void setstate(gmtl::VecBase<T, 4>& v, boost::python::tuple state)
   {
      v[0] = boost::python::extract<T>(state[0]);
      v[1] = boost::python::extract<T>(state[1]);
      v[2] = boost::python::extract<T>(state[2]);
      v[3] = boost::python::extract<T>(state[3]);
   }
};

template<typename T>
struct Vec2_pickle : boost::python::pickle_suite
{
   static boost::python::tuple getstate(const gmtl::Vec<T, 2>& v)
   {
      return boost::python::make_tuple(v[0], v[1]);
   }

   static void setstate(gmtl::Vec<T, 2>& v, boost::python::tuple state)
   {
      v[0] = boost::python::extract<T>(state[0]);
      v[1] = boost::python::extract<T>(state[1]);
   }
};

template<typename T>
struct Vec3_pickle : boost::python::pickle_suite
{
   static boost::python::tuple getstate(const gmtl::Vec<T, 3>& v)
   {
      return boost::python::make_tuple(v[0], v[1], v[2]);
   }

   static void setstate(gmtl::Vec<T, 3>& v, boost::python::tuple state)
   {
      v[0] = boost::python::extract<T>(state[0]);
      v[1] = boost::python::extract<T>(state[1]);
      v[2] = boost::python::extract<T>(state[2]);
   }
};

template<typename T>
struct Vec4_pickle : boost::python::pickle_suite
{
   static boost::python::tuple getstate(const gmtl::Vec<T, 4>& v)
   {
      return boost::python::make_tuple(v[0], v[1], v[2], v[3]);
   }

   static void setstate(gmtl::Vec<T, 4>& v, boost::python::tuple state)
   {
      v[0] = boost::python::extract<T>(state[0]);
      v[1] = boost::python::extract<T>(state[1]);
      v[2] = boost::python::extract<T>(state[2]);
      v[3] = boost::python::extract<T>(state[3]);
   }
};

template<typename T>
struct Frustum_pickle : boost::python::pickle_suite
{
   static boost::python::tuple getstate(const gmtl::Frustum<T>& f)
   {
      return boost::python::make_tuple(f.mPlanes[0], f.mPlanes[1],
                                       f.mPlanes[2], f.mPlanes[3],
                                       f.mPlanes[4], f.mPlanes[5]);
   }

   static void setstate(gmtl::Frustum<T>& f, boost::python::tuple state)
   {
      f.mPlanes[0] = boost::python::extract< gmtl::Plane<T> >(state[0]);
      f.mPlanes[1] = boost::python::extract< gmtl::Plane<T> >(state[1]);
      f.mPlanes[2] = boost::python::extract< gmtl::Plane<T> >(state[2]);
      f.mPlanes[3] = boost::python::extract< gmtl::Plane<T> >(state[3]);
      f.mPlanes[4] = boost::python::extract< gmtl::Plane<T> >(state[4]);
      f.mPlanes[5] = boost::python::extract< gmtl::Plane<T> >(state[5]);
   }
};

}

#endif /* _PYGMTL_PICKLE_H_ */

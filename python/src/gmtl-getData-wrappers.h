// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

// This file was originally part of PyJuggler.

// PyJuggler is (C) Copyright 2002, 2003 by Patrick Hartling
// Distributed under the GNU Lesser General Public License 2.1.  (See
// accompanying file COPYING.txt or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _PYJUGGLER_GMTL_GETDATA_WRAPPERS_H_
#define _PYJUGGLER_GMTL_GETDATA_WRAPPERS_H_

#include <boost/python/tuple.hpp>
#include <gmtl/Matrix.h>
#include <gmtl/VecBase.h>
#include <gmtl/Quat.h>
#include <gmtl/EulerAngle.h>
#include <gmtl/Frustum.h>


namespace gmtlWrappers
{
   template<typename T, unsigned SIZE>
   static boost::python::list makeDataList(T* data)
   {
      boost::python::list l;

      for ( unsigned int i = 0; i < SIZE; ++i )
      {
         l.append(data[i]);
      }

      return l;
   }

   template<typename T>
   boost::python::list Matrix_3_3_getData(gmtl::Matrix<T, 3, 3>* m)
   {
      return makeDataList<float, 9>(m->mData);
   }

   template<typename T>
   boost::python::list Matrix_4_4_getData(gmtl::Matrix<T, 4, 4>* m)
   {
      return makeDataList<float, 16>(m->mData);
   }

   template<typename T>
   boost::python::tuple VecBase_2_getData(gmtl::VecBase<T, 2>* v)
   {
      return boost::python::make_tuple(v->mData[0], v->mData[1]);
   }

   template<typename T>
   boost::python::tuple VecBase_3_getData(gmtl::VecBase<T, 3>* v)
   {
      return boost::python::make_tuple(v->mData[0], v->mData[1], v->mData[2]);
   }

   template<typename T>
   boost::python::tuple VecBase_4_getData(gmtl::VecBase<T, 4>* v)
   {
      return boost::python::make_tuple(v->mData[0], v->mData[1], v->mData[2],
                                       v->mData[3]);
   }

   template<typename T>
   boost::python::tuple Quat_getData(gmtl::Quat<T>* q)
   {
      return boost::python::make_tuple(q->mData[0], q->mData[1], q->mData[2],
                                       q->mData[3]);
   }

   template<typename TYPE, typename ROT>
   boost::python::tuple EulerAngle_getData(gmtl::EulerAngle<TYPE, ROT>* ang)
   {
      return boost::python::make_tuple(ang->getData()[0], ang->getData()[1],
                                       ang->getData()[2]);
   }

   template<typename TYPE>
   boost::python::tuple Frustum_getPlanes(gmtl::Frustum<TYPE>* f)
   {
      return boost::python::make_tuple(f->mPlanes[0], f->mPlanes[1],
                                       f->mPlanes[2], f->mPlanes[3],
                                       f->mPlanes[4], f->mPlanes[5]);
   }
}

#if ! defined(__APPLE__)
namespace gmtlWrappers
{
   template boost::python::list Matrix_3_3_getData(gmtl::Matrix<float, 3, 3>*);

   template boost::python::list Matrix_4_4_getData(gmtl::Matrix<float, 4, 4>*);

   template boost::python::tuple VecBase_2_getData(gmtl::VecBase<double, 2>*);
   template boost::python::tuple VecBase_2_getData(gmtl::VecBase<float, 2>*);
   template boost::python::tuple VecBase_2_getData(gmtl::VecBase<int, 2>*);

   template boost::python::tuple VecBase_3_getData(gmtl::VecBase<double, 3>*);
   template boost::python::tuple VecBase_3_getData(gmtl::VecBase<float, 3>*);
   template boost::python::tuple VecBase_3_getData(gmtl::VecBase<int, 3>*);

   template boost::python::tuple VecBase_4_getData(gmtl::VecBase<double, 4>*);
   template boost::python::tuple VecBase_4_getData(gmtl::VecBase<float, 4>*);
   template boost::python::tuple VecBase_4_getData(gmtl::VecBase<int, 4>*);

   template boost::python::tuple Quat_getData(gmtl::Quatd*);
   template boost::python::tuple Quat_getData(gmtl::Quatf*);

   template boost::python::tuple EulerAngle_getData(gmtl::EulerAngleXYZf*);
   template boost::python::tuple EulerAngle_getData(gmtl::EulerAngleZYXf*);
   template boost::python::tuple EulerAngle_getData(gmtl::EulerAngleZXYf*);

   template boost::python::tuple Frustum_getPlanes(gmtl::Frustumf*);
   template boost::python::tuple Frustum_getPlanes(gmtl::Frustumd*);
}
#endif


#endif /* _GMTL_GETDATA_WRAPPERS_H_ */

// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _PYGMTL_GMTL_ARRAY_WRAPPERS_H_
#define _PYGMTL_GMTL_ARRAY_WRAPPERS_H_

#include <boost/python/list.hpp>
#include <gmtl/Matrix.h>
#include <gmtl/VecBase.h>


namespace gmtlWrappers
{
   template<typename T, unsigned int ROWS, unsigned int COLS>
   void Matrix_set(gmtl::Matrix<T, ROWS, COLS>* m, boost::python::list pyData)
   {
      T gmtl_data[ROWS * COLS];

      for ( unsigned int i = 0; i < ROWS * COLS; ++i )
      {
         gmtl_data[i] = boost::python::extract<T>(pyData[i]);
      }

      m->set(gmtl_data);
   }

   template<typename T, unsigned int ROWS, unsigned int COLS>
   void Matrix_setTranspose(gmtl::Matrix<T, ROWS, COLS>* m,
                            boost::python::list pyData)
   {
      T gmtl_data[ROWS * COLS];

      for ( unsigned int i = 0; i < ROWS * COLS; ++i )
      {
         gmtl_data[i] = boost::python::extract<T>(pyData[i]);
      }

      m->setTranspose(gmtl_data);
   }

   template<typename T, unsigned int SIZE>
   void VecBase_set(gmtl::VecBase<T, SIZE>* v, boost::python::list pyData)
   {
      T gmtl_data[SIZE];

      for ( unsigned int i = 0; i < SIZE; ++i )
      {
         gmtl_data[i] = boost::python::extract<T>(pyData[i]);
      }

      v->set(gmtl_data);
   }
}

#if ! defined(__APPLE__)
namespace gmtlWrappers
{
   template void Matrix_set(gmtl::Matrix<float, 3, 3>*, boost::python::list);
   template void Matrix_set(gmtl::Matrix<float, 4, 4>*, boost::python::list);

   template void Matrix_setTranspose(gmtl::Matrix<float, 3, 3>*,
                                     boost::python::list);
   template void Matrix_setTranspose(gmtl::Matrix<float, 4, 4>*,
                                     boost::python::list);

   template void VecBase_set(gmtl::VecBase<double, 2>*, boost::python::list);
   template void VecBase_set(gmtl::VecBase<double, 3>*, boost::python::list);
   template void VecBase_set(gmtl::VecBase<double, 4>*, boost::python::list);
   template void VecBase_set(gmtl::VecBase<float, 2>*, boost::python::list);
   template void VecBase_set(gmtl::VecBase<float, 3>*, boost::python::list);
   template void VecBase_set(gmtl::VecBase<float, 4>*, boost::python::list);
   template void VecBase_set(gmtl::VecBase<int, 2>*, boost::python::list);
   template void VecBase_set(gmtl::VecBase<int, 3>*, boost::python::list);
   template void VecBase_set(gmtl::VecBase<int, 4>*, boost::python::list);
}
#endif


#endif /* _PYGMTL_GMTL_ARRAY_WRAPPERS_H_ */

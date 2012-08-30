// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

// This file was originally part of PyJuggler.

// PyJuggler is (C) Copyright 2002, 2003 by Patrick Hartling
// Distributed under the GNU Lesser General Public License 2.1.  (See
// accompanying file COPYING.txt or http://www.gnu.org/copyleft/lesser.txt)

// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl/Matrix.h>
#include <gmtl/Output.h>
#include <gmtl-wrappers.h>
#include <gmtl-getData-wrappers.h>
#include <gmtl-array-wrappers.h>
#include <gmtl-callable-wrappers.h>
#include <gmtl-pickle.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_Matrix_float_4_4()
{
    scope* gmtl_Matrix_float_4_4_scope = new scope(
    class_< gmtl::Matrix<float,4,4> >("Matrix44f", init<  >())
        .def(init< const gmtl::Matrix<float,4,4> & >())
        .def_readwrite("state", &gmtl::Matrix<float,4,4>::mState)
        .def("set", (void (gmtl::Matrix<float,4,4>::*)(float, float, float, float, float, float, float, float, float, float, float, float, float, float, float, float) )&gmtl::Matrix<float,4,4>::set)
        .def("set", (void (*)(gmtl::Matrix<float,4,4>*,list))&gmtlWrappers::Matrix_set)
        .def("set",
             (gmtl::Matrix<float, 4, 4>& (gmtl::Matrix<float, 4, 4>::*)(const gmtl::Matrix<float, 4, 4>&)) &gmtl::Matrix<float, 4, 4>::operator=,
             return_internal_reference<1>())
        .def("setTranspose", (void (*)(gmtl::Matrix<float,4,4>*,list))&gmtlWrappers::Matrix_setTranspose)
        .def("getData", (list (*)(gmtl::Matrix<float,4,4>*)) &gmtlWrappers::Matrix_4_4_getData)
        .add_property("data", (list (*)(gmtl::Matrix<float,4,4>*)) &gmtlWrappers::Matrix_4_4_getData)
        .def("isError", &gmtl::Matrix<float,4,4>::isError)
        .def("setError", &gmtl::Matrix<float,4,4>::setError)
        .def("__getitem__", (gmtl::Matrix<float,4,4>::RowAccessor (gmtl::Matrix<float,4,4>::*)(const unsigned) )&gmtl::Matrix<float,4,4>::operator[])
        .def("__call__", (float (*)(gmtl::Matrix<float,4,4>*, const unsigned int, const unsigned int))&gmtlWrappers::callable)
        .def_pickle(gmtlPickle::Matrix44_pickle<float>())
        .def(self * self)
        .def(self * gmtl::Point3f())
        .def(self * gmtl::Point4f())
        .def(self * gmtl::Vec3f())
        .def(self * gmtl::Vec4f())
        .def(self * gmtl::LineSegf())
        .def(self * gmtl::Rayf())
        .def(self *= self)
//        .def(self * float())
        .def(self *= float())
        .def(self == self)
        .def(self != self)
        .def(self_ns::str(self))
    );

    class_< gmtl::Matrix<float,4,4>::RowAccessor >("RowAccessor", no_init)
       .def("__getitem__", &gmtl::Matrix<float,4,4>::RowAccessor::operator[], return_value_policy<copy_non_const_reference>())
       .def("__setitem__", (void (*)(gmtl::Matrix<float,4,4>::RowAccessor*, const unsigned, float)) &gmtlWrappers::setArrayElement)
    ;


    enum_< gmtl::Matrix<float,4,4>::Params >("Params")
        .value("Rows", gmtl::Matrix<float,4,4>::Rows)
        .value("Cols", gmtl::Matrix<float,4,4>::Cols)
    ;


    enum_< gmtl::Matrix<float,4,4>::XformState >("XformState")
        .value("TRANS", gmtl::Matrix<float,4,4>::TRANS)
        .value("FULL", gmtl::Matrix<float,4,4>::FULL)
        .value("ORTHOGONAL", gmtl::Matrix<float,4,4>::ORTHOGONAL)
        .value("AFFINE", gmtl::Matrix<float,4,4>::AFFINE)
        .value("NON_UNISCALE", gmtl::Matrix<float,4,4>::NON_UNISCALE)
        .value("XFORM_ERROR", gmtl::Matrix<float,4,4>::XFORM_ERROR)
        .value("IDENTITY", gmtl::Matrix<float,4,4>::IDENTITY)
    ;

    delete gmtl_Matrix_float_4_4_scope;

}

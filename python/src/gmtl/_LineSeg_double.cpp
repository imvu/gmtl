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
#include <gmtl/LineSeg.h>
#include <gmtl/LineSegOps.h>
#include <gmtl/Xforms.h>
#include <gmtl/Output.h>
#include <gmtl-pickle.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_LineSeg_double()
{
    class_< gmtl::LineSeg<double>, bases< gmtl::Ray<double> >  >("LineSegd", init<  >())
        .def(init< const gmtl::Point<double,3> &, const gmtl::Vec<double,3> & >())
        .def(init< const gmtl::LineSeg<double> & >())
        .def(init< const gmtl::Point<double,3> &, const gmtl::Point<double,3> & >())
        .def("getLength", &gmtl::LineSeg<double>::getLength)
        .def("set",
             (gmtl::LineSeg<double>& (gmtl::LineSeg<double>::*)(const gmtl::LineSeg<double>&)) &gmtl::LineSeg<double>::operator=,
             return_internal_reference<1>())
        .def_pickle(gmtlPickle::LineSeg_pickle<double>())
        .def(self == self)
        .def(self != self)
        .def(self *= gmtl::Matrix<double,3,3>())
        .def(self *= gmtl::Matrix<double,4,4>())
        .def(self_ns::str(self))
    ;

}

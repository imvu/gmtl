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
#include <gmtl/Point.h>
#include <gmtl-pickle.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_Point_double_3()
{
    scope* gmtl_Point_double_3_scope = new scope(
    class_< gmtl::Point<double,3>, bases< gmtl::VecBase<double,3> > >("Point3d", init<  >())
        .def(init< const gmtl::Point<double,3> & >())
        .def(init< const gmtl::VecBase<double,3> & >())
        .def(init< const double &, const double &, const double & >())
        .def_pickle(gmtlPickle::Point3_pickle<double>())
    );

    enum_< gmtl::Point<double,3>::Params >("Params")
        .value("Size", gmtl::Point<double,3>::Size)
    ;

    delete gmtl_Point_double_3_scope;

}

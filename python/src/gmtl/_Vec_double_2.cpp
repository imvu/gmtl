// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl/Vec.h>
#include <gmtl-pickle.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_Vec_double_2()
{
    scope* gmtl_Vec_double_2_scope = new scope(
    class_< gmtl::Vec<double,2>, bases< gmtl::VecBase<double,2> >  >("Vec2d", init<  >())
        .def(init< const gmtl::Vec<double,2> & >())
        .def(init< const gmtl::VecBase<double,2> & >())
        .def(init< const double &, const double & >())
        .def_pickle(gmtlPickle::Vec2_pickle<double>())
    );

    enum_< gmtl::Vec<double,2>::Params >("Params")
        .value("Size", gmtl::Vec<double,2>::Size)
    ;

    delete gmtl_Vec_double_2_scope;

}

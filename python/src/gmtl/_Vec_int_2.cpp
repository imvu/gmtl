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
void _Export_Vec_int_2()
{
    scope* gmtl_Vec_int_2_scope = new scope(
    class_< gmtl::Vec<int,2>, bases< gmtl::VecBase<int,2> >  >("Vec2i", init<  >())
        .def(init< const gmtl::Vec<int,2> & >())
        .def(init< const gmtl::VecBase<int,2> & >())
        .def(init< const int &, const int & >())
        .def_pickle(gmtlPickle::Vec2_pickle<int>())
    );

    enum_< gmtl::Vec<int,2>::Params >("Params")
        .value("Size", gmtl::Vec<int,2>::Size)
    ;

    delete gmtl_Vec_int_2_scope;

}

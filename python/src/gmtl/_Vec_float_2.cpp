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
void _Export_Vec_float_2()
{
    scope* gmtl_Vec_float_2_scope = new scope(
    class_< gmtl::Vec<float,2>, bases< gmtl::VecBase<float,2> > >("Vec2f", init<  >())
        .def(init< const gmtl::Vec<float,2> & >())
        .def(init< const gmtl::VecBase<float,2> & >())
        .def(init< const float &, const float & >())
        .def_pickle(gmtlPickle::Vec2_pickle<float>())
    );

    enum_< gmtl::Vec<float,2>::Params >("Params")
        .value("Size", gmtl::Vec<float,2>::Size)
    ;

    delete gmtl_Vec_float_2_scope;

}

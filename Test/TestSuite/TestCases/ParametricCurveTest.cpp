// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#define GMTL_COUNT_CONSTRUCT_CALLS 1      // Count the consturctor calls

#include "ParametriCurveTest.h"
#include "../Suites.h"
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/ParametriCurve.h>

namespace gmtlTest
{

CPPUNIT_TEST_SUITE_REGISTRATION(ParametriCurveTest);
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(ParametriCurveMetricTest,
                                      Suites::metric());

void ParametriCurveTest::testParametriCurveMeta()
{
   // Begin
   gmtl::Vec2f cp[3], result1, result2;
   cp[0].set(0.0f, 0.0f);
   cp[1].set(1.0f, 1.0f);
   cp[2].set(2.0f, 0.0f);
   gmtl::QuadraticCurve2f test;
   test.makeBezier();
   test.setControlPoints(cp);
   result1 = test.getInterpolatedValue(0.5f);
   result2 = test.getInterpolatedDerivative(0.5f);
   // End
   Assert::AreEqual(1.0f, result1[0], 0.0000001f);
   Assert::AreEqual(0.5f, result1[1], 0.0000001f);
   Assert::AreEqual(2.0f, result2[0], 0.0000001f);
   Assert::AreEqual(0.0f, result2[1], 0.0000001f);
}

}

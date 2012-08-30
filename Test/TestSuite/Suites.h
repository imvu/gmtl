// GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
// Distributed under the GNU Lesser General Public License 2.1 with an
// addendum covering inlined code. (See accompanying files LICENSE and
// LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

#ifndef _SUITES_H_
#define _SUITES_H_

#include <string>

namespace gmtlTest
{
   namespace Suites
   {
      inline std::string metric()
      {
        return "metric";
      }

      inline std::string noninteractive()
      {
        return "noninteractive";
      }

      inline std::string interactive()
      {
        return "interactive";
      }
   }
}

#endif

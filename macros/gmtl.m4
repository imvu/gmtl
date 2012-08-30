dnl GMTL is (C) Copyright 2001-2011 by Allen Bierbaum
dnl Distributed under the GNU Lesser General Public License 2.1 with an
dnl addendum covering inlined code. (See accompanying files LICENSE and
dnl LICENSE.addendum or http://www.gnu.org/copyleft/lesser.txt)

dnl ---------------------------------------------------------------------------
dnl Test for GMTL and then define GMTL_CXXFLAGS, GMTL_INCLUDES, and
dnl GMTL_VERSION.
dnl
dnl Usage:
dnl    GMTL_PATH(version , gmtl-root [, include-path [, action-if-found [, action-if-not-found]]])
dnl
dnl Arguments:
dnl    version             - The minimum required version.
dnl    action-if-found     - The action to take if a GMTL implementation is
dnl                          found.  This argument is optional.
dnl    action-if-not-found - The action to take if a GMTL implementation is
dnl                          not found.  This argument is optional.
dnl ---------------------------------------------------------------------------
AC_DEFUN([GMTL_PATH],
[
   AM_PATH_FLAGPOLL([0.8.1], ,
                    [AC_MSG_ERROR(*** Flagpoll required for GMTL flags ***)])

   min_gmtl_version=ifelse([$1], ,0.4.11,$1)
   AC_MSG_CHECKING([for GMTL version >= $min_gmtl_version])

   GMTL_VERSION=`$FLAGPOLL gmtl --modversion`
   if $FLAGPOLL gmtl --atleast-version=$min_gmtl_version >/dev/null 2>&1
   then
      :
   else
      no_gmtl='yes'
   fi

   if test "x$no_gmtl" = "xyes" ; then
      AC_MSG_RESULT([no ($GMTL_VERSION)])

      ifelse([$3], , :, [$3])
   else
      AC_MSG_RESULT([yes ($GMTL_VERSION)])

      GMTL_CXXFLAGS=`$FLAGPOLL gmtl --cflags`
      GMTL_INCLUDES=`$FLAGPOLL gmtl --cflags-only-I`

      ifelse([$2], , :, [$2])
   fi

   AC_SUBST(GMTL_CXXFLAGS)
   AC_SUBST(GMTL_INCLUDES)
   AC_SUBST(GMTL_VERSION)
])

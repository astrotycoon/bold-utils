##############################################################################
#
#                       Bold Configuration
#
#  This file is distributed under the New BSD License.
#  See LICENSE for details.
#
##############################################################################

####################
#  Autoconf/Automake Initialization

dnl AC_INIT(PKG_NAME, BUILD_VERSION, BUG_REPORTER)
AC_INIT([Bold],[newbabe],[bold-dev@googlegroups.com])
AC_PREREQ(2.59)

AC_CONFIG_SRCDIR([LICENSE])
AC_CONFIG_AUX_DIR([scripts])
AC_CONFIG_MACRO_DIR([m4])

####################
#  Check environments - `host`, `target` and `build`
CHECK_CANONICAL_SYSTEM

AM_INIT_AUTOMAKE([1.9 dist-bzip2 foreign nostdinc subdir-objects])

####################
#  Versioning, see VERSION
MAJOR=0
MINOR=1
MICRO=0
AGE=0
PKG=newbabe

DEV_VERSION=$MAJOR:$MINOR:$AGE
PKG_VERSION=$MAJOR.$MINOR.$MICRO-$PKG
BOLD_VERSION=$DEV_VERSION
AC_SUBST(BOLD_VERSION)

####################
#  Languages
AC_PROG_CC
AC_PROG_CXX
AC_LANG([C++])
AC_CXX_STL_HASH
AM_CONDITIONAL(GCC, test "$GCC" = yes)   # let the Makefile know if we're gcc
LT_INIT

####################
# Check for compiler warnings
CHECK_WERROR_FLAGS
CXX_FLAG_CHECK([-Wno-variadic-macros])

####################
# Check for libraries
SETUP_CONFIG_HEADER
SETUP_PAT
AC_CONFIG_HEADER(include/bold/Config/Config.h)
AC_CONFIG_HEADER(include/bold/Support/DataTypes.h)

####################
# Check for types
AC_CHECK_TYPES([int8_t, int16_t, int32_t, int64_t, intptr_t])
AC_CHECK_TYPES([uint8_t, uint16_t, uint32_t, uint64_t, uintptr_t])
AC_CHECK_TYPES([long double, long long, long long int, unsigned long long int])
AC_CHECK_TYPES([off_t, size_t, ssize_t])
AC_TYPE_LONG_DOUBLE_WIDER

####################
# Check for options
CHECK_PTHREAD
CHECK_ZLIB
CHECK_ENABLE_UNITTEST
CHECK_ENABLE_OPTIMIZE

DX_INIT_DOXYGEN([bold], [doxygen.cfg], [docs])
DX_DOT_FEATURE(OFF)
DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(OFF)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(OFF)
DX_PS_FEATURE(OFF)

####################
# OUTPUT
AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([include/Makefile])
AC_CONFIG_FILES([lib/Makefile])
AC_CONFIG_FILES([tools/Makefile])
AC_CONFIG_FILES([tools/bold/Makefile])
AC_CONFIG_FILES([utils/Makefile])
AC_CONFIG_FILES([utils/pat/Makefile])
AC_CONFIG_FILES([utils/pat/lib/Makefile])

AC_OUTPUT

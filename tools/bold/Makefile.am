
SKY_SOURCES = main.cpp

SKY_INCLUDES = -I${abs_top_srcdir}/include \
               -I${abs_top_builddir}/include

ANDROID_CPPFLAGS=-fno-rtti -fno-exceptions -Waddress -Wchar-subscripts -Wcomment -Wformat -Wparentheses -Wreorder -Wreturn-type -Wsequence-point -Wstrict-aliasing -Wstrict-overflow=1 -Wswitch -Wtrigraphs -Wuninitialized -Wunknown-pragmas -Wunused-function -Wunused-label -Wunused-value -Wunused-variable -Wvolatile-register-var

if ENABLE_OPTIMIZE
SKY_CPPFLAGS = -O2 -DTOPDIR=\"${abs_top_srcdir}\"
else
SKY_CPPFLAGS = -g -DTOPDIR=\"${abs_top_srcdir}\"
endif

SKYLDFLAGS = -L$(abs_top_builddir)/lib

if ENABLE_UNITTEST
UNITTEST=${abs_top_srcdir}/unittests

SKY_INCLUDES += -I${UNITTEST}

SKY_CPPFLAGS += -DENABLE_UNITTEST -DTOPDIR=\"${abs_top_srcdir}\" ${SKYTEST_CPPFLAGS}

SKYLDFLAGS += ${SKYTEST_LDFLAGS}
endif


if ENABLE_WERROR
SKY_CPPFLAGS += -Werror
endif

AM_CPPFLAGS = ${SKY_INCLUDES} ${SKY_CPPFLAGS} ${ANDROID_CPPFLAGS}

bolddir = $(pkgdatadir)/tools

bold_PROGRAMS = bold

bold_LDFLAGS = ${SKYLDFLAGS}

bold_LDADD = -lbold

dist_bold_SOURCES = ${SKY_SOURCES}


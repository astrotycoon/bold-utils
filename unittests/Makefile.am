BOLD_SOURCES = main.cpp

BOLD_INCLUDES = -I${abs_top_srcdir}/include \
               -I${abs_top_builddir}/include

ANDROID_CPPFLAGS=-fno-rtti -fno-exceptions -Waddress -Wchar-subscripts -Wcomment -Wformat -Wparentheses -Wreorder -Wreturn-type -Wsequence-point -Wstrict-aliasing -Wstrict-overflow=1 -Wswitch -Wtrigraphs -Wuninitialized -Wunknown-pragmas -Wunused-function -Wunused-label -Wunused-value -Wunused-variable -Wvolatile-register-var

if ENABLE_OPTIMIZE
BOLD_CPPFLAGS = -O2 -DTOPDIR=\"${abs_top_srcdir}\"
else
BOLD_CPPFLAGS = -g -DTOPDIR=\"${abs_top_srcdir}\"
endif

BOLDLDFLAGS = -L$(abs_top_builddir)/lib

if ENABLE_UNITTEST
UNITTEST=${abs_top_srcdir}/unittests

BOLD_SOURCES += AllocatorsTest.cpp \
	FourpleTest.cpp \
	IListTest.cpp \
	MemoryPoolTest.cpp \
	OStrStreamTest.cpp \
	OwningPtrTest.cpp \
	OFStreamTest.cpp \
	PathTest.cpp \
	RopeTest.cpp \
	StringRefTest.cpp \
	StringSwitchTest.cpp

BOLD_INCLUDES += -I${UNITTEST}

BOLD_CPPFLAGS += -DENABLE_UNITTEST -DTOPDIR=\"${abs_top_srcdir}\" ${PAT_CPPFLAGS}

BOLDLDFLAGS += ${PAT_LDFLAGS}
endif


if ENABLE_WERROR
BOLD_CPPFLAGS += -Werror
endif

AM_CPPFLAGS = ${BOLD_INCLUDES} ${BOLD_CPPFLAGS} ${ANDROID_CPPFLAGS}

bolddir = $(pkgdatadir)/tools

bold_PROGRAMS = unittest

unittest_LDFLAGS = ${BOLDLDFLAGS}

unittest_LDADD = -lbold

dist_unittest_SOURCES = ${BOLD_SOURCES}


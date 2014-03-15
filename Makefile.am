ACLOCAL_AMFLAGS=-I m4

AUTOMAKE_OPTIONS = foreign

if ENABLE_UNITTEST
SUBDIRS = utils lib tools unittests
else
SUBDIRS = utils lib tools
endif

include docs/doxygen.am

EXTRA_DIST = ./autogen.sh $(DX_CONFIG) docs/html

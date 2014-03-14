# Automake file
ACLOCAL_AMFLAGS = -I m4

# We define the global AM_CPPFLAGS as everything we compile includes from these
# directories.
AM_CPPFLAGS = -I$(srcdir)/../include/

SOURCES = pat.cpp \
	ADT/Color.cpp \
	Support/ManagedStatic.cpp \
	Support/Timer.cpp \
	Listeners/PrettyResultPrinter.cpp \
	Core/Test.cpp

# Build rules for libraries.
noinst_LTLIBRARIES = ../lib/libpat.la

___lib_libpat_la_SOURCES = $(SOURCES)

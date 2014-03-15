SOURCE = pat.cpp \
	ADT/Color.cpp \
	Support/ManagedStatic.cpp \
	Support/Timer.cpp \
	Listeners/PrettyResultPrinter.cpp \
	Core/Test.cpp

ANDROID_CPPFLAGS=-fno-rtti -fno-exceptions -Waddress -Wchar-subscripts -Wcomment -Wformat -Wparentheses -Wreorder -Wreturn-type -Wsequence-point -Wstrict-aliasing -Wstrict-overflow=1 -Wswitch -Wtrigraphs -Wuninitialized -Wunknown-pragmas -Wunused-function -Wunused-label -Wunused-value -Wunused-variable -Wvolatile-register-var

PAT_INCLUDES = -I${srcdir}/../include

if ENABLE_OPTIMIZE
PAT_CPPFLAGS += -O2
else
PAT_CPPFLAGS += -g
endif

PAT_CPPFLAGS += -fvisibility=hidden

AM_CPPFLAGS = ${PAT_INCLUDES} ${PAT_CPPFLAGS} ${ANDROID_CPPFLAGS}

#############################
# Build rules for libraries.
noinst_LTLIBRARIES = ../lib/libpat.la

___lib_libpat_la_SOURCES = ${SOURCE}

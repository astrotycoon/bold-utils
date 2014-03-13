INCDIR=../include/bold

SOURCE = ADT/IList.cpp \
	ADT/IListIterator.cpp \
	ADT/Rope.cpp \
	ADT/StringRef.cpp \
	ADT/StringList.cpp \
	Config/GeneralOptions.cpp \
	Config/SkySettings.cpp \
	Language/Compiler.cpp \
	Language/CompilerConfig.cpp \
	Language/Fourple.cpp \
	Language/Tool.cpp \
	Language/ToolConfig.cpp \
	Support/Diagnostic.cpp \
	Support/DiagnosticEngine.cpp \
	Support/DiagnosticInfoMap.cpp \
	Support/DiagnosticPrinter.cpp \
	Support/DiagnosticPolicy.cpp \
	Support/IOStream.cpp \
	Support/ManagedStatic.cpp \
	Support/MsgHandler.cpp \
	Support/MsgHandling.cpp \
	Support/Path.cpp \
	Support/FileSystem.cpp \
	Support/TextDiagnosticPrinter.cpp \
	Support/Unix/Path.inc \
	Support/Unix/FileSystem.inc \
	Support/Windows/Path.inc \
	Support/Windows/FileSystem.inc \
	Support/Dragon/Path.inc \
	Support/Dragon/FileSystem.inc \
	Thread/Thread.cpp \
	Option/Combo.cpp \
	Option/EnumOption.cpp \
	Option/FlagOption.cpp \
	Option/Option.cpp \
	Option/OptionPool.cpp \
	Option/RangeOption.cpp


ANDROID_CPPFLAGS=-fno-rtti -fno-exceptions -Waddress -Wchar-subscripts -Wcomment -Wformat -Wparentheses -Wreorder -Wreturn-type -Wsequence-point -Wstrict-aliasing -Wstrict-overflow=1 -Wswitch -Wtrigraphs -Wuninitialized -Wunknown-pragmas -Wunused-function -Wunused-label -Wunused-value -Wunused-variable -Wvolatile-register-var

BOLD_INCLUDES = -I${abs_top_srcdir}/include -I${abs_top_builddir}/include

if ENABLE_OPTIMIZE
BOLD_CPPFLAGS = -O2
else
BOLD_CPPFLAGS = -g
endif

AM_CPPFLAGS = ${BOLD_INCLUDES} ${BOLD_CPPFLAGS} ${ANDROID_CPPFLAGS}

#####################################
# Build shared libraries
lib_LTLIBRARIES = libbold.la

libbold_la_SOURCES = ${SOURCE}

libbold_la_LDFLAGS = -version-info @BOLD_VERSION@


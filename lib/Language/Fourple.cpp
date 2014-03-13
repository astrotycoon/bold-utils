//===- Fourple.cpp --------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include <bold/Language/Fourple.h>
#include <bold/ADT/Rope.h>
#include <bold/ADT/StringSwitch.h>

using namespace bold;

//===----------------------------------------------------------------------===//
// Non-member functions
//===----------------------------------------------------------------------===//
static Fourple::ArchType parseArch(StringRef pArchName)
{
  return StringSwitch<Fourple::ArchType>(pArchName)
    .Cases("i386", "i486", "i586", "i686", Fourple::x86)
    // FIXME: Do we need to support these?
    .Case("x32", Fourple::x32)
    .Cases("i786", "i886", "i986", Fourple::x86)
    .Cases("amd64", "x86_64", Fourple::x86_64)
    .Case("powerpc", Fourple::ppc)
    .Cases("powerpc64", "ppu", Fourple::ppc64)
    .Case("mblaze", Fourple::mblaze)
    .Case("aarch64", Fourple::aarch64)
    .Cases("arm", "xscale", Fourple::arm)
    // FIXME: It would be good to replace these with explicit names for all the
    // various suffixes supported.
    .StartsWith("armv", Fourple::arm)
    .Case("thumb", Fourple::thumb)
    .StartsWith("thumbv", Fourple::thumb)
    .Case("msp430", Fourple::msp430)
    .Cases("mips", "mipseb", "mipsallegrex", Fourple::mips)
    .Cases("mipsel", "mipsallegrexel", Fourple::mipsel)
    .Cases("mips64", "mips64eb", Fourple::mips64)
    .Case("mips64el", Fourple::mips64el)
    .Case("r600", Fourple::r600)
    .Case("hexagon", Fourple::hexagon)
    .Case("s390x", Fourple::systemz)
    .Case("sparc", Fourple::sparc)
    .Case("sparcv9", Fourple::sparcv9)
    .Case("tce", Fourple::tce)
    .Case("xcore", Fourple::xcore)
    .Case("nvptx", Fourple::nvptx)
    .Case("nvptx64", Fourple::nvptx64)
    .Case("le32", Fourple::le32)
    .Case("amdil", Fourple::amdil)
    .Case("spir", Fourple::spir)
    .Case("spir64", Fourple::spir64)
    .Default(Fourple::UnknownArch);
}

static Fourple::ArchVendorType parseArchVendor(StringRef pArchVendorName) {
  return StringSwitch<Fourple::ArchVendorType>(pArchVendorName)
    .Case("apple", Fourple::Apple)
    .Case("pc", Fourple::PC)
    .Case("scei", Fourple::SCEI)
    .Case("bgp", Fourple::BGP)
    .Case("bgq", Fourple::BGQ)
    .Case("fsl", Fourple::Freescale)
    .Case("ibm", Fourple::IBM)
    .Default(Fourple::UnknownArchVendor);
}

static Fourple::OSType parseOS(StringRef pOSName) {
  return StringSwitch<Fourple::OSType>(pOSName)
    .StartsWith("auroraux", Fourple::AuroraUX)
    .StartsWith("cygwin", Fourple::Cygwin)
    .StartsWith("darwin", Fourple::Darwin)
    .StartsWith("dragonfly", Fourple::DragonFly)
    .StartsWith("freebsd", Fourple::FreeBSD)
    .StartsWith("ios", Fourple::IOS)
    .StartsWith("kfreebsd", Fourple::KFreeBSD)
    .StartsWith("linux", Fourple::Linux)
    .StartsWith("lv2", Fourple::Lv2)
    .StartsWith("macosx", Fourple::MacOSX)
    .StartsWith("mingw32", Fourple::MinGW32)
    .StartsWith("netbsd", Fourple::NetBSD)
    .StartsWith("openbsd", Fourple::OpenBSD)
    .StartsWith("solaris", Fourple::Solaris)
    .StartsWith("win32", Fourple::Win32)
    .StartsWith("haiku", Fourple::Haiku)
    .StartsWith("minix", Fourple::Minix)
    .StartsWith("rtems", Fourple::RTEMS)
    .StartsWith("nacl", Fourple::NaCl)
    .StartsWith("cnk", Fourple::CNK)
    .StartsWith("bitrig", Fourple::Bitrig)
    .StartsWith("aix", Fourple::AIX)
    .Default(Fourple::UnknownOS);
}

static Fourple::EnvironmentType
parseEnvironment(StringRef pEnvironmentName) {
  return StringSwitch<Fourple::EnvironmentType>(pEnvironmentName)
    .StartsWith("eabi", Fourple::EABI)
    .StartsWith("gnueabihf", Fourple::GNUEABIHF)
    .StartsWith("gnueabi", Fourple::GNUEABI)
    .StartsWith("gnux32", Fourple::GNUX32)
    .StartsWith("gnu", Fourple::GNU)
    .StartsWith("macho", Fourple::MachO)
    .StartsWith("android", Fourple::Android)
    .StartsWith("elf", Fourple::ELF)
    .Default(Fourple::UnknownEnvironment);
}

static Fourple::ToolType parseTool(StringRef pToolName) {
  return StringSwitch<Fourple::ToolType>(pToolName)
    .Case("ar", Fourple::AR)
    .Cases("as", "gas", Fourple::AS)
    .Cases("cc", "gcc", "clang", Fourple::CC)
    .Case("cpp", Fourple::CPP)
    .Cases("clang++", "c++", "g++", Fourple::CXX)
    .Case("elfedit", Fourple::ELFEDIT)
    .Cases("ld.bfd", "ld.gold", "ld.mcld", "ld", Fourple::LD)
    .Case("ranlib", Fourple::RANLIB)
    .Case("strip", Fourple::STRIP)
    .Default(Fourple::UnknownTool);
}

static Fourple::ToolVendorType parseToolVendor(StringRef pToolVendorName)
{
  return StringSwitch<Fourple::ToolVendorType>(pToolVendorName)
    .StartsWith("fsf", "gnu", Fourple::FSF)
    .StartsWith("llvm", Fourple::LLVM)
    .StartsWith("linaro", Fourple::Linaro)
    .StartsWith("bold", Fourple::Skymizer)
    .StartsWith("sourcery", Fourple::Sourcery)
    .StartsWith("apple", "xcode", Fourple::XCode)
    .Default(Fourple::UnknownToolVendor);
}

static unsigned getArchBitWidth(Fourple::ArchType pArch)
{
  switch (pArch) {
  case Fourple::UnknownArch:
    return 0;

  case Fourple::msp430:
    return 16;

  case Fourple::amdil:
  case Fourple::arm:
  case Fourple::hexagon:
  case Fourple::le32:
  case Fourple::mblaze:
  case Fourple::mips:
  case Fourple::mipsel:
  case Fourple::nvptx:
  case Fourple::ppc:
  case Fourple::r600:
  case Fourple::sparc:
  case Fourple::tce:
  case Fourple::thumb:
  case Fourple::x86:
  case Fourple::xcore:
  case Fourple::spir:
    return 32;

  case Fourple::aarch64:
  case Fourple::mips64:
  case Fourple::mips64el:
  case Fourple::nvptx64:
  case Fourple::ppc64:
  case Fourple::sparcv9:
  case Fourple::systemz:
  case Fourple::x32:
  case Fourple::x86_64:
  case Fourple::spir64:
    return 64;
  }
  // FIXME: use unreachable
}
static unsigned getPointerBitWidth(Fourple::ArchType pArch)
{
  switch (pArch) {
  case Fourple::UnknownArch:
    return 0;

  case Fourple::msp430:
    return 16;

  case Fourple::amdil:
  case Fourple::arm:
  case Fourple::hexagon:
  case Fourple::le32:
  case Fourple::mblaze:
  case Fourple::mips:
  case Fourple::mipsel:
  case Fourple::nvptx:
  case Fourple::ppc:
  case Fourple::r600:
  case Fourple::sparc:
  case Fourple::tce:
  case Fourple::thumb:
  case Fourple::x32:
  case Fourple::x86:
  case Fourple::xcore:
  case Fourple::spir:
    return 32;

  case Fourple::aarch64:
  case Fourple::mips64:
  case Fourple::mips64el:
  case Fourple::nvptx64:
  case Fourple::ppc64:
  case Fourple::sparcv9:
  case Fourple::systemz:
  case Fourple::x86_64:
  case Fourple::spir64:
    return 64;
  }
  // FIXME: use unreachable
}

//===----------------------------------------------------------------------===//
// Fourple
//===----------------------------------------------------------------------===//
/// Constructor
Fourple::Fourple()
  : m_Data(), m_Arch(), m_ArchVendor(), m_OS(), m_Environment(),
    m_Tool(), m_ToolVersion(), m_ToolVendor() {
}

/// Constructor
Fourple::Fourple(const std::string& pStr)
  : m_Data(pStr),
    m_Arch(parseArch(getArchName())),
    m_ArchVendor(parseArchVendor(getArchVendorName())),
    m_OS(parseOS(getOSName())),
    m_Environment(parseEnvironment(getEnvironmentName())),
    m_Tool(parseTool(getToolName())),
    m_ToolVersion(getToolVersionName()),
    m_ToolVendor(parseToolVendor(getToolVendorName())) {
}

/// Constructor
Fourple::Fourple(StringRef pArchStr,
                 StringRef pArchVendorStr,
                 StringRef pOSStr)
  : m_Data((pArchStr + Rope('-') + pArchVendorStr + Rope('-') + pOSStr).str()),
    m_Arch(parseArch(pArchStr)),
    m_ArchVendor(parseArchVendor(pArchVendorStr)),
    m_OS(parseOS(pOSStr)),
    m_Environment(),
    m_Tool(),
    m_ToolVersion(),
    m_ToolVendor() {
}

/// Constructor
Fourple::Fourple(StringRef pArchStr,
                 StringRef pArchVendorStr,
                 StringRef pOSStr,
                 StringRef pEnvironmentStr)
  : m_Data((pArchStr + Rope('-') + pArchVendorStr + Rope('-') + pOSStr +
            Rope('-') + pEnvironmentStr).str()),
    m_Arch(parseArch(pArchStr)),
    m_ArchVendor(parseArchVendor(pArchVendorStr)),
    m_OS(parseOS(pOSStr)),
    m_Environment(parseEnvironment(pEnvironmentStr)),
    m_Tool(),
    m_ToolVersion(),
    m_ToolVendor() {
}

/// Constructor
Fourple::Fourple(StringRef pArchStr,
                 StringRef pArchVendorStr,
                 StringRef pOSStr,
                 StringRef pEnvironmentStr,
                 StringRef pToolStr)
  : m_Data((pArchStr + Rope('-') + pArchVendorStr + Rope('-') + pOSStr +
            Rope('-') + pEnvironmentStr + Rope('-') + pToolStr).str()),
    m_Arch(parseArch(pArchStr)),
    m_ArchVendor(parseArchVendor(pArchVendorStr)),
    m_OS(parseOS(pOSStr)),
    m_Environment(parseEnvironment(pEnvironmentStr)),
    m_Tool(parseTool(pToolStr)),
    m_ToolVersion(),
    m_ToolVendor() {
}

/// Constructor
Fourple::Fourple(StringRef pArchStr,
                 StringRef pArchVendorStr,
                 StringRef pOSStr,
                 StringRef pEnvironmentStr,
                 StringRef pToolStr,
                 StringRef pToolVersionStr)
  : m_Data((pArchStr + Rope('-') + pArchVendorStr + Rope('-') + pOSStr +
            Rope('-') + pEnvironmentStr + Rope('-') + pToolStr + Rope('-') +
            pToolVersionStr).str()),
    m_Arch(parseArch(pArchStr)),
    m_ArchVendor(parseArchVendor(pArchVendorStr)),
    m_OS(parseOS(pOSStr)),
    m_Environment(parseEnvironment(pEnvironmentStr)),
    m_Tool(parseTool(pToolStr)),
    m_ToolVersion(pToolVersionStr),
    m_ToolVendor() {
}

/// Constructor
Fourple::Fourple(StringRef pArchStr,
                 StringRef pArchVendorStr,
                 StringRef pOSStr,
                 StringRef pEnvironmentStr,
                 StringRef pToolStr,
                 StringRef pToolVersionStr,
                 StringRef pToolVendorStr)
  : m_Data((pArchStr + Rope('-') + pArchVendorStr + Rope('-') + pOSStr +
            Rope('-') + pEnvironmentStr + Rope('-') + pToolStr + Rope('-') +
            pToolVersionStr + Rope('-') + pToolVendorStr).str()),
    m_Arch(parseArch(pArchStr)),
    m_ArchVendor(parseArchVendor(pArchVendorStr)),
    m_OS(parseOS(pOSStr)),
    m_Environment(parseEnvironment(pEnvironmentStr)),
    m_Tool(parseTool(pToolStr)),
    m_ToolVersion(pToolVersionStr),
    m_ToolVendor(parseToolVendor(pToolVendorStr)) {
}

/// getArchName - Get the architecture (first) component of the fourple.
StringRef Fourple::getArchName() const
{
  return getArchName(StringRef(m_Data));
}

/// getArchVendorName - Get the architecture vendor (second) component of the
/// fourple.
StringRef Fourple::getArchVendorName() const
{
  StringRef tmp = StringRef(m_Data).split('-').second; // strip 1st component
  return tmp.split('-').first;                         // isolate 2nd component
}

/// getOSName - Get the os (thrid) component of the fourple.
StringRef Fourple::getOSName() const
{
  StringRef tmp = StringRef(m_Data).split('-').second; // strip 1st component
  tmp = tmp.split('-').second;                         // strip 2nd component
  return tmp.split('-').first;                         // isolate 3th component
}

/// getEnvironmentName - Get the environment (ABI) componenet of the fourple.
StringRef Fourple::getEnvironmentName() const
{
  StringRef tmp = StringRef(m_Data).split('-').second; // strip 1st component
  tmp = tmp.split('-').second;                         // strip 2nd component
  return tmp.split('-').second;                        // strip 3th component
}

/// getToolName - Get the tool componenet of the fourple.
StringRef Fourple::getToolName() const
{
  StringRef tmp = StringRef(m_Data).split('-').second; // strip 1st component
  tmp = tmp.split('-').second;                         // strip 2nd component
  tmp = tmp.split('-').second;                         // strip 3th component
  tmp = tmp.split('-').second;                         // strip 4th component
  return tmp.split('-').first;                         // isolate 5th component
}

/// getToolVersionName - Get the tool version componenet of the fourple.
StringRef Fourple::getToolVersionName() const
{
  StringRef tmp = StringRef(m_Data).split('-').second; // strip 1st component
  tmp = tmp.split('-').second;                         // strip 2nd component
  tmp = tmp.split('-').second;                         // strip 3th component
  tmp = tmp.split('-').second;                         // strip 4th component
  tmp = tmp.split('-').second;                         // strip 5th component
  return tmp.split('-').first;                         // isolate 6th component
}

/// getToolVendorName - Get the tool vendor component of the fourple.
StringRef Fourple::getToolVendorName() const
{
  StringRef tmp = StringRef(m_Data).split('-').second; // strip 1st component
  tmp = tmp.split('-').second;                         // strip 2nd component
  tmp = tmp.split('-').second;                         // strip 3th component
  tmp = tmp.split('-').second;                         // strip 4th component
  tmp = tmp.split('-').second;                         // strip 5th component
  return tmp.split('-').second;                        // strip 6th component
}

/// Test whether the data-path width is 64-bit
bool Fourple::isArch64Bit() const
{
  return (64 == getArchBitWidth(getArch()));
}

/// Test whether the data-path width is 32-bit
bool Fourple::isArch32Bit() const
{
  return (32 == getArchBitWidth(getArch()));
}

/// Test whether the data-path width is 16-bit
bool Fourple::isArch16Bit() const
{
  return (16 == getArchBitWidth(getArch()));
}

/// \brief Test whether the pointer width is 64-bit
/// Note that some 64-bit architecture remains 32-bit pointer width, for
/// example, Intel X32 is 64-bit architecture, but its pointer is 32-bit.
bool Fourple::isPointer64Bit() const
{
  return (64 == getPointerBitWidth(getArch()));
}

/// Test for 32-bit pointer width
bool Fourple::isPointer32Bit() const
{
  return (32 == getPointerBitWidth(getArch()));
}

/// Test for 16-bit pointer width
bool Fourple::isPointer16Bit() const
{
  return (16 == getPointerBitWidth(getArch()));
}

//===----------------------------------------------------------------------===//
// Static Member Functions
//===----------------------------------------------------------------------===//
const char* Fourple::getArchTypeName(ArchType pType)
{
  switch(pType) {
    case UnknownArch: return "unknown";

    case arm:         return "arm";
    case aarch64:     return "aarch64";
    case hexagon:     return "hexagon";
    case mips:        return "mips";
    case mipsel:      return "mipsel";
    case mips64:      return "mips64";
    case mips64el:    return "mips64el";
    case msp430:      return "msp430";
    case ppc:         return "ppc";
    case ppc64:       return "ppc64";
    case r600:        return "r600";
    case sparc:       return "sparc";
    case sparcv9:     return "sparcv9";
    case systemz:     return "systemz";
    case tce:         return "tce";
    case thumb:       return "thumb";
    case x32:         return "x32";
    case x86:         return "x86";
    case x86_64:      return "x86_64";
    case xcore:       return "xcore";
    case mblaze:      return "mblaze";
    case nvptx:       return "nvptx";
    case nvptx64:     return "nvptx64";
    case le32:        return "le32";
    case amdil:       return "amdil";
    case spir:        return "spir";
    case spir64:      return "spir64";
  }
  // FIXME: add unreachable here
  assert(false && "Unreachable!");
  return NULL;
}

const char* Fourple::getArchVendorTypeName(ArchVendorType pType)
{
  switch (pType) {
    case UnknownArchVendor: return "unknown";

    case Apple:             return "apple";
    case PC:                return "pc";
    case SCEI:              return "scei";
    case BGP:               return "bgp";
    case BGQ:               return "bgq";
    case Freescale:         return "freescale";
    case IBM:               return "ibm";
  }

  // FIXME: add unreachable here
  assert(false && "Unreachable!");
  return NULL;
}

const char* Fourple::getOSTypeName(OSType pType)
{
  switch (pType) {
    case UnknownOS: return "unknown";

    case AuroraUX:  return "auroraux";
    case Cygwin:    return "cygwin";
    case Darwin:    return "darwin";
    case DragonFly: return "dragonfly";
    case FreeBSD:   return "freebsd";
    case IOS:       return "ios";
    case KFreeBSD:  return "kfreebsd";
    case Linux:     return "linux";
    case Lv2:       return "lv2";
    case MacOSX:    return "macosx";
    case MinGW32:   return "mingw32";
    case NetBSD:    return "netbsd";
    case OpenBSD:   return "openbsd";
    case Solaris:   return "solaris";
    case Win32:     return "win32";
    case Haiku:     return "haiku";
    case Minix:     return "minix";
    case RTEMS:     return "rtems";
    case NaCl:      return "nacl";
    case CNK:       return "cnk";
    case Bitrig:    return "bitrig";
    case AIX:       return "aix";
  }

  // FIXME: add unreachable here
  assert(false && "Unreachable!");
  return NULL;
}

const char* Fourple::getEnvironmentTypeName(EnvironmentType pType)
{
  switch (pType) {
    case UnknownEnvironment: return "unknown";

    case GNU:                return "gnu";
    case GNUEABI:            return "gnueabi";
    case GNUEABIHF:          return "gnueabihf";
    case GNUX32:             return "gnux32";
    case EABI:               return "eabi";
    case MachO:              return "macho";
    case Android:            return "android";
    case ELF:                return "elf";
  }

  // FIXME: add unreachable here
  assert(false && "Unreachable!");
  return NULL;
}

const char* Fourple::getToolTypeName(ToolType pType)
{
  switch(pType) {
    case UnknownTool: return "none";

    case AR:          return "ar";
    case AS:          return "as";
    case CC:          return "cc";
    case CPP:         return "cpp";
    case CXX:         return "cxx";
    case ELFEDIT:     return "elfedit";
    case LD:          return "ld";
    case RANLIB:      return "ranlib";
    case STRIP:       return "strip";
  }

  // FIXME: add unreachable here
  assert(false && "Unreachable!");
  return NULL;
}

const char* Fourple::getToolVendorTypeName(ToolVendorType pType)
{
  switch(pType) {
    case UnknownToolVendor: return "unknown";

    case FSF:               return "fsf";
    case LLVM:              return "llvm";
    case Linaro:            return "linaro";
    case Skymizer:          return "bold";
    case Sourcery:          return "sourcery";
    case XCode:             return "xcode";
  }

  // FIXME: add unreachable here
  assert(false && "Unreachable!");
  return NULL;
}

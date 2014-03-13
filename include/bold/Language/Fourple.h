//===- Fourple.h ----------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_LANGUAGE_FOURPLE_H
#define BOLD_LANGUAGE_FOURPLE_H
#include <string>
#include <bold/ADT/StringRef.h>

namespace bold {

class Rope;

/** \class Fourple
 *  \brief Fourple is a helper class for working with targets and toolchain.
 *
 *  Target fourples are strings in the canonical forms:
 *    ARCH-ARCH_VENDOR-OS-ENVIRON-TOOL-TOOL_VERSION-TOOL_VENDOR
 *
 *  Among the components, TOOL_VENDOR, ARCH_VENDOR and TOOL_VERSION are optional.
 *  That means, they may not exist in a fourple. If a fourple does not have
 *  TOOL, then it is reduced to a target triple.
 *
 *  Fourple is an extension of LLVM llvm::Triple class. It contains additional
 *  tool and version information.
 */
class Fourple
{
public:
  enum ArchType {
    UnknownArch,

    aarch64, // AArch64: aarch64
    arm,     // ARM: arm, armv.*, xscale
    hexagon, // Hexagon: hexagon
    mips,    // MIPS: mips, mipsallegrex
    mipsel,  // MIPSEL: mipsel, mipsallegrexel
    mips64,  // MIPS64: mips64
    mips64el,// MIPS64EL: mips64el
    msp430,  // MSP430: msp430
    ppc,     // PPC: powerpc
    ppc64,   // PPC64: powerpc64, ppu
    r600,    // R600: AMD GPUs HD2XXX - HD6XXX
    sparc,   // Sparc: sparc
    sparcv9, // Sparcv9: Sparcv9
    systemz, // SystemZ: s390x
    tce,     // TCE (http://tce.cs.tut.fi/): tce
    thumb,   // Thumb: thumb, thumbv.*
    x32,     // Intel X32
    x86,     // X86: i[3-9]86
    x86_64,  // X86-64: amd64, x86_64
    xcore,   // XCore: xcore
    mblaze,  // MBlaze: mblaze
    nvptx,   // NVPTX: 32-bit
    nvptx64, // NVPTX: 64-bit
    le32,    // le32: generic little-endian 32-bit CPU (PNaCl / Emscripten)
    amdil,   // amdil: amd IL
    spir,    // SPIR: standard portable IR for OpenCL 32-bit version
    spir64   // SPIR: standard portable IR for OpenCL 64-bit version
  };

  enum ArchVendorType {
    UnknownArchVendor,

    Apple,
    PC,
    SCEI,
    BGP,
    BGQ,
    Freescale,
    IBM
  };

  enum OSType {
    UnknownOS,

    AuroraUX,
    Cygwin,
    Darwin,
    DragonFly,
    FreeBSD,
    IOS,
    KFreeBSD,
    Linux,
    Lv2,        // PS3
    MacOSX,
    MinGW32,    // i*86-pc-mingw32, *-w64-mingw32
    NetBSD,
    OpenBSD,
    Solaris,
    Win32,
    Haiku,
    Minix,
    RTEMS,
    NaCl,       // Native Client
    CNK,        // BG/P Compute-Node Kernel
    Bitrig,
    AIX
  };

  enum EnvironmentType {
    UnknownEnvironment,

    GNU,
    GNUEABI,
    GNUEABIHF,
    GNUX32,
    EABI,
    MachO,
    Android,
    ELF
  };

  enum ToolType {
    UnknownTool,

    AR,
    AS,
    CC,
    CPP,
    CXX,
    ELFEDIT,
    LD,
    RANLIB,
    STRIP
  };

  enum ToolVendorType {
    UnknownToolVendor,

    FSF,       // Free Software Foundation
    LLVM,      // LLVM open source
    Linaro,    // Linaro
    Skymizer,  // Skymizer
    Sourcery,  // Code Sourcery
    XCode      // XCode
  };

public:
  /// @name Constructors
  /// @{
  Fourple();

  explicit Fourple(const std::string& pStr);

  Fourple(StringRef pArchStr,
          StringRef pArchVendorStr,
          StringRef pOSStr);

  Fourple(StringRef pArchStr,
          StringRef pArchVendorStr,
          StringRef pOSStr,
          StringRef pEnvironmentStr);

  Fourple(StringRef pArchStr,
          StringRef pArchVendorStr,
          StringRef pOSStr,
          StringRef pEnvironmentStr,
          StringRef pToolStr);

  Fourple(StringRef pArchStr,
          StringRef pArchVendorStr,
          StringRef pOSStr,
          StringRef pEnvironmentStr,
          StringRef pToolStr,
          StringRef pToolVersionStr);

  Fourple(StringRef pArchStr,
          StringRef pArchVendorStr,
          StringRef pOSStr,
          StringRef pEnvironStr,
          StringRef pToolStr,
          StringRef pToolVersionStr,
          StringRef pToolVendorStr);

  /// @}
  /// @name Typed Component Access
  /// @{

  /// getArch - Get the parsed architecture type of this fourple.
  ArchType getArch() const { return m_Arch; }

  /// getArchVendor - Get the parsed architecture vendor type of this fourple.
  ArchVendorType getArchVendor() const { return m_ArchVendor; }

  /// getOS - Get the parsed operating system type of this fourple.
  OSType getOS() const { return m_OS; }

  /// getEnvironment - Get the parsed environment type of this fourple.
  EnvironmentType getEnvironment() const { return m_Environment; }

  /// getTool - Get the parsed tool type of this fourple.
  ToolType getTool() const { return m_Tool; }

  /// getToolVersion - Get the tool version string
  StringRef getToolVersion() const { return m_ToolVersion; }

  /// getToolVendor - Get the parsed tool vendor of this fourple
  ToolVendorType getToolVendor() const { return m_ToolVendor; }

  /// @}
  /// @name Typed Component Name Access
  /// @{
  /// getArchName - Get the architecture (first) component of the fourple.
  StringRef getArchName() const;

  /// getArchVendorName - Get the architecture vendor (second) component of the
  /// fourple.
  StringRef getArchVendorName() const;

  /// getOSName - Get the os (thrid) component of the fourple.
  StringRef getOSName() const;

  /// getEnvironmentName - Get the environment (ABI) componenet of the fourple.
  StringRef getEnvironmentName() const;

  /// getToolName - Get the tool componenet of the fourple.
  StringRef getToolName() const;

  /// getToolVersionName - Get the tool version component of the fourple.
  StringRef getToolVersionName() const;

  /// getToolVendorName - Get the tool vendor component of the fourple.
  StringRef getToolVendorName() const;

  /// @}
  /// @name Convenience Predicates
  /// @{

  /// Test whether the data-path width is 64-bit
  bool isArch64Bit() const;

  /// Test whether the data-path width is 32-bit
  bool isArch32Bit() const;

  /// Test whether the data-path width is 16-bit
  bool isArch16Bit() const;

  /// \brief Test whether the pointer width is 64-bit
  /// Note that some 64-bit architecture remains 32-bit pointer width, for
  /// example, Intel X32 is 64-bit architecture, but its pointer is 32-bit.
  bool isPointer64Bit() const;

  /// Test for 32-bit pointer width
  bool isPointer32Bit() const;

  /// Test for 16-bit pointer width
  bool isPointer16Bit() const;

  /// @}
  /// @name Static Helpers for IDs.
  /// @{
  static const char* getArchTypeName(ArchType pType);

  static const char* getArchVendorTypeName(ArchVendorType pType);

  static const char* getOSTypeName(OSType pType);

  static const char* getEnvironmentTypeName(EnvironmentType pType);

  static const char* getToolTypeName(ToolType pType);

  static const char* getToolVendorTypeName(ToolVendorType pType);

  /// @}

private:
  StringRef getArchName(StringRef pData) const;

private:
  /// The wrapped string
  std::string m_Data;

  /// The parsed arch type.
  ArchType m_Arch;

  /// The parsed vendor type.
  ArchVendorType m_ArchVendor;

  /// The parsed OS type.
  OSType m_OS;

  /// The parsed environment type.
  EnvironmentType m_Environment;

  /// The parsed tool type.
  ToolType m_Tool;

  /// The parsed version
  StringRef m_ToolVersion;

  /// The parsed tool vendor type.
  ToolVendorType m_ToolVendor;
};

//===----------------------------------------------------------------------===//
// Inline member functions
//===----------------------------------------------------------------------===//
/// getArchName - Get the architecture (first) component of the fourple.
inline StringRef Fourple::getArchName(StringRef pData) const
{
  return pData.split('-').first;
}

} // namespace of bold

#endif


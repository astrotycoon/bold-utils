//===- Tool.h -------------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_LANGUAGE_TOOLCHAIN_REGISTRY_H
#define BOLD_LANGUAGE_TOOLCHAIN_REGISTRY_H
#include <bold/Language/Toolchain.h>

#include <string>

namespace bold {

/** \class ToolchainRegistry
 *  \brief ToolchainRegistry is used for getting the appropriate toolchain by
 *  target fourple.
 */
class ToolchainRegistry {
public:
  /// RegisterToolchain - Register the given toolchain. Attempts to register a
  /// toolchain which has already been registered will be ignored.
  ///
  /// Clients are responsible for ensuring that registration doesn't occur
  /// while another thread is attempting to access the registry. Typically
  /// this is done by initializing all toolchains at program startup.
  ///
  /// @param Toolchain - The toolchain being registered.
  /// @param Name - The toolchain name.
  /// @param QualityFn - The function for rating the match quality of a fourple.
  static void RegisterToolchain(Toolchain& pToolchain,
                                const char* pName,
                                Toolchain::FourpleMatchQualityFnTy pQualityFn) {
    // TODO: Implement.
  }

  /// Register toolchain by a protobuf file.
  ///
  /// @param ProtobufFileName - The protobuf file's name.
  static void RegisterToolchain(const std::string& pProtobufFileName) {
    // TODO: Define the protobuf description file.
    // TODO: Implement.
  }

  /// lookupToolchain - Look up Toolchain.
  ///
  /// @param Fourple - The Fourple string
  /// @param Error  - The returned error message
  static const bold::Toolchain *lookupToolchain(const std::string& pFourple,
                                                    std::string& pError) {
    // TODO: Implement.
  }
};

} // namespace of bold

#endif


//===- Tool.h -------------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_LANGUAGE_TOOLCHAIN_H
#define BOLD_LANGUAGE_TOOLCHAIN_H
#include <bold/Language/Tool.h>

#include <string>

namespace bold {

/** \class Toolchain
 *  \brief Toolchain is a set of Tools. 
 */
class Toolchain {
public:
  friend class ToolchainRegistry;

  typedef unsigned (*FourpleMatchQualityFnTy)(const std::string &TT);

private:
  FourpleMatchQualityFnTy FourpleMatchQualityFn;

  // TODO: Tool getter.
};

} // namespace of bold

#endif


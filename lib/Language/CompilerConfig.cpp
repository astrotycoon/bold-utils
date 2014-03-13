//===- CompilerConfig.cpp -------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include <bold/Language/CompilerConfig.h>

using namespace bold;

//===----------------------------------------------------------------------===//
// CompilerConfig
//===----------------------------------------------------------------------===//
CompilerConfig::CompilerConfig(const Compiler& pCompiler)
  : m_Compiler(pCompiler) {
}

const Compiler& CompilerConfig::getTool() const
{
  return m_Compiler;
}

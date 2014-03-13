//===- CompilerConfig.h ---------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_LANGUAGE_COMPILER_CONFIG_H
#define BOLD_LANGUAGE_COMPILER_CONFIG_H
#include <bold/Language/ToolConfig.h>
#include <bold/Language/Compiler.h>

namespace bold {

/** \class CompilerConfig
 *  \brief CompilerConfig contains the configuration of a compiler.
 */
class CompilerConfig : public ToolConfig
{
public:
  explicit CompilerConfig(const Compiler& pCompiler);

  const Compiler& getTool() const;

private:
  const Compiler& m_Compiler;
};

} // namespace of bold

#endif


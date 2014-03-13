//===- ToolConfig.h -------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_LANGUAGE_TOOL_CONFIG_H
#define BOLD_LANGUAGE_TOOL_CONFIG_H

namespace bold {

class Tool;

/** \class ToolConfig
 *  \brief ToolConfig provides interfaces for config of tools, such as
 *  CompilerConfig and LinkerConfig.
 */
class ToolConfig
{
public:
  virtual const Tool& getTool() const = 0;
};

} // namespace of bold

#endif


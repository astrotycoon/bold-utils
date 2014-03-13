//===- CompilerOption.h ----------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_COMPILER_OPTION_H
#define BOLD_COMPILER_OPTION_H

namespace bold {

/** \class Option
 */
class Option
{
public:
  enum Formatting {
    kNormalFormatting = 0x00, ///< Nothing special
    kPositional       = 0x01, ///< Is a positional argument, no '-' required
    kPrefix           = 0x02, ///< Can this option directly prefix its value?
    kGrouping         = 0x03  ///< Can this option group with other options?
  };

  enum MiscFlags {              ///< Miscellaneous flags to adjust argument
    kCommaSeparated     = 0x01, ///< Should this cl::list split between commas?
    kPositionalEatsArgs = 0x02, ///< Should this positional cl::list eat -args?
    kSink               = 0x04  ///< Should this cl::list eat all unknown options?
  };

public:
  Formatting getFormattingFlag() const { return m_Formatting; }

  void setFormattingFlag(Formatting pV) { m_Formatting = pV; }

  unsigned int getMiscFlags() const { return m_MiscFlags; }

  void setMiscFlags(enum MiscFlags pM) { m_MiscFlags |= pM; }
  
private:
  Formatting m_Formatting;       ///< enum Formatting
  unsigned int m_MiscFlags : 3;  ///< enum MiscFlags
};

/** \class CompilerOption
 *  \brief CompilerOption provides interface for general compiler options.
 */
class CompilerOption
{
protected:
  CompilerOption();

  virtual ~CompilerOption() = 0;
};

} // namespace of bold

#endif


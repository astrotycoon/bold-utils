//===- GeneralOptions.h ---------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_CONFIG_GENERAL_OPTIONS_H
#define BOLD_CONFIG_GENERAL_OPTIONS_H
#include <bold/Support/DataTypes.h>

namespace bold {

/** \class GeneralOptions
 *  \brief GeneralOptions collects the frequent-used options.
 */
class GeneralOptions
{
public:
  GeneralOptions();

  bool isFatalWarnings() const { return m_bIsFatalWarnings; }

  void setFatalWarnings(bool pEnable = true) { m_bIsFatalWarnings = pEnable; }

  /// return the verbose level [-1, 0, 1, 2]
  int8_t verbose() const { return m_Verbose; }

  /// --verbose[=0, 1, 2]
  void setVerbose(int8_t pVerbose = -1) { m_Verbose = pVerbose; }

  /// get the limit of maximum number of errors.
  int16_t getMaxErrorNum() const { return m_MaxErrorNum; }

  /// --error-liit=N
  void setMaxErrorNum(int16_t pMaxErrorNum) { m_MaxErrorNum = pMaxErrorNum; }

  /// get the limit of maximum number of warnings.
  int16_t getMaxWarnNum() const { return m_MaxWarnNum; }

  /// --warning-limit=N
  void setMaxWarnNum(int16_t pMaxWarnNum) { m_MaxWarnNum = pMaxWarnNum; }

private:
  bool m_bIsFatalWarnings : 1; ///< --fatal-warnings
  int8_t m_Verbose;            ///< --verbose[=0,1,2]
  int16_t m_MaxErrorNum;       ///< --error-limit=N
  int16_t m_MaxWarnNum;        ///< --warning-limit=N
};

} // namespace of bold

#endif


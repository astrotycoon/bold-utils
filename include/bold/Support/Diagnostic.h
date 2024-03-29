//===- Diagnostic.h -------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_SUPPORT_DIAGNOSTIC_H
#define BOLD_SUPPORT_DIAGNOSTIC_H
#include <bold/Support/DiagnosticEngine.h>
#include <string>

namespace bold {
namespace diagnostic {

/** \class Diagnostic
 *  \brief Diagnostic stores the result of a diagnostic.
 */
class Diagnostic
{
public:
  /// id - return the id of the diagnostic
  unsigned int id() const { return m_State.ID; }

  /// getNumOfArgs - return the number of formal arguments.
  unsigned int getNumOfArgs() const { return m_State.NumOfArgs; }

  /// severity - return the current severity.
  Engine::Severity severity() const { return m_Severity; }

  /// setSeverity - assign severity to this diagnostic
  void setSeverity(Engine::Severity pSeverity) { m_Severity = pSeverity; }

  /// format - format this diagnostic into string.
  void format(std::string& pOutStr) const;

  /// format - format this diagnostic into string.
  void format(const char* pBegin, const char* pEnd, std::string& pOutStr) const;

  /// @name Argument operators
  /// @{
  /// getArgKind - get argument kind
  Engine::ArgumentKind getArgKind(unsigned int pID) const;

  /// getArgStdStr - get argument as standard string
  const std::string& getArgStdStr(unsigned int pID) const;

  /// getArgCStr - get argument as c-string
  const char* getArgCStr(unsigned int pID) const;

  /// getArgSInt32 - get argument as int32_t
  int32_t getArgSInt32(unsigned int pID) const;

  /// getArgUInt32 - get argument as uint32_t
  uint32_t getArgUInt32(unsigned int pID) const;

  /// getArgSInt64 - get argument as int64_t
  int64_t getArgSInt64(unsigned int pID) const;

  /// getArgUInt64 - get argument as uint64_t
  uint64_t getArgUInt64(unsigned int pID) const;

  /// getArgBool - get argument as boolean
  bool getArgBool(unsigned int pID) const;

  /// getRawValue - get the raw value of argument
  intptr_t getRawValue(unsigned int pID) const;
  /// @}

private:
  friend class Engine;

  Diagnostic(const Engine::State& pState, const InfoMap& pInfoMap);

private:
  const Engine::State& m_State;
  const InfoMap& m_InfoMap;
  Engine::Severity m_Severity;
};

} // namespace of diagnostic
} // namespace of bold

#endif


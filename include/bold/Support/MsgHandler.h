//===- MsgHandler.h -------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_SUPPORT_MSGHANDLER_H
#define BOLD_SUPPORT_MSGHANDLER_H
#include <bold/ADT/StringRef.h>
#include <bold/Support/DataTypes.h>
#include <bold/Support/DiagnosticEngine.h>

namespace bold {

namespace diagnostic {

/** \class MsgHandler
 *  \brief MsgHandler handles the timing of reporting a diagnostic result.
 *
 *  MsgHandler controls the process to display the message. The message is
 *  emitted when calling MsgHandler's destructor.
 */
class MsgHandler
{
public:
  MsgHandler(Engine& pEngine);

  ~MsgHandler();

  /// emit the message
  bool emit();

  /// add an argument as a StringRef.
  void addString(StringRef pStr) const;

  /// add an argument as a std::string.
  void addString(const std::string& pStr) const;

  /// add an argument with tagged value.
  void addTaggedValue(intptr_t pValue, Engine::ArgumentKind pKind) const;

private:
  void flushCounts();

private:
  Engine& m_Engine;
  mutable unsigned int m_NumOfArgs;

};

} // namespace of diagnostic

//===----------------------------------------------------------------------===//
// Non-member functions
//===----------------------------------------------------------------------===//
inline const diagnostic::MsgHandler&
operator<<(const diagnostic::MsgHandler& pHandler, StringRef pStr)
{
  pHandler.addString(pStr);
  return pHandler;
}

inline const diagnostic::MsgHandler&
operator<<(const diagnostic::MsgHandler& pHandler, const std::string& pStr)
{
  pHandler.addString(pStr);
  return pHandler;
}

inline const diagnostic::MsgHandler&
operator<<(const diagnostic::MsgHandler& pHandler, const char* pStr)
{
  pHandler.addTaggedValue(reinterpret_cast<intptr_t>(pStr),
                          diagnostic::Engine::ak_c_string);
  return pHandler;
}

inline const diagnostic::MsgHandler&
operator<<(const diagnostic::MsgHandler& pHandler, int32_t pValue)
{
  pHandler.addTaggedValue(pValue, diagnostic::Engine::ak_sint32);
  return pHandler;
}

inline const diagnostic::MsgHandler&
operator<<(const diagnostic::MsgHandler& pHandler, uint32_t pValue)
{
  pHandler.addTaggedValue(pValue, diagnostic::Engine::ak_uint32);
  return pHandler;
}

inline const diagnostic::MsgHandler&
operator<<(const diagnostic::MsgHandler& pHandler, int64_t pValue)
{
  pHandler.addTaggedValue(pValue, diagnostic::Engine::ak_sint64);
  return pHandler;
}

inline const diagnostic::MsgHandler&
operator<<(const diagnostic::MsgHandler& pHandler, uint64_t pValue)
{
  pHandler.addTaggedValue(pValue, diagnostic::Engine::ak_uint64);
  return pHandler;
}

inline const diagnostic::MsgHandler&
operator<<(const diagnostic::MsgHandler& pHandler, bool pValue)
{
  pHandler.addTaggedValue(pValue, diagnostic::Engine::ak_bool);
  return pHandler;
}

} // namespace of bold

#endif

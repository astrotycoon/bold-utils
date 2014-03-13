//===- MsgHandling.h ------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_SUPPORT_MSG_HANDLING_H
#define BOLD_SUPPORT_MSG_HANDLING_H
#include <bold/ADT/OwningPtr.h>
#include <bold/Support/DiagnosticEngine.h>
#include <bold/Support/DiagnosticPrinter.h>
#include <bold/Support/MsgHandler.h>

namespace bold {

class SkySettings;

diagnostic::MsgHandler unreachable(unsigned int pID);
diagnostic::MsgHandler fatal      (unsigned int pID);
diagnostic::MsgHandler error      (unsigned int pID);
diagnostic::MsgHandler warning    (unsigned int pID);
diagnostic::MsgHandler debug      (unsigned int pID);
diagnostic::MsgHandler note       (unsigned int pID);
diagnostic::MsgHandler ignore     (unsigned int pID);

/** \class MsgHandling
 *  \brief MsgHandling is a helper class that calls diagnostic::Initialize() when
 *  it's constructing and calls diagnostic::Finalize() when it's destroyed.
 */
class MsgHandling
{
public:
  MsgHandling(const SkySettings& pSettings);

  ~MsgHandling();

  static bool diagnose();
};

/** \namespace diagnostic
 *  diagnostic namespace collects all classes of diagnostic system.
 */
namespace diagnostic {

/// InitializeMsgHandling - initialize diagnostic system.
void Initialize(const SkySettings& pSettings);

/// FinalizeMsgHandling - finalize diagnostic system and flush all messages.
void Finalize();

/// Diagnose - check system status and flush all error messages.
bool Diagnose();

/// diagnostic::getEngine - Get the global-wise diagnostic engine.
Engine& getEngine();

} // namespace of diagnostic

//===----------------------------------------------------------------------===//
// Inline non-member function
//===----------------------------------------------------------------------===//
inline diagnostic::MsgHandler unreachable(unsigned int pID)
{
  return diagnostic::getEngine().report(pID, diagnostic::Engine::Unreachable);
}

inline diagnostic::MsgHandler fatal(unsigned int pID)
{
  return diagnostic::getEngine().report(pID, diagnostic::Engine::Fatal);
}

inline diagnostic::MsgHandler error(unsigned int pID)
{
  return diagnostic::getEngine().report(pID, diagnostic::Engine::Error);
}

inline diagnostic::MsgHandler warning(unsigned int pID)
{
  return diagnostic::getEngine().report(pID, diagnostic::Engine::Warning);
}

inline diagnostic::MsgHandler debug(unsigned int pID)
{
  return diagnostic::getEngine().report(pID, diagnostic::Engine::Debug);
}

inline diagnostic::MsgHandler note(unsigned int pID)
{
  return diagnostic::getEngine().report(pID, diagnostic::Engine::Note);
}

inline diagnostic::MsgHandler ignore(unsigned int pID)
{
  return diagnostic::getEngine().report(pID, diagnostic::Engine::Ignore);
}

} // namespace of bold

#endif


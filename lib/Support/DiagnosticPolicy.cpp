//===- DiagnosticPolicy.cpp -----------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include <bold/Support/DiagnosticPolicy.h>
#include <bold/Config/SkySettings.h>
#include <bold/Support/DiagnosticEngine.h>
#include <bold/Support/Diagnostic.h>

using namespace bold;

//===----------------------------------------------------------------------===//
// DiagnosticPolicy
//===----------------------------------------------------------------------===//
bool diagnostic::DefaultPolicy::process(const SkySettings& pSettings,
                                        Diagnostic& pDiag)
{
  // if --fatal-warnings is turned on, then switch warnings and errors to fatal.
  if (pSettings.options().isFatalWarnings()) {
    if (Engine::Warning == pDiag.severity() ||
        Engine::Error   == pDiag.severity()) {
      pDiag.setSeverity(Engine::Fatal);
    }
  }

  return true;
}


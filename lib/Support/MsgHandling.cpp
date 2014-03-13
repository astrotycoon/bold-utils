//===- MsgHandling.cpp ----------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include <bold/Support/MsgHandling.h>
#include <bold/Support/ManagedStatic.h>
#include <bold/ADT/OwningPtr.h>

using namespace bold;

static bold::ManagedStatic<diagnostic::Engine> g_pEngine;

//===----------------------------------------------------------------------===//
// Non-member Functions
//===----------------------------------------------------------------------===//
/// InitializeMsgHandling - initialize diagnostic system.
void bold::diagnostic::Initialize(const SkySettings& pSettings)
{
  diagnostic::getEngine().setup(pSettings);
}

/// Finalize - finalize diagnostic system and flush all messages.
void bold::diagnostic::Finalize()
{
  g_pEngine->getPrinter()->finish();
}

/// Diagnose - check system status and flush all error messages.
bool bold::diagnostic::Diagnose()
{
  if (0 < g_pEngine->getPrinter()->getNumErrors()) {
    g_pEngine->getPrinter()->finish();
    return false;
  }
  return true;
}

/// getDiagnosticEngine - Get the global-wise diagnostic engine.
diagnostic::Engine& bold::diagnostic::getEngine()
{
  return *g_pEngine;
}

//===----------------------------------------------------------------------===//
// MsgHandling
//===----------------------------------------------------------------------===//
bold::MsgHandling::MsgHandling(const SkySettings& pSettings)
{
  diagnostic::Initialize(pSettings);
}

bold::MsgHandling::~MsgHandling()
{
  diagnostic::Finalize();
}

bool bold::MsgHandling::diagnose()
{
  return diagnostic::Diagnose();
}

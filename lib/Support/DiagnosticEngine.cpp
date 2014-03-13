//===- DiagnosticEngine.cpp -----------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include <bold/Support/DiagnosticEngine.h>
#include <bold/Support/Diagnostic.h>
#include <bold/Support/DiagnosticPolicy.h>
#include <bold/Support/DiagnosticPrinter.h>
#include <bold/Support/IOStream.h>
#include <bold/Support/TextDiagnosticPrinter.h>
#include <bold/Support/MsgHandler.h>
#include <cassert>

using namespace bold;

//===----------------------------------------------------------------------===//
// Engine
//===----------------------------------------------------------------------===//
diagnostic::Engine::Engine()
  : m_pSettings(NULL), m_pPrinter(NULL) {
}

diagnostic::Engine::~Engine()
{
  delete m_pPrinter;
}

void diagnostic::Engine::setup(const SkySettings& pSettings, Printer* pPrinter)
{
  m_pSettings = &pSettings;

  if (NULL == pPrinter)
    m_pPrinter = new TextPrinter(errs(), pSettings);
  else
    takePrinter(pPrinter);
}

diagnostic::MsgHandler
diagnostic::Engine::report(unsigned int pID, Severity pSeverity)
{
  state().ID = pID;
  state().CurrentSeverity = pSeverity;

  MsgHandler result(*this);
  return result;
}

void diagnostic::Engine::takePrinter(diagnostic::Printer* pPrinter)
{
  delete m_pPrinter;
  m_pPrinter = pPrinter;
}

bool diagnostic::Engine::emit()
{
  assert(NULL != m_pPrinter && "Engine wasn't set-up yet");

  Diagnostic info(m_State, m_InfoMap);
  // TODO: select policy by some way.
  bool emitted = DefaultPolicy::process(*m_pSettings, info);

  m_pPrinter->handle(info);
  m_State.reset();
  return emitted;
}

//===----------------------------------------------------------------------===//
// Engine::State
//===----------------------------------------------------------------------===//
diagnostic::Engine::State::State()
  : NumOfArgs(0), ID(0), CurrentSeverity(None) {
}

void diagnostic::Engine::State::reset()
{
  NumOfArgs       = 0;
  ID              = 0;
  CurrentSeverity = None;
}

//===- DiagnosticPrinter.cpp ----------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include <bold/Support/DiagnosticPrinter.h>
#include <bold/Support/Diagnostic.h>
#include <bold/Support/DiagnosticEngine.h>

using namespace bold;

//===----------------------------------------------------------------------===//
// Printer
//===----------------------------------------------------------------------===//
diagnostic::Printer::Printer()
  : m_NumWarnings(0), m_NumErrors(0) {
}

diagnostic::Printer::~Printer()
{
  this->reset();
}

bool diagnostic::Printer::handle(const Diagnostic& pDiag)
{
  if (Engine::Warning == pDiag.severity())
    ++m_NumWarnings;

  if (Engine::Error >= pDiag.severity())
    ++m_NumErrors;

  return true;
}

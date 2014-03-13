//===- DiagnosticPrinter.h ------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_SUPPORT_DIAGNOSTIC_PRINTER_H
#define BOLD_SUPPORT_DIAGNOSTIC_PRINTER_H

namespace bold {
namespace diagnostic {

class Diagnostic;

/** \class Printer
 *  \brief Printer provides abstract interface for the printers to
 *   display diagnostic result.
 */
class Printer
{
public:
  Printer();

  virtual ~Printer() = 0;

  virtual void finish() = 0;

  virtual void reset() { m_NumWarnings = m_NumErrors = 0; }

  virtual bool handle(const Diagnostic& pDiag);

  unsigned int getNumWarnings() const { return m_NumWarnings; }

  unsigned int getNumErrors() const { return m_NumErrors; }

private:
  unsigned int m_NumWarnings;
  unsigned int m_NumErrors;

};

} // namespace of diagnostic
} // namespace of bold

#endif


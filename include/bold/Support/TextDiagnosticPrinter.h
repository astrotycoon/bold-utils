//===- TextDiagnosticPrinter.h --------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_SUPPORT_TEXT_DIAGNOSTIC_PRINTER_H
#define BOLD_SUPPORT_TEXT_DIAGNOSTIC_PRINTER_H
#include <bold/Support/DiagnosticPrinter.h>
#include <bold/Support/IOSFwd.h>

namespace bold {

class SkySettings;

namespace diagnostic {

/** \class TextPrinter
 *  \brief TextPrinter display the result of diagnostic in text
 *  format.
 */
class TextPrinter : public Printer
{
public:
  TextPrinter(OStream& pOStream, const SkySettings& pSettings);

  ~TextPrinter();

  void finish();

  bool handle(const Diagnostic& pDiag);

private:
  OStream& m_OStream;
  const SkySettings& m_Settings;

};

} // namespace of diagnostic
} // namespace of bold

#endif


//===- TextDiagnosticPrinter.cpp ------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include <bold/Support/TextDiagnosticPrinter.h>
#include <bold/Config/SkySettings.h>
#include <bold/Support/Diagnostic.h>
#include <bold/Support/IOStream.h>
#include <cstdlib>

using namespace bold;

//===----------------------------------------------------------------------===//
// Variable Dictionary
//===----------------------------------------------------------------------===//
static const enum OStream::Colors UnreachableColor = OStream::RED;
static const enum OStream::Colors FatalColor       = OStream::YELLOW;
static const enum OStream::Colors ErrorColor       = OStream::RED;
static const enum OStream::Colors WarningColor     = OStream::MAGENTA;
static const enum OStream::Colors DebugColor       = OStream::CYAN;
static const enum OStream::Colors NoteColor        = OStream::GREEN;
static const enum OStream::Colors IgnoreColor      = OStream::BLUE;
//===----------------------------------------------------------------------===//
// TextPrinter
//===----------------------------------------------------------------------===//
diagnostic::TextPrinter::TextPrinter(OStream& pOStream,
                                     const SkySettings& m_Settings)
  : m_OStream(pOStream), m_Settings(m_Settings) {
}
                                                    
diagnostic::TextPrinter::~TextPrinter()
{
}
                                                   
void diagnostic::TextPrinter::finish()
{
}
 
bool diagnostic::TextPrinter::handle(const Diagnostic& pDiag)
{
  Printer::handle(pDiag);

  std::string out_str;
  pDiag.format(out_str);

  // TODO: print the information according to the severity.
  switch (pDiag.severity()) {
    case Engine::Unreachable: {
      m_OStream.changeColor(UnreachableColor, true);
      m_OStream << "Unreachable: ";
      m_OStream.resetColor();
      m_OStream << out_str << "\n";
      break;
    }
    case Engine::Fatal: {
      m_OStream.changeColor(FatalColor, true);
      m_OStream << "Fatal: ";
      m_OStream.resetColor();
      m_OStream << out_str << "\n";
      break;
    }
    case Engine::Error: {
      m_OStream.changeColor(ErrorColor, true);
      m_OStream << "Error: ";
      m_OStream.resetColor();
      m_OStream << out_str << "\n";
      break;
    }
    case Engine::Warning: {
      m_OStream.changeColor(WarningColor, true);
      m_OStream << "Warning: ";
      m_OStream.resetColor();
      m_OStream << out_str << "\n";
      break;
    }
    case Engine::Debug: {
      // show debug message only if verbose >=0
      if (0 <= m_Settings.options().verbose()) {
        m_OStream.changeColor(DebugColor, true);
        m_OStream << "Debug: ";
        m_OStream.resetColor();
        m_OStream << out_str << "\n";
      }
      break;
    }
    case Engine::Note: {
      // show noted messages only if verbose >= 1.
      if (1 <= m_Settings.options().verbose()) {
        m_OStream.changeColor(NoteColor, true);
        m_OStream << "Note: ";
        m_OStream.resetColor();
        m_OStream << out_str << "\n";
      }
      break;
    }
    case Engine::Ignore: {
      // show ignored messages only if verbose >= 2
      if (2 <= m_Settings.options().verbose()) {
        m_OStream.changeColor(IgnoreColor, true);
        m_OStream << "Ignore: ";
        m_OStream.resetColor();
        m_OStream << out_str << "\n";
      }
      break;
    }
  } // end of switch

  switch (pDiag.severity()) {
    case Engine::Unreachable: {
      m_OStream << "\n\n";
      m_OStream.changeColor(OStream::YELLOW);
      m_OStream << "You meet a bug of Skymizer. Please report to:\n"
                << "  bugs@bold.com\n";
      m_OStream.resetColor();
    }
    /** fall through **/
    case Engine::Fatal: {
      // If we get in here, then we are failing ungracefully.
      exit(1);
    }
    case Engine::Error: {
      int16_t error_limit = m_Settings.options().getMaxErrorNum();
      if ((-1 != error_limit) &&
          (this->getNumErrors() > static_cast<unsigned int>(error_limit))) {
        m_OStream << "\n\n";
        m_OStream.changeColor(OStream::YELLOW);
        m_OStream << "too many error messages (>" << error_limit << ")...\n";
        m_OStream.resetColor();
        // If we get in here, then we are failing ungracefully.
        exit(1);
      }
      break;
    }
    case Engine::Warning: {
      int16_t warning_limit = m_Settings.options().getMaxWarnNum();
      if ((-1 != warning_limit) &&
          (this->getNumWarnings() > static_cast<unsigned>(warning_limit))) {
        m_OStream << "\n\n";
        m_OStream.changeColor(OStream::YELLOW);
        m_OStream << "too many warning messages (>" << warning_limit << ")...\n";
        m_OStream.resetColor();
        // If we get in here, then we are failing ungracefully.
        exit(1);
      }
      break;
    }
    default:
      break;
  }
}

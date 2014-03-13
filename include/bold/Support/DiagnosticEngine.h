//===- DiagnosticEngine.h -------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_SUPPORT_DIAGNOSTIC_ENGINE_H
#define BOLD_SUPPORT_DIAGNOSTIC_ENGINE_H
#include <bold/Support/DiagnosticInfoMap.h>
#include <bold/Support/DataTypes.h>
#include <string>

namespace bold {

class SkySettings;

namespace diagnostic {

class MsgHandler;
class Printer;

/** \class Engine
 *  \brief Engine drives the diagnostic system to display information.
 */
class Engine
{
public:
  enum Severity {
    Unreachable,
    Fatal,
    Error,
    Warning,
    Debug,
    Note,
    Ignore,
    None
  };

  enum ArgumentKind {
    ak_std_string,  // std::string
    ak_c_string,    // const char *
    ak_sint32,      // int32_t
    ak_uint32,      // uint32_t
    ak_sint64,      // uint64_t
    ak_uint64,      // uint64_t
    ak_bool         // bool
  };

public:
  /// Default constructor
  Engine();

  /// Destructor
  ~Engine();

  /// Report a diagnostic result
  MsgHandler report(unsigned int pID, Severity pSeverity);

  /// Set up engine. If the Printer is not given, Engine will create a
  /// TextPrinter.
  void setup(const SkySettings& pSettings, Printer* pPrinter = NULL);

  /// Take over the printer. Engine will delete the given printer while calling
  /// the destructor.
  void takePrinter(Printer* pPrinter);

  /// Return true if Engine've taken over a printer
  bool hasPrinter() const { return (NULL != m_pPrinter); }

  /// Return the printer.
  const Printer* getPrinter() const { return m_pPrinter; }

  /// Return the printer.
  Printer*       getPrinter()       { return m_pPrinter; }

  /// Emit the message
  bool emit();

private:
  class State
  {
  public:
    enum {
      MaxArguments = 10
    };

  public:
    State();

    void reset();

  public:
    std::string ArgumentStrs[MaxArguments];
    intptr_t    ArgumentVals[MaxArguments];
    uint8_t     ArgumentKinds[MaxArguments];
    uint8_t     NumOfArgs;
    uint16_t    ID;
    Severity    CurrentSeverity;
  };

  friend class MsgHandler;
  friend class Diagnostic;

private:
  const State& state() const { return m_State; }
  State&       state()       { return m_State; }

private:
  const SkySettings* m_pSettings;
  Printer* m_pPrinter;
  State m_State;
  InfoMap m_InfoMap;

};

} // namespace of diagnostic
} // namespace of bold

#endif


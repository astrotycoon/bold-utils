//===- MsgHandler.cpp -----------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include <bold/Support/MsgHandler.h>
#include <bold/Support/DiagnosticEngine.h>
#include <cassert>

using namespace bold;

//===----------------------------------------------------------------------===//
// MsgHandler
//===----------------------------------------------------------------------===//
diagnostic::MsgHandler::MsgHandler(Engine& pEngine)
  : m_Engine(pEngine), m_NumOfArgs(0) {
}

diagnostic::MsgHandler::~MsgHandler()
{
  emit();
}

bool diagnostic::MsgHandler::emit()
{
  flushCounts();
  return m_Engine.emit();
}

/// add an argument as a StringRef.
void diagnostic::MsgHandler::addString(StringRef pStr) const
{
  assert(m_NumOfArgs <= Engine::State::MaxArguments &&
         "Too many arguments in a diagnostic");
  m_Engine.state().ArgumentKinds[m_NumOfArgs] = Engine::ak_c_string;
  m_Engine.state().ArgumentStrs[m_NumOfArgs++] = pStr.data();
}

/// add an argument as a std::string.
void diagnostic::MsgHandler::addString(const std::string& pStr) const
{
  assert(m_NumOfArgs <= Engine::State::MaxArguments &&
         "Too many arguments in a diagnostic");
  m_Engine.state().ArgumentKinds[m_NumOfArgs] = Engine::ak_std_string;
  m_Engine.state().ArgumentStrs[m_NumOfArgs++] = pStr.data();
}

/// add an argument with tagged value.
void diagnostic::MsgHandler::addTaggedValue(intptr_t pValue,
                                 diagnostic::Engine::ArgumentKind pKind) const
{
  assert(m_NumOfArgs <= Engine::State::MaxArguments &&
         "Too many arguments in a diagnostic");
  m_Engine.state().ArgumentKinds[m_NumOfArgs] = pKind;
  m_Engine.state().ArgumentStrs[m_NumOfArgs++] = pValue;
}

void diagnostic::MsgHandler::flushCounts()
{
  m_Engine.state().NumOfArgs = m_NumOfArgs;
}


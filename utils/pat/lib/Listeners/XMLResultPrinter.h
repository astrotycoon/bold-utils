//===- XMLResultPrinter.h -------------------------------------------------===//
//
//                     The pat Team
//
// This file is distributed under the New BSD License. 
// See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef PAT_LISTENERS_XML_RESULT_PRINTER_H
#define PAT_LISTENERS_XML_RESULT_PRINTER_H
#include <string>
#include <pat/pat.h>

namespace pat {

namespace testing {

class UnitTest;
class TestCase;
class TestInfo;

} // namespace of UnitTest

//===----------------------------------------------------------------------===//
// XMLResultPrinter
//===----------------------------------------------------------------------===//
class XMLResultPrinter : public pat::testing::Listener
{
public:
  static void PrintCaseName(const std::string& pCase, const std::string& pTest);
  void OnTestProgramStart(const testing::UnitTest& pUnitTest);
  void OnTestCaseStart(const testing::TestCase& pTestCase);
  void OnTestStart(const testing::TestInfo& pTestInfo);
  void OnSetUpStart(const testing::UnitTest& pUnitTest);
  void OnSetUpEnd(const testing::UnitTest& pUnitTest);
  void OnTestEnd(const testing::TestInfo& pTestInfo);
  void OnTestProgramEnd(const testing::UnitTest& pUnitTest);
};

} // namespace pat

#endif

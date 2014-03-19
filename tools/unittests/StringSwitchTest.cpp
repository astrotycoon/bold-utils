//===- StringSwitchTest.cpp -----------------------------------------------===//
//
//                             The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include "StringSwitchTest.h"
#include <bold/ADT/StringSwitch.h>

using namespace bold;
using namespace bold::test;

//===----------------------------------------------------------------------===//
// StringSwitch
//===----------------------------------------------------------------------===//
// Constructor can do set-up work for all test here.
StringSwitchTest::StringSwitchTest()
{
}

// Destructor can do clean-up work that doesn't throw exceptions here.
StringSwitchTest::~StringSwitchTest()
{
}

// SetUp() will be called immediately before each test.
void StringSwitchTest::SetUp()
{
}

// TearDown() will be called immediately after each test.
void StringSwitchTest::TearDown()
{
}

//===----------------------------------------------------------------------===//
// Testcases
//===----------------------------------------------------------------------===//
namespace {

enum Color {
  Red,
  Blue,
  Yello,
  Unknown
};

} // anonymous namespace

PAT_C( StringSwitchTest, simple_test) {
  const char* color_str = "Red";
  Color color = StringSwitch<Color>(color_str)
    .Case("Red", Red)
    .Case("Blue", Blue)
    .Case("Yello", Yello)
    .Default(Unknown);

  ASSERT_TRUE(Red == color);
}

PAT_C( StringSwitchTest, default_test) {
  const char* color_str = "NoColor";
  Color color = StringSwitch<Color>(color_str)
    .Case("Red", Red)
    .Case("Blue", Blue)
    .Case("Yello", Yello)
    .Default(Unknown);

  ASSERT_TRUE(Unknown == color);
}

PAT_C( StringSwitchTest, start_with_test) {
  const char* color_str = "BlueSky";
  Color color = StringSwitch<Color>(color_str)
    .StartsWith("Red", Red)
    .StartsWith("Blue", Blue)
    .StartsWith("Yello", Yello)
    .Default(Unknown);

  ASSERT_TRUE(Blue == color);
}

PAT_C( StringSwitchTest, end_with_test) {
  const char* color_str = "TheLightIsYello";
  Color color = StringSwitch<Color>(color_str)
    .EndsWith("Red", Red)
    .Case("Blue", Blue)
    .EndsWith("Yello", Yello)
    .Default(Unknown);

  ASSERT_TRUE(Yello == color);
}

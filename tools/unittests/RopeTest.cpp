//===- RopeTest.cpp -------------------------------------------------------===//
//
//                             The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include "RopeTest.h"
#include <bold/ADT/Rope.h>
#include <bold/ADT/StringRef.h>

using namespace bold;
using namespace bold::test;

//===----------------------------------------------------------------------===//
// Rope
//===----------------------------------------------------------------------===//
// Constructor can do set-up work for all test here.
RopeTest::RopeTest()
{
}

// Destructor can do clean-up work that doesn't throw exceptions here.
RopeTest::~RopeTest()
{
}

// SetUp() will be called immediately before each test.
void RopeTest::SetUp()
{
}

// TearDown() will be called immediately after each test.
void RopeTest::TearDown()
{
}

//===----------------------------------------------------------------------===//
// Testcases
//===----------------------------------------------------------------------===//
PAT_C( RopeTest, string_test1) {
  ASSERT_TRUE(16 == (Rope("test") + Rope("another") + Rope("three")).str().size());
  std::string test("test");
  StringRef   another("another");
  ASSERT_TRUE(16 == (Rope(test) + Rope(another) + Rope("three")).str().size());

  ASSERT_TRUE(4 == Rope(test).str().size());
  ASSERT_TRUE(7 == Rope(another).str().size());
  ASSERT_TRUE(6 == Rope("string").str().size());
  ASSERT_TRUE(1 == Rope('a').str().size());
  ASSERT_TRUE(1 == Rope(5).str().size());

  ASSERT_TRUE(18 == (Rope(test) + Rope(another) + Rope(' ') + Rope("test") + Rope(15)).str().size());
}

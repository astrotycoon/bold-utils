//===- OStrStreamTest.cpp -------------------------------------------------===//
//
//                             The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include "OStrStreamTest.h"
#include <bold/Support/OStrStream.h>

using namespace bold;
using namespace bold::test;

//===----------------------------------------------------------------------===//
// OStrStream
//===----------------------------------------------------------------------===//
// Constructor can do set-up work for all test here.
OStrStreamTest::OStrStreamTest()
{
}

// Destructor can do clean-up work that doesn't throw exceptions here.
OStrStreamTest::~OStrStreamTest()
{
}

// SetUp() will be called immediately before each test.
void OStrStreamTest::SetUp()
{
}

// TearDown() will be called immediately after each test.
void OStrStreamTest::TearDown()
{
}

//===----------------------------------------------------------------------===//
// Testcases
//===----------------------------------------------------------------------===//
PAT_C( OStrStreamTest, basic_test_int) {
  std::string out_str;
  OStrStream ss(out_str);
  ss << "test" << 12;
  ASSERT_TRUE(6 == out_str.size());
  ASSERT_TRUE(0 == out_str.compare("test12"));  
}

PAT_C( OStrStreamTest, basic_test_double) {
  std::string out_str;
  OStrStream ss(out_str);
  ss << "test" << 0.05;
  ASSERT_TRUE(8 == out_str.size());
  ASSERT_TRUE(0 == out_str.compare("test0.05"));  
}

PAT_C( OStrStreamTest, basic_test_overflow) {
  std::string out_str;
  out_str.reserve(1);
  OStrStream ss(out_str);
  ss << "test";
  ASSERT_TRUE(4 == out_str.size());
  ASSERT_TRUE(0 == out_str.compare("test"));
}

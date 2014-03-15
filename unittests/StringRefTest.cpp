//===- StringRefTest.cpp --------------------------------------------------===//
//
//                             The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include "StringRefTest.h"
#include <bold/ADT/StringRef.h>
#include <cstring>

using namespace bold;
using namespace bold::test;

//===----------------------------------------------------------------------===//
// StringRef
//===----------------------------------------------------------------------===//
// Constructor can do set-up work for all test here.
StringRefTest::StringRefTest()
{
}

// Destructor can do clean-up work that doesn't throw exceptions here.
StringRefTest::~StringRefTest()
{
}

// SetUp() will be called immediately before each test.
void StringRefTest::SetUp()
{
}

// TearDown() will be called immediately after each test.
void StringRefTest::TearDown()
{
}

//===----------------------------------------------------------------------===//
// Testcases
//===----------------------------------------------------------------------===//
PAT_C( StringRefTest, default_constructor) {
  StringRef str;
  ASSERT_TRUE(NULL == str.data());
  ASSERT_TRUE(0 == str.size());
  ASSERT_TRUE(0 == str.length());
  ASSERT_TRUE(str.str().empty());
  ASSERT_TRUE(str.begin() == str.end());
}

PAT_C( StringRefTest, const_constructor) {
  StringRef str("test string");
  ASSERT_TRUE(11 == str.size());
  ASSERT_TRUE(str.length() == str.size());
  ASSERT_FALSE(str.empty());
  ASSERT_TRUE(2 == str.count('s'));
  ASSERT_TRUE(2 == str.count("st"));
  ASSERT_TRUE(0 == str.count('z'));
  ASSERT_TRUE(0 == str.count("ts"));
  ASSERT_TRUE(0 == str.count("test string is larger than original string"));
  ASSERT_TRUE(0 == strcmp("test string", str.data()));
  int counter = 0;
  for (StringRef::iterator i = str.begin(), e = str.end(); i != e; ++i)
    ++counter;
  ASSERT_TRUE(11 == counter);
  ASSERT_TRUE('t' == str.front());
  ASSERT_TRUE('g' == str.back());

  StringRef str_ne("another test string");
  StringRef str_eq("test string");
  ASSERT_FALSE(str.equals(str_ne));
  ASSERT_FALSE(str.equals("the other one"));
  ASSERT_TRUE(str.equals(str_eq));
  ASSERT_TRUE(str.equals("test string"));

  StringRef complex_str("Test StrinG");
  ASSERT_TRUE(complex_str.equals_lower(str));
  ASSERT_TRUE(0   == complex_str.compare_lower(str));
  ASSERT_TRUE(-1  == complex_str.compare(str));
  ASSERT_TRUE(1   == str.compare(complex_str));
  ASSERT_TRUE('s' == str[2]);
  ASSERT_TRUE(0   == strcmp("test string", complex_str.lower().data()));

  ASSERT_TRUE(complex_str.startswith("Test"));
  ASSERT_TRUE(str.startswith("test"));
  ASSERT_TRUE(complex_str.endswith(" StrinG"));
  ASSERT_TRUE(str.endswith("ing"));
}

PAT_C( StringRefTest, string_search) {
  StringRef str("TeSt sTrInG");
  ASSERT_TRUE(0 == str.find('T'));
  ASSERT_TRUE(1 == str.find('e'));
  ASSERT_TRUE(2 == str.find('S'));
  ASSERT_TRUE(3 == str.find('t'));
  ASSERT_TRUE(6 == str.find('T', 1));

  ASSERT_TRUE(2 == str.find("St"));
  ASSERT_TRUE(StringRef::npos == str.find('z'));

  ASSERT_TRUE(6 == str.rfind('T'));

  ASSERT_TRUE(5 == str.find_first_of('s'));
  ASSERT_TRUE(0 == str.find_first_of('T'));
  ASSERT_TRUE(6 == str.find_last_of('T'));
  ASSERT_TRUE(7 == str.find_last_of("sTr"));

  ASSERT_TRUE(1 == str.find_first_not_of('T'));
}

PAT_C( StringRefTest, substring_op) {
  StringRef str("tEsT StRiNg");

  ASSERT_TRUE(str.substr(1, 3).equals("EsT"));
  ASSERT_TRUE(str.slice(1, 6).equals("EsT S"));

  std::pair<StringRef, StringRef> res1 = str.split(' ');
  ASSERT_TRUE(res1.first.equals("tEsT"));
  ASSERT_TRUE(res1.second.equals("StRiNg"));

  std::pair<StringRef, StringRef> res2 = str.split("T S");
  ASSERT_TRUE(res2.first.equals("tEs"));
  ASSERT_TRUE(res2.second.equals("tRiNg"));
}

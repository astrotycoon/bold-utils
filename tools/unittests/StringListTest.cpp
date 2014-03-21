//===- StringListTest.cpp --------------------------------------------------===//
//
//                             The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include <bold/ADT/StringList.h>
#include <pat/pat.h>

using namespace bold;

//===----------------------------------------------------------------------===//
// Testcases
//===----------------------------------------------------------------------===//
PAT_F(StringListCase, size_test)
{
  StringRef a("a");
  StringRef b("b");
  StringRef c("c");

  StringList list;
  list.append(a);
  list.append(b);
  list.append(c);

  ASSERT_EQ(3, list.size());
  ASSERT_FALSE(list.empty());
  ASSERT_TRUE(0 == list.front().compare(a));
}


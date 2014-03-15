//===- OwningPtrTest.cpp --------------------------------------------------===//
//
//                             The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include "OwningPtrTest.h"
#include <bold/ADT/OwningPtr.h>

using namespace bold;
using namespace bold::test;

//===----------------------------------------------------------------------===//
// OwningPtr
//===----------------------------------------------------------------------===//
// Constructor can do set-up work for all test here.
OwningPtrTest::OwningPtrTest()
{
}

// Destructor can do clean-up work that doesn't throw exceptions here.
OwningPtrTest::~OwningPtrTest()
{
}

// SetUp() will be called immediately before each test.
void OwningPtrTest::SetUp()
{
}

// TearDown() will be called immediately after each test.
void OwningPtrTest::TearDown()
{
}

//===----------------------------------------------------------------------===//
// Testcases
//===----------------------------------------------------------------------===//
namespace {

class TestObj {
};

} // anonymous namespace

PAT_C( OwningPtrTest, trival )
{
  bold::OwningPtr<TestObj> ptr;

  ASSERT_TRUE(NULL == ptr.give());
  ASSERT_TRUE(NULL == ptr.get());
}

PAT_C( OwningPtrTest, simple )
{
  bold::OwningPtr<TestObj> ptr(new TestObj());
  ASSERT_FALSE(NULL == ptr.get());
  ASSERT_FALSE(NULL == ptr.give());
  ASSERT_TRUE(NULL == ptr.get());
}

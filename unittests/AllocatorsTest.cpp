//===- AllocatorsTest.cpp -------------------------------------------------===//
//
//                             The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include "AllocatorsTest.h"
#include <bold/Support/DataTypes.h>
#include <bold/Support/MallocAllocator.h>

using namespace bold;
using namespace bold::test;

//===----------------------------------------------------------------------===//
// AllocatorsTest
//===----------------------------------------------------------------------===//
// Constructor can do set-up work for all test here.
AllocatorsTest::AllocatorsTest()
{
}

// Destructor can do clean-up work that doesn't throw exceptions here.
AllocatorsTest::~AllocatorsTest()
{
}

// SetUp() will be called immediately before each test.
void AllocatorsTest::SetUp()
{
}

// TearDown() will be called immediately after each test.
void AllocatorsTest::TearDown()
{
}

//===----------------------------------------------------------------------===//
// Testcases
//===----------------------------------------------------------------------===//
PAT_C( AllocatorsTest, max_size_check_int)
{
  MallocAllocator<int> int_alloc;
  ASSERT_TRUE((size_t(-1)/sizeof(int)) == int_alloc.max_size());

  MallocAllocator<uint8_t> uint8_alloc;
  ASSERT_TRUE((size_t(-1)/sizeof(uint8_t)) == uint8_alloc.max_size());
}

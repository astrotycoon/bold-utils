//===- MemoryAllocatorTest.cpp ---------------------------------------------===//
//
//                             The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include <pat/pat.h>
#include <bold/Support/MemoryAllocator.h>
#include <bold/Support/DataTypes.h>
#include <cstring>

using namespace bold;

namespace {

struct Element {
  uint8_t  a;
  double   b;
  uint16_t c;
  uint64_t d;
};

} // anonymous namespace

//===----------------------------------------------------------------------===//
// Testcases
//===----------------------------------------------------------------------===//
PAT_F( MemoryAllocatorTest, initialization_test)
{
  MemoryAllocator<int, 32> int_array;
  ASSERT_EQ(0, int_array.size());
  ASSERT_TRUE(int_array.empty());
}

PAT_F( MemoryAllocatorTest, simple_allocate)
{
  MemoryAllocator<int, 32> int_array;
  int* a = int_array.allocate();
  new (a) int(3);
  ASSERT_EQ(*a, 3);
  ASSERT_EQ(int_array.size(), 1);
}

PAT_F( MemoryAllocatorTest, simple_allocate_more_than_a_slab)
{
  MemoryAllocator<int, 3> int_mem_pool;
  int* a = int_mem_pool.allocate();
  new (a) int(3);
  ASSERT_EQ(*a, 3);
  ASSERT_EQ(int_mem_pool.size(), 1);

  a = int_mem_pool.allocate();
  new (a) int(2);
  ASSERT_EQ(*a, 2);
  ASSERT_EQ(int_mem_pool.size(), 2);

  a = int_mem_pool.allocate();
  new (a) int(1);
  ASSERT_TRUE(1 == *a);
  ASSERT_TRUE(3 == int_mem_pool.size());


  a = int_mem_pool.allocate();
  new (a) int(0);
  ASSERT_TRUE(0 == *a);
  ASSERT_TRUE(4 == int_mem_pool.size());
}

PAT_F( MemoryAllocatorTest, complex_allocate)
{
  MemoryAllocator<Element, 2> e_mempool;

  Element* a = e_mempool.allocate();
  a->a = '1';
  a->b = 2.0;
  a->c = 254;
  a->d = -1;

  EXPECT_EQ(e_mempool.size(), 1);

  a = e_mempool.allocate();
  ASSERT_TRUE(2 == e_mempool.size());

  a = e_mempool.allocate();
  ASSERT_TRUE(3 == e_mempool.size());

  a = e_mempool.allocate();
  ASSERT_TRUE(4 == e_mempool.size());
}

PAT_F( MemoryAllocatorTest, StringPoolTest )
{
  MemoryAllocator<char, 10> str_pool;
  char* str1 = str_pool.allocate(7);
  str1[0] = 't';
  str1[1] = 'h';
  str1[2] = 'i';
  str1[3] = 's';
  str1[4] = ' ';
  str1[5] = 'i';
  str1[6] = '\0';
  EXPECT_EQ(strlen(str1), 6);
  EXPECT_EQ(str_pool.size(), 7);

  char* str2 = str_pool.allocate(4);
  ASSERT_TRUE(str_pool.isOverflow());
  EXPECT_EQ(str_pool.size(), 14);
  str2[0] = 's';
  str2[1] = ' ';
  str2[2] = 'a';
  str2[3] = '\0';
  EXPECT_TRUE(3 == strlen(str2));
}

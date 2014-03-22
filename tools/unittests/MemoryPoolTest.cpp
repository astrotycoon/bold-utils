//===- MemoryPoolTest.cpp -------------------------------------------------===//
//
//                             The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include <pat/pat.h>
#include <bold/Support/MemoryPool.h>
#include <bold/Support/DataTypes.h>
#include <cstring>

using namespace bold;

//===----------------------------------------------------------------------===//
// Testcases
//===----------------------------------------------------------------------===//
namespace {

struct Element {
  uint8_t  a;
  double   b;
  uint16_t c;
  uint64_t d;
};

} // anonymous namespace

PAT_F( MemoryPoolTest, simple_allocate) {
  MemoryPool<int, 32> int_array;
  int* a = int_array.allocate();
  new (a) int(3);
  ASSERT_EQ(*a, 3);
  ASSERT_EQ(int_array.size(), 1);
}

PAT_F( MemoryPoolTest, simple_allocate_more_than_a_slab) {
  MemoryPool<int, 3> int_mem_pool;
  int* a = int_mem_pool.allocate();
  new (a) int(3);
  ASSERT_TRUE(3 == *a);
  ASSERT_TRUE(1 == int_mem_pool.size());

  a = int_mem_pool.allocate();
  new (a) int(2);
  ASSERT_TRUE(2 == *a);
  ASSERT_TRUE(2 == int_mem_pool.size());

  a = int_mem_pool.allocate();
  new (a) int(1);
  ASSERT_TRUE(1 == *a);
  ASSERT_TRUE(3 == int_mem_pool.size());


  a = int_mem_pool.allocate();
  new (a) int(0);
  ASSERT_TRUE(0 == *a);
  ASSERT_TRUE(4 == int_mem_pool.size());

  int counter = 0;
  MemoryPool<int, 3>::iterator it;
  MemoryPool<int, 3>::iterator itEnd = int_mem_pool.end();
  for (it = int_mem_pool.begin(); it != itEnd; ++it) {
    ++counter;
  }
  ASSERT_TRUE(4 == counter);
}

PAT_F( MemoryPoolTest, complex_allocate) {
  MemoryPool<Element, 2> e_mempool;

  Element* a = e_mempool.allocate();
  a->a = '1';
  a->b = 2.0;
  a->c = 254;
  a->d = -1;

  ASSERT_TRUE(1 == e_mempool.size());

  a = e_mempool.allocate();
  ASSERT_TRUE(2 == e_mempool.size());

  a = e_mempool.allocate();
  ASSERT_TRUE(3 == e_mempool.size());

  a = e_mempool.allocate();
  ASSERT_TRUE(4 == e_mempool.size());

  unsigned int counter = 0;
  MemoryPool<Element, 2>::iterator it, End = e_mempool.end();
  for (it = e_mempool.begin(); it != End; ++it) {
    ++counter;
  }
  ASSERT_TRUE(4 == counter);
}

PAT_F( MemoryPoolTest, complex_iterate) {
  MemoryPool<Element, 2> e_mempool;

  Element* a = e_mempool.allocate();
  a->a = '1';
  a->b = 2.0;
  a->c = 254;
  a->d = -1;

  ASSERT_TRUE(1 == e_mempool.size());

  MemoryPool<Element, 2>::iterator it = e_mempool.begin();
  ASSERT_TRUE('1' == it->a);
  ASSERT_TRUE(2.0 == it->b);
  ASSERT_TRUE(254 == it->c);
  ASSERT_TRUE(-1 == it->d);

  a = e_mempool.allocate();
  a->a = '2';
  a->b = 3.0;
  a->c = 253;
  a->d = -2;

  ++it;

  ASSERT_TRUE('2' == it->a);
  ASSERT_TRUE(3.0 == it->b);
  ASSERT_TRUE(253 == it->c);
  ASSERT_TRUE(-2 == it->d);

  a = e_mempool.allocate();
  ASSERT_TRUE(3 == e_mempool.size());
  a->a = '3';
  a->b = 4.0;
  a->c = 252;
  a->d = -3;

  ++it;

  ASSERT_TRUE('3' == it->a);
  ASSERT_TRUE(4.0 == it->b);
  ASSERT_TRUE(252 == it->c);
  ASSERT_TRUE(-3 == it->d);
}

PAT_F( MemoryPoolTest, StringPoolTest )
{
  MemoryPool<char, 10> str_pool;
  char* str1 = str_pool.allocate(7);
  str1[0] = 't';
  str1[1] = 'h';
  str1[2] = 'i';
  str1[3] = 's';
  str1[4] = ' ';
  str1[5] = 'i';
  str1[6] = '\0';
  ASSERT_TRUE(6 == strlen(str1));
  ASSERT_TRUE(7 == str_pool.size());

  char* str2 = str_pool.allocate(4);
  ASSERT_TRUE(14 == str_pool.size());
  str2[0] = 's';
  str2[1] = ' ';
  str2[2] = 'a';
  str2[3] = '\0';
  ASSERT_TRUE(3 == strlen(str2));
}

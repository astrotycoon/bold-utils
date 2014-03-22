//===- IListTest.cpp ------------------------------------------------------===//
//
//                             The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include "IListTest.h"
#include <bold/ADT/IListNode.h>
#include <bold/ADT/IList.h>
#include <vector>

using namespace bold;
using namespace bold::test;

//===----------------------------------------------------------------------===//
// IListNode
//===----------------------------------------------------------------------===//
// Constructor can do set-up work for all test here.
IListTest::IListTest()
{
}

// Destructor can do clean-up work that doesn't throw exceptions here.
IListTest::~IListTest()
{
}

// SetUp() will be called immediately before each test.
void IListTest::SetUp()
{
}

// TearDown() will be called immediately after each test.
void IListTest::TearDown()
{
}

//===----------------------------------------------------------------------===//
// Testcases
//===----------------------------------------------------------------------===//
namespace {
  struct IntNode : public IListNode<IntNode> {
    int value;
  };

} // anonymous namespace

PAT_C( IListTest, default_constructor)
{
  IList<IntNode> int_list;

  ASSERT_TRUE(0 == int_list.size());
  ASSERT_TRUE(int_list.empty());

  ASSERT_TRUE(int_list.begin() == int_list.end());
}

PAT_C( IListTest, push_back_test)
{
  IntNode a;
  IntNode b;
  a.value = 7;
  b.value = 13;

  IList<IntNode> int_list;

  int_list.push_back(&a);
  int_list.push_back(&b);

  ASSERT_FALSE(int_list.empty());
  ASSERT_TRUE(2 == int_list.size());

  ASSERT_TRUE(7  == int_list.front().value);
  ASSERT_TRUE(13 == int_list.back().value);
}

PAT_C( IListTest, push_front_test)
{
  IntNode a;
  IntNode b;
  a.value = 7;
  b.value = 13;

  IList<IntNode> int_list;

  int_list.push_front(&a);
  int_list.push_front(&b);

  ASSERT_FALSE(int_list.empty());
  ASSERT_TRUE(2  == int_list.size());

  ASSERT_TRUE(13 == int_list.front().value);
  ASSERT_TRUE(7  == int_list.back().value);
}

PAT_C( IListTest, iterate_list)
{
  IntNode a;
  IntNode b;
  a.value = 7;
  b.value = 13;

  IList<IntNode> int_list;

  int_list.push_back(&a);
  int_list.push_back(&b);

  IList<IntNode>::iterator it, iEnd = int_list.end();
  int counter = 0;
  for (it = int_list.begin(); it != iEnd; ++it) {
    ++counter;
  }
  ASSERT_TRUE(2 == counter);

  it = int_list.begin();
  ASSERT_TRUE(7 == it->value);
  ++it;
  ASSERT_TRUE(13 == it->value);
  ++it;
  ++it;
  ++it;
  ASSERT_TRUE(int_list.end() == it);
}

PAT_C( IListTest, reverse_iterate_list)
{
  IntNode a;
  IntNode b;
  a.value = 7;
  b.value = 13;

  IList<IntNode> int_list;

  int_list.push_back(&a);
  int_list.push_back(&b);

  IList<IntNode>::reverse_iterator it, iEnd = int_list.rend();
  int counter = 0;
  for (it = int_list.rbegin(); it != iEnd; ++it) {
    ++counter;
  }
  ASSERT_TRUE(2 == counter);

  it = int_list.rbegin();
  ASSERT_TRUE(13 == it->value);
  ++it;
  ASSERT_TRUE(7 == it->value);
  ++it;
  ASSERT_TRUE(int_list.rend() == it);
}

PAT_C( IListTest, pop_front_test )
{
  IntNode a;
  IntNode b;
  a.value = 7;
  b.value = 13;

  IList<IntNode> int_list;

  int_list.push_back(&a);
  int_list.push_back(&b);

  ASSERT_TRUE(2 == int_list.size());

  int_list.pop_front();
  ASSERT_TRUE(1 == int_list.size());
  ASSERT_TRUE(13 == int_list.front().value);

  int_list.pop_front();
  ASSERT_TRUE(0 == int_list.size());
}

PAT_C( IListTest, pop_back_test )
{
  IntNode a;
  IntNode b;
  a.value = 7;
  b.value = 13;

  IList<IntNode> int_list;

  int_list.push_back(&a);
  int_list.push_back(&b);

  ASSERT_TRUE(2 == int_list.size());

  int_list.pop_back();
  ASSERT_TRUE(1 == int_list.size());
  ASSERT_TRUE(7 == int_list.back().value);

  int_list.pop_front();
  ASSERT_TRUE(0 == int_list.size());
}

PAT_C( IListTest, clear_test)
{
  IntNode a;
  IntNode b;
  a.value = 7;
  b.value = 13;

  IList<IntNode> int_list;

  int_list.push_back(&a);
  int_list.push_back(&b);

  ASSERT_TRUE(2 == int_list.size());

  int_list.clear();
  ASSERT_TRUE(0 == int_list.size());
  ASSERT_TRUE(NULL == a.getPrev());
  ASSERT_TRUE(NULL == a.getNext());
  ASSERT_TRUE(NULL == b.getPrev());
  ASSERT_TRUE(NULL == b.getNext());
}

PAT_C( IListTest, swap_test)
{
  IntNode a;
  IntNode b;
  IntNode c;
  IntNode d;
  a.value = 7;
  b.value = 13;
  c.value = 17;
  d.value = 19;

  IList<IntNode> prime_list;

  prime_list.push_back(&a);
  prime_list.push_back(&b);
  prime_list.push_back(&c);
  prime_list.push_back(&d);

  IntNode x;
  IntNode y;
  IntNode z;
  x.value = 2;
  y.value = 4;
  z.value = 6;

  IList<IntNode> even_list;

  even_list.push_back(&x);
  even_list.push_back(&y);
  even_list.push_back(&z);

  ASSERT_TRUE(4 == prime_list.size());
  ASSERT_TRUE(3 == even_list.size());

  prime_list.swap(even_list);

  ASSERT_TRUE(3 == prime_list.size());
  ASSERT_TRUE(4 == even_list.size());

  ASSERT_TRUE(2 == prime_list.front().value);
}

PAT_C( IListTest, insert_in_the_middle_test)
{
  IntNode a;
  IntNode b;
  IntNode c;
  IntNode d;
  a.value = 7;
  b.value = 13;
  c.value = 17;
  d.value = 19;

  IList<IntNode> prime_list;

  prime_list.push_back(&a);
  prime_list.push_back(&b);
  prime_list.push_back(&c);
  prime_list.push_back(&d);

  IntNode x;
  x.value = 2;

  IList<IntNode>::iterator it = prime_list.begin();
  ++it; ++it;
  prime_list.insert(it, &x);

  ASSERT_TRUE(5 == prime_list.size());
  ASSERT_TRUE(7 == prime_list.front().value);
  ASSERT_TRUE(19 == prime_list.back().value);
  ASSERT_TRUE(17 == it->value);
  --it;
  ASSERT_TRUE(2 == it->value);
}

PAT_C( IListTest, erase_in_the_middle_test)
{
  IntNode a;
  IntNode b;
  IntNode c;
  IntNode d;
  a.value = 7;
  b.value = 13;
  c.value = 17;
  d.value = 19;

  IList<IntNode> prime_list;

  prime_list.push_back(&a);
  prime_list.push_back(&b);
  prime_list.push_back(&c);
  prime_list.push_back(&d);

  IList<IntNode>::iterator it = prime_list.begin();
  ++it; ++it;
  it = prime_list.erase(it);

  ASSERT_TRUE(3 == prime_list.size());
  ASSERT_TRUE(7 == prime_list.front().value);
  ASSERT_TRUE(19 == prime_list.back().value);
  ASSERT_TRUE(19 == it->value);
  --it;
  ASSERT_TRUE(13 == it->value);
}

PAT_C( IListTest, constant_iterator_test)
{
  IntNode a;
  IntNode b;
  IntNode c;
  IntNode d;
  a.value = 7;
  b.value = 13;
  c.value = 17;
  d.value = 19;

  IList<IntNode> prime_list;

  prime_list.push_back(&a);
  prime_list.push_back(&b);
  prime_list.push_back(&c);
  prime_list.push_back(&d);

  IList<IntNode>::const_iterator it =
                      const_cast<const IList<IntNode>* >(&prime_list)->begin();
  ++it; ++it;

  ASSERT_TRUE(4 == prime_list.size());
  ASSERT_TRUE(7 == prime_list.front().value);
  ASSERT_TRUE(19 == prime_list.back().value);
  ASSERT_TRUE(17 == it->value);
  --it;
  ASSERT_TRUE(13 == it->value);
}

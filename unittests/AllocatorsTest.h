//===- AllocatorsTest.h ---------------------------------------------------===//
//
//                             The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_ALLOCATORS_TEST_H
#define BOLD_ALLOCATORS_TEST_H
#include <pat/pat.h>

namespace bold {

class Allocators;

namespace test {

/** \class Allocators
 *  \brief Testcases for all kinds of allocators.
 */
class AllocatorsTest : public pat::Test
{
public:
  // Constructor can do set-up work for all test here.
  AllocatorsTest();

  // Destructor can do clean-up work that doesn't throw exceptions here.
  virtual ~AllocatorsTest();

  // SetUp() will be called immediately before each test.
  virtual void SetUp();

  // TearDown() will be called immediately after each test.
  virtual void TearDown();
};

} // namespace of test
} // namespace of bold

#endif

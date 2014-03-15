//===- RopeTest.h ---------------------------------------------------------===//
//
//                             The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_ROPE_TEST_H
#define BOLD_ROPE_TEST_H
#include <pat/pat.h>

namespace bold {

class Rope;

namespace test {

/** \class Rope
 *  \brief Test cases for Rope.
 */
class RopeTest : public pat::Test
{
public:
  // Constructor can do set-up work for all test here.
  RopeTest();

  // Destructor can do clean-up work that doesn't throw exceptions here.
  virtual ~RopeTest();

  // SetUp() will be called immediately before each test.
  virtual void SetUp();

  // TearDown() will be called immediately after each test.
  virtual void TearDown();
};

} // namespace of test
} // namespace of bold

#endif

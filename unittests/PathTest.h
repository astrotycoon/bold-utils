//===- PathTest.h ---------------------------------------------------------===//
//
//                             The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_PATH_TEST_H
#define BOLD_PATH_TEST_H
#include <pat/pat.h>

namespace bold {

class Path;

namespace test {

/** \class PathTest
 *  \brief a testcase for mcld::Path and its non-member funtions.
 */
class PathTest : public pat::Test
{
public:
  // Constructor can do set-up work for all test here.
  PathTest();

  // Destructor can do clean-up work that doesn't throw exceptions here.
  virtual ~PathTest();

  // SetUp() will be called immediately before each test.
  virtual void SetUp();

  // TearDown() will be called immediately after each test.
  virtual void TearDown();

protected:
  bold::Path* m_pTestee;
};

} // namespace of test
} // namespace of bold

#endif

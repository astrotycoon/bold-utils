//===- OFStreamTest.h -----------------------------------------------------===//
//
//                             The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_OFSTREAM_TEST_H
#define BOLD_OFSTREAM_TEST_H
#include <pat/pat.h>

namespace bold {
namespace test {

/** \class OFStream
 *  \brief 
 */
class OFStreamTest : public pat::Test
{
public:
  // Constructor can do set-up work for all test here.
  OFStreamTest();

  // Destructor can do clean-up work that doesn't throw exceptions here.
  virtual ~OFStreamTest();

  // SetUp() will be called immediately before each test.
  virtual void SetUp();

  // TearDown() will be called immediately after each test.
  virtual void TearDown();
};

} // namespace of test
} // namespace of bold

#endif

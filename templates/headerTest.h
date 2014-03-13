//===- headerTest.h -------------------------------------------------------===//
//
//
//                            The Bold Project
//
// This file is distributed under the New BSD License. 
// See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_${CLASS_NAME}_TEST_H
#define BOLD_${CLASS_NAME}_TEST_H
#ifdef ENABLE_UNITTEST
#include <pat/pat.h>
#endif

namespace bold {

class ${class_name};

namespace test {

/** \class ${class_name}
 *  \brief ${brief}
 */
class ${class_name}Test : public pat::Test
{
public:
  // Constructor can do set-up work for all test here.
  ${class_name}Test();

  // Destructor can do clean-up work that doesn't throw exceptions here.
  virtual ~${class_name}Test();

  // SetUp() will be called immediately before each test.
  virtual void SetUp();

  // TearDown() will be called immediately after each test.
  virtual void TearDown();
};

} // namespace of test
} // namespace of bold

#endif

//===- FourpleTest.cpp ----------------------------------------------------===//
//
//                             The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include "FourpleTest.h"
#include <bold/Language/Fourple.h>

using namespace bold;
using namespace bold::test;

//===----------------------------------------------------------------------===//
// Fourple
//===----------------------------------------------------------------------===//
// Constructor can do set-up work for all test here.
FourpleTest::FourpleTest()
{
}

// Destructor can do clean-up work that doesn't throw exceptions here.
FourpleTest::~FourpleTest()
{
}

// SetUp() will be called immediately before each test.
void FourpleTest::SetUp()
{
}

// TearDown() will be called immediately after each test.
void FourpleTest::TearDown()
{
}

//===----------------------------------------------------------------------===//
// Testcases
//===----------------------------------------------------------------------===//
PAT_C( FourpleTest, empty )
{
  Fourple fourple;
  ASSERT_TRUE(Fourple::UnknownArch == fourple.getArch());
  ASSERT_TRUE(Fourple::UnknownArchVendor == fourple.getArchVendor());
  ASSERT_TRUE(Fourple::UnknownOS == fourple.getOS());
  ASSERT_TRUE(Fourple::UnknownEnvironment == fourple.getEnvironment());
  ASSERT_TRUE(Fourple::UnknownTool == fourple.getTool());
  ASSERT_TRUE(Fourple::UnknownToolVendor == fourple.getToolVendor());
  ASSERT_TRUE(fourple.getToolVersion().empty());
}

PAT_C( FourpleTest, linaro_arm)
{
  Fourple fourple("arm-none-linux-gnueabihf-gcc-4.8.2-linaro");

  ASSERT_TRUE(Fourple::arm == fourple.getArch());
  ASSERT_TRUE(Fourple::UnknownArchVendor == fourple.getArchVendor());
  ASSERT_TRUE(Fourple::Linux == fourple.getOS());
  ASSERT_TRUE(Fourple::GNUEABIHF == fourple.getEnvironment());
  ASSERT_TRUE(Fourple::CC == fourple.getTool());
  ASSERT_TRUE(Fourple::Linaro == fourple.getToolVendor());
  ASSERT_TRUE(0 == fourple.getToolVersion().compare("4.8.2"));
}

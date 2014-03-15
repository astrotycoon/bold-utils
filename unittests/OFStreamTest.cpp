//===- OFStreamTest.cpp ---------------------------------------------------===//
//
//                             The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include "OFStreamTest.h"
#include <bold/Support/IOStream.h>
#include <bold/Support/OFStream.h>
#include <bold/Support/Path.h>

using namespace bold;
using namespace bold::test;

//===----------------------------------------------------------------------===//
// OFStream
//===----------------------------------------------------------------------===//
// Constructor can do set-up work for all test here.
OFStreamTest::OFStreamTest()
{
}

// Destructor can do clean-up work that doesn't throw exceptions here.
OFStreamTest::~OFStreamTest()
{
}

// SetUp() will be called immediately before each test.
void OFStreamTest::SetUp()
{
}

// TearDown() will be called immediately after each test.
void OFStreamTest::TearDown()
{
}

//===----------------------------------------------------------------------===//
// Testcases
//===----------------------------------------------------------------------===//
PAT_C(OFStreamTest, open_file) {
  bold::Path path(TOPDIR);
  path.append("/tools/bold/unittests/data/file1.txt");

  bold::OFStream ofs;
  ofs.open(path.c_str());

  ASSERT_TRUE(ofs.is_open());

  ofs << "Skymizer Inc." << std::endl;
  ofs.close();
}

//===- implTest.cpp -------------------------------------------------------===//
//
//                            The Bold Project
//
// This file is distributed under the New BSD License. 
// See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include "${class_name}Test.h"
#include <bold/${deployment}/${class_name}.h>

using namespace bold;
using namespace bold::test;

//===----------------------------------------------------------------------===//
// ${class_name}
//===----------------------------------------------------------------------===//
// Constructor can do set-up work for all test here.
${class_name}Test::${class_name}Test()
{
}

// Destructor can do clean-up work that doesn't throw exceptions here.
${class_name}Test::~${class_name}Test()
{
}

// SetUp() will be called immediately before each test.
void ${class_name}Test::SetUp()
{
}

// TearDown() will be called immediately after each test.
void ${class_name}Test::TearDown()
{
}

//===----------------------------------------------------------------------===//
// Testcases
//===----------------------------------------------------------------------===//
PAT_C( ${class_name}Test, empty ) {
  // Write you exercise here
}

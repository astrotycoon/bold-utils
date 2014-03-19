//===- main.cpp -----------------------------------------------------------===//
//
//                            The Bold Team
//
// This file is distributed under the New BSD License. 
// See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include <pat/pat.h>

int unit_test( int argc, char* argv[] )
{
  pat::Test::Initialize(&argc, argv);
  pat::Test::RunAll();
  return 0;
}

int main(int argc, char* argv[])
{
   return unit_test( argc, argv );
}

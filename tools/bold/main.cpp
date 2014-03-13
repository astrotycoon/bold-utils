//===- main.cpp -----------------------------------------------------------===//
//
//                            The Bold Team
//
// This file is distributed under the New BSD License. 
// See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include <bold/Config/SkySettings.h>
#include <bold/Support/ManagedStatic.h>
#include <bold/Support/MsgHandling.h>
#include <bold/Support/TextDiagnosticPrinter.h>
#ifdef ENABLE_UNITTEST
#include <pat/pat.h>

int unit_test( int argc, char* argv[] )
{
  pat::Test::Initialize(&argc, argv);
  pat::Test::RunAll();
  return 0;
}

#endif

int main(int argc, char* argv[])
{
  bold::Shutdown shutdown;

  bold::SkySettings settings;

  bold::MsgHandling msg_handling(settings);

#ifdef ENABLE_UNITTEST
   return unit_test( argc, argv );
#endif
  return 0;
}


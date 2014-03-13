//===- FileSystem.cpp -----------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include <bold/Support/FileSystem.h>
#include <bold/Support/Path.h>
#include <bold/Config/Config.h>
// Include the truly platform-specific parts. 
#if defined(BOLD_ON_UNIX)
#include "Unix/FileSystem.inc"
#endif
#if defined(BOLD_ON_WIN32)
#include "Windows/FileSystem.inc"
#endif
#if defined(BOLD_ON_DRAGON)
#include "Dragon/FileSystem.inc"
#endif

//===----------------------------------------------------------------------===//
// FileSystem
//===----------------------------------------------------------------------===//
bool bold::exists(const Path &pPath)
{
  FileStatus file_status;
  status(pPath, file_status);

  return (file_status.type() != FileStatus::kError) &&
         (file_status.type() != FileStatus::kFileNotFound);
}

bool bold::is_directory(const Path &pPath)
{
  FileStatus file_status;
  status(pPath, file_status);
  return (file_status.type() == FileStatus::kDirectoryFile);
}

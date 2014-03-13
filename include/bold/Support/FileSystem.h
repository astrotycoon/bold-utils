//===- FileSystem.h -------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_SUPPORT_FILESYSTEM_H
#define BOLD_SUPPORT_FILESYSTEM_H

namespace bold {

class Path;

//===----------------------------------------------------------------------===//
// FileStatus
//===----------------------------------------------------------------------===//
class FileStatus
{
public:
  enum Type {
   kError,
   kStatusUnknown = kError,
   kFileNotFound,
   kRegularFile,
   kDirectoryFile,
   kSymlinkFile,
   kBlockFile,
   kCharacterFile,
   kFifoFile,
   kSocketFile,
   kReparseFile,
   kTypeUnknown,
   kStatusKnown,
   kIsSymLink
  };

public:
  FileStatus()
    : m_Value(kStatusUnknown) {}

  explicit FileStatus(Type pType)
    : m_Value(pType) {}

  void setType(Type pType)   { m_Value = pType; }

  void setSize(unsigned int pSize) { m_Size = pSize; }

  Type type() const   { return m_Value; }

  // the size of file, in bytes.
  unsigned int size() const { return m_Size; }

private:
  Type m_Value;
  unsigned int m_Size;
};

inline bool operator==(const FileStatus& rhs, const FileStatus& lhs)
{
  return rhs.type() == lhs.type();
}

inline bool operator!=(const FileStatus& rhs, const FileStatus& lhs)
{
  return !(rhs == lhs);
}

/// Checks whether \pPath exists or not.
bool exists(const Path &pPath);

/// Checks if \pPath is a directory.
bool is_directory(const Path &pPath);

/// Checks the status of the \ref pPathName.
/// @param [in]  pPathName   the path name.
/// @param [out] pFileStatus the result of status.
void status(const Path& pPathName, FileStatus& pFileStatus);

/// Checks the status of the \ref pFD file descriptor.
/// @param [in]  pFD   the file descript
/// @param [out] pFileStatus the result of status.
void status(int pFD, FileStatus& pFileStatus);

} // namespace of bold

#endif


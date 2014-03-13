//===- IOStream.cpp -------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include <bold/Support/IOStream.h>
#include <bold/Support/OFStream.h>
#include <bold/Config/Config.h>

#if defined(HAVE_UNISTD_H)
# include <unistd.h>
#endif
#if defined(HAVE_FCNTL_H)
# include <fcntl.h>
#endif
#if defined(HAVE_SYS_UIO_H) && defined(HAVE_WRITEV)
#  include <sys/uio.h>
#endif

#if defined(__CYGWIN__)
#include <io.h>
#endif

#if defined(_MSC_VER)
#include <io.h>
#include <fcntl.h>
#ifndef STDIN_FILENO
# define STDIN_FILENO 0
#endif
#ifndef STDOUT_FILENO
# define STDOUT_FILENO 1
#endif
#ifndef STDERR_FILENO
# define STDERR_FILENO 2
#endif
#endif

//===----------------------------------------------------------------------===//
// outs(), errs() and nulls()
//===----------------------------------------------------------------------===//
/// outs() - This returns a reference to a OStream for standard output.
/// Use it like: outs() << "foo" << "bar";
bold::OStream& bold::outs()
{
  static OFStream OS(STDOUT_FILENO);
  return OS;
}

/// errs() - This returns a reference to a OStream for standard error.
/// Use it like: errs() << "foo" << "bar";
bold::OStream& bold::errs()
{
  static OFStream OS(STDERR_FILENO);
  return OS;
}


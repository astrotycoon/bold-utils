//===- IOStream.h ---------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_SUPPORT_IOSTREAM_H
#define BOLD_SUPPORT_IOSTREAM_H
#include <bold/Support/OStream.h>

namespace bold {

/// outs() - This returns a reference to a OStream for standard output.
/// Use it like: outs() << "foo" << "bar";
OStream& outs();

/// errs() - This returns a reference to a OStream for standard error.
/// Use it like: errs() << "foo" << "bar";
OStream& errs();

} // namespace of bold

#endif


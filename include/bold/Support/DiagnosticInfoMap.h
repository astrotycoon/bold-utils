//===- DiagnosticInfoMap.h ------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_SUPPORT_DIAGNOSTIC_INFOMAP_H
#define BOLD_SUPPORT_DIAGNOSTIC_INFOMAP_H
#include <bold/ADT/StringRef.h>

namespace bold {

enum ID {
#define DIAG(ENUM, CLASS, MSG) ENUM,
#include "bold/Support/DiagCommonKinds.inc"
#undef DIAG
  NUM_OF_BUILDIN_DIAGNOSTIC_INFO
};

namespace diagnostic {

/** \class InfoMap
 *  \brief InfoMap caches run-time information of Diagnostic.
 */
class InfoMap
{
public:
  StringRef description(unsigned int pID) const;
};

} // namespace of diagnostic
} // namespace of bold

#endif


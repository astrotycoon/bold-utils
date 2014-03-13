//===- DiagnosticInfoMap.cpp ----------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include <bold/Support/DiagnosticInfoMap.h>
#include <bold/Support/DiagnosticEngine.h>
#include <bold/Support/DataTypes.h>
#include <cassert>

using namespace bold;

namespace bold {
namespace diagnostic {

struct DiagStaticInfo
{
  uint16_t         id;
  Engine::Severity severity;
  uint16_t         desc_len;
  const char*      desc_str;
};

static bool operator<(const DiagStaticInfo& pLHS, const DiagStaticInfo& pRHS)
{
  return (pLHS.id < pRHS.id);
}

static const DiagStaticInfo DiagInfo[] = {
#define DIAG(ENUM, CLASS, MSG) { ::ENUM, CLASS, sizeof(MSG)-1, MSG },
#include "bold/Support/DiagCommonKinds.inc"
#undef DIAG
  { 0, Engine::None, 0, 0 }
};

// DiagStaticInfoSize - the number of entries in the DiagInfo
static const unsigned int DiagInfoSize = sizeof(DiagInfo)/sizeof(DiagInfo[0])-1;

} // namespace of diagnostic
} // namespace of bold

//===----------------------------------------------------------------------===//
// DiagnosticInfoMap
//===----------------------------------------------------------------------===//
StringRef diagnostic::InfoMap::description(unsigned int pID) const
{
  DiagStaticInfo key = { pID, Engine::None, 0, 0 };
  const DiagStaticInfo* info =
                       std::lower_bound(DiagInfo, DiagInfo + DiagInfoSize, key);

  assert((DiagInfo + DiagInfoSize) != info &&
         info->id == pID &&
         "cannot get correct information by id!");

  return StringRef(info->desc_str, info->desc_len);
}

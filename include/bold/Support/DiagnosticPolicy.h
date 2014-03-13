//===- DiagnosticPolicy.h -------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_SUPPORT_DIAGNOSTIC_POLICY_H
#define BOLD_SUPPORT_DIAGNOSTIC_POLICY_H

namespace bold {

class SkySettings;

namespace diagnostic {

class Diagnostic;

/** \class DefaultPolicy
 *  \brief DefaultyPolicy defines the default policy to revise the severity
 *   of diagnostic result.
 */
class DefaultPolicy
{
public:
  static bool process(const SkySettings& pSettings, Diagnostic& pDiag);
};

} // namespace of diagnostic
} // namespace of bold

#endif


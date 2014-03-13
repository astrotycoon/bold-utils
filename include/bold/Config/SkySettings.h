//===- SkySettings.h ------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_CONFIG_SKYSETTINGS_H
#define BOLD_CONFIG_SKYSETTINGS_H
#include <bold/Config/GeneralOptions.h>

namespace bold {

/** \class SkySettings
 *  \brief SkySettings collects the preference of bold.
 */
class SkySettings
{
public:
  const GeneralOptions& options() const { return m_GeneralOptions; }
  GeneralOptions&       options()       { return m_GeneralOptions; }
  
private:
  GeneralOptions m_GeneralOptions;
};

} // namespace of bold

#endif


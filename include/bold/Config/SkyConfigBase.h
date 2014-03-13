//===- SkyConfigBase.h ----------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_CONFIG_SKYCONFIG_BASE_H
#define BOLD_CONFIG_SKYCONFIG_BASE_H
#include <bold/ADT/StringRef.h>
#include <bold/ADT/IListNode.h>

namespace bold {

/** \class SkyConfigBase
 *  \brief Skymizer Configuration Management abstract base class.
 */
class SkyConfigBase
{
public:
  virtual ~SkyConfigBase();

  /// @name Group Operators
  /// @{
  virtual StringList groupList() const = 0;

  void setGroup(StringRef pGroup);

  bool hasGroup(StringRef pGroup) const;

  /// deleteGroup - Deletes a configuration entry group.
  /// If the group is not empty and pDeep is false, nothing gets deleted
  bool deleteGroup(StringRef pGroup, bool pDeep = true);
  /// @}
};

} // namespace of bold

#endif


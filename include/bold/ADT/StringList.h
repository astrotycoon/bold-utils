//===- StringList.h -------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_ADT_STRING_LIST_H
#define BOLD_ADT_STRING_LIST_H
#include <bold/ADT/StringRef.h>
#include <bold/Support/MemoryPool.h>
#include <string>

namespace bold {

/** \class StringList
 *  \brief StringList is a list of StringRef.
 */
class StringList : public MemoryPool<StringRef, 64>
{
public:
  typedef MemoryPool<StringRef, 64> BaseType;

public:
  inline StringList() { }

  inline StringList(const StringList& pCopy) : BaseType(pCopy) { }

  inline explicit StringList(StringRef pCopy) { append(pCopy); }

  StringList& append(StringRef& pStr);
  StringList& append(const std::string& pStr);
  StringList& append(const char* pStr);

  StringList& operator<<(StringRef& pStr);
  StringList& operator<<(const std::string& pStr);

private:
  /// hide allocate symbol
  using BaseType::allocate;

  /// deallocate - release a StringRef.
  /// This does not really delete StringRef. Instead, it just turn the
  /// StringRef to empty.
  void deallocate(BaseType::pointer pPtr);
};

} // namespace of bold

#endif


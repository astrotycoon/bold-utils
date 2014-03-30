//===- StringList.h -------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_ADT_STRING_LIST_H
#define BOLD_ADT_STRING_LIST_H
#include <bold/ADT/StringRef.h>
#include <bold/Config/Config.h>
#include <bold/Support/MemoryPool.h>
#include <string>

namespace bold {

/** \class StringList
 *  \brief StringList is a list of StringRef.
 */
class StringList : public MemoryPool<StringRef, BOLD_NUM_OF_STR>
{
public:
  typedef MemoryPool<StringRef, BOLD_NUM_OF_STR> BaseType;

public:
  inline StringList() { }

  inline StringList(const StringList& pCopy);

  inline explicit StringList(StringRef pCopy) { append(pCopy); }

  StringList& operator=(const StringList& pCopy);

  StringList& append(const StringRef& pStr);

  StringList& append(const std::string& pStr);

  StringList& append(const char* pStr);

  StringList& operator<<(StringRef& pStr);

  StringList& operator<<(const std::string& pStr);

private:
  /// hide allocate symbol
  using BaseType::allocate;

  /// hide construct symbol
  using BaseType::construct;

  /// deallocate - release a StringRef.
  /// This does not really delete StringRef. Instead, it just turn the
  /// StringRef to empty.
  void deallocate(BaseType::pointer pPtr);

  /// destruct - destruct a StringRef
  void destruct(BaseType::pointer pPtr);
};

} // namespace of bold

#endif


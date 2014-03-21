//===- StringList.cpp -----------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include <bold/ADT/StringList.h>

using namespace bold;

//===----------------------------------------------------------------------===//
// StringList
//===----------------------------------------------------------------------===//
StringList& StringList::append(const StringRef& pStr)
{
  return *this;
}

StringList& StringList::append(const std::string& pStr)
{
  return *this;
}

StringList& StringList::append(const char* pStr)
{
  return *this;
}

StringList& StringList::operator<<(StringRef& pStr)
{
  return *this;
}

StringList& StringList::operator<<(const std::string& pStr)
{
  return *this;
}

/// deallocate - release a StringRef.
/// This does not really delete StringRef. Instead, it just turn the
/// StringRef to empty.
void StringList::deallocate(BaseType::pointer pPtr)
{
  // reset pointer and length
  BaseType::getSentinel()->countOut();
  destruct(pPtr);
  pPtr = NULL;
}

void StringList::destruct(BaseType::pointer pPtr)
{
  pPtr->~StringRef();
}

//===- OwningPtr.h --------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_ADT_OWNING_PTR_H
#define BOLD_ADT_OWNING_PTR_H
#include <bold/ADT/Uncopyable.h>
#include <bold/Support/DataTypes.h>
#include <cassert>

namespace bold {

/** \class OwningPtr
 *  \brief OwningPtr is a smart pointer that usually used to transfer the life
 *  cycle of a object.
 */
template<class T>
class OwningPtr : private Uncopyable
{
public:
  explicit OwningPtr(T* pPtr = NULL) : m_pPtr(pPtr) { }

  ~OwningPtr() { delete m_pPtr; }

  /// give - Reset the owning pointer to null and return its pointer.
  /// This does not delete the pointer before returning it.
  T* give() {
    T* tmp = m_pPtr;
    m_pPtr = NULL;
    return tmp;
  }

  T& operator*() const {
    assert(NULL != m_pPtr && "Cannot dereference null pointer");
    return *m_pPtr;
  }

  T* operator->() const { return m_pPtr; }

  T* get() const { return m_pPtr; }

private:
  T* m_pPtr;
};

} // namespace bold

#endif

//===- MemoryAllocator.h --------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_ADT_MEMORY_ALLOCATOR_H
#define BOLD_ADT_MEMORY_ALLOCATOR_H
#include <bold/ADT/IList.h>
#include <bold/Support/Slab.h>

namespace bold {

/** \class MemoryAllocator
 *  \brief MemoryAllocator allocates numerous small objects.
 *
 *  MemoryAllocator is a memory pool allocator. It preallocates a number
 *  of memory blocks to avoid the system from memory fragmentation.
 *
 *  MemoryAllocator doesn't provide deallocator. Users should design his own
 *  deallocators. That is because the implementation of deallocators need
 *  careful consideration of trade-offs between speed and memory usage, and
 *  we think users should design one for themselves.
 */
template<typename DataType, unsigned int Amount>
class MemoryAllocator : public IListBase
{
public:
  typedef DataType value_type;
  typedef DataType* pointer;
  typedef DataType& reference;

  typedef Slab<DataType, Amount> slab;

  template<typename NewDataType>
  struct rebind {
    typedef MemoryAllocator<NewDataType, Amount> other;
  };

public:
  MemoryAllocator();

  virtual ~MemoryAllocator() { }

  /// allocate - to allocate one datum.
  pointer allocate();

  /// allocate - to allocate multiple data
  pointer allocate(size_type pN);

  /// construct - to construct an element object on the location of pointed by
  /// pPtr
  void construct(pointer pPtr, reference pVal);

  /// overflow - true if number of data being allocated is more than
  /// size of a block
  bool isOverflow() const { return m_bOverflow; }

  /// setOverflow - set overflow flag
  void setOverflow(bool pEnable = true) { m_bOverflow = pEnable; }

protected:
  bool m_bOverflow : 1;
};

//===----------------------------------------------------------------------===//
// MemoryAllocator
//===----------------------------------------------------------------------===//
template<typename DataType, unsigned int Amount>
MemoryAllocator<DataType, Amount>::MemoryAllocator()
  : IListBase(), m_bOverflow(false) {
}

template<typename DataType, unsigned int Amount>
typename MemoryAllocator<DataType, Amount>::pointer
MemoryAllocator<DataType, Amount>::allocate()
{
  unsigned int index = size() % Amount;
  doCountIn();
  if (0 == index) { // slab full
    slab* new_slab = new slab();
    doInsert(*getSentinel(), *new_slab);
    return new_slab->data;
  }

  return static_cast<slab*>(IListBase::getSentinel()->getPrev())->data + index;
}

template<typename DataType, unsigned int Amount>
typename MemoryAllocator<DataType, Amount>::pointer
MemoryAllocator<DataType, Amount>::allocate(size_type pN)
{
  assert(pN <= Amount && "allocate too many data");

  // lazy intialization
  if (empty()) {
    slab* new_slab = new slab();
    doInsert(*getSentinel(), *new_slab);
    doCountIn(pN);
    return new_slab->data;
  }

  // Overflow: can not allocate in the same slab
  if (pN > Amount - size() %Amount) {
    slab* new_slab = new slab();
    setOverflow(true);
    doInsert(*getSentinel(), *new_slab);
    doCountIn(pN + Amount - size() % Amount);
    return new_slab->data;
  }

  unsigned int head = IListBase::size() % size();
  return static_cast<slab*>(IListBase::getSentinel()->getPrev())->data + head;
}

template<typename DataType, unsigned int Amount> void
MemoryAllocator<DataType, Amount>::construct(pointer pPtr, reference pVal)
{
  new (pPtr) DataType(pVal);
}

} // namespace of bold

#endif

//===- MemoryPool.h -------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_ADT_MEMORY_POOL_H
#define BOLD_ADT_MEMORY_POOL_H
#include <bold/ADT/TypeTraits.h>
#include <bold/ADT/IList.h>
#include <bold/Support/Slab.h>
#include <bold/Support/SlabIterator.h>

#include <cassert>
#include <iterator>

namespace bold {

/** \class MemoryAllocator
 *  \brief MemoryAllocator allocates numerous small objects.
 *
 *  MemoryAllocator is a memory pool allocator. It preallocates a number
 *  of memory blocks to avoid the system from memory fragmentation.
 *
 *  MemoryAllocator doesn't provide deallocator. Users should design his own
 *  deallocators. That is because the implementation of deallocators need
 *  very careful consideration of trade-offs between speed and memory usage.
 */
template<typename DataType, unsigned int Amount>
class MemoryAllocator : public IListBase
{
public:
  typedef DataType value_type;
  typedef const DataType* const_pointer;
  typedef DataType* pointer;
  typedef const DataType& const_reference;
  typedef DataType& reference;

  typedef Slab<DataType, Amount> slab_type;

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
  void construct(pointer pPtr, const_reference pVal);

protected:
  void AppendSlab(IListNodeBase& pSlab);

  void PrependSlab(IListNodeBase& pSlab);

};

/** \class MemoryPool
 *  \brief MemoryPool provides a factory that guaratees to remove all allocated
 *  data.
 *
 *  In particular, MemoryPool just keeps allocating memory and never deletes it
 *  until an entire block is dead. This makes allocation fast, but must be used
 *  merely when the trade-off is considered.
 *
 *  The concept of MemoryPool is a simple implementation of boost::pool.
 *
 *  This class obeys allocator requirements of C++ standard.
 *  <a href="http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3690.pdf">
 *  17.6.3.5 Allocator requirements, C++ 11 n3690</a>
 *
 *  @tparam DataType - the type of elements.
 *  @tparam Amount   - the number of elements in a slab.
 */
template<typename DataType, unsigned int Amount>
class MemoryPool : public MemoryAllocator<DataType, Amount>
{
public:
  typedef MemoryAllocator<DataType, Amount> Alloc;
  typedef typename Alloc::value_type value_type;
  typedef typename Alloc::const_pointer const_pointer;
  typedef typename Alloc::pointer pointer;
  typedef typename Alloc::const_reference const_reference;
  typedef typename Alloc::reference reference;
  typedef typename Alloc::slab_type slab_type;

  typedef SlabIterator<MemoryPool,
                       NonConstTraits<DataType> > iterator;
  typedef SlabIterator<MemoryPool,
                       ConstTraits<DataType> > const_iterator;

  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::reverse_iterator<iterator>       reverse_iterator;

  template<typename NewDataType>
  struct rebind {
    typedef MemoryPool<NewDataType, Amount> other;
  };

public:
  MemoryPool();

  MemoryPool(const MemoryPool& pCopy);

  MemoryPool& operator=(const MemoryPool& pCopy);

  virtual ~MemoryPool();

  const_iterator begin() const;
  iterator       begin();
  const_iterator end()   const;
  iterator       end();

  const_reverse_iterator rbegin() const;
  reverse_iterator       rbegin();
  const_reverse_iterator rend()   const;
  reverse_iterator       rend();

  const_reference front() const;
  reference       front();
  const_reference back() const;
  reference       back();

  void clear();

  using Alloc::empty;
  using Alloc::size;
  using Alloc::max_size;

protected:
  friend class SlabIterator<MemoryPool, NonConstTraits<DataType> >;
  friend class SlabIterator<MemoryPool, ConstTraits<DataType> >;

protected:
  using Alloc::head;
  using Alloc::getSentinel;

};

//===----------------------------------------------------------------------===//
// MemoryAllocator
//===----------------------------------------------------------------------===//
template<typename DataType, unsigned int Amount>
MemoryAllocator<DataType, Amount>::MemoryAllocator()
  : IListBase() {
}

template<typename DataType, unsigned int Amount>
typename MemoryAllocator<DataType, Amount>::pointer
MemoryAllocator<DataType, Amount>::allocate()
{
  unsigned int index = size() % Amount;
  IListBase::getSentinel()->countIn();
  if (0 == index) { // slab full
    slab_type* new_slab = new slab_type();
    AppendSlab(*new_slab);
    return new_slab->data;
  }

  return static_cast<slab_type*>(IListBase::getSentinel()->getPrev())->data + index;
}

template<typename DataType, unsigned int Amount>
typename MemoryAllocator<DataType, Amount>::pointer
MemoryAllocator<DataType, Amount>::allocate(size_type pN)
{
  assert(pN <= Amount && "allocate too many data");

  // lazy intialization
  if (IListBase::empty()) {
    slab_type* new_slab = new slab_type();
    AppendSlab(*new_slab);
    IListBase::getSentinel()->countIn(pN);
    return new_slab->data;
  }

  // can not allocate in the same slab
  if (Amount - pN < IListBase::size() %Amount) {
    slab_type* new_slab = new slab_type();
    AppendSlab(*new_slab);
    IListBase::getSentinel()->countIn(pN + Amount - size()%Amount);
    return new_slab->data;
  }

  unsigned int head = IListBase::getSentinel()->size() % size();
  return static_cast<slab_type*>(IListBase::getSentinel()->getPrev())->data + head;
}

template<typename DataType, unsigned int Amount> void
MemoryAllocator<DataType, Amount>::construct(pointer pPtr, const_reference pVal)
{
  new (pPtr) DataType(pVal);
}

template<typename DataType, unsigned int Amount>
void MemoryAllocator<DataType, Amount>::AppendSlab(IListNodeBase& pValue)
{
  doInsert(*IListBase::getSentinel(), pValue);
}

template<typename DataType, unsigned int Amount>
void MemoryAllocator<DataType, Amount>::PrependSlab(IListNodeBase& pValue)
{
  doInsert(*IListBase::head(), pValue);
}

//===----------------------------------------------------------------------===//
// MemoryPool
//===----------------------------------------------------------------------===//
template<typename DataType, unsigned int Amount>
MemoryPool<DataType, Amount>::MemoryPool()
  : Alloc() {
}

template<typename DataType, unsigned int Amount>
MemoryPool<DataType, Amount>::MemoryPool(const MemoryPool& pCopy)
  : Alloc() {
  const_iterator data, dEnd = pCopy.end();
  for (data = pCopy.begin(); data != dEnd; ++data) {
    DataType* new_data = Alloc::allocate();
    Alloc::construct(new_data, *data);
  }
}

template<typename DataType, unsigned int Amount>
MemoryPool<DataType, Amount>&
MemoryPool<DataType, Amount>::operator=(const MemoryPool& pCopy)
{
  clear();

  const_iterator data, dEnd = pCopy.end();
  for (data = pCopy.begin(); data != dEnd; ++data) {
    DataType* new_data = Alloc::allocate();
    Alloc::construct(new_data, *data);
  }

  return *this;
}

template<typename DataType, unsigned int Amount>
MemoryPool<DataType, Amount>::~MemoryPool()
{
  clear();
}

template<typename DataType, unsigned int Amount>
typename MemoryPool<DataType, Amount>::const_iterator
MemoryPool<DataType, Amount>::begin() const
{
  IListNodeBase* node = const_cast<IListNodeBase*>(Alloc::head());
  return const_iterator(*Alloc::getSentinel(), node, 0);
}

template<typename DataType, unsigned int Amount>
typename MemoryPool<DataType, Amount>::iterator
MemoryPool<DataType, Amount>::begin()
{
  return iterator(*Alloc::getSentinel(), Alloc::head(), 0);
}

template<typename DataType, unsigned int Amount>
typename MemoryPool<DataType, Amount>::const_iterator
MemoryPool<DataType, Amount>::end() const
{
  typename Alloc::Sentinel* node =
                    const_cast<typename Alloc::Sentinel*>(Alloc::getSentinel());
  return const_iterator(*Alloc::getSentinel(), node, -1);
}

template<typename DataType, unsigned int Amount>
typename MemoryPool<DataType, Amount>::iterator
MemoryPool<DataType, Amount>::end()
{
  return iterator(*Alloc::getSentinel(), Alloc::getSentinel(), -1);
}

template<typename DataType, unsigned int Amount>
typename MemoryPool<DataType, Amount>::const_reverse_iterator
MemoryPool<DataType, Amount>::rbegin() const
{
  return const_reverse_iterator(end());
}

template<typename DataType, unsigned int Amount>
typename MemoryPool<DataType, Amount>::reverse_iterator
MemoryPool<DataType, Amount>::rbegin()
{
  return reverse_iterator(end());
}

template<typename DataType, unsigned int Amount>
typename MemoryPool<DataType, Amount>::const_reverse_iterator
MemoryPool<DataType, Amount>::rend() const
{
  return const_reverse_iterator(begin());
}

template<typename DataType, unsigned int Amount>
typename MemoryPool<DataType, Amount>::reverse_iterator
MemoryPool<DataType, Amount>::rend()
{
  return reverse_iterator(begin());
}

template<typename DataType, unsigned int Amount>
typename MemoryPool<DataType, Amount>::const_reference
MemoryPool<DataType, Amount>::front() const
{
  assert(!empty() && "Calling front() on empty memory pool");
  return static_cast<slab_type*>(Alloc::head())->data[0];
}

template<typename DataType, unsigned int Amount>
typename MemoryPool<DataType, Amount>::reference
MemoryPool<DataType, Amount>::front()
{
  assert(!empty() && "Calling front() on empty memory pool");
  return static_cast<slab_type*>(Alloc::head())->data[0];
}

template<typename DataType, unsigned int Amount>
typename MemoryPool<DataType, Amount>::const_reference
MemoryPool<DataType, Amount>::back() const
{
  assert(!empty() && "Calling back() on empty memory pool");
  unsigned int back = (size()-1) % Amount;
  return static_cast<slab_type*>(Alloc::getSentinel()->getPrev())->data[back];
}

template<typename DataType, unsigned int Amount>
typename MemoryPool<DataType, Amount>::reference
MemoryPool<DataType, Amount>::back()
{
  assert(!empty() && "Calling back() on empty memory pool");
  unsigned int back = (size()-1) % Amount;
  return static_cast<slab_type*>(Alloc::getSentinel()->getPrev())->data[back];
}

template<typename DataType, unsigned int Amount>
void MemoryPool<DataType, Amount>::clear()
{
  IListNodeBase* cur = head();
  IListNodeBase* sentinel = Alloc::getSentinel();
  while (cur != sentinel) {
    IListNodeBase* next = cur->getNext();
    Alloc::doErase(*cur);
    delete cur;
    cur = next;
  }

  // The last node is sentinel. Do not delete it.
}

} // namespace of bold

#endif

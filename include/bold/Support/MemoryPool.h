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
class MemoryPool : public IListBase
{
public:
  typedef DataType value_type;
  typedef const DataType* const_pointer;
  typedef DataType* pointer;
  typedef const DataType& const_reference;
  typedef DataType& reference;

  typedef Slab<DataType, Amount> slab_type;

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

  /// allocate - to allocate one datum.
  pointer allocate();

  /// allocate - to allocate multiple data
  pointer allocate(size_type pN);

protected:
  friend class SlabIterator<MemoryPool, NonConstTraits<DataType> >;
  friend class SlabIterator<MemoryPool, ConstTraits<DataType> >;

protected:
  void appendSlab(IListNodeBase& pValue);

  void prependSlab(IListNodeBase& pValue);

};

//===----------------------------------------------------------------------===//
// MemoryPool
//===----------------------------------------------------------------------===//
template<typename DataType, unsigned int Amount>
MemoryPool<DataType, Amount>::MemoryPool()
  : IListBase() {
}

template<typename DataType, unsigned int Amount>
MemoryPool<DataType, Amount>::MemoryPool(const MemoryPool& pCopy)
  : IListBase() {
  const_iterator data, dEnd = pCopy.end();
  for (data = pCopy.begin(); data != dEnd; ++data) {
    pointer new_data = allocate();
    // copy constructor
    new (new_data) DataType(*data);
  }
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
  return const_iterator(*getSentinel(), m_pHead, 0);
}

template<typename DataType, unsigned int Amount>
typename MemoryPool<DataType, Amount>::iterator
MemoryPool<DataType, Amount>::begin()
{
  return iterator(*getSentinel(), m_pHead, 0);
}

template<typename DataType, unsigned int Amount>
typename MemoryPool<DataType, Amount>::const_iterator
MemoryPool<DataType, Amount>::end() const
{
  Sentinel* node = const_cast<Sentinel*>(getSentinel());
  return const_iterator(*getSentinel(), node, -1);
}

template<typename DataType, unsigned int Amount>
typename MemoryPool<DataType, Amount>::iterator
MemoryPool<DataType, Amount>::end()
{
  return iterator(*getSentinel(), getSentinel(), -1);
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
  return static_cast<slab_type*>(m_pHead)->data[0];
}

template<typename DataType, unsigned int Amount>
typename MemoryPool<DataType, Amount>::reference
MemoryPool<DataType, Amount>::front()
{
  assert(!empty() && "Calling front() on empty memory pool");
  return static_cast<slab_type*>(m_pHead)->data[0];
}

template<typename DataType, unsigned int Amount>
typename MemoryPool<DataType, Amount>::const_reference
MemoryPool<DataType, Amount>::back() const
{
  assert(!empty() && "Calling back() on empty memory pool");
  unsigned int back = (size()-1) % Amount;
  return static_cast<slab_type*>(getSentinel()->getPrev())->data[back];
}

template<typename DataType, unsigned int Amount>
typename MemoryPool<DataType, Amount>::reference
MemoryPool<DataType, Amount>::back()
{
  assert(!empty() && "Calling back() on empty memory pool");
  unsigned int back = (size()-1) % Amount;
  return static_cast<slab_type*>(getSentinel()->getPrev())->data[back];
}

template<typename DataType, unsigned int Amount>
void MemoryPool<DataType, Amount>::clear()
{
  IListNodeBase* cur = m_pHead;
  IListNodeBase* sentinel = getSentinel();
  while (cur != sentinel) {
    IListNodeBase* next = cur->getNext();
    delete cur;
    cur = next;
  }
}

template<typename DataType, unsigned int Amount>
typename MemoryPool<DataType, Amount>::pointer
MemoryPool<DataType, Amount>::allocate()
{
  unsigned int index = size() % Amount;
  getSentinel()->countIn();
  if (0 == index) { // slab full
    slab_type* new_slab = new slab_type();
    appendSlab(*new_slab);
    return new_slab->data;
  }

  return static_cast<slab_type*>(getSentinel()->getPrev())->data + index;
}

template<typename DataType, unsigned int Amount>
typename MemoryPool<DataType, Amount>::pointer
MemoryPool<DataType, Amount>::allocate(size_type pN)
{
  assert(pN <= Amount && "allocate too many data");

  // lazy intialization
  if (empty()) {
    slab_type* new_slab = new slab_type();
    appendSlab(*new_slab);
    getSentinel()->countIn(pN);
    return new_slab->data;
  }

  // can not allocate in the same slab
  if (Amount - pN < size() %Amount) {
    slab_type* new_slab = new slab_type();
    appendSlab(*new_slab);
    getSentinel()->countIn(pN + Amount - size()%Amount);
    return new_slab->data;
  }

  unsigned int head = getSentinel()->size() % size();
  return static_cast<slab_type*>(getSentinel()->getPrev())->data + head;
}

template<typename DataType, unsigned int Amount>
void MemoryPool<DataType, Amount>::appendSlab(IListNodeBase& pValue)
{
  doInsert(*getSentinel(), pValue);
}

template<typename DataType, unsigned int Amount>
void MemoryPool<DataType, Amount>::prependSlab(IListNodeBase& pValue)
{
  doInsert(*head(), pValue);
}

} // namespace of bold

#endif

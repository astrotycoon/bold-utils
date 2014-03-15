//===- IList.h ------------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_ADT_ILIST_H
#define BOLD_ADT_ILIST_H
#include <bold/ADT/IListIterator.h>
#include <bold/ADT/TypeTraits.h>
#include <bold/ADT/Uncopyable.h>
#include <bold/Support/DataTypes.h>
#include <iterator>
#include <algorithm>
#include <cassert>

namespace bold {

/** \class IListBase
 *  \brief IListBase provids type-independent APIs for IList.
 */
class IListBase : private Uncopyable
{
public:
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

public:
  IListBase() : m_pHead(new Sentinel()) { }

  virtual ~IListBase() { delete getSentinel(); }

  bool empty() const;

  size_type size() const;

  size_type max_size() const;

  void swap(IListBase& pOther);

protected:
  class Sentinel : public IListNodeBase
  {
  public:
    Sentinel() : IListNodeBase(this, this), m_Size(0) { }

    unsigned int size() const { return m_Size; }

    void countIn(unsigned int pN = 1) { m_Size += pN; }

    void countOut(unsigned int pN = 1) { m_Size -= pN; }

  private:
    unsigned int m_Size;
  };

protected:
  static bool isSentinel(const IListNodeBase& pNode);

  const Sentinel* getSentinel() const;
  Sentinel*       getSentinel();

  const IListNodeBase* head() const { return m_pHead; }
  IListNodeBase* head()             { return m_pHead; }

  void setHead(IListNodeBase* pHead) { m_pHead = pHead; }

  /// doInsert inserts @ref pNew at the front of @ref pWhere
  void doInsert(IListNodeBase& pWhere, IListNodeBase& pNew);

  void doErase(IListNodeBase& pWhere);

protected:
  mutable IListNodeBase* m_pHead;
};

/** \class IList
 *  \brief IList is an intrusive linked list.
 *
 *  Note that IList is unlike LLVM iplist:
 *  1) IList doesn't destroy elements.
 *  2) IList is not a factory. It doesn't produce any elements.
 *     That is, insert(), push() and erase() don't create new nodes.
 *  3) Fixed end(). (end() == end()) is always true.
 *  4) Calling begin()/end() doesn't change the state of IList.
 *
 *  IList doesn't have some functions, such as assign and resize, which
 *  requires the ability to produce NodeType. Its interface is not compatible
 *  to STL list and LLVM iplist.
 *
 *  Note that advancing end() iterator goes nowhere. The iterator still stays
 *  at end(). However, advancing rend() iterator goes to rbegin() and missing
 *  conditions may causes reverse_iterator loop infinitely.
 */
template<typename NodeType>
class IList : public IListBase 
{
public:
  typedef IListIterator<NodeType, NonConstTraits<NodeType> > iterator;
  typedef IListIterator<NodeType, ConstTraits<NodeType> >    const_iterator;

  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::reverse_iterator<iterator>       reverse_iterator;

  typedef const NodeType* const_pointer;
  typedef NodeType*       pointer;
  typedef const NodeType& const_reference;
  typedef NodeType&       reference;

public:
  IList() : IListBase() { }

  virtual ~IList() { clear(); }
  
  const_iterator begin() const { return const_iterator(head()); }
  iterator       begin()       { return iterator(head());       }
  const_iterator end()   const { return const_iterator(head()->getPrev()); }
  iterator       end()         { return iterator(head()->getPrev());       }

  const_reverse_iterator rbegin() const;
  reverse_iterator       rbegin();
  const_reverse_iterator rend()   const;
  reverse_iterator       rend();

  const_reference front() const;
  reference       front();
  const_reference back() const;
  reference       back();

  /// Insert element at beginning
  void push_front(NodeType* pValue);

  /// Delete first element
  void pop_front();

  /// Add element at the end
  void push_back(NodeType* pValue);

  /// Delete last element
  void pop_back();

  /// Insert new elements before the element at the specified position
  iterator insert(iterator pWhere, NodeType* pValue);

  iterator erase(iterator pWhere);
  iterator erase(iterator pFirst, iterator pLast);

  void clear();
};

//===----------------------------------------------------------------------===//
// IList Member Functions
//===----------------------------------------------------------------------===//
template<typename NodeType>
typename IList<NodeType>::const_reverse_iterator IList<NodeType>::rbegin() const
{
  return const_reverse_iterator(end());
}

template<typename NodeType>
typename IList<NodeType>::reverse_iterator IList<NodeType>::rbegin()
{
  return reverse_iterator(end());
}

template<typename NodeType>
typename IList<NodeType>::const_reverse_iterator IList<NodeType>::rend()   const
{
  return const_reverse_iterator(begin());
}

template<typename NodeType>
typename IList<NodeType>::reverse_iterator IList<NodeType>::rend()
{
  return reverse_iterator(begin());
}

template<typename NodeType>
typename IList<NodeType>::const_reference IList<NodeType>::front() const
{
  assert(!empty() && "Calling front() on empty list!");
  return *static_cast<const NodeType*>(head());
}

template<typename NodeType>
typename IList<NodeType>::reference IList<NodeType>::front()
{
  assert(!empty() && "Calling front() on empty list!");
  return *static_cast<NodeType*>(head());
}

template<typename NodeType>
typename IList<NodeType>::const_reference IList<NodeType>::back() const
{
  assert(!empty() && "Calling back() on empty list!");
  return *static_cast<const NodeType*>(getSentinel()->getPrev());
}

template<typename NodeType>
typename IList<NodeType>::reference IList<NodeType>::back()
{
  assert(!empty() && "Calling back() on empty list!");
  return *static_cast<NodeType*>(getSentinel()->getPrev());
}

template<typename NodeType>
void IList<NodeType>::push_front(NodeType* pValue)
{
  insert(this->begin(), pValue);
}

template<typename NodeType>
void IList<NodeType>::pop_front()
{
  assert(!empty() && "pop_front() on an empty list");
  erase(begin());
}

template<typename NodeType>
void IList<NodeType>::push_back(NodeType* pValue)
{
  insert(this->end(), pValue);
}

template<typename NodeType>
void IList<NodeType>::pop_back()
{
  assert(!empty() && "pop_back() on an empty list");
  iterator it = end();
  erase(--it);
}

template<typename NodeType> typename IList<NodeType>::iterator
IList<NodeType>::insert(iterator pWhere, NodeType* pNew)
{
  doInsert(*pWhere.getRawPtr(), *pNew);
  return iterator(pNew);
}

template<typename NodeType> typename IList<NodeType>::iterator
IList<NodeType>::erase(iterator pWhere)
{
  assert(pWhere != end() && "Cannot remove end()");
  IListNodeBase* cur = pWhere.getRawPtr();
  IListNodeBase* next = pWhere.getRawPtr()->getNext();
  doErase(*cur);
  return iterator(next);
}

template<typename NodeType>
typename IList<NodeType>::iterator
IList<NodeType>::erase(iterator pFirst, iterator pLast)
{
  while (pFirst != pLast) {
    pFirst = erase(pFirst);
  }
  return pLast;
}

template<typename NodeType>
void IList<NodeType>::clear()
{
  erase(begin(), end());
}

} // namespace of bold

#endif


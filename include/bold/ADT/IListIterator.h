//===- IListIterator.h ----------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_ADT_ILIST_ITERATOR_H
#define BOLD_ADT_ILIST_ITERATOR_H
#include <bold/ADT/IListNode.h>
#include <bold/Support/DataTypes.h>
#include <cassert>
#include <iterator>

namespace bold {

class IListIteratorBase
{
public:
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;
  typedef IListNodeBase NodeBase;

protected:
  NodeBase* m_pNodePtr;
  
public:
  IListIteratorBase();

  explicit IListIteratorBase(NodeBase* pNode);

  virtual ~IListIteratorBase() { }

  NodeBase* getRawPtr() const { return m_pNodePtr; }

protected:
  void advance();

  void retreat();
};

/** \class IListIterator
 *
 *  IListIterator is a bidirectional iterator.
 */
template<typename NodeType, typename Traits>
class IListIterator : public IListIteratorBase
{
public:
  typedef NodeType  value_type;
  typedef typename Traits::pointer        pointer;
  typedef typename Traits::reference      reference;

public:
  IListIterator();

  explicit IListIterator(NodeBase* pNode);

  virtual ~IListIterator() { }

  operator pointer() const;

  reference operator* () const;
  pointer   operator->() const;

  IListIterator& operator++();
  IListIterator& operator--();
  IListIterator  operator++(int);
  IListIterator  operator--(int);

private:
  // IListIterator is a bidirectional iterator, but it has an implicit
  // conversion to pointer-type. Therefore, declare these functions
  // (but don't implement them) as private can help users catch
  // accidential mis-use.
  void operator+(difference_type) const;
  void operator-(difference_type) const;
  void operator+=(difference_type) const;
  void operator-=(difference_type) const;
  template<class T> void operator<(T) const;
  template<class T> void operator<=(T) const;
  template<class T> void operator>(T) const;
  template<class T> void operator>=(T) const;
  template<class T> void operator-(T) const;
};

//===----------------------------------------------------------------------===//
// IListIterator Member Functions
//===----------------------------------------------------------------------===//
template<typename NodeType, typename Traits>
IListIterator<NodeType, Traits>::IListIterator()
  : IListIteratorBase() {
}

template<typename NodeType, typename Traits>
IListIterator<NodeType, Traits>::IListIterator(NodeBase* pNode)
  : IListIteratorBase(pNode) {
}

template<typename NodeType, typename Traits>
IListIterator<NodeType, Traits>::operator pointer() const
{
  return static_cast<pointer>(m_pNodePtr);
}

template<typename NodeType, typename Traits>
typename IListIterator<NodeType, Traits>::reference
IListIterator<NodeType, Traits>::operator* () const
{
  assert(NULL != m_pNodePtr && "Can not derefer a NULL pointer");
  return *static_cast<pointer>(m_pNodePtr);
}

template<typename NodeType, typename Traits>
typename IListIterator<NodeType, Traits>::pointer
IListIterator<NodeType, Traits>::operator->() const
{
  return static_cast<pointer>(m_pNodePtr);
}

template<typename NodeType, typename Traits>
IListIterator<NodeType, Traits>& IListIterator<NodeType, Traits>::operator++()
{
  advance();
  return *this;
}

template<typename NodeType, typename Traits>
IListIterator<NodeType, Traits>& IListIterator<NodeType, Traits>::operator--()
{
  retreat();
  return *this;
}

template<typename NodeType, typename Traits>
IListIterator<NodeType, Traits> IListIterator<NodeType, Traits>::operator++(int)
{
  IListIterator result(*this);
  advance();
  return result;
}

template<typename NodeType, typename Traits>
IListIterator<NodeType, Traits> IListIterator<NodeType, Traits>::operator--(int)
{
  IListIterator result(*this);
  retreat();
  return result;
}

} // namespace of bold

#endif

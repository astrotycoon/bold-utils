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

protected:
  IListNodeBase* m_pNodePtr;
  
public:
  IListIteratorBase();

  explicit IListIteratorBase(IListNodeBase* pNode);

  virtual ~IListIteratorBase() { }

  const IListNodeBase* getRawPtr() const { return m_pNodePtr; }

  IListNodeBase*       getRawPtr()       { return m_pNodePtr; }

protected:
  void advance();

  void retreat();
};

/** \class IListIterator
 *
 *  IListIterator is a bidirectional iterator.
 */
template<typename NodeType>
class IListIterator : public IListIteratorBase
{
public:
  typedef NodeType  value_type;
  typedef NodeType* pointer;
  typedef NodeType& reference;

public:
  IListIterator();

  explicit IListIterator(IListNodeBase* pNode);

  virtual ~IListIterator() { }

  template<typename NT>
  IListIterator(const IListIterator<NT>& pRHS)
    : IListIterator(pRHS.getRawPtr()) { }

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
template<typename NodeType>
IListIterator<NodeType>::IListIterator()
  : IListIteratorBase() {
}

template<typename NodeType>
IListIterator<NodeType>::IListIterator(IListNodeBase* pNode)
  : IListIteratorBase(pNode) {
}

template<typename NodeType>
IListIterator<NodeType>::operator pointer() const
{
  return static_cast<pointer>(m_pNodePtr);
}

template<typename NodeType>
typename IListIterator<NodeType>::reference
IListIterator<NodeType>::operator* () const
{
  assert(NULL != m_pNodePtr && "Can not derefer a NULL pointer");
  return *static_cast<pointer>(m_pNodePtr);
}

template<typename NodeType>
typename IListIterator<NodeType>::pointer
IListIterator<NodeType>::operator->() const
{
  return static_cast<pointer>(m_pNodePtr);
}

template<typename NodeType>
IListIterator<NodeType>& IListIterator<NodeType>::operator++()
{
  advance();
  return *this;
}

template<typename NodeType>
IListIterator<NodeType>& IListIterator<NodeType>::operator--()
{
  retreat();
  return *this;
}

template<typename NodeType>
IListIterator<NodeType> IListIterator<NodeType>::operator++(int)
{
  IListIterator result(*this);
  advance();
  return result;
}

template<typename NodeType>
IListIterator<NodeType> IListIterator<NodeType>::operator--(int)
{
  IListIterator result(*this);
  retreat();
  return result;
}

} // namespace of bold

#endif

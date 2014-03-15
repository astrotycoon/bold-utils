//===- SlabIterator.h -----------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_SUPPORT_SLAB_ITERATOR_H
#define BOLD_SUPPORT_SLAB_ITERATOR_H
#include <bold/Support/DataTypes.h>
#include <bold/ADT/IListIterator.h>

namespace bold {

/** \class SlabIterator
 *
 *  SlabIterator is a bidirectional iterator.
 */
template<typename Container, typename Traits>
class SlabIterator : public IListIteratorBase
{
public:
  typedef std::bidirectional_iterator_tag iterator_category;
  typedef typename Container::Sentinel    sentinel_type;
  typedef typename Container::value_type  value_type;
  typedef ptrdiff_t                       difference_type;
  typedef typename Traits::pointer        pointer;
  typedef typename Traits::reference      reference;

  typedef typename Traits::template
  rebind<typename Container::slab_type>::other::value_type slab_type;

public:
  SlabIterator();

  SlabIterator(const sentinel_type& pSentinel,
               IListNodeBase* pSlab,
               unsigned int pIdx);

  reference operator* () const;
  pointer   operator->() const;

  SlabIterator& operator++();
  SlabIterator& operator--();
  SlabIterator  operator++(int);
  SlabIterator  operator--(int);

  bool operator==(const SlabIterator& pOther) const;
  bool operator!=(const SlabIterator& pOther) const;

private:
  void forward();

  void backward();

  // SlabIterator is a bidirectional iterator, but it has an implicit
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

private:
  const sentinel_type* m_pSentinel;
  unsigned int m_Idx;
};

//===----------------------------------------------------------------------===//
// SlabIterator Member Functions
//===----------------------------------------------------------------------===//
template<typename Container, typename Traits>
SlabIterator<Container, Traits>::SlabIterator()
  : IListIteratorBase(), m_pSentinel(NULL), m_Idx(-1) {
}

template<typename Container, typename Traits>
SlabIterator<Container, Traits>::SlabIterator(const sentinel_type& pSentinel,
                                              IListNodeBase* pSlab,
                                              unsigned int pIdx)
  : IListIteratorBase(pSlab), m_pSentinel(&pSentinel), m_Idx(pIdx) {
}

template<typename Container, typename Traits>
typename SlabIterator<Container, Traits>::reference
SlabIterator<Container, Traits>::operator* () const
{
  assert(NULL != m_pSentinel && NULL != m_pNodePtr &&
         "Cannot derefer a NULL pointer");
  assert((unsigned int)-1 != m_Idx && "Cannot derefer end()");

  return static_cast<slab_type*>(m_pNodePtr)->data[m_Idx];
}

template<typename Container, typename Traits>
typename SlabIterator<Container, Traits>::pointer
SlabIterator<Container, Traits>::operator->() const
{
  assert(NULL != m_pSentinel && NULL != m_pNodePtr &&
         "Cannot derefer a NULL pointer");
  assert((unsigned int)-1 != m_Idx && "Cannot derefer end()");

  return static_cast<pointer>(static_cast<slab_type*>(m_pNodePtr)->data + m_Idx);
}

template<typename Container, typename Traits>
SlabIterator<Container, Traits>& SlabIterator<Container, Traits>::operator++()
{
  forward();
  return *this;
}

template<typename Container, typename Traits>
SlabIterator<Container, Traits>& SlabIterator<Container, Traits>::operator--()
{
  backward();
  return *this;
}

template<typename Container, typename Traits>
SlabIterator<Container, Traits> SlabIterator<Container, Traits>::operator++(int)
{
  SlabIterator result(*this);
  forward();
  return result;
}

template<typename Container, typename Traits>
SlabIterator<Container, Traits> SlabIterator<Container, Traits>::operator--(int)
{
  SlabIterator result(*this);
  backward();
  return result;
}

template<typename Container, typename Traits> bool
SlabIterator<Container, Traits>::operator==(const SlabIterator& pOther) const
{
  return (m_pSentinel == pOther.m_pSentinel &&
          m_pNodePtr == pOther.m_pNodePtr &&
          m_Idx == pOther.m_Idx);
}

template<typename Container, typename Traits> bool
SlabIterator<Container, Traits>::operator!=(const SlabIterator& pOther) const
{
  return !(*this == pOther);
}

template<typename Container, typename Traits>
void SlabIterator<Container, Traits>::forward()
{
  assert(NULL != m_pSentinel && NULL != m_pNodePtr &&
         "trivial iterator can not forward");

  assert(m_pNodePtr != m_pSentinel && -1 != m_Idx &&
         "end() iterator can not forward");

  m_Idx = (m_Idx + 1) % slab_type::max_size;

  // if I'm at the last of the container, then go to the end
  if (m_pNodePtr == m_pSentinel->getPrev() &&
      m_Idx == m_pSentinel->size() % slab_type::max_size) {
    advance();
    m_Idx = -1;
    return;
  }

  // otherwise, if I'm at the last of the slab, then go to the next slab
  if (0 == m_Idx) {
    advance();
  }

  // the rest, move one step.
}

template<typename Container, typename Traits>
void SlabIterator<Container, Traits>::backward()
{
  assert(NULL != m_pSentinel && NULL != m_pNodePtr &&
         "trivial iterator can not backward");

  assert(m_pNodePtr != m_pSentinel && -1 != m_Idx &&
         "rend() iterator can not backward");

  // if I'm at the front of the container, then go to the rend()
  if (m_pSentinel == m_pNodePtr->getPrev() && 0 == m_Idx) {
    retreat();
    m_Idx = -1;
    return;
  }

  // otherwise, if I'm at the front of a slab, then go to the previous slab
  if (0 == m_Idx) {
    retreat();
    m_Idx = slab_type::max_size - 1;
    return;
  }

  // the rest, move back one step.
  --m_Idx;
}

} // namespace bold

#endif

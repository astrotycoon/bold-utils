//===- IList.cpp ----------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include <bold/ADT/IList.h>

using namespace bold;

//===----------------------------------------------------------------------===//
// IListBase
//===----------------------------------------------------------------------===//
bool IListBase::isSentinel(const IListNodeBase& pNode)
{
  return (&pNode == pNode.getNext());
}

const IListBase::Sentinel* IListBase::getSentinel() const
{
  return static_cast<const Sentinel*>(head()->getPrev());
}

IListBase::Sentinel* IListBase::getSentinel()
{
  return static_cast<Sentinel*>(head()->getPrev());
}

bool IListBase::empty() const
{
  return (0 == getSentinel()->size());
}

IListBase::size_type IListBase::size() const
{
  return getSentinel()->size();
}

IListBase::size_type IListBase::max_size() const
{
  return size_type(-1);
}

void IListBase::swap(IListBase& pOther)
{
  std::swap(m_pHead, pOther.m_pHead);
}

void IListBase::doInsert(IListNodeBase& pWhere, IListNodeBase& pNew)
{
  IListNodeBase* cur = &pWhere;
  IListNodeBase* prev = cur->getPrev();

  pNew.setNext(cur);
  pNew.setPrev(prev);

  if (!isSentinel(*prev))
    prev->setNext(&pNew);
  else
    setHead(&pNew);

  cur->setPrev(&pNew);

  getSentinel()->countIn();
}

void IListBase::doErase(IListNodeBase& pWhere)
{
  IListNodeBase* cur = &pWhere;
  IListNodeBase* prev = cur->getPrev();
  IListNodeBase* next = cur->getNext();

  if (!isSentinel(*prev)) {
    prev->setNext(next);
  }
  else { //< that is, cur is head
    setHead(next);
  }

  next->setPrev(prev);

  cur->setPrev(NULL);
  cur->setNext(NULL);

  getSentinel()->countOut();
}

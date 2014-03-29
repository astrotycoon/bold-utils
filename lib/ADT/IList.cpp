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
IListBase::IListBase()
{
  m_pHead = new IListNodeBase();
  m_pHead->setPrev(m_pHead);
  m_pHead->setNext(m_pHead);
}

IListBase::~IListBase()
{
  delete getSentinel();
}

bool IListBase::isSentinel(const IListNodeBase& pNode)
{
  return (&pNode == pNode.getNext());
}

const IListNodeBase* IListBase::getSentinel() const
{
  return head()->getPrev();
}

IListNodeBase* IListBase::getSentinel()
{
  return head()->getPrev();
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
}

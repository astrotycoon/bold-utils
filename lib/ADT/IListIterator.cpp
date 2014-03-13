//===- IListIterator.cpp --------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#include <bold/ADT/IListIterator.h>
#include <cassert>

using namespace bold;

//===----------------------------------------------------------------------===//
// IListIteratorBase
//===----------------------------------------------------------------------===//
IListIteratorBase::IListIteratorBase()
  : m_pNodePtr(NULL) {
}

IListIteratorBase::IListIteratorBase(NodeBase* pNode)
  : m_pNodePtr(pNode) {
}

void IListIteratorBase::advance()
{
  assert(NULL != m_pNodePtr && "trivial iterator can not advance");
  m_pNodePtr = m_pNodePtr->getNext();
}

void IListIteratorBase::retreat()
{
  assert(NULL != m_pNodePtr && "trivial iterator can not retreat");
  m_pNodePtr = m_pNodePtr->getPrev();
}

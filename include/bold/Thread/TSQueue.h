//===- TSQueue.h ----------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_TSQUEUE_H
#define BOLD_TSQUEUE_H
#ifdef ENABLE_UNITTEST
#include <gtest.h>
#endif
#include <bold/ADT/Uncopyable.h>

namespace bold {

/** \class TSQueue
 *  \brief TSQueue provides a thread-safe queue.
 */
template<typename DATATYPE>
class TSQueue : private Uncopyable
{
public:
  typedef DATATYPE DataType;

public:
  TSQueue();
  ~TSQueue();

  unsigned int size() const;
  bool empty();

  void push(const DataType& pData);
  void pop();

  const DataType& front() const;
  DataType&       front();

  const DataType& back() const;
  DataType&       back();
};

#include "TSQueue.tcc"

} // namespace of bold

#endif


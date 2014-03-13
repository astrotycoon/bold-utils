//===- Thread.h -----------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_THREAD_H
#define BOLD_THREAD_H

namespace bold {

class ThreadImpl;

/** \class Thread
 *  \brief Thread provides the abstract interface for threads.
 */
class Thread
{
public:
  Thread();

  virtual ~Thread();

  void start();

  void quit();

protected:
  virtual void run() = 0;

};

} // namespace of bold

#endif


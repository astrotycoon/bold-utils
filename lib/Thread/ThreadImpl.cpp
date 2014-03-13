//===- ThreadImpl.cpp -----------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//

// Include the truly platform-specific parts. 
#if defined(HAVE_PTHREAD)
#include "PThreadImpl.inc"
#else
#include "QThreadImpl.inc"
#endif

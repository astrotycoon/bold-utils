//===- Slab.h -------------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_SUPPORT_SLAB_H
#define BOLD_SUPPORT_SLAB_H
#include <bold/ADT/IListNode.h>

namespace bold {

/** \class Slab
 *  \brief Slab is a continuous memory space that amounts to `Amount`
 *  `DataType` elements.
 *
 *  Slab is a basic allocated unit of BumpAllocator.
 *
 *  @tparam DataType the type of elements
 *  @tparam Amount   the amount of elements in a slab
 */
template<typename DataType, unsigned int Amount>
struct Slab : public IListNodeBase
{
public:
  enum {
    max_size = Amount
  };

public:
  DataType data[max_size];
};

} // namespace bold

#endif

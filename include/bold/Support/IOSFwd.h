//===- IOSFwd.h -----------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_SUPPORT_IOSFWD_H
#define BOLD_SUPPORT_IOSFWD_H
#include <ios>

namespace bold {

template<typename CharT> class BasicFile;

template<typename CharT, typename Traits = std::char_traits<CharT> >
  class BasicOStream;

template<typename CharT, typename Traits = std::char_traits<CharT> >
  class BasicFileBuf;

template<typename CharT, typename Traits = std::char_traits<CharT> >
  class BasicOFStream;

template<typename CharT, typename Traits = std::char_traits<CharT>,
         typename Alloc = std::allocator<CharT> >
  class BasicOStringBuf;

template<typename CharT, typename Traits = std::char_traits<CharT>,
         typename Alloc = std::allocator<CharT> >
  class BasicOStrStream;

/// @defgroup I/O Forward Declaration
/// @{
typedef BasicOStream<char>    OStream;
typedef BasicFileBuf<char>    FileBuf;
typedef BasicOFStream<char>   OFStream;
typedef BasicOStringBuf<char> OStringBuf;
typedef BasicOStrStream<char> OStrStream;
/// @}

} // namespace of bold

#endif


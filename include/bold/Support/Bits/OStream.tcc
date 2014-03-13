//===- OStream.tcc --------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_SUPPORT_OSTREAM_TCC
#define BOLD_SUPPORT_OSTREAM_TCC

namespace bold {

template<typename CharT, typename Traits> BasicOStream<CharT, Traits>&
BasicOStream<CharT, Traits>::changeColor(enum Colors pColor,
                                         bool pBold,
                                         bool pBG)
{
  return *this;
}

template<typename CharT, typename Traits> BasicOStream<CharT, Traits>&
BasicOStream<CharT, Traits>::resetColor()
{
  return *this;
}

/// reverseColor - Revers the foreground and background colors.
template<typename CharT, typename Traits> BasicOStream<CharT, Traits>&
BasicOStream<CharT, Traits>::reverseColor()
{
  return *this;
}

/// isDisplayed - Can the stream connected to a terminal that can
/// display ANSI color, such as "tty" or "console" window.
template<typename CharT, typename Traits>
bool BasicOStream<CharT, Traits>::isDisplayed() const
{
  return false;
}

} // namespace of bold

#endif

//===- OStream.h ----------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_SUPPORT_OSTREAM_H
#define BOLD_SUPPORT_OSTREAM_H
#include <bold/Support/IOSFwd.h>
#include <ostream>

namespace bold {

/** \class OStream
 *  \brief 
 */
template<typename CharT, typename Traits>
class BasicOStream : public std::basic_ostream<CharT, Traits>
{
public:
  // color order matches ANSI escape sequence, don't change
  enum Colors {
    BLACK=0,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    SAVEDCOLOR
  };

public:
  typedef CharT  char_type;
  typedef Traits traits_type;
  typedef typename traits_type::int_type int_type;
  typedef typename traits_type::pos_type pos_type;
  typedef typename traits_type::off_type off_type;

  // Non-standard Types:
  typedef std::basic_streambuf<CharT, Traits> streambuf_type;
  typedef std::basic_ios<CharT, Traits>       ios_type;
  typedef std::basic_ostream<CharT, Traits>   ostream_type;
  typedef std::num_put<CharT,
                       std::ostreambuf_iterator<CharT, Traits> > num_put_type;
  typedef std::ctype<CharT> ctype_type;

public:
  explicit BasicOStream(streambuf_type* pSB) { this->init(pSB); }

  virtual ~BasicOStream() { }

  /// changeColor - Change the foreground color of text that will be output
  /// from this point forward.
  /// @param pColor ANSI color to use. The special SAVEDCOLOR can be used to
  /// change only the bold attribute, and keep colors untouched.
  /// @param pBold bold/brighter text.
  /// @param pBG change the background if true; otherwise, change the
  /// foreground.
  virtual BasicOStream& changeColor(enum Colors pColor,
                                    bool pBold = false,
                                    bool pBG = false);

  /// resetColor - Resets the colors to terminal defaults.
  virtual BasicOStream& resetColor();

  /// reverseColor - Revers the foreground and background colors.
  virtual BasicOStream& reverseColor();

  /// isDisplayed - Can the stream connected to a terminal that can
  /// display ANSI color, such as "tty" or "console" window.
  virtual bool isDisplayed() const;

  /// hasColor - Is the stream displayed and supports colors.
  virtual bool hasColors() const { return isDisplayed(); }

protected:
  BasicOStream() { this->init(NULL); }

};

} // namespace of bold

#include <bold/Support/Bits/OStream.tcc>

#endif


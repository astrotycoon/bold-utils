//===- OStrStream.h -------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_SUPPORT_OUT_STRING_STREAM_H
#define BOLD_SUPPORT_OUT_STRING_STREAM_H
#include <bold/Support/IOSFwd.h>
#include <bold/Support/OStream.h>
#include <ostream>
#include <cassert>

namespace bold {

/** \class BasicOStringBuf
 *  \brief The actual work of input and output (for std::string)
 *
 *  Unlike std::basic_stringbuf, BasicOStringBuf doesn't own a string for the
 *  internal buffer. Otherwise, BasicOStringBuf uses the given string as the
 *  internal buffer. Every change to the BasicOStringBuf also changes the
 *  content of given string directly.
 */
template<typename CharT, typename Traits, typename Alloc>
class BasicOStringBuf : public std::basic_streambuf<CharT, Traits>
{
public:
  typedef CharT  char_type;
  typedef Traits traits_type;
  typedef Alloc  allocator_type;
  typedef typename traits_type::int_type    int_type;
  typedef typename traits_type::pos_type    pos_type;
  typedef typename traits_type::off_type    off_type;

  typedef std::basic_streambuf<char_type, traits_type> streambuf_type;
  typedef std::basic_string<char_type, Traits, Alloc>  string_type;
  typedef typename string_type::size_type              size_type;

public:
  explicit BasicOStringBuf(string_type& pStr,
                           std::ios_base::openmode pMode = std::ios_base::out);

  ~BasicOStringBuf() { }

  /// str - return a copy
  string_type str() const;

  /// length - return the length of the buffer.
  std::streamsize length() const;

protected:
  void BasicOStringBufInit(std::ios_base::openmode pMode);

  void doSync(char_type* pBase, size_type pO);

  /// Put sequence of characters
  /// override std::streambuf::xsputn
  std::streamsize xsputn(const char_type* pS, std::streamsize pN);

  int_type overflow(int_type pC = traits_type::eof());

protected:
  std::ios_base::openmode m_Mode;
  string_type&            m_String;
};

/** \class BasicOStrStream
 *  \brief BasicOStrStream is an OStream that writes to an std::string.
 */
template<typename CharT, typename Traits, typename Alloc>
class BasicOStrStream : public BasicOStream<CharT, Traits>
{
public:
  typedef CharT  char_type;
  typedef Traits traits_type;
  typedef Alloc  allocator_type;
  typedef typename traits_type::int_type int_type;
  typedef typename traits_type::pos_type pos_type;
  typedef typename traits_type::off_type off_type;

  // Non-standard types:
  typedef std::basic_string<CharT, Traits, Alloc> string_type;
  typedef BasicOStringBuf<CharT, Traits, Alloc> stringbuf_type;
  typedef BasicOStream<CharT, Traits> ostream_type;

public:
  explicit BasicOStrStream(string_type& pStr,
                           std::ios_base::openmode pMode = std::ios_base::out);

  /// Destructor - does nothing
  ~BasicOStrStream() {}

  stringbuf_type* rdbuf() const {
    return const_cast<stringbuf_type*>(&m_StringBuf);
  }

  /// str - get a copy of output stream
  string_type str() const { return m_StringBuf.str(); }

private:
  stringbuf_type m_StringBuf;
};

} // namespace of bold

#include <bold/Support/Bits/OStrStream.tcc>

#endif

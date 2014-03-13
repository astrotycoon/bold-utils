//===- OptionPoolReader.h -------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_OPTION_OPTIONPOOL_READER_H
#define BOLD_OPTION_OPTIONPOOL_READER_H
#include <string>

namespace bold {

class Option;

/** \class OptionPoolReaderReaderBase
 *  \brief OptionPoolReaderReaderBase provides the base class for all
 *  derived PolicyReader.
 */
class OptionPoolPolicyReaderBase
{
public:
  explicit OptionPoolPolicyReaderBase(const std::string& pName)
    : m_Name(pName) { }

  std::string name() const { return m_Name; }

private:
  std::string m_Name;
};

/** \class OptionPoolReader
 *  \brief OptionPoolReader provides interfaces for OptionPoolBuilder to build
 *  an option pool.
 */
template<typename PolicyReader>
class OptionPoolReader : public PolicyReader
{
public:
  typedef typename PolicyReader::const_iterator const_iterator;
  typedef typename PolicyReader::iterator       iterator;

public:
  const_iterator begin() const { return PolicyReader::doBegin(); }
  iterator       begin()       { return PolicyReader::doBegin(); }
  const_iterator end()   const { return PolicyReader::doEnd(); }
  iterator       end()         { return PolicyReader::doEnd(); }

  bool parseFile(istream& pInStream) {
    return PolicyReader::doParseFile(pInStream);
  }
};

} // namespace of bold

#endif


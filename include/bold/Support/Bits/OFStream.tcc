//===- OFStream.tcc -------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
#ifndef BOLD_SUPPORT_OUTPUT_FILE_STREAM_TCC
#define BOLD_SUPPORT_OUTPUT_FILE_STREAM_TCC

namespace bold {
//===----------------------------------------------------------------------===//
// BasicOFStream Member Functions
//===----------------------------------------------------------------------===//
// BasicOFStream is designed as the manager of error state flags. It just like
// a decorator of BasicFileBuf.
template<typename CharT, typename Traits>
BasicOFStream<CharT, Traits>::BasicOFStream()
  : ostream_type(), m_FileBuf() {
  this->init(&m_FileBuf);
}

template<typename CharT, typename Traits>
BasicOFStream<CharT, Traits>::BasicOFStream(const Path& pFileName,
                                            std::ios_base::openmode pMode)
  : ostream_type(), m_FileBuf() {
  this->init(&m_FileBuf);
  this->open(pFileName, pMode);
}

template<typename CharT, typename Traits>
BasicOFStream<CharT, Traits>::BasicOFStream(int pFD,
                                            std::ios_base::openmode pMode)
  : ostream_type(), m_FileBuf() {
  this->init(&m_FileBuf);
  this->open(pFD, pMode);
}

template<typename CharT, typename Traits>
BasicOFStream<CharT, Traits>::BasicOFStream(file_type* pCFile,
                                            std::ios_base::openmode pMode)
  : ostream_type(), m_FileBuf() {
  this->init(&m_FileBuf);
  this->open(pCFile, pMode);
}

template<typename CharT, typename Traits>
BasicOFStream<CharT, Traits>::~BasicOFStream()
{
  // The file is close by filebuf.
}

template<typename CharT, typename Traits> void
BasicOFStream<CharT, Traits>::open(const Path& pFileName,
                                   std::ios_base::openmode pMode)
{
  if (!m_FileBuf.open(pFileName, pMode | std::ios_base::out))
    this->setstate(std::ios_base::failbit);
  else
    this->clear(); ///< clear error state flags
}

template<typename CharT, typename Traits> void
BasicOFStream<CharT, Traits>::open(int pFD,
                                   std::ios_base::openmode pMode)
{
  if (!m_FileBuf.associate(pFD, pMode | std::ios_base::out))
    this->setstate(std::ios_base::failbit);
  else
    this->clear(); ///< clear error state flags
}

template<typename CharT, typename Traits> void
BasicOFStream<CharT, Traits>::open(file_type* pCFile,
                                   std::ios_base::openmode pMode)
{
  if (!m_FileBuf.associate(pCFile, pMode | std::ios_base::out))
    this->setstate(std::ios_base::failbit);
  else
    this->clear(); ///< clear error state flags
}

template<typename CharT, typename Traits> void
BasicOFStream<CharT, Traits>::close()
{
  if (!m_FileBuf.close())
    this->setstate(std::ios_base::failbit);
}

} // namespace of bold

#endif


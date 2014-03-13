//===- TSQueue.tcc --------------------------------------------------------===//
//
//                            The Bold Project
//
//  This file is distributed under the New BSD License.
//  See LICENSE for details.
//
//===----------------------------------------------------------------------===//
// TSQueue - Thread Safe Queue
// TSQueue is designed to run on super computers.
//===----------------------------------------------------------------------===//
template<typename DATATYPE>
TSQueue::TSQueue()
{
}

template<typename DATATYPE>
TSQueue::~TSQueue()
{
}

template<typename DATATYPE>
unsigned int TSQueue::size() const
{
}

template<typename DATATYPE>
bool TSQueue::empty()
{
}

template<typename DATATYPE>
void TSQueue::push(const DATATYPE& pData)
{
}

template<typename DATATYPE>
void TSQueue::pop()
{
}

template<typename DATATYPE>
const DATATYPE& TSQueue::front() const
{
}

template<typename DATATYPE>
DATATYPE& TSQueue::front()
{
}

template<typename DATATYPE>
const DATATYPE& TSQueue::back() const
{
}

template<typename DATATYPE>
DATATYPE& TSQueue::back()
{
}


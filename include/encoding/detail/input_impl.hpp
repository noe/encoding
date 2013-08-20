// Copyright (c) 2013, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)



namespace encoding
{


InputStream::InputStream (std::istream& input)
  : input_(input),
    buffer_(0)
{
  // do nothing
}

void InputStream::fillBuffer(std::size_t neededBitsFromInput) throw(InputError)
{

  std::size_t neededBytesFromInput = ( neededBitsFromInput + CHAR_BIT - 1) / CHAR_BIT;
  std::vector<char> bytes(neededBytesFromInput);
  input_.read(&bytes[0], neededBytesFromInput);

  if (!input_)
  {
    throw InputError();
  }

  // Insert bytes from input_ into the buffer
  std::size_t newBufferSize = buffer_.size() + (neededBytesFromInput * CHAR_BIT);
  buffer_.resize(newBufferSize);

  for (std::size_t k = 0; k < neededBytesFromInput; ++k)
  {
    unsigned value = bytes[k];
    const Bitset singleByte(newBufferSize, value);

    buffer_ <<= CHAR_BIT;
    buffer_ |= singleByte;
  }
}



template<typename Type>
Type InputStream::read(Codec<Type>& codec) throw(InputError)
{
  std::size_t totalBitsToBeRead = codec.sizeInBits;
  std::size_t bitsAlreadyRead = 0;
  std::size_t bitsPendingToBeRead = totalBitsToBeRead;

  std::size_t neededBitsFromInput = buffer_.size() >= totalBitsToBeRead ? 
                                     0 : totalBitsToBeRead - buffer_.size();

  if (neededBitsFromInput > 0)
  {
    fillBuffer(neededBitsFromInput);
  }

  std::size_t unusedBits = buffer_.size() - totalBitsToBeRead;

  Bitset result (buffer_);
  result >>= unusedBits;
  result.resize(totalBitsToBeRead);

  buffer_.resize(unusedBits);

  return codec.decode(result);
}

}

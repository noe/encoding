

namespace encoding
{


InputStream::InputStream (std::istream& in)
  : input(in),
    buffer(0)
{
  // do nothing
}

void InputStream::fillBuffer(std::size_t neededBitsFromInput) throw(InputError)
{

  std::size_t neededBytesFromInput = ( neededBitsFromInput + CHAR_BIT - 1) / CHAR_BIT;
  std::vector<char> bytes(neededBytesFromInput);
  input.read(&bytes[0], neededBytesFromInput);

  if (!input)
  {
    throw InputError();
  }

  // Insert bytes from input into the buffer
  std::size_t newBufferSize = buffer.size() + (neededBytesFromInput * CHAR_BIT);
  buffer.resize(newBufferSize);

  for (std::size_t k = 0; k < neededBytesFromInput; ++k)
  {
    unsigned value = bytes[k];
    const boost::dynamic_bitset<> singleByte(newBufferSize, value);

    buffer <<= CHAR_BIT;
    buffer |= singleByte;
  }
}



template<typename Type>
Type InputStream::read(Codec<Type>& codec) throw(InputError)
{
  std::size_t totalBitsToBeRead = codec.sizeInBits;
  std::size_t bitsAlreadyRead = 0;
  std::size_t bitsPendingToBeRead = totalBitsToBeRead;

  std::size_t neededBitsFromInput = buffer.size() >= totalBitsToBeRead ? 
                                     0 : totalBitsToBeRead - buffer.size();

  if (neededBitsFromInput > 0)
  {
    fillBuffer(neededBitsFromInput);
  }

  std::size_t unusedBits = buffer.size() - totalBitsToBeRead;

  boost::dynamic_bitset<> result (buffer);
  result >>= unusedBits;
  result.resize(totalBitsToBeRead);

  buffer.resize(unusedBits);

  return codec.decode(result);
}

}

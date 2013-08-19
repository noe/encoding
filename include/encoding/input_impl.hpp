

namespace encoding
{


InputStream::InputStream (std::istream& in)
  : input(in),
    buffer(CHAR_BIT, 0),
    availableBitsInBuffer(0)
{

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
  std::size_t newBufferSize = availableBitsInBuffer + (neededBytesFromInput * CHAR_BIT);
  buffer.resize(newBufferSize);

  for (int k = neededBytesFromInput - 1; k >= 0; --k)
  {
    if (availableBitsInBuffer > 0)
    {
      buffer <<= CHAR_BIT;
    }

    using namespace std;
    cout << "Read from input: " << bytes[k] << endl;

    boost::dynamic_bitset<> singleByte(newBufferSize, bytes[k]);

    buffer |= singleByte;
    buffer &= singleByte;
    availableBitsInBuffer += CHAR_BIT;
  }
}



template<typename Type>
Type InputStream::read(Codec<Type>& codec) throw(InputError)
{
  std::size_t totalBitsToBeRead = codec.sizeInBits;
  std::size_t bitsAlreadyRead = 0;
  std::size_t bitsPendingToBeRead = totalBitsToBeRead;

  std::size_t neededBitsFromInput = availableBitsInBuffer >= totalBitsToBeRead ? 
                                     0 : totalBitsToBeRead - availableBitsInBuffer;

  if (neededBitsFromInput > 0)
  {
    fillBuffer(neededBitsFromInput);
  }

  std::size_t unusedBits = availableBitsInBuffer - totalBitsToBeRead;

  boost::dynamic_bitset<> result (buffer);
  result >>= unusedBits;
  result.resize(totalBitsToBeRead);


  buffer.resize(unusedBits);
  availableBitsInBuffer = unusedBits;

  return codec.decode(result);
}

}

// Copyright (c) 2013, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)


namespace encoding
{

OutputStream::OutputStream(std::ostream& output)
  : output_(output),
    buffer_(0),
    closed_(false)
{
  // do nothing
}

OutputStream::~OutputStream() noexcept(true)
{
  if (!closed_)
  {
    try
    {
      close();
    }
    catch (OutputError& error)
    {
      // destructors do not throw
    }
  }
}

template<typename Type>
void OutputStream::write(Codec<Type>& codec, Type value) throw(OutputError)
{
  Bitset encoded = codec.encode(value);
  if (buffer_.empty())
  {
    buffer_.swap(encoded);
  }
  else
  {
    std::size_t newSize = buffer_.size() + encoded.size();
    buffer_.resize(newSize);
    buffer_ <<= encoded.size();

    encoded.resize(newSize);
    buffer_ |= encoded;
  }

  flushInternalBuffer();
}

void OutputStream::flushInternalBuffer() throw(OutputError)
{
  std::size_t  bitsToBeWrittenNow =
                 buffer_.size() >= CHAR_BIT? CHAR_BIT : 0;

  Bitset tmp;

  while (bitsToBeWrittenNow > 0)
  {
    std::size_t bitsLeftUnwritten = buffer_.size() - bitsToBeWrittenNow;
    tmp = buffer_ >> bitsLeftUnwritten;

    char byteToBeWritten = tmp.to_ulong();
    unsigned long x = tmp.to_ulong();

    output_.write(&byteToBeWritten, 1);

    if (!output_)
    {
      throw OutputError();
    }

    buffer_.resize(bitsLeftUnwritten);
    bitsToBeWrittenNow = buffer_.size() >= CHAR_BIT? CHAR_BIT : 0;
  }

}

void OutputStream::close() throw(OutputError)
{
  closed_ = true;

  if (buffer_.empty())
  {
    return;
  }

  std::size_t paddingBits = CHAR_BIT - buffer_.size();
  buffer_ <<= paddingBits;

  flushInternalBuffer();

  output_.flush();
  if (!output_)
  {
    throw OutputError();
  }
}

}

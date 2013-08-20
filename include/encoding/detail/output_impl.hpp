
namespace encoding
{

OutputStream::OutputStream(std::ostream& out)
  : output(out),
    buffer(0),
    closed(false)
{
  // do nothing
}

OutputStream::~OutputStream()
{
  if (!closed)
  {
    close();
  }
}

template<typename Type>
void OutputStream::write(Codec<Type>& codec, Type value) throw(OutputError)
{
  Bitset encoded = codec.encode(value);
  if (buffer.empty())
  {
    buffer.swap(encoded);
  }
  else
  {
    std::size_t newSize = buffer.size() + encoded.size();
    buffer.resize(newSize);
    buffer <<= encoded.size();

    encoded.resize(newSize);
    buffer |= encoded;
  }

  using namespace std;
  cout << "buffer is " << buffer << endl;

  flushInternalBuffer();
}

void OutputStream::flushInternalBuffer() throw(OutputError)
{
  std::size_t  bitsToBeWrittenNow =
                 buffer.size() >= CHAR_BIT? CHAR_BIT : 0;

  Bitset tmp;

  while (bitsToBeWrittenNow > 0)
  {
    std::size_t bitsLeftUnwritten = buffer.size() - bitsToBeWrittenNow;
    tmp = buffer >> bitsLeftUnwritten;

    char byteToBeWritten = tmp.to_ulong();
    unsigned long x = tmp.to_ulong();

    using namespace std;
    cout << "char to be written: " << byteToBeWritten << endl;
    cout << "...as uling: " << x << endl;
    cout << "...bits were: " << tmp<< endl;

    output.write(&byteToBeWritten, 1);

    if (!output)
    {
      throw OutputError();
    }

    buffer.resize(bitsLeftUnwritten);
    bitsToBeWrittenNow = buffer.size() >= CHAR_BIT? CHAR_BIT : 0;
  }

}

void OutputStream::close()
{
  closed = true;

  if (buffer.empty())
  {
    return;
  }

  std::size_t paddingBits = CHAR_BIT - buffer.size();
  buffer <<= paddingBits;

  flushInternalBuffer();

  output.flush();
  if (!output)
  {
    throw OutputError();
  }
}

}

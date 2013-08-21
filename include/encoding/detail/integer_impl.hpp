// Copyright (c) 2013, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)


namespace encoding
{


UnsignedIntegerCodec::UnsignedIntegerCodec(std::size_t bits)
  : Codec<uint32_t>(bits)
{
  // do nothing
}

Bitset UnsignedIntegerCodec::encode(uint32_t value) const
{
  return Bitset(sizeInBits, value);
}

uint32_t UnsignedIntegerCodec::decode(const Bitset& bits) const
{
  return bits.to_ulong();
}


GrayCodec::GrayCodec(std::size_t bits)
  : Codec<uint32_t>(bits)
{
  // do nothing
}

Bitset GrayCodec::encode(uint32_t value) const
{
  uint32_t grayEncodedValue =  value ^ (value >> 1);
  UnsignedIntegerCodec normalCodec(sizeInBits);
  return normalCodec.encode(grayEncodedValue);
}

uint32_t GrayCodec::decode(const Bitset& bits) const
{
  UnsignedIntegerCodec normalCodec(sizeInBits);
  const uint32_t grayEncodedValue = normalCodec.decode(bits);
  uint32_t value = grayEncodedValue;
  for (uint32_t bit = 1U << 31; bit > 1; bit >>= 1)
  {
    if (value & bit) value ^= bit >> 1;
  }
  return value;
}

}

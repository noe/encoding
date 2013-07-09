#include "encoding.hpp"

namespace encoding
{

///////////////////////////////////////////////////////////////////////////////
UnsignedIntegerCodec::UnsignedIntegerCodec(std::size_t bits)
  : FieldCodec(bits)
{
  // do nothing
}

///////////////////////////////////////////////////////////////////////////////
boost::dynamic_bitset<> UnsignedIntegerCodec::encode(uint32_t value) const
{
  return boost::dynamic_bitset<>(sizeInBits, value);
}


///////////////////////////////////////////////////////////////////////////////
uint32_t UnsignedIntegerCodec::decode(boost::dynamic_bitset<> bits) const
{
  return bits.to_ulong();
}

///////////////////////////////////////////////////////////////////////////////
GrayCodec::GrayCodec(std::size_t bits)
  : FieldCodec(bits)
{
  // do nothing
}

///////////////////////////////////////////////////////////////////////////////
boost::dynamic_bitset<> GrayCodec::encode(uint32_t value) const
{
  uint32_t grayEncodedValue =  value ^ (value >> 1);
  UnsignedIntegerCodec normalCodec(sizeInBits);
  return normalCodec.encode(grayEncodedValue);
}

///////////////////////////////////////////////////////////////////////////////
uint32_t GrayCodec::decode(boost::dynamic_bitset<> bits) const
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

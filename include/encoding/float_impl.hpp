#include "encoding/integer.hpp"
#include <limits>

namespace encoding
{

namespace detail
{
  template<typename FixedPointType, std::size_t FractionalBits>
  constexpr FixedPointType fixedPointOne ()
  {
    return FixedPointType(1) << FractionalBits;
  }
}

FloatCodec::FloatCodec()
  : Codec<double>(sizeof(double) * CHAR_BIT)
{
  static_assert(std::numeric_limits<double>::is_iec559,
                "Only compilers with IEEE floats are supported");
}

boost::dynamic_bitset<> FloatCodec::encode(double value) const
{
  typedef boost::dynamic_bitset<>::block_type block_type;

  union
  {
    double input;
    block_type output[sizeof(double)/sizeof(block_type)];
  } data;

  data.input = value;

  boost::dynamic_bitset<> bitset (sizeInBits);
  boost::from_block_range(std::begin(data.output), std::end(data.output), bitset); 
  return bitset;
}

double FloatCodec::decode(boost::dynamic_bitset<> bits) const
{
  typedef boost::dynamic_bitset<>::block_type block_type;
  std::vector<block_type> blocks; 
  boost::to_block_range(bits, std::back_inserter(blocks));

  union
  {
    block_type input[sizeof(double) / sizeof(block_type)];
    double output;
  } data;

  std::copy (blocks.begin(), blocks.end(), data.input);
  return data.output;
}


template<std::size_t IntegerPart, std::size_t FractionalPart>
FixedPointFloatCodec<IntegerPart, FractionalPart>::FixedPointFloatCodec()
  : Codec<double>(IntegerPart + FractionalPart)
{
  static_assert(std::numeric_limits<double>::is_iec559,
                "Only compilers with IEEE floats are supported");
  static_assert(IntegerPart + FractionalPart <= 32, "Only floats up to 32 bits supported");
}

template<std::size_t IntegerPart, std::size_t FractionalPart>
boost::dynamic_bitset<> FixedPointFloatCodec<IntegerPart, FractionalPart>::encode(double value) const
{
  static const uint32_t one = detail::fixedPointOne<uint32_t, FractionalPart>();
  uint32_t fpValue = static_cast<uint32_t>(value * one);

  UnsignedIntegerCodec codec (sizeInBits);
  return codec.encode(fpValue);
}

template<std::size_t IntegerPart, std::size_t FractionalPart>
double FixedPointFloatCodec<IntegerPart, FractionalPart>::decode(boost::dynamic_bitset<> bits) const
{
  static const uint32_t one = detail::fixedPointOne<uint32_t, FractionalPart>();
  UnsignedIntegerCodec codec (sizeInBits);
  uint32_t fpValue = codec.decode(bits);

  return static_cast<double>(fpValue) / static_cast<double>(one);
}

}

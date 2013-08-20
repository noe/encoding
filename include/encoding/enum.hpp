#ifndef ENCODING_ENUM_HEADER_SEEN__
#define ENCODING_ENUM_HEADER_SEEN__

#include "encoding/codec.hpp"
#include "encoding/integer.hpp"

namespace encoding
{
  template<typename EnumType>
  struct EnumCodec : public Codec<EnumType>
  {
    const EnumType defaultValue;
    const std::vector<EnumType> enumValues;
    UnsignedIntegerCodec auxCodec;

    EnumCodec(std::initializer_list<EnumType> possibleValues,
              EnumType defaultEnumValue /* for unsupported bit representations */);
    boost::dynamic_bitset<> encode(EnumType value) const;
    EnumType decode(boost::dynamic_bitset<> bits) const;
  };
}

#include "encoding/detail/enum_impl.hpp"

#endif

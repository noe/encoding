// Copyright (c) 2013, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

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
    Bitset encode(EnumType value) const;
    EnumType decode(Bitset bits) const;
  };
}

#include "encoding/detail/enum_impl.hpp"

#endif

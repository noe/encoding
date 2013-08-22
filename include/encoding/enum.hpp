// Copyright (c) 2013, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef ENCODING_ENUM_HEADER_SEEN__
#define ENCODING_ENUM_HEADER_SEEN__

#include "encoding/codec.hpp"
#include "encoding/integer.hpp"

namespace encoding
{
  /****************************************************************************
   * Implementation of Codec for a finite set of elements of whatever type.
   * It is templatized with the type of the elements of the enumeration.
   ***************************************************************************/
  template<typename EnumType>
  struct EnumCodec : public Codec<EnumType>
  {

    EnumCodec(std::initializer_list<EnumType> possibleValues,
              EnumType defaultEnumValue /* for unsupported bit representations */);

    Bitset encode(EnumType value) const override;

    EnumType decode(const Bitset& bits) const override;

   private: 

    const EnumType defaultValue;

    const std::vector<EnumType> enumValues;

    UnsignedIntegerCodec auxCodec;
  };
}

#include "encoding/detail/enum_impl.hpp"

#endif

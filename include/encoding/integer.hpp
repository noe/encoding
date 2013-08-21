// Copyright (c) 2013, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef ENCODING_INTEGER_HEADER_SEEN__
#define ENCODING_INTEGER_HEADER_SEEN__

#include "encoding/codec.hpp"

namespace encoding
{
  /****************************************************************************
   * Implementation of Codec for uint32_t that uses 2's compliment
   * representation.
   ***************************************************************************/
  struct UnsignedIntegerCodec : public Codec<uint32_t>
  {
    inline UnsignedIntegerCodec(std::size_t bits);

    inline Bitset encode(uint32_t value) const override;

    inline uint32_t decode(const Bitset& bits) const override;
  };

  /****************************************************************************
   * Implementation of Codec for uint32_t that uses Gray code representation.
   ***************************************************************************/
  struct GrayCodec : public Codec<uint32_t>
  {
    inline GrayCodec(std::size_t bits);

    inline Bitset encode(uint32_t value) const override;

    inline uint32_t decode(const Bitset& bits) const override;
  };

// TODO: struct RangeCodec : public Codec<int>

}

#include "encoding/detail/integer_impl.hpp"

#endif

// Copyright (c) 2013, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef ENCODING_INTEGER_HEADER_SEEN__
#define ENCODING_INTEGER_HEADER_SEEN__

#include "encoding/codec.hpp"

namespace encoding
{
  /////////////////////////////////////////////////////////////////////////////
  /**
   ** 
   **//////////////////////////////////////////////////////////////////////////
  struct UnsignedIntegerCodec : public Codec<uint32_t>
  {
    inline UnsignedIntegerCodec(std::size_t bits);
    inline Bitset encode(uint32_t value) const;
    inline uint32_t decode(const Bitset& bits) const;
  };

  /////////////////////////////////////////////////////////////////////////////
  /**
   ** 
   **//////////////////////////////////////////////////////////////////////////
  struct GrayCodec : public Codec<uint32_t>
  {
    inline GrayCodec(std::size_t bits);
    inline Bitset encode(uint32_t value) const;
    inline uint32_t decode(const Bitset& bits) const;
  };

// TODO: struct RangeCodec : public Codec<int>

}

#include "encoding/detail/integer_impl.hpp"

#endif

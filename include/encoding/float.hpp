// Copyright (c) 2013, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef ENCODING_FLOAT_HEADER_SEEN_
#define ENCODING_FLOAT_HEADER_SEEN_

#include "codec.hpp"

namespace encoding
{
  struct FloatCodec : public Codec<double>
  {
    inline FloatCodec();
    inline Bitset encode(double value) const;
    inline double decode(Bitset bits) const;
  };

  /////////////////////////////////////////////////////////////////////////////
  /**
   ** 
   **//////////////////////////////////////////////////////////////////////////
  template<std::size_t IntegerPart, std::size_t FractionalPart>
  struct FixedPointFloatCodec : public Codec<double>
  {
    FixedPointFloatCodec();
    Bitset encode(double value) const;
    double decode(Bitset bits) const;
  };

}

#include "encoding/detail/float_impl.hpp"
#endif

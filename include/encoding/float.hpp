// Copyright (c) 2013, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef ENCODING_FLOAT_HEADER_SEEN_
#define ENCODING_FLOAT_HEADER_SEEN_

#include "codec.hpp"

namespace encoding
{
  /****************************************************************************
   * Implementation of Codec for double that uses IEEE597 as representation.
   ***************************************************************************/
  struct FloatCodec : public Codec<double>
  {
    inline FloatCodec();

    inline Bitset encode(double value) const override;

    inline double decode(const Bitset& bits) const override;
  };

  /****************************************************************************
   * Implementation of Codec for double that uses fixed point representation.
   * It receives as template arguments the number of bits before and after
   * the decimal point; both numbers added must not exceed 32.
   ***************************************************************************/
  template<std::size_t IntegerPart, std::size_t FractionalPart>
  struct FixedPointFloatCodec : public Codec<double>
  {
    FixedPointFloatCodec();

    Bitset encode(double value) const override;

    double decode(const Bitset& bits) const override;
  };
}

#include "encoding/detail/float_impl.hpp"
#endif

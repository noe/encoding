#ifndef ENCODING_FLOAT_HEADER_SEEN_
#define ENCODING_FLOAT_HEADER_SEEN_

#include "codec.hpp"

namespace encoding
{

  /////////////////////////////////////////////////////////////////////////////
  /**
   ** 
   **//////////////////////////////////////////////////////////////////////////
  template<std::size_t IntegerPart, std::size_t FractionalPart>
  struct FixedPointFloatCodec : public Codec<double>
  {
    FixedPointFloatCodec();
    boost::dynamic_bitset<> encode(double value) const;
    double decode(boost::dynamic_bitset<> bits) const;
  };

}
#endif

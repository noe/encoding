#ifndef ENCODING_CODEC_HEADER_SEEN__
#define ENCODING_CODEC_HEADER_SEEN__

#include <boost/dynamic_bitset.hpp>

namespace encoding
{

  /////////////////////////////////////////////////////////////////////////////
  /**
   ** 
   **//////////////////////////////////////////////////////////////////////////
  template<typename Type>
  struct Codec
  {
    // TODO: replace virtual with CRTP
    const std::size_t sizeInBits;
    Codec (std::size_t bits) : sizeInBits(bits) { }
    virtual boost::dynamic_bitset<> encode(Type value) const = 0;
    virtual Type decode(boost::dynamic_bitset<> bits) const = 0;
    virtual ~Codec() { }
  };
}

#endif

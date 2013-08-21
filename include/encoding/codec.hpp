// Copyright (c) 2013, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef ENCODING_CODEC_HEADER_SEEN__
#define ENCODING_CODEC_HEADER_SEEN__

#include <boost/dynamic_bitset.hpp>

namespace encoding
{
  /** Type to be used as bit storage */
  typedef boost::dynamic_bitset<> Bitset; 

  /****************************************************************************
   * Interface of an encoding/decoding strategy.
   * 
   ***************************************************************************/
  template<typename Type>
  struct Codec
  {
    /** Number of bits of the encoded data */
    const std::size_t sizeInBits;

    /**************************************************************************
     * Constructor.
     * \param bits Number of bits of the encoded data,
     *************************************************************************/
    Codec (std::size_t bits) : sizeInBits(bits) { }

    /**************************************************************************
     * Encodes the supplied piece of data.
     * \param value Value to be encoded.
     * \return The encoded bits.
     *************************************************************************/
    virtual Bitset encode(Type value) const = 0;

    /**************************************************************************
     * Decodes a piece of data from the supplied bits.
     * \param bits Encoded data to be decoded.
     * \return The decoded piece of data.
     *************************************************************************/
    virtual Type decode(const Bitset& bits) const = 0;

    /**************************************************************************
     * Destructor.
     *************************************************************************/
    virtual ~Codec() noexcept (true) { }
  };
}

#endif

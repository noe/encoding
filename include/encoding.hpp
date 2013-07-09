#ifndef ENCODING_HEADER_SEEN__
#define ENCODING_HEADER_SEEN__

#include <boost/dynamic_bitset.hpp>

namespace genalg
{

  /////////////////////////////////////////////////////////////////////////////
  /**
   ** 
   **//////////////////////////////////////////////////////////////////////////
  template<typename Type>
  struct FieldCodec
  {
    const std::size_t sizeInBits;
    FieldCodec (std::size_t bits) : sizeInBits(bits) { }
    virtual boost::dynamic_bitset<> encode(Type value) const = 0;
    virtual Type decode(boost::dynamic_bitset<> bits) const = 0;
    virtual ~FieldCodec() { }
  };

  /////////////////////////////////////////////////////////////////////////////
  /**
   ** 
   **//////////////////////////////////////////////////////////////////////////
  template<std::size_t IntegerPart, std::size_t FractionalPart>
  struct FixedPointFloatCodec : public FieldCodec<double>
  {
    FixedPointFloatCodec();
    boost::dynamic_bitset<> encode(double value) const;
    double decode(boost::dynamic_bitset<> bits) const;
  };

  /////////////////////////////////////////////////////////////////////////////
  /**
   ** 
   **//////////////////////////////////////////////////////////////////////////
  struct UnsignedIntegerCodec : public FieldCodec<uint32_t>
  {
    UnsignedIntegerCodec(std::size_t bits);
    boost::dynamic_bitset<> encode(uint32_t value) const;
    uint32_t decode(boost::dynamic_bitset<> bits) const;
  };

  /////////////////////////////////////////////////////////////////////////////
  /**
   ** 
   **//////////////////////////////////////////////////////////////////////////
  struct GrayCodec : public FieldCodec<uint32_t>
  {
    GrayCodec(std::size_t bits);
    boost::dynamic_bitset<> encode(uint32_t value) const;
    uint32_t decode(boost::dynamic_bitset<> bits) const;
  };

  /////////////////////////////////////////////////////////////////////////////
  /**
   ** 
   **//////////////////////////////////////////////////////////////////////////
  template<typename EnumType>
  struct EnumCodec : public FieldCodec<EnumType>
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

///////////////////////////////////////////////////////////////////////////////
//// Implementation details of class templates
#include "encoding_inl.hpp"

#endif

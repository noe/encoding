// Copyright (c) 2013, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef TEST_FUNCTIONS_HEADER_SEEN__
#define TEST_FUNCTIONS_HEADER_SEEN__

#include "encoding/codec.hpp"
#include <iostream>
#include <string>

/*****************************************************************************/
template<typename Type>
inline void testEncode(const encoding::Codec<Type>& codec,
                const Type& value,
                const std::string& bits)
{
  encoding::Bitset obtainedBits = codec.encode(value);
  if (obtainedBits == encoding::Bitset(bits))
  {
    std::cout << "[PASS] Encoded " << value
              << " and obtained " << bits
              << std::endl;
  }
  else
  {
    std::cout << "[FAIL] Encoded " << value
         << " and obtained " << obtainedBits
         << " but expected " << bits
         << std::endl;
  }
}

/*****************************************************************************/
template<typename Type>
inline void testDecode(const encoding::Codec<Type>& codec,
                const Type& value,
                const std::string& bits)
{
  Type obtainedValue = codec.decode(encoding::Bitset(bits));
  if (obtainedValue == value)
  {
    std::cout << "[PASS] Decoded " << bits 
              << " and obtained " << value
              << std::endl;
  }
  else
  {
    std::cout << "[FAIL] Decoded " << bits
              << " and obtained " << obtainedValue
              << " but expected " << value
              << std::endl;
  }
}

/*****************************************************************************/
template<typename Type>
inline void testRoundtripValue(const encoding::Codec<Type>& codec, const Type& value)
{
  Type roundtripValue = codec.decode(codec.encode(value));

  if (roundtripValue == value)
  {
    std::cout << "[PASS] Rountrip converted " << value
              << std::endl;
  }
  else
  {
    std::cout << "[FAIL] Roundtrip converted " << value
              << " and obtained " << roundtripValue
              << std::endl;
  }
}

/*****************************************************************************/
template<typename Type>
inline void testEncodeAndDecode(const encoding::Codec<Type>& codec,
                         const Type& value,
                         const std::string& bits)
{
  testEncode (codec, value, bits);
  testDecode (codec, value, bits);
}

#endif

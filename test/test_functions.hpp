// Copyright (c) 2013, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef TEST_FUNCTIONS_HEADER_SEEN__
#define TEST_FUNCTIONS_HEADER_SEEN__

#include "encoding/codec.hpp"

#include <gtest/gtest.h>


/*****************************************************************************/
template<typename Type>
inline void testEncode(const encoding::Codec<Type>& codec,
                const Type& value,
                const std::string& bits)
{
  encoding::Bitset obtainedBits = codec.encode(value);
  ASSERT_EQ(obtainedBits, encoding::Bitset(bits));
}

/*****************************************************************************/
template<typename Type>
inline void testDecode(const encoding::Codec<Type>& codec,
                const Type& value,
                const std::string& bits)
{
  Type obtainedValue = codec.decode(encoding::Bitset(bits));
  ASSERT_EQ(obtainedValue, value);
}

/*****************************************************************************/
template<typename Type>
inline void testRoundtripValue(const encoding::Codec<Type>& codec, const Type& value)
{
  Type roundtripValue = codec.decode(codec.encode(value));
  ASSERT_EQ(roundtripValue, value);
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

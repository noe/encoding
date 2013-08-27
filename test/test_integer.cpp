#include "test_functions.hpp"

#include "encoding/codec.hpp"
#include "encoding/integer.hpp"

#include <iostream>
#include <string>

#include <gtest/gtest.h>

/*****************************************************************************/
TEST(TestUnsigned, SimpleConversions)
{
  testEncodeAndDecode (encoding::UnsignedIntegerCodec(1), uint32_t(0), "0");
  testEncodeAndDecode (encoding::UnsignedIntegerCodec(1), uint32_t(1), "1");
  testEncodeAndDecode (encoding::UnsignedIntegerCodec(11), uint32_t(1024), "10000000000");
  testEncodeAndDecode (encoding::UnsignedIntegerCodec(16), uint32_t(1024), "0000010000000000");
}

/*****************************************************************************/
TEST(TestUnsigned, RandomRoundtrip)
{
  srand (time(0));
  for (std::size_t i = 0; i < 5; ++i)
  {
    std::size_t numBits = rand() % 65;

    for (std::size_t k = 0; k < 20; ++k)
    {
      uint32_t randomNumber = rand() % (1 << numBits);
      testRoundtripValue (encoding::UnsignedIntegerCodec(numBits), randomNumber);
    }
  }
}

/*****************************************************************************/
TEST(TestUnsigned, EncodePerformance)
{
  const std::size_t performanceSamples = 10000000;
  encoding::UnsignedIntegerCodec codec(32);
  clock_t begin = clock();
  for (uint32_t x = 0; x < performanceSamples ; ++x)
  {
    encoding::Bitset result = codec.encode(x);
  }
  clock_t end = clock();
  double elapsedmsecs = 1000.0 * double(end - begin) / CLOCKS_PER_SEC;

  double encodeTime = 1000 * elapsedmsecs / performanceSamples;
  EXPECT_LT(encodeTime, 1.0);
}

/*****************************************************************************/
TEST(TestRange, SimpleConversions)
{
  testEncodeAndDecode (encoding::RangeCodec(-45,423), int32_t(-45), "00000000000000000000000000000000");
}

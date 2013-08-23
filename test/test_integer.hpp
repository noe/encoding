#include "test_functions.hpp"

#include "encoding/codec.hpp"
#include "encoding/integer.hpp"

#include <iostream>
#include <string>

/*****************************************************************************/
void testUnsignedIntegerRandomRoundtrip()
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
void testUnsignedIntegerEncodePerformance()
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
  std::cout << "Unsigned integer encode time: "
            << (1000 * elapsedmsecs / performanceSamples) << "usecs "
            << "( " << performanceSamples << " samples )"
            << std::endl;
}

/*****************************************************************************/
void testUnsigned ()
{
  testEncodeAndDecode (encoding::UnsignedIntegerCodec(1), uint32_t(0), "0");
  testEncodeAndDecode (encoding::UnsignedIntegerCodec(1), uint32_t(1), "1");
  testEncodeAndDecode (encoding::UnsignedIntegerCodec(11), uint32_t(1024), "10000000000");
  testEncodeAndDecode (encoding::UnsignedIntegerCodec(16), uint32_t(1024), "0000010000000000");
  testUnsignedIntegerRandomRoundtrip();
  testUnsignedIntegerEncodePerformance();
}

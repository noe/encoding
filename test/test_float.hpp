#include "test_functions.hpp"

#include "encoding/codec.hpp"
#include "encoding/float.hpp"

#include <iostream>
#include <string>

/*****************************************************************************/
void testDoubleRandomRoundtrip()
{
  srand (time(0));
  for (std::size_t i = 0; i < 5; ++i)
  {
    std::size_t numBits = rand() % 65;

    for (std::size_t k = 0; k < 20; ++k)
    {
      double randomNumber = double(rand() % (1 << numBits)) / 100.0;
      testRoundtripValue (encoding::FloatCodec(), randomNumber);
    }
  }
}

/*****************************************************************************/
void testDoubleEncodePerformance()
{
  const std::size_t performanceSamples = 10000000;
  encoding::UnsignedIntegerCodec codec(32);
  clock_t begin = clock();
  double x = 0.0;
  for (std::size_t k = 0; k < performanceSamples ; ++k)
  {
    x += 0.005;
    encoding::Bitset result = codec.encode(x);
  }
  clock_t end = clock();
  double elapsedmsecs = 1000.0 * double(end - begin) / CLOCKS_PER_SEC;
  std::cout << "Double encode time: "
            << (1000 * elapsedmsecs / performanceSamples) << "usecs "
            << "( " << performanceSamples << " samples )"
            << std::endl;
}

/*****************************************************************************/
void testFloat()
{
  testDoubleRandomRoundtrip();
  testDoubleEncodePerformance();
}


// Copyright (c) 2013, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)


#include "test_functions.hpp"

#include "encoding/enum.hpp"
#include "encoding/integer.hpp"
#include "encoding/float.hpp"
#include "encoding/input.hpp"
#include "encoding/output.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace encoding;

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
      testRoundtripValue (UnsignedIntegerCodec(numBits), randomNumber);
    }
  }
}

/*****************************************************************************/
void testUnsignedIntegerEncodePerformance()
{
  const std::size_t performanceSamples = 10000000;
  UnsignedIntegerCodec codec(32);
  clock_t begin = clock();
  for (uint32_t x = 0; x < performanceSamples ; ++x)
  {
    Bitset result = codec.encode(x);
  }
  clock_t end = clock();
  double elapsedmsecs = 1000.0 * double(end - begin) / CLOCKS_PER_SEC;
  cout << "Unsigned integer encode time: "
       << (1000 * elapsedmsecs / performanceSamples) << "usecs "
       << "( " << performanceSamples << " samples )"
       << endl;
}

/*****************************************************************************/
void testUnsigned ()
{
  testEncodeAndDecode (UnsignedIntegerCodec(1), uint32_t(0), "0");
  testEncodeAndDecode (UnsignedIntegerCodec(1), uint32_t(1), "1");
  testEncodeAndDecode (UnsignedIntegerCodec(11), uint32_t(1024), "10000000000");
  testEncodeAndDecode (UnsignedIntegerCodec(16), uint32_t(1024), "0000010000000000");
  testUnsignedIntegerRandomRoundtrip();
  testUnsignedIntegerEncodePerformance();
}

/*****************************************************************************/
void testEnum ()
{
  testEncodeAndDecode(EnumCodec<string>({"a","b","c"},"a"), string("a"), "00");
  testEncodeAndDecode(EnumCodec<string>({"a","b","c"},"a"), string("b"), "01");
  testEncodeAndDecode(EnumCodec<string>({"a","b","c"},"a"), string("c"), "10");
  testDecode(EnumCodec<string>({"a","b","c"},"a"), string("a"), "11");
}

/*****************************************************************************/
/*****************************************************************************/


int main(void)
{
  testUnsigned();
  testEnum();

/*
  encoding::EnumCodec<string> c2({"hola","adios"}, "hola");
  cout << c2.encode("hola") << endl;
  cout << c2.decode(encoding::Bitset(1, 1)) << endl;

  encoding::FloatCodec c3;
  cout << c3.decode(c3.encode(1.5f)) << endl;
  
  encoding::FixedPointFloatCodec<4,28> c4;
  cout << "bits: " << c4.sizeInBits << endl;
  cout << c4.decode(c4.encode(1.5f)) << endl;

  std::istringstream in({0x01,0x25,0x23,0x53});
  encoding::InputStream input(in);
  cout << "paco: " << input.read(c1) << endl;
  cout << "paco: " << input.read(c1) << endl;

  encoding::UnsignedIntegerCodec c5(8);  
  encoding::UnsignedIntegerCodec c6(4);  
  std::stringstream out;
  encoding::OutputStream output(out);
  output.write(c5, 97U);
  output.write(c5, 98U);
  output.write(c5, 99U);
  output.write(c6, 6U);
  output.write(c6, 4U);
  output.close();
  cout << "miau: " << out.str() << endl;
*/
  return 0;
}

// Copyright (c) 2013, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)


#include "test_integer.hpp"
#include "test_enum.hpp"

#include "encoding/enum.hpp"
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

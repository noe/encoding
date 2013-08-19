#include <iostream>
#include <sstream>
#include <string>
#include "encoding/enum.hpp"
#include "encoding/integer.hpp"
#include "encoding/float.hpp"
#include "encoding/input.hpp"

using namespace std;

int main(void)
{
  encoding::UnsignedIntegerCodec c1(16);  
  cout << c1.encode(1024) <<endl;

  encoding::EnumCodec<string> c2({"hola","adios"}, "hola");
  cout << c2.encode("hola") << endl;
  cout << c2.decode(boost::dynamic_bitset<>(1, 1)) << endl;

  encoding::FloatCodec c3;
  cout << c3.decode(c3.encode(1.5f)) << endl;
  
  encoding::FixedPointFloatCodec<4,28> c4;
  cout << "bits: " << c4.sizeInBits << endl;
  cout << c4.decode(c4.encode(1.5f)) << endl;

  std::istringstream buffer("0ab0");
  encoding::InputStream input(buffer);
  cout << "paco: " << input.read(c1) << endl;
  return 0;
}

#include <iostream>
#include <string>
#include "encoding/enum.hpp"
#include "encoding/integer.hpp"

using namespace std;

int main(void)
{
  encoding::UnsignedIntegerCodec caca(16);  
  cout << caca.encode(5) <<endl;

  encoding::EnumCodec<string> codec({"hola","adios"}, "hola");
  cout << codec.encode("hola") << endl;
  cout << codec.decode(boost::dynamic_bitset<>(1, 1)) << endl;
  return 0;
}

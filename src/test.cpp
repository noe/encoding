#include <iostream>
#include <string>
#include "encoding.hpp"

using namespace std;

int main(void)
{
  genalg::UnsignedIntegerCodec caca(16);  
  cout << caca.encode(5) <<endl;

  genalg::EnumCodec<string> codec({"hola","adios"}, "hola");
  cout << codec.encode("hola") << endl;
  cout << codec.decode(boost::dynamic_bitset<>(1, 0)) << endl;
  return 0;
}

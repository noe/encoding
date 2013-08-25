#include <sstream>

#include "encoding/codec.hpp"
#include "encoding/integer.hpp"
#include "encoding/input.hpp"
#include "encoding/output.hpp"


void testInputStream ()
{
  std::istringstream in({0x01,0x25,0x23,0x53});
  encoding::InputStream input(in);

  encoding::UnsignedIntegerCodec c(16);  
  std::cout << "paco: " << input.read(c) << std::endl;
  std::cout << "paco: " << input.read(c) << std::endl;
}

void testOutputStream ()
{
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
  std::cout << "miau: " << out.str() << std::endl;
}

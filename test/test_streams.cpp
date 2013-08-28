#include <sstream>

#include "encoding/codec.hpp"
#include "encoding/integer.hpp"
#include "encoding/input.hpp"
#include "encoding/output.hpp"

#include <gtest/gtest.h>

TEST(TestInputStream, SimpleTest)
{
  std::istringstream in({0x01,0x25,0x23,0x53});
  encoding::InputStream input(in);

  encoding::UnsignedIntegerCodec c(16);  
  ASSERT_EQ(input.read(c), 0x0125);
  ASSERT_EQ(input.read(c), 0x2353);
}

TEST(testOutputStream, SimpleTest)
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
  ASSERT_EQ(out.str(), std::string("abcd"));
}

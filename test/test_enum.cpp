#include "test_functions.hpp"

#include "encoding/codec.hpp"
#include "encoding/enum.hpp"

#include <iostream>
#include <string>

#include <gtest/gtest.h>

/*****************************************************************************/
TEST (TestEnum, SimpleConversions)
{
  using namespace std;
  using namespace encoding;

  testEncodeAndDecode(EnumCodec<string>({"a","b","c"},"a"), string("a"), "00");

  testEncodeAndDecode(EnumCodec<string>({"a","b","c"},"a"), string("b"), "01");

  testEncodeAndDecode(EnumCodec<string>({"a","b","c"},"a"), string("c"), "10");

  testDecode(EnumCodec<string>({"a","b","c"},"a"), string("a"), "11");
}


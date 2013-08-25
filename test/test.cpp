// Copyright (c) 2013, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)


#include "test_integer.hpp"
#include "test_enum.hpp"
#include "test_float.hpp"
#include "test_streams.hpp"

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
  cout << "** TEST UNSIGNED CODECS ************************************************" << endl;
  testUnsigned ();

  cout << "** TEST RANGE CODECS ***************************************************" << endl;
  testRange ();

  cout << "** TEST ENUM CODECS ****************************************************" << endl;
  testEnum ();

  cout << "** TEST FLOAT CODECS ***************************************************" << endl;
  testFloat ();

  cout << "** TEST OUTPUT STREAM **************************************************" << endl;
  testInputStream ();

/*

  encoding::FloatCodec c3;
  cout << c3.decode(c3.encode(1.5f)) << endl;
  
  encoding::FixedPointFloatCodec<4,28> c4;
  cout << "bits: " << c4.sizeInBits << endl;
  cout << c4.decode(c4.encode(1.5f)) << endl;

*/
  return 0;
}

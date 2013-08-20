#ifndef ENCODING_INPUT_HEADER_SEEN__
#define ENCODING_INPUT_HEADER_SEEN__

#include "encoding/codec.hpp"


namespace encoding
{
  struct InputError { };

  class InputStream
  {

    public:

      inline InputStream (std::istream& in);

      template<typename Type>
      Type read(Codec<Type>& codec) throw(InputError);

    private:

      inline void fillBuffer(std::size_t neededBitsFromInput) throw(InputError);

      std::istream& input;

      boost::dynamic_bitset<> buffer;

      std::size_t availableBitsInBuffer; /* least significant ones */    
  };
}

#include "encoding/detail/input_impl.hpp"

#endif

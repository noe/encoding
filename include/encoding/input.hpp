// Copyright (c) 2013, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef ENCODING_INPUT_HEADER_SEEN__
#define ENCODING_INPUT_HEADER_SEEN__

#include "encoding/codec.hpp"


namespace encoding
{
  struct InputError { };

  class InputStream
  {

    public:

      inline InputStream (std::istream& input);

      template<typename Type>
      Type read(Codec<Type>& codec) throw(InputError);

    private:

      inline void fillBuffer(std::size_t neededBitsFromInput) throw(InputError);

      std::istream& input_;

      Bitset buffer_;

  };
}

#include "encoding/detail/input_impl.hpp"

#endif

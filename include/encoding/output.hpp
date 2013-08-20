// Copyright (c) 2013, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

#ifndef ENCODING_OUTPUT_HEADER_SEEN__
#define ENCODING_OUTPUT_HEADER_SEEN__

#include "encoding/codec.hpp"

namespace encoding
{
  struct OutputError { };

  class OutputStream
  {
    public:

      OutputStream(std::ostream& output);
      ~OutputStream();
    
      template<typename Type>
      void write(Codec<Type>& codec, Type value) throw(OutputError);

      void close();

    private:

      void flushInternalBuffer() throw(OutputError);

      std::ostream& output_;

      Bitset buffer_;

      bool closed_;
  };
}

#include "encoding/detail/output_impl.hpp"
#endif

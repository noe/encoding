#ifndef ENCODING_OUTPUT_HEADER_SEEN__
#define ENCODING_OUTPUT_HEADER_SEEN__

#include "encoding/codec.hpp"

namespace encoding
{
  struct OutputError { };

  class OutputStream
  {
    public:

      OutputStream(std::ostream& out);
      ~OutputStream();
    
      template<typename Type>
      void write(Codec<Type>& codec, Type value) throw(OutputError);

      void close();

    private:

      void flushInternalBuffer() throw(OutputError);

      std::ostream& output;

      Bitset buffer;

      bool closed;
  };
}

#include "encoding/detail/output_impl.hpp"
#endif

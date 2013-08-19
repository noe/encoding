
namespace encoding
{
  class OutputStream
  {
    std::ostream& output;

    
    template<typename Type>
    void write(Codec<Type>& codec, Type value);

  };
}

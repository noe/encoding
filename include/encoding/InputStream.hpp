


namespace encoding
{
  class InputStream
  {
    std::istream& input;

    
    template<typename Type>
    Type read(Codec<Type>& codec);

  };
}

#include <cassert>
#include <cmath>
#include <algorithm>

namespace encoding
{

///////////////////////////////////////////////////////////////////////////////
namespace details
{
  inline std::size_t bits4enum(std::size_t numElements)
  {
    return std::size_t(std::log2(float(numElements)));
  }
}

///////////////////////////////////////////////////////////////////////////////
template<typename EnumType>
EnumCodec<EnumType>::EnumCodec(std::initializer_list<EnumType> possibleValues,
                               EnumType defaultEnumValue)
  : Codec<EnumType>(details::bits4enum(possibleValues.size())),
    defaultValue(defaultEnumValue),
    enumValues(possibleValues),
    auxCodec(Codec<EnumType>::sizeInBits)
{
  typename std::vector<EnumType>::const_iterator
     it = find(enumValues.begin(), enumValues.end(), defaultEnumValue);
  assert (it != enumValues.end());
}

///////////////////////////////////////////////////////////////////////////////
template<typename EnumType>
boost::dynamic_bitset<> EnumCodec<EnumType>::encode(EnumType value) const
{
  typename std::vector<EnumType>::const_iterator it =
        std::find(enumValues.begin(), enumValues.end(), value);
  assert (it != enumValues.end());
  std::ptrdiff_t index = it - enumValues.begin();
  return auxCodec.encode(index);
}

///////////////////////////////////////////////////////////////////////////////
template<typename EnumType>
EnumType EnumCodec<EnumType>::decode(boost::dynamic_bitset<> bits) const
{
  uint32_t index = auxCodec.decode(bits);
  return index < enumValues.size()? enumValues[index] : defaultValue;
}

}

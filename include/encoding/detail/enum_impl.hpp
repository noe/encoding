// Copyright (c) 2013, Noe Casas (noe.casas@gmail.com).
// Distributed under New BSD License.
// (see accompanying file COPYING)

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
    unsigned int maxRepresentableIndex = numElements - 1;
    unsigned int bitsNeeded = 0;
    while (maxRepresentableIndex >>= 1)
    {
      bitsNeeded++;
    }
    return bitsNeeded + 1;
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
Bitset EnumCodec<EnumType>::encode(EnumType value) const
{
  typename std::vector<EnumType>::const_iterator it =
        std::find(enumValues.begin(), enumValues.end(), value);
  assert (it != enumValues.end());
  std::ptrdiff_t index = it - enumValues.begin();
  return auxCodec.encode(index);
}

///////////////////////////////////////////////////////////////////////////////
template<typename EnumType>
EnumType EnumCodec<EnumType>::decode(const Bitset& bits) const
{
  uint32_t index = auxCodec.decode(bits);
  return index < enumValues.size()? enumValues[index] : defaultValue;
}

}

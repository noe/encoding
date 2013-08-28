Encoding library
================

Header-only C++11 library to encode pieces of data with tight control over their bit-level representation.

Stuff it allows:
* Two's complement encoding/decoding.
* Gray encoding/decoding.
* Encoding/decoding of enumerations.
* IEEE floating point number encoding/decoding.
* Fixed point number encoding/decoding.
* Encoding/decoding of any combination of the above into/from binary streams.

For unit tests, it uses Google C++ Testing Framework.

Its original intent was to be used for the genotype encoding for evolutionary algorithms. However, nothing constraints its use for other encoding needs.

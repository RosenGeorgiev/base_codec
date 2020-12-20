[![License: WTFPL](http://www.wtfpl.net/wp-content/uploads/2012/12/wtfpl-badge-2.png)](http://www.wtfpl.net/txt/copying/)
# About
`base_codec` is a library containing base16/32/64 encoding/decoding routines, implemnting
[RFC4648](https://tools.ietf.org/html/rfc4648).

# Requirements
This library depends on Catch2 for testing. Not mandatory, since you can turn of the tests with
`-DBASE_CODEC_ENABLE_TESTS=OFF`.

# Usage
## Using with CMake
Just add it as a subdirectory and link it to your program. It builds both static and dynamic
libraries and you can choose between the `base_codec::base_codec_static` and
`base_codec::base_codec_shared` targets.

```
add_subdirectory(base_codec)
...
target_link_libraries(my_executable PRIVATE base_codec::base_codec_static)
```

## Using the library
Just include the appropriate header and call the encoding/decoding routines.

Base16:
```
#include <vector>
#include <cstdint>
#include <cassert>
#include <system_error>

#include <base_codec/base16.hpp>

void encode()
{
    std::vector<std::uint8_t> encode_data = {
        'f', 'o', 'o', 'b', 'a', 'r'
    };

    std::error_code ec;
    auto res = rs::base_codec::base16_encode(encode_data, ec);
    assert(!ec);
    assert(res == "666F6F626172");
}

void decode()
{
    std::string decode_data = "666F6F626172";

    std::error_code ec;
    auto res = rs::base_codec::base16_decode(decode_data, ec);
    assert(!ec);
    assert(res == std::vector<std::uint8_t>{'f', 'o', 'o', 'b', 'a', 'r'});
}
```

[![License: WTFPL](http://www.wtfpl.net/wp-content/uploads/2012/12/wtfpl-badge-2.png)](http://www.wtfpl.net/txt/copying/)
# About
`base_codec` is a library containing base16/32/64 encoding/decoding routines, implementing
[RFC4648](https://tools.ietf.org/html/rfc4648). The code is not battle tested yet, so it might have
issues.

# Requirements
- [Catch2](https://github.com/catchorg/Catch2) for testing. Not mandatory, since you can turn of
the tests with `-DBASE_CODEC_ENABLE_TESTS=OFF`.
- CMake
- Compiler with C++20 support

# Usage
## Using with CMake
Just add it as a subdirectory and link it to your program. It builds both static and dynamic
libraries and you can choose between the `base_codec::base_codec_static` and
`base_codec::base_codec_shared` targets.

```CMake
add_subdirectory(base_codec)
...
target_link_libraries(my_executable PRIVATE base_codec::base_codec_static)
```

## Using the library
Just include the appropriate header and call the encoding/decoding routines.

Base16:
```cpp
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

void validate()
{
    std::string validate_data = "666F6F626172";

    auto res = rs::base_codec::is_base16(decode_data);
    assert(res == true);
}
```

Base32:
```cpp
#include <vector>
#include <cstdint>
#include <cassert>
#include <system_error>

#include <base_codec/base32.hpp>

void encode()
{
    std::vector<std::uint8_t> encode_data = {
        'f', 'o', 'o', 'b', 'a', 'r'
    };

    std::error_code ec;
    auto res = rs::base_codec::base32_encode(encode_data, ec);
    assert(!ec);
    assert(res == "MZXW6YTBOI======");
}

void decode()
{
    std::string decode_data = "MZXW6YTBOI======";

    std::error_code ec;
    auto res = rs::base_codec::base32_decode(decode_data, ec);
    assert(!ec);
    assert(res == std::vector<std::uint8_t>{'f', 'o', 'o', 'b', 'a', 'r'});
}

void validate()
{
    std::string validate_data = "MZXW6YTBOI======";

    auto res = rs::base_codec::is_base32(decode_data);
    assert(res == true);
}
```

Base32Hex:
```cpp
#include <vector>
#include <cstdint>
#include <cassert>
#include <system_error>

#include <base_codec/base32.hpp>

void encode()
{
    std::vector<std::uint8_t> encode_data = {
        'f', 'o', 'o', 'b', 'a', 'r'
    };

    std::error_code ec;
    auto res = rs::base_codec::base32hex_encode(encode_data, ec);
    assert(!ec);
    assert(res == "MZXW6YTBOI======");
}

void decode()
{
    std::string decode_data = "MZXW6YTBOI======";

    std::error_code ec;
    auto res = rs::base_codec::base32hex_decode(decode_data, ec);
    assert(!ec);
    assert(res == std::vector<std::uint8_t>{'f', 'o', 'o', 'b', 'a', 'r'});
}

void validate()
{
    std::string validate_data = "MZXW6YTBOI======";

    auto res = rs::base_codec::is_base32hex(decode_data);
    assert(res == true);
}
```

Base64:
```cpp
#include <vector>
#include <cstdint>
#include <cassert>
#include <system_error>

#include <base_codec/base64.hpp>

void encode()
{
    std::vector<std::uint8_t> encode_data = {
        'f', 'o', 'o', 'b', 'a', 'r'
    };

    std::error_code ec;
    auto res = rs::base_codec::base64_encode(encode_data, ec);
    assert(!ec);
    assert(res == "Zm9vYmFy");
}

void decode()
{
    std::string decode_data = "Zm9vYmFy";

    std::error_code ec;
    auto res = rs::base_codec::base64_decode(decode_data, ec);
    assert(!ec);
    assert(res == std::vector<std::uint8_t>{'f', 'o', 'o', 'b', 'a', 'r'});
}

void validate()
{
    std::string validate_data = "Zm9vYmFy";

    auto res = rs::base_codec::is_base64(decode_data);
    assert(res == true);
}
```


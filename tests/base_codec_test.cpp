#include <catch2/catch.hpp>

#include <system_error>

#include <base_codec/base16.hpp>
#include <base_codec/base32.hpp>
#include <base_codec/base64.hpp>


TEST_CASE(
    "Base16 encode",
    "[base16_encode]"
)
{
    SECTION("Encode empty")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_encode({}, ec) == "");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'f'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_encode({'f'}, ec) == "66");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'fo'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_encode({'f', 'o'}, ec) == "666F");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'foo'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_encode({'f', 'o', 'o'}, ec) == "666F6F");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'foob'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_encode({'f', 'o', 'o', 'b'}, ec) == "666F6F62");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'fooba'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_encode({'f', 'o', 'o', 'b', 'a'}, ec) == "666F6F6261");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'foobar'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_encode({'f', 'o', 'o', 'b', 'a', 'r'}, ec) == "666F6F626172");
        REQUIRE_FALSE(ec);
    }
}

TEST_CASE(
    "Base16 decode",
    "[base16_decode]"
)
{
    SECTION("Decode empty")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_decode("", ec) == std::vector<std::uint8_t>{});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode '66'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_decode("66", ec) == std::vector<std::uint8_t>{'f'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode '666F'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_decode("666F", ec) == std::vector<std::uint8_t>{'f', 'o'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode '666F6F'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_decode("666F6F", ec) == std::vector<std::uint8_t>{'f', 'o', 'o'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode '666F6F62'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_decode("666F6F62", ec) == std::vector<std::uint8_t>{'f', 'o', 'o', 'b'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode '666F6F6261'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_decode("666F6F6261", ec) == std::vector<std::uint8_t>{'f', 'o', 'o', 'b', 'a'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode '666F6F626172'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_decode("666F6F626172", ec) == std::vector<std::uint8_t>{'f', 'o', 'o', 'b', 'a', 'r'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode illegal sequence")
    {
        auto base64_str = "Zm9vYmFy";
        std::error_code ec;
        rs::base_codec::base16_decode(base64_str, ec);
        REQUIRE(ec);
    }

    SECTION("Decode single letter")
    {
        std::error_code ec;
        rs::base_codec::base16_decode("F", ec);
        REQUIRE(ec);
    }
}

TEST_CASE(
    "Base16 validate",
    "[is_base16]"
)
{
    SECTION("Validate if string is Base16 encoded")
    {
        REQUIRE(rs::base_codec::is_base16("666F6F626172"));
        REQUIRE_FALSE(rs::base_codec::is_base16("Zm9vYmFy"));
    }
}

TEST_CASE(
    "Base32 encode",
    "[base32_encode]"
)
{
    SECTION("Encode empty")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_encode({}, ec) == "");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'f'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_encode({'f'}, ec) == "MY======");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'fo'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_encode({'f', 'o'}, ec) == "MZXQ====");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'foo'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_encode({'f', 'o', 'o'}, ec) == "MZXW6===");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'foob'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_encode({'f', 'o', 'o', 'b'}, ec) == "MZXW6YQ=");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'fooba'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_encode({'f', 'o', 'o', 'b', 'a'}, ec) == "MZXW6YTB");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'foobar'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_encode({'f', 'o', 'o', 'b', 'a', 'r'}, ec) == "MZXW6YTBOI======");
        REQUIRE_FALSE(ec);
    }
}

TEST_CASE(
    "Base32 decode",
    "[base32_decode]"
)
{
    SECTION("Decode empty")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_decode("", ec) == std::vector<std::uint8_t>{});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'MY======'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_decode("MY======", ec) == std::vector<std::uint8_t>{'f'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'MZXQ===='")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_decode("MZXQ====", ec) == std::vector<std::uint8_t>{'f', 'o'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'MZXW6==='")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_decode("MZXW6===", ec) == std::vector<std::uint8_t>{'f', 'o', 'o'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'MZXW6YQ='")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_decode("MZXW6YQ=", ec) == std::vector<std::uint8_t>{'f', 'o', 'o', 'b'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'MZXW6YTB'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_decode("MZXW6YTB", ec) == std::vector<std::uint8_t>{'f', 'o', 'o', 'b', 'a'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'MZXW6YTBOI======'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_decode("MZXW6YTBOI======", ec) == std::vector<std::uint8_t>{'f', 'o', 'o', 'b', 'a', 'r'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode invalid")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_decode("394uijifkwlenkl2jh34", ec) == std::vector<std::uint8_t>{});
        REQUIRE(ec);
    }
}

TEST_CASE(
    "Base32 validate",
    "[is_base32]"
)
{
    SECTION("Validate if string is Base32 encoded")
    {
        REQUIRE(rs::base_codec::is_base32("MZXW6YTBOI======"));
        REQUIRE_FALSE(rs::base_codec::is_base32("daskjdasd-9uas900909009asdasd"));
    }
}

TEST_CASE(
    "Base32Hex encode",
    "[base32hex_encode]"
)
{
    SECTION("Encode empty")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32hex_encode({}, ec) == "");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'f'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32hex_encode({'f'}, ec) == "CO======");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'fo'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32hex_encode({'f', 'o'}, ec) == "CPNG====");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'foo'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32hex_encode({'f', 'o', 'o'}, ec) == "CPNMU===");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'foob'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32hex_encode({'f', 'o', 'o', 'b'}, ec) == "CPNMUOG=");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'fooba'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32hex_encode({'f', 'o', 'o', 'b', 'a'}, ec) == "CPNMUOJ1");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'foobar'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32hex_encode({'f', 'o', 'o', 'b', 'a', 'r'}, ec) == "CPNMUOJ1E8======");
        REQUIRE_FALSE(ec);
    }
}

TEST_CASE(
    "Base64 encode",
    "[base64_encode]"
)
{
    SECTION("Encode empty")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64_encode({}, ec) == "");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'f'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64_encode({'f'}, ec) == "Zg==");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'fo'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64_encode({'f', 'o'}, ec) == "Zm8=");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'foo'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64_encode({'f', 'o', 'o'}, ec) == "Zm9v");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'foob'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64_encode({'f', 'o', 'o', 'b'}, ec) == "Zm9vYg==");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'fooba'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64_encode({'f', 'o', 'o', 'b', 'a'}, ec) == "Zm9vYmE=");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'foobar'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64_encode({'f', 'o', 'o', 'b', 'a', 'r'}, ec) == "Zm9vYmFy");
        REQUIRE_FALSE(ec);
    }
}

TEST_CASE(
    "Base64 decode",
    "[base64_decode]"
)
{
    SECTION("Decode empty")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64_decode("", ec) == std::vector<std::uint8_t>{});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'Zg=='")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64_decode("Zg==", ec) == std::vector<std::uint8_t>{'f'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'Zm8='")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64_decode("Zm8=", ec) == std::vector<std::uint8_t>{'f', 'o'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'Zm9v'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64_decode("Zm9v", ec) == std::vector<std::uint8_t>{'f', 'o', 'o'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'Zm9vYg=='")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64_decode("Zm9vYg==", ec) == std::vector<std::uint8_t>{'f', 'o', 'o', 'b'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'Zm9vYmE='")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64_decode("Zm9vYmE=", ec) == std::vector<std::uint8_t>{'f', 'o', 'o', 'b', 'a'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'Zm9vYmFy'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64_decode("Zm9vYmFy", ec) == std::vector<std::uint8_t>{'f', 'o', 'o', 'b', 'a', 'r'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode invalid")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64_decode("****", ec) == std::vector<std::uint8_t>{});
        REQUIRE(ec);
    }
}

TEST_CASE(
    "Base64 validate",
    "[is_base64]"
)
{
    SECTION("Validate if string is Base64 encoded")
    {
        REQUIRE(rs::base_codec::is_base64("Zm9vYmFy"));
        REQUIRE_FALSE(rs::base_codec::is_base64("****"));
    }
}

TEST_CASE(
    "Base64Url encode",
    "[base64url_encode]"
)
{
    SECTION("Encode empty")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64url_encode({}, ec) == "");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'f'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64url_encode({'f'}, ec) == "Zg");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'fo'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64url_encode({'f', 'o'}, ec) == "Zm8");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'foo'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64url_encode({'f', 'o', 'o'}, ec) == "Zm9v");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'foob'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64url_encode({'f', 'o', 'o', 'b'}, ec) == "Zm9vYg");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'fooba'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64url_encode({'f', 'o', 'o', 'b', 'a'}, ec) == "Zm9vYmE");
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'foobar'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64url_encode({'f', 'o', 'o', 'b', 'a', 'r'}, ec) == "Zm9vYmFy");
        REQUIRE_FALSE(ec);
    }
}

TEST_CASE(
    "Base64Url decode",
    "[base64url_decode]"
)
{
    SECTION("Decode empty")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64url_decode("", ec) == std::vector<std::uint8_t>{});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'Zg'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64url_decode("Zg", ec) == std::vector<std::uint8_t>{'f'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'Zm8'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64url_decode("Zm8", ec) == std::vector<std::uint8_t>{'f', 'o'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'Zm9v'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64url_decode("Zm9v", ec) == std::vector<std::uint8_t>{'f', 'o', 'o'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'Zm9vYg'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64url_decode("Zm9vYg", ec) == std::vector<std::uint8_t>{'f', 'o', 'o', 'b'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'Zm9vYmE'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64url_decode("Zm9vYmE", ec) == std::vector<std::uint8_t>{'f', 'o', 'o', 'b', 'a'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'Zm9vYmFy'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base64url_decode("Zm9vYmFy", ec) == std::vector<std::uint8_t>{'f', 'o', 'o', 'b', 'a', 'r'});
        REQUIRE_FALSE(ec);
    }
}

TEST_CASE(
    "Base64Url validate",
    "[is_base64url]"
)
{
    SECTION("Validate if string is Base64Url encoded")
    {
        REQUIRE(rs::base_codec::is_base64url("Zm9vYmFy"));
        REQUIRE_FALSE(rs::base_codec::is_base64url("****"));
    }
}


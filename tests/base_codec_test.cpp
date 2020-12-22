#include <catch2/catch.hpp>

#include <system_error>

#include <base_codec/base16.hpp>
#include <base_codec/base32.hpp>


TEST_CASE(
    "Base16",
    "[base16_encode][base16_decode][is_base16]"
)
{
    SECTION("Encode empty")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_encode({}, ec) == "");
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode empty")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_decode("", ec) == std::vector<std::uint8_t>{});
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'f'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_encode({'f'}, ec) == "66");
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode '66'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_decode("66", ec) == std::vector<std::uint8_t>{'f'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'fo'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_encode({'f', 'o'}, ec) == "666F");
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode '666F'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_decode("666F", ec) == std::vector<std::uint8_t>{'f', 'o'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'foo'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_encode({'f', 'o', 'o'}, ec) == "666F6F");
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode '666F6F'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_decode("666F6F", ec) == std::vector<std::uint8_t>{'f', 'o', 'o'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'foob'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_encode({'f', 'o', 'o', 'b'}, ec) == "666F6F62");
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode '666F6F62'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_decode("666F6F62", ec) == std::vector<std::uint8_t>{'f', 'o', 'o', 'b'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'fooba'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_encode({'f', 'o', 'o', 'b', 'a'}, ec) == "666F6F6261");
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode '666F6F6261'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_decode("666F6F6261", ec) == std::vector<std::uint8_t>{'f', 'o', 'o', 'b', 'a'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'foobar'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base16_encode({'f', 'o', 'o', 'b', 'a', 'r'}, ec) == "666F6F626172");
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

    SECTION("Validate if string is Base16 encoded")
    {
        REQUIRE(rs::base_codec::is_base16("666F6F626172"));
        REQUIRE_FALSE(rs::base_codec::is_base16("Zm9vYmFy"));
    }
}

TEST_CASE(
    "Base32",
    "[base32_encode][base32_decode][is_base32]"
)
{
    SECTION("Encode empty")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_encode({}, ec) == "");
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode empty")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_decode("", ec) == std::vector<std::uint8_t>{});
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'f'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_encode({'f'}, ec) == "MY======");
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'MY======'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_decode("MY======", ec) == std::vector<std::uint8_t>{'f'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'fo'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_encode({'f', 'o'}, ec) == "MZXQ====");
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'MZXQ===='")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_decode("MZXQ====", ec) == std::vector<std::uint8_t>{'f', 'o'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'foo'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_encode({'f', 'o', 'o'}, ec) == "MZXW6===");
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'MZXW6==='")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_decode("MZXW6===", ec) == std::vector<std::uint8_t>{'f', 'o', 'o'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'foob'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_encode({'f', 'o', 'o', 'b'}, ec) == "MZXW6YQ=");
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'MZXW6YQ='")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_decode("MZXW6YQ=", ec) == std::vector<std::uint8_t>{'f', 'o', 'o', 'b'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'fooba'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_encode({'f', 'o', 'o', 'b', 'a'}, ec) == "MZXW6YTB");
        REQUIRE_FALSE(ec);
    }

    SECTION("Decode 'MZXW6YTB'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_decode("MZXW6YTB", ec) == std::vector<std::uint8_t>{'f', 'o', 'o', 'b', 'a'});
        REQUIRE_FALSE(ec);
    }

    SECTION("Encode 'foobar'")
    {
        std::error_code ec;
        REQUIRE(rs::base_codec::base32_encode({'f', 'o', 'o', 'b', 'a', 'r'}, ec) == "MZXW6YTBOI======");
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

    SECTION("Validate if string is Base32 encoded")
    {
        REQUIRE(rs::base_codec::is_base32("MZXW6YTBOI======"));
        REQUIRE_FALSE(rs::base_codec::is_base32("daskjdasd-9uas900909009asdasd"));
    }
}

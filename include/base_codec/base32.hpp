#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <string_view>
#include <system_error>


namespace rs
{
namespace base_codec
{

/**
 * @brief Encodes a vector of bytes as a Base32 string.
 *
 * @param[in] a_data Bytes to encode.
 * @param[in][out] a_ec std::error_code that gets set if a problem occurs.
 * @param[in] a_padding Should the string be padded at the end with the given padding character, if
 * it's too short.
 * @param[in] a_pad_character Character to use as padding.
 *
 * @returns std::string The encoded string. Empty if an error occurred.
 */
auto base32_encode(
    std::vector<std::uint8_t> const& a_data,
    std::error_code& a_ec,
    bool a_padding = true,
    char a_pad_character = '='
)
-> std::string;

/**
 * @brief
 *
 * @param[in] a_data Base32 encoded string to decode.
 * @param[in][out] a_ec std::error_code that gets set if a problem occurs.
 * @param[in] a_strict Enable/disable strict mode. When on - if an invalid Base32 alphabet
 * character is encountered - an error is returned, else it just gets ignored and the function
 * proceeds to the next character. Disabling this check is not recommended.
 * @param[in] a_pad_character Character to recognize as a padding character.
 *
 * @returns std::vector<std::uint8_t> Byte representation of the decoded string.
 */
auto base32_decode(
    std::string_view const& a_data,
    std::error_code& a_ec,
    bool a_strict = true,
    char a_pad_character = '='
)
-> std::vector<std::uint8_t>;

}   // namespace base_codec
}   // namespace rs


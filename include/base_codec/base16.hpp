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
 * @brief Encodes a vector of bytes as a Base16 string.
 *
 * @param[in] a_data Bytes to encode.
 * @param[in][out] a_ec std::error_code that gets set if a problem occurs.
 *
 * @returns std::string Base16 representation of the data. Empty if an error occurred.
 */
auto base16_encode(
    std::vector<std::uint8_t> const& a_data,
    std::error_code& a_ec
)
-> std::string;

/**
 * @brief Decodes a Base16 encoded string.
 *
 * @param[in] a_data Base16 encoded string to decode.
 * @param[in][out] a_ec std::error_code that gets set if a problem occurs.
 * @param[in] a_strict Enable/disable strict mode. When on - if an invalid Base16 alphabet
 * character is encountered - an error is returned, else it just gets ignored and the function
 * proceeds to the next character. Disabling this check is not recommended.
 *
 * @returns std::vector<std::uint8_t> Byte representation of the decoded string.
 */
auto base16_decode(
    std::string_view const& a_data,
    std::error_code& a_ec,
    bool a_strict = true
)
-> std::vector<std::uint8_t>;

/**
 * @brief Checks if the string contains invalid Base16 characters.
 *
 * @param[in] String to check for conformance.
 *
 * @returns true If the string is possibly Base16 encoded.
 * @returns false If the string can't be Base16 encoded, or at least not strictly.
 */
auto is_base16(std::string_view const& a_data) -> bool;

}   // namespace base_codec
}   // namespace rs


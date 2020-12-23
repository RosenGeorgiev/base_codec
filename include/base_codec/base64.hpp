/**
 * @file base64.hpp
 *
 * Holds the implementation of the Base64 algorithms from https://tools.ietf.org/html/rfc4648
 */
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
 * @brief Encodes a vector of bytes as a Base64 string.
 *
 * @param[in] a_data Bytes to encode.
 * @param[in][out] a_ec std::error_code that gets set if a problem occurs.
 * @param[in] a_padding Should the string be padded at the end with the given padding character, if
 * it's too short.
 * @param[in] a_pad_character Character to use as padding.
 *
 * @returns std::string The encoded string. Empty if an error occurred.
 */
auto base64_encode(
    std::vector<std::uint8_t> const& a_data,
    std::error_code& a_ec,
    bool a_padding = true,
    char a_pad_character = '='
)
-> std::string;

/**
 * @brief Encodes a vector of bytes as a Base64Url string.
 *
 * @param[in] a_data Bytes to encode.
 * @param[in][out] a_ec std::error_code that gets set if a problem occurs.
 * @param[in] a_padding Should the string be padded at the end with the given padding character, if
 * it's too short. For url's this is recommended to be off. If turned on, the padding symbols won't
 * be automatically percent encoded, which does not conform with standards.
 * @param[in] a_pad_character Character to use as padding.
 *
 * @returns std::string The encoded string. Empty if an error occurred.
 */
auto base64url_encode(
    std::vector<std::uint8_t> const& a_data,
    std::error_code& a_ec,
    bool a_padding = false,
    char a_pad_character = '='
)
-> std::string;

/**
 * @brief Decodes a Base64 encoded string.
 *
 * @param[in] a_data Base64 encoded string to decode.
 * @param[in][out] a_ec std::error_code that gets set if a problem occurs.
 * @param[in] a_strict Enable/disable strict mode. When on - if an invalid Base64 alphabet
 * character is encountered - an error is returned, else it just gets ignored and the function
 * proceeds to the next character. Disabling this check is not recommended.
 * @param[in] a_pad_character Character to recognize as a padding character.
 *
 * @returns std::vector<std::uint8_t> Byte representation of the decoded string.
 */
auto base64_decode(
    std::string_view const& a_data,
    std::error_code& a_ec,
    bool a_strict = true,
    char a_pad_character = '='
)
-> std::vector<std::uint8_t>;

/**
 * @brief Decodes a Base64Url encoded string.
 *
 * @param[in] a_data Base64Url encoded string to decode.
 * @param[in][out] a_ec std::error_code that gets set if a problem occurs.
 * @param[in] a_strict Enable/disable strict mode. When on - if an invalid Base64Url alphabet
 * character is encountered - an error is returned, else it just gets ignored and the function
 * proceeds to the next character. Disabling this check is not recommended.
 * @param[in] a_pad_character Character to recognize as a padding character.
 *
 * @returns std::vector<std::uint8_t> Byte representation of the decoded string.
 */
auto base64url_decode(
    std::string_view const& a_data,
    std::error_code& a_ec,
    bool a_strict = true,
    char a_pad_character = '='
)
-> std::vector<std::uint8_t>;

/**
 * @brief Checks if the string contains invalid Base64 characters.
 *
 * @param[in] a_data String to check for conformance.
 * @param[in] a_pad_character Character to recognize as a padding character.
 *
 * @returns true If the string is possibly Base64 encoded.
 * @returns false If the string can't be Base64 encoded, or at least not strictly.
 */
auto is_base64(
    std::string_view const& a_data,
    char a_pad_character = '='
)
-> bool;

/**
 * @brief Checks if the string contains invalid Base64Url characters.
 *
 * @param[in] a_data String to check for conformance.
 * @param[in] a_pad_character Character to recognize as a padding character.
 *
 * @returns true If the string is possibly Base64Url encoded.
 * @returns false If the string can't be Base64Url encoded, or at least not strictly.
 */
auto is_base64url(
    std::string_view const& a_data,
    char a_pad_character = '='
)
-> bool;

}   // namespace base_codec
}   // namespace rs


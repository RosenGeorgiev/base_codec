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
 * @param[in] a_input Bytes to encode.
 * @param[in] a_ec std::error_code that gets set if a problem occurs.
 *
 * @returns std::string Base16 representation of the data.
 */
auto base16_encode(
    std::vector<std::uint8_t> const& a_input,
    std::error_code& a_ec
)
-> std::string;

auto base16_decode(
    std::string_view const& a_data,
    std::error_code& a_ec,
    bool a_strict = true
)
-> std::vector<std::uint8_t>;

}   // namespace base_codec
}   // namespace rs


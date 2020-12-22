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

auto base32_encode(
    std::vector<std::uint8_t> const& a_data,
    std::error_code& a_ec,
    bool a_padding = true,
    char a_pad_character = '='
)
-> std::string;

}   // namespace base_codec
}   // namespace rs


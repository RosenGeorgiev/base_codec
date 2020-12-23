#include <base_codec/base16.hpp>

#include <sstream>
#include <cassert>
#include <stdexcept>
#include <unordered_map>


namespace rs
{
namespace base_codec
{

static std::vector<char> const base16_encode_alphabet = {
'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

static std::unordered_map<char, uint8_t> const base16_decode_alpahbet = {
    {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8},
    {'9', 9}, {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}
};

auto base16_encode(
    std::vector<std::uint8_t> const& a_data,
    std::error_code& a_ec
)
-> std::string
{
    std::ostringstream s;

    for (auto const datum : a_data)
    {
        std::uint8_t first_idx = datum >> 4;
        std::uint8_t second_idx = datum & 0b00001111;

        try
        {
            s << base16_encode_alphabet.at(first_idx)
              << base16_encode_alphabet.at(second_idx);
        } catch (std::out_of_range const& e)
        {
            a_ec = std::make_error_code(std::errc::result_out_of_range);
            assert(false && "you really shouldn't be here");
            return {};
        }
    }

    return s.str();
}

auto base16_decode(
    std::string_view const& a_data,
    std::error_code& a_ec,
    bool a_strict
)
-> std::vector<std::uint8_t>
{
    if (a_strict && a_data.size() % 2 != 0)
    {
        a_ec = std::make_error_code(std::errc::invalid_argument);
        return {};
    }

    std::vector<std::uint8_t> ret;
    ret.reserve(a_data.size() / 2);

    bool is_even = true;
    std::uint8_t decoded = 0;

    for (auto const datum : a_data)
    {
        try
        {
            if (is_even)
            {
                decoded |= base16_decode_alpahbet.at(datum) << 4;
            } else
            {
                decoded |= base16_decode_alpahbet.at(datum);
                ret.push_back(decoded);
                decoded = 0;
            }

            is_even = !is_even;
        } catch (std::out_of_range const& e)
        {
            if (a_strict)
            {
                a_ec = std::make_error_code(std::errc::invalid_argument);
                return {};
            }

            continue;
        }
    }

    return ret;
}

auto is_base16(std::string_view const& a_data) -> bool
{
    for (auto const datum : a_data)
    {
        if (!base16_decode_alpahbet.contains(datum))
        {
            return false;
        }
    }

    return true;
}

}   // namespace base_codec
}   // namespace rs


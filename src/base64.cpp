#include <base_codec/base64.hpp>

#include <bitset>
#include <sstream>
#include <cassert>
#include <stdexcept>
#include <unordered_map>


namespace rs
{
namespace base_codec
{

static std::vector<char> const base64_encode_alphabet = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
    'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4',
    '5', '6', '7', '8', '9', '+', '/'
};

static std::vector<char> const base64url_encode_alphabet = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
    'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4',
    '5', '6', '7', '8', '9', '-', '_'
};

static std::unordered_map<char, uint8_t> const base64_decode_alpahbet = {
    {'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}, {'I', 8},
    {'J', 9}, {'K', 10}, {'L', 11}, {'M', 12}, {'N', 13}, {'O', 14}, {'P', 15}, {'Q', 16},
    {'R', 17}, {'S', 18}, {'T', 19}, {'U', 20}, {'V', 21}, {'W', 22}, {'X', 23}, {'Y', 24},
    {'Z', 25}, {'a', 26}, {'b', 27}, {'c', 28}, {'d', 29}, {'e', 30}, {'f', 31}, {'g', 32},
    {'h', 33}, {'i', 34}, {'j', 35}, {'k', 36}, {'l', 37}, {'m', 38}, {'n', 39}, {'o', 40},
    {'p', 41}, {'q', 42}, {'r', 43}, {'s', 44}, {'t', 45}, {'u', 46}, {'v', 47}, {'w', 48},
    {'x', 49}, {'y', 50}, {'z', 51}, {'0', 52}, {'1', 53}, {'2', 54}, {'3', 55}, {'4', 56},
    {'5', 57}, {'6', 58}, {'7', 59}, {'8', 60}, {'9', 61}, {'+', 62}, {'/', 63}
};

static std::unordered_map<char, uint8_t> const base64url_decode_alpahbet = {
    {'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}, {'I', 8},
    {'J', 9}, {'K', 10}, {'L', 11}, {'M', 12}, {'N', 13}, {'O', 14}, {'P', 15}, {'Q', 16},
    {'R', 17}, {'S', 18}, {'T', 19}, {'U', 20}, {'V', 21}, {'W', 22}, {'X', 23}, {'Y', 24},
    {'Z', 25}, {'a', 26}, {'b', 27}, {'c', 28}, {'d', 29}, {'e', 30}, {'f', 31}, {'g', 32},
    {'h', 33}, {'i', 34}, {'j', 35}, {'k', 36}, {'l', 37}, {'m', 38}, {'n', 39}, {'o', 40},
    {'p', 41}, {'q', 42}, {'r', 43}, {'s', 44}, {'t', 45}, {'u', 46}, {'v', 47}, {'w', 48},
    {'x', 49}, {'y', 50}, {'z', 51}, {'0', 52}, {'1', 53}, {'2', 54}, {'3', 55}, {'4', 56},
    {'5', 57}, {'6', 58}, {'7', 59}, {'8', 60}, {'9', 61}, {'-', 62}, {'_', 63}
};

static auto base64_encode_algo(
    std::vector<std::uint8_t> const& a_data,
    std::error_code& a_ec,
    bool a_padding,
    char a_pad_character,
    std::vector<char> const& a_encode_alphabet
)
-> std::string
{
    std::ostringstream s;

    static std::bitset<24> const mask {0x3F};
    std::uint64_t num_bits = 0;
    std::bitset<24> bit_buffer {0};

    for (auto const datum : a_data)
    {
        bit_buffer <<= 8;
        bit_buffer |= datum;
        num_bits += 8;

        while (num_bits >= 6)
        {
            auto mask_at_pos = mask << (num_bits - 6);
            auto idx = bit_buffer & mask_at_pos;
            idx >>= num_bits - 6;
            // bit_buffer &= ~mask_at_pos;
            num_bits -= 6;
            try
            {
                s << a_encode_alphabet.at(idx.to_ulong());
            } catch (std::out_of_range const& e)
            {
                a_ec = std::make_error_code(std::errc::result_out_of_range);
                assert(false && "you shouldn't be here");
                return {};
            }
        }
    }

    if (num_bits > 0)
    {
        try
        {
            bit_buffer <<= 6 - num_bits;
            s << a_encode_alphabet.at((bit_buffer & mask).to_ulong());
        } catch (std::out_of_range const& e)
        {
            a_ec = std::make_error_code(std::errc::result_out_of_range);
            assert(false && "you shouldn't be here");
            return {};
        }
    }

    if (a_padding)
    {
        switch (a_data.size() % 3)
        {
        case 2:
            s << std::string(1, a_pad_character);
            break;
        case 1:
            s << std::string(2, a_pad_character);
            break;
        case 0:
            break;
        default:
            assert(false && "you really shoudn't be here");
            break;
        }
    }

    return s.str();
}

auto base64_encode(
    std::vector<std::uint8_t> const& a_data,
    std::error_code& a_ec,
    bool a_padding,
    char a_pad_character
)
-> std::string
{
    return base64_encode_algo(a_data, a_ec, a_padding, a_pad_character, base64_encode_alphabet);
}

auto base64url_encode(
    std::vector<std::uint8_t> const& a_data,
    std::error_code& a_ec,
    bool a_padding,
    char a_pad_character
)
-> std::string
{
    return base64_encode_algo(a_data, a_ec, a_padding, a_pad_character, base64url_encode_alphabet);
}

static auto base64_decode_algo(
    std::string_view const& a_data,
    std::error_code& a_ec,
    bool a_strict,
    char a_pad_character,
    std::unordered_map<char, uint8_t> const& a_decode_alphabet
)
-> std::vector<std::uint8_t>
{
    std::vector<std::uint8_t> ret;

    static std::bitset<24> const mask {0xFF};
    std::uint64_t num_bits = 0;
    std::bitset<24> bit_buffer;

    for (auto const datum : a_data)
    {
        if (datum == a_pad_character)
        {
            break;
        }

        try
        {
            std::uint8_t value = a_decode_alphabet.at(datum);
            bit_buffer <<= 6;
            bit_buffer |= value;
            num_bits += 6;

            while (num_bits >= 8)
            {
                auto mask_at_pos = mask << (num_bits - 8);
                auto value = bit_buffer & mask_at_pos;
                value >>= num_bits - 8;
                ret.push_back(static_cast<std::uint8_t>(value.to_ulong()));
                // bit_buffer &= ~mask_at_pos;
                num_bits -= 8;
            }
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

auto base64_decode(
    std::string_view const& a_data,
    std::error_code& a_ec,
    bool a_strict,
    char a_pad_character
)
-> std::vector<std::uint8_t>
{
    return base64_decode_algo(a_data, a_ec, a_strict, a_pad_character, base64_decode_alpahbet);
}

auto base64url_decode(
    std::string_view const& a_data,
    std::error_code& a_ec,
    bool a_strict,
    char a_pad_character
)
-> std::vector<std::uint8_t>
{
    return base64_decode_algo(a_data, a_ec, a_strict, a_pad_character, base64url_decode_alpahbet);
}

static auto is_base64_algo(
    std::string_view const& a_data,
    char a_pad_character,
    std::unordered_map<char, uint8_t> const& a_verify_alphabet
)
-> bool
{
    for (auto const datum : a_data)
    {
        if (datum != a_pad_character && !a_verify_alphabet.contains(datum))
        {
            return false;
        }
    }

    return true;
}

auto is_base64(
    std::string_view const& a_data,
    char a_pad_character
)
-> bool
{
    return is_base64_algo(a_data, a_pad_character, base64_decode_alpahbet);
}

auto is_base64url(
    std::string_view const& a_data,
    char a_pad_character
)
-> bool
{
    return is_base64_algo(a_data, a_pad_character, base64url_decode_alpahbet);
}

}   // namespace base_codec
}   // namespace rs


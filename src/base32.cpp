#include <base_codec/base32.hpp>

#include <bitset>
#include <sstream>
#include <cassert>
#include <stdexcept>
#include <unordered_map>

#include <iostream>


namespace rs
{
namespace base_codec
{

static std::vector<char> const base32_encode_alphabet = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
    'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '2', '3', '4', '5', '6', '7'
};

static std::vector<char> const base32hex_encode_alphabet = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
    'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
};

static std::unordered_map<char, uint8_t> const base32_decode_alpahbet = {
    {'A', 0},  {'B', 1},  {'C', 2},  {'D', 3},  {'E', 4},  {'F', 5},  {'G', 6},  {'H', 7}, {'I', 8},
    {'J', 9},  {'K', 10}, {'L', 11}, {'M', 12}, {'N', 13}, {'O', 14}, {'P', 15}, {'Q', 16},
    {'R', 17}, {'S', 18}, {'T', 19}, {'U', 20}, {'V', 21}, {'W', 22}, {'X', 23}, {'Y', 24},
    {'Z', 25}, {'2', 26}, {'3', 27}, {'4', 28}, {'5', 29}, {'6', 30}, {'7', 31}
};

static std::unordered_map<char, uint8_t> const base32hex_decode_alpahbet = {
    {'0', 0},  {'1', 1},  {'2', 2},  {'3', 3},  {'4', 4},  {'5', 5},  {'6', 6},  {'7', 7}, {'8', 8},
    {'9', 9},  {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}, {'G', 16},
    {'H', 17}, {'I', 18}, {'J', 19}, {'K', 20}, {'L', 21}, {'M', 22}, {'N', 23}, {'O', 24},
    {'P', 25}, {'Q', 26}, {'R', 27}, {'S', 28}, {'T', 29}, {'U', 30}, {'V', 31}
};

auto base32_encode(
    std::vector<std::uint8_t> const& a_data,
    std::error_code& a_ec,
    bool a_padding,
    char a_pad_character
)
-> std::string
{
    std::ostringstream s;

    static std::bitset<40> const mask {0x1F};
    std::uint64_t num_bits = 0;
    std::bitset<40> bit_buffer {0};

    for (auto const datum : a_data)
    {
        bit_buffer <<= 8;
        bit_buffer |= datum;
        num_bits += 8;

        while (num_bits >= 5)
        {
            auto mask_at_pos = mask << (num_bits - 5);
            auto idx = bit_buffer & mask_at_pos;
            idx >>= num_bits - 5;
            // bit_buffer &= ~mask_at_pos;
            num_bits -= 5;
            try
            {
                s << base32_encode_alphabet.at(idx.to_ulong());
            } catch (std::out_of_range const& e)
            {
                a_ec = std::make_error_code(std::errc::result_out_of_range);
                assert(false && "you shouldn't be here");
                return {};
            }
        }
    }

    // NOTE - At the end of this we might have a few bytes left (less than five) in the buffer,
    //        so we process them too.
    if (num_bits > 0)
    {
        try
        {
            // NOTE - We need to pad the bits on the right with 0 to make it 5 bits.
            bit_buffer <<= 5 - num_bits;
            s << base32_encode_alphabet.at((bit_buffer & mask).to_ulong());
        } catch (std::out_of_range const& e)
        {
            a_ec = std::make_error_code(std::errc::result_out_of_range);
            assert(false && "you shouldn't be here");
            return {};
        }
    }

    if (a_padding)
    {
        switch (a_data.size() % 5)
        {
        case 4:
            s << std::string(1, a_pad_character);
            break;
        case 3:
            s << std::string(3, a_pad_character);
            break;
        case 2:
            s << std::string(4, a_pad_character);
            break;
        case 1:
            s << std::string(6, a_pad_character);
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

auto base32_decode(
    std::string_view const& a_data,
    std::error_code& a_ec,
    bool a_strict,
    char a_pad_character
)
-> std::vector<std::uint8_t>
{
    std::vector<std::uint8_t> ret;

    static std::bitset<40> const mask {0xFF};
    std::uint64_t num_bits = 0;
    std::bitset<40> bit_buffer;

    for (auto const datum : a_data)
    {
        if (datum == a_pad_character)
        {
            break;
        }

        try
        {
            std::uint8_t value = base32_decode_alpahbet.at(datum);
            bit_buffer <<= 5;
            bit_buffer |= value;
            num_bits += 5;

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

auto is_base32(
    std::string_view const& a_data,
    char a_pad_character
)
-> bool
{
    for (auto const datum : a_data)
    {
        if (datum != a_pad_character && !base32_decode_alpahbet.contains(datum))
        {
            return false;
        }
    }

    return true;
}

}   // namespace base_codec
}   // namespace rs


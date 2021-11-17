#pragma once

#include <array>
#include <cstdint>
#include <initializer_list>
#include <tuple>

namespace lab2 {
constexpr std::size_t key128bit = 128u;
constexpr std::size_t key256bit = 256u;

template <std::size_t KeySize>
class RTEA {
public: // methods
    static_assert(KeySize == 128 || KeySize == 256, "Expected 128- or 256-bits key");

    template <typename ...Args>
    RTEA(Args&&... args) : key{{std::forward<Args>(args)...}} {}

    [[nodiscard]]
    auto encrypt(std::uint64_t in) const -> std::uint64_t {
        auto [a, b, kw] = std::make_tuple(std::uint32_t(in >> 32), std::uint32_t(in), getArrSize());
        for (std::int32_t r = 0; r < static_cast<std::int32_t>(kw) * 4 + 32;) {
            a += b + ((b << 6) ^ (b >> 8)) + key[r % kw] + (r++);
            b += a + ((a << 6) ^ (a >> 8)) + key[r % kw] + (r++);
        }
        return std::uint64_t{a} << 32 | b;
    }

    [[nodiscard]]
    auto decrypt(std::uint64_t in) const -> std::uint64_t{
        auto [a, b, kw] = std::make_tuple(std::uint32_t(in >> 32), std::uint32_t(in), getArrSize());
        for (std::int32_t r = static_cast<std::int32_t>(kw) * 4 + 31; r >= 0;) {
            b -= a + ((a << 6) ^ (a >> 8)) + key[r % kw] + (r--);
            a -= b + ((b << 6) ^ (b >> 8)) + key[r % kw] + (r--);
        }
        return std::uint64_t{a} << 32 | b;
    }

private: // fields
    static constexpr auto getArrSize() -> std::size_t {
        return KeySize / 32u;
    }
    const std::array<std::uint32_t, getArrSize()> key;
};
} // namespace lab2

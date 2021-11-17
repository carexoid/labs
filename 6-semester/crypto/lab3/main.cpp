#include <iostream>
#include <vector>
#include <string_view>
#include <zlib.h>

namespace lab3 {
constexpr std::uint32_t adler_mod = 65521;

auto adler32(std::string_view data) -> std::uint32_t {
    std::uint32_t a = 1, b = 0;
    for (const auto& ch : data) {
        a = (a + ch) % adler_mod;
        b = (b + a) % adler_mod;
    }
    return (b << 16) | a;
}
} // namespace lab3

int main() {
    std::vector<std::string_view> values = {"amogus",
                                            "sus",
                                            "sugoma",
                                            "amogusgus"};
    bool tests_passed = true;
    for (const auto& value : values) {
        tests_passed &=
                lab3::adler32(value) ==
                adler32((0u << 16 | 1u), reinterpret_cast<const Bytef *>(value.data()), value.size());
    }
    std::cout << (tests_passed ? "Tests passed!" : "Tests failed") << '\n';
    return 0;
}

#include <iostream>
#include <random>

#include "RTEA.hpp"

int main() {

    const auto get_new_rand_uint64 = []() {
        static std::mt19937 gen{std::random_device{}()};
        std::uniform_int_distribution<std::uint64_t> dist{};
        return dist(gen);
    };

    static constexpr std::size_t number_of_runs = 40;

    {
        std::cout << "Testing 128bit key...\n";

        const auto rtea = lab2::RTEA<lab2::key256bit>({0x20B94801u, 0x7A69A953u, 0x7EFBC60Fu, 0xAEDE318Eu});
        bool tests_successful = true;
        for (std::size_t i = 0; i < number_of_runs; ++i) {
            const std::uint64_t initial = get_new_rand_uint64();
            const auto encrypted = rtea.encrypt(initial);
            const auto decrypted = rtea.decrypt(encrypted);
            tests_successful &= initial == decrypted;
        }

        std::cout << std::boolalpha << "Successful: " << tests_successful << std::endl;
    }


    {
        std::cout << "Testing 256bit key...\n";

        const auto rtea = lab2::RTEA<lab2::key256bit>({0x20B94801u, 0x84F25364u, 0x52A795BDu, 0x7569A953u,
                                                       0x7EFBC60Fu, 0xA2F47F5Eu, 0x23637D6u, 0xA55E318Eu});
        bool tests_successful = true;
        for (std::size_t i = 0; i < number_of_runs; ++i) {
            const std::uint64_t initial = get_new_rand_uint64();
            const auto encrypted = rtea.encrypt(initial);
            const auto decrypted = rtea.decrypt(encrypted);
            tests_successful &= initial == decrypted;
        }

        std::cout << std::boolalpha << "Successful: " << tests_successful << std::endl;
    }

    return 0;
}

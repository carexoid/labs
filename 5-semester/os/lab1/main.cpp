#include <iostream>
#include <utility>

#include "lib/demofuncs.hpp"

#include "Process.hpp"
#include "Manager.hpp"

int main() {
    std::cout << "Enter:\n 1 - AND operation\n 2 - OR operation" << std::endl;
    int cmd = 0;
    std::cin >> cmd;
    std::cout << "Enter argument: ";
    int arg = 0;
    std::cin >> arg;
    switch (cmd)
    {
        case 1:
            lab::Manager<lab::Operations::AND> {
                    spos::lab1::demo::f_func<spos::lab1::demo::op_group::AND>,
                    spos::lab1::demo::g_func<spos::lab1::demo::op_group::AND>
            }.compute(arg);
            break;
        case 2:
            lab::Manager<lab::Operations::OR> {
                    spos::lab1::demo::f_func<spos::lab1::demo::op_group::OR>,
                    spos::lab1::demo::g_func<spos::lab1::demo::op_group::OR>
            }.compute(arg);
            break;
        default:
            std::cout << "Wrong operation's option chosen" << std::endl;
    }

    return 0;
}

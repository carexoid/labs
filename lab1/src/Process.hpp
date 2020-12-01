#pragma once

#include <future>
#include <unistd.h>

namespace lab {
    /**
     * @brief Run a callable object in a new process
     * @tparam Callable type of a callable object to run in a new process
     * @param func callable object
     * @return child's process id
     */
    template <class Callable>
    auto process(Callable&& func) -> pid_t
    {
        const auto child_pid = fork();
        if (child_pid == 0) { /// child code
            func();
            exit(0);
        } /// no parent code
        return child_pid;
    }
} // namespace lab

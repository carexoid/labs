#pragma once

#include <functional>
#include <utility>
#include <future>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ncurses.h>
#include <iostream>
#include <csignal>
#include <sstream>

#include "Process.hpp"
#include "Errors.hpp"
#include "demofuncs.hpp"

namespace lab {

    /**
     * @enum Operations
     * @brief possible binary operations
     */
    enum class Operations {
        AND, OR
    };

    /**
     * @class Manager
     * @brief manages computation of f(x) @ g(x) statement, where @ is one of possible operations (AND/OR)
     * @tparam Operation operation to be applied to function results
     */
    template <Operations Operation>
    class Manager {
    public: // methods
        template <class CallableF, class CallableG>
        Manager(CallableF&& f_func, CallableG&& g_func)
            : _f_func(std::forward<CallableF>(f_func))
            , _g_func(std::forward<CallableG>(g_func))
            , _operation(Operation)
        {}

        /**
         * @brief Runs computation of each function in its own process, got the result of computation by named pipes
         * @param arg integer to pass to functions being computed
         * @throws lab::CantCreateFIFOException
         */
        void compute(int arg);

        /**
         * @brief Resets results of a previous computation
         */
        void reset();

    private: // methods
        [[nodiscard]]
        inline auto _getZeroValue() const -> bool;

        [[nodiscard]]
        inline auto _applyOperation() const -> bool;

    private: // fields
        std::function<bool(int)> _f_func, _g_func;
        std::optional<bool> _f_res, _g_res;
        Operations _operation;
    };

    template <Operations Operation>
    void Manager<Operation>::compute(int arg)
    {
        initscr();
        unlink("/tmp/f_pipe"); /// delete pipe if it already exists
        if (mkfifo("/tmp/f_pipe", S_IFIFO|0777) == -1) {
            throw CantCreateFIFOException{"Named pipe for F function failed"};
        }

        unlink("/tmp/g_pipe"); /// delete pipe if it already exists
        if (mkfifo("/tmp/g_pipe", S_IFIFO|0777) == -1) {
            throw CantCreateFIFOException{"Named pipe for G function failed"};
        }

        std::shared_future f_future{std::async(std::launch::async, [&]() {
            int reader_descriptor = open("/tmp/f_pipe", O_RDONLY);
            bool result = true;
            read(reader_descriptor, &result, sizeof(result));
            close(reader_descriptor);
            return result;
        })
        };
        auto f_computation_pid = process([&]() {
            int writer_descriptor = open("/tmp/f_pipe", O_WRONLY);
            bool result = _f_func(arg);
            write(writer_descriptor, &result, sizeof(result));
            close(writer_descriptor);
        });

        std::shared_future g_future{std::async(std::launch::async, [&]() {
            int reader_descriptor = open("/tmp/g_pipe", O_RDONLY);
            bool result = true;
            read(reader_descriptor, &result, sizeof(result));
            close(reader_descriptor);
            return result;
        })};
        auto g_computation_pid = process([&]() {
            int writer_descriptor = open("/tmp/g_pipe", O_WRONLY);
            bool result = _g_func(arg);
            write(writer_descriptor, &result, sizeof(result));
            close(writer_descriptor);
        });
        std::atomic_bool computation_finished = false;
        auto cancellation_future = std::async(std::launch::async, [&]() {
            while (!(wgetch(stdscr) == 'q' || computation_finished.load())) {}
        });

        const auto calculations_timeout_duration = std::chrono::milliseconds(10);
        const auto zero_value = _getZeroValue();
        std::ostringstream output;

        while (true) {
            if (cancellation_future.wait_for(calculations_timeout_duration) == std::future_status::ready) {
                kill(f_computation_pid, SIGKILL);
                kill(g_computation_pid, SIGKILL);
                output << "Computation terminated. Result was not computed.\nResult of F:"
                          << (_f_res.has_value() ? std::to_string(_f_res.has_value()) : "not computed")
                          << "\nResult of G:"
                          << (_g_res.has_value() ? std::to_string(_g_res.has_value()) : "not computed")
                          << std::endl;
                break;
            }
            std::this_thread::sleep_for(std::chrono::microseconds(1));
            if (f_future.wait_for(calculations_timeout_duration) == std::future_status::ready) {
                _f_res = f_future.get();
                if (_f_res.value() == zero_value) {
                    kill(g_computation_pid, SIGKILL);
                    output << "Result of computation is: " << zero_value
                              << "\nComputation of G function was aborted, F got zero value." << std::endl;
                    break;
                }
            }
            if (g_future.wait_for(calculations_timeout_duration) == std::future_status::ready) {
                _g_res = g_future.get();
                if (_g_res.value() == zero_value) {
                    kill(f_computation_pid, SIGKILL);
                    output << "Result of computation is: " << zero_value
                              << "\nComputation of F function was aborted, G got zero value." << std::endl;
                    break;
                }
            }
            if (_f_res.has_value() && _g_res.has_value()) {
                output << "Result of computation is: " << _applyOperation()
                          << "\nResults of both functions were awaited." << std::endl;
                break;
            }
        }
        computation_finished.store(true);
        reset();
        printw(output.str().c_str());
        printw("\n\nPress any key to continue...");
        getch();
        endwin();
    }

    template <Operations Operation>
    void Manager<Operation>::reset() {
        _f_res = _g_res = std::nullopt;
    }

    template <>
    inline auto Manager<Operations::AND>::_getZeroValue() const -> bool
    {
        return false;
    }

    template <>
    inline auto Manager<Operations::OR>::_getZeroValue() const -> bool
    {
        return true;
    }

    template <>
    inline auto Manager<Operations::AND>::_applyOperation() const -> bool
    {
        return _f_res.value() && _g_res.value();
    }

    template <>
    inline auto Manager<Operations::OR>::_applyOperation() const -> bool
    {
        return _f_res.value() || _g_res.value();
    }



} // namespace lab

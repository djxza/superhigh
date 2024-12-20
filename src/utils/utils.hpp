/* file importovan iz nekog drugog projekta */

#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <filesystem>
#include <cinttypes>
#include <cassert>

/* 3rd party libraries */
// #include "../interpreter/json.hpp"
// using json = nlohmann::json;

namespace fs = std::filesystem;

#include "platform.hpp"

class str : public std::string
{
public:
    str() : std::string() {}
    str(const std::string &s) : std::string(s) {}
    str(const char *s) : std::string(s) {}

    void operator-(const usize i);
    void operator+(const usize i);

    bool starts_with(const str &prefix) const;
    bool ends_with(const str &suffix) const;
    usize find_first(const str first) const;
    usize find_last(const str last) const;

    std::string cpp_str() const;

    str after(const usize i) const;
    str remove_char(char c) const;
    str no_newline() const;
    str &operator=(const str &s);
};

/* added namespace to make managment easier */
namespace utils
{
    using str = str;

    enum class fn_attempt : bool {
        SUCCESS = 1,
        FAILURE = 0
    };

    void _throw(
        const str& title,
        const str& msg);

    /* relative executable bath thing */
    void set_arg0(const str& arg0);
    const str get_arg0();

    /* Json related functions */
    // void add_to_array(const str& filename, const str& key, const json& element);

    void exec(const str &cmd);
    void tryexec(const str &cmd);
    fn_attempt int_exec(const str &cmd);
    void msg_tryexec(const str &cmd, const str& msg);

    str trim(const str& x);
    str get_exec(const str &cmd);
    str read_file(const str &filename);
    str read_file_newline(const str &filename);
}
#pragma once

#ifndef ERRORS_H
#define ERRORS_H

#include <stdexcept>
#include <string>

class app_error : public std::runtime_error {
public:
    explicit app_error(const std::string &arg) : runtime_error(arg) {}
};

class piece_error : public app_error {
public:
    explicit piece_error(const std::string &arg) : app_error(arg) {}
};

class move_error : public app_error {
public:
    explicit move_error(const std::string &arg) : app_error(arg) {}
};

#endif
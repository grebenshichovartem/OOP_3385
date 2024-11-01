//
// Created by MSI Catana GF66 on 12.10.2024.
//

#include "DebuggingException.h"

using namespace std::string_literals;

DebuggingException::DebuggingException(std::string &&message) : message{"Exception: " + message + "!!"} {
}

const char *DebuggingException::what() const noexcept { return message.c_str(); }

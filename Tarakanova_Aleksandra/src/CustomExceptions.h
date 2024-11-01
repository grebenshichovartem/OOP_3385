#ifndef CUSTOM_EXCEPTIONS_H
#define CUSTOM_EXCEPTIONS_H

#include <stdexcept>

class GameFieldException : public std::runtime_error {
public:
    GameFieldException(const char* message) : runtime_error(message) {}
};

class ShipManagerException : public std::runtime_error {
public:
    ShipManagerException(const char* message) : runtime_error(message) {}
};

class AbilityManagerException : public std::runtime_error {
public:
    AbilityManagerException(const char* message) : runtime_error(message) {}
};

#endif // CUSTOM_EXCEPTIONS_H

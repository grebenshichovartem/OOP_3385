//
// Created by MSI Catana GF66 on 12.10.2024.
//

#ifndef DEBUGGINGEXCEPTION_H
#define DEBUGGINGEXCEPTION_H

#include <string>

class DebuggingException : public std::exception {
private:
    std::string message;

public:
    explicit DebuggingException(std::string &&message);

    [[nodiscard]] const char *what() const noexcept override;
};


#endif //DEBUGGINGEXCEPTION_H

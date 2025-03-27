#pragma once
#include <iostream>
class WrongQueueSize : public std::exception {
public:
    WrongQueueSize(const std::string& message = "Wrong Queue Size: The entered queue size is invalid.")
        : message_(message) {
    }

    virtual const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};
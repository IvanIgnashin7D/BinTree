#pragma once
#include <iostream>
class QueueUnderflow : public std::exception {
public:
    QueueUnderflow(const std::string& message = "Queue underflow: cannot delete element, queue is empty.")
        : message_(message) {
    }

    virtual const char* what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};

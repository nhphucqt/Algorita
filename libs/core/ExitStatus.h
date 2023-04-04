#ifndef EXIT_STATUS_H
#define EXIT_STATUS_H

#include <string>

class ExitStatus {
public:
    bool success;
    std::string message;

    ExitStatus();
    ExitStatus(bool _success, const std::string &_message);
};

#endif
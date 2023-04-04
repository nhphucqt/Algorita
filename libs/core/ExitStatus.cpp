#include "ExitStatus.h"

ExitStatus::ExitStatus() {}
ExitStatus::ExitStatus(bool _success, const std::string &_message) {
    success = _success;
    message = _message;
}
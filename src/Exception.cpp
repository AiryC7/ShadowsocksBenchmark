#include "Exception.h"

Exception::Exception(const string &reason) noexcept {
	this->reason = reason;
}

const char *Exception::what(void) const noexcept {
	return reason.c_str();
}



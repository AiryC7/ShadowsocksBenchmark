#pragma once

#include <exception>
#include <string>

using std::string;

class Exception : public std::exception {
public:
	Exception(string const &reason) noexcept;

public:
	const char *what(void) const noexcept override;

private:
	string reason;
};

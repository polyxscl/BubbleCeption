#pragma once
#include <iostream>
#include <sstream>

#undef ERROR

enum class LOG_FLAG { INFO, WARN, ERROR };

class Logger {
public:

	Logger();
	Logger(std::string header);

	template<typename T>
	Logger& operator<<(const T& value) {
		this->buffer << value;
		return *this;
	}

	Logger& operator<<(const LOG_FLAG flag);

	static const LOG_FLAG info, warn, error;

private:
	std::stringstream buffer;
	std::string header = "";
};
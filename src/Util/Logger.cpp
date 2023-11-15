#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include <iomanip>

#include "Logger.h"

#undef ERROR

const LOG_FLAG Logger::info = LOG_FLAG::INFO;
const LOG_FLAG Logger::warn = LOG_FLAG::WARN;
const LOG_FLAG Logger::error = LOG_FLAG::ERROR;

static const char* RESET = "\033[0m";
static const char* COLOR_RED = "\033[31m";
static const char* COLOR_YELLOW = "\033[33m";
static const char* COLOR_WHITE = "\033[37m";

Logger::Logger() : header("All") {};
Logger::Logger(std::string header) : header(header) {};

const char* get_flag_color(const LOG_FLAG flag) {
	switch (flag) {
	case LOG_FLAG::INFO:
		return COLOR_WHITE;
	case LOG_FLAG::WARN:
		return COLOR_YELLOW;
	case LOG_FLAG::ERROR:
		return COLOR_RED;
	default:
		throw std::runtime_error("InvalidFlagColor");
	}
}

const char* get_flag_identifier(const LOG_FLAG flag) {
	switch (flag) {
	case LOG_FLAG::INFO:
		return "INF";
	case LOG_FLAG::WARN:
		return "WRN";
	case LOG_FLAG::ERROR:
		return "ERR";
	default:
		throw std::runtime_error("InvalidFlagIdentifier");
	}
}

Logger& Logger::operator<<(const LOG_FLAG flag) {
	auto now = std::chrono::system_clock::now();
	std::time_t now_t = std::chrono::system_clock::to_time_t(now);
	tm local_tm;
	localtime_s(&local_tm, &now_t);

	(flag == LOG_FLAG::ERROR ? std::cerr : std::cout)
		<< get_flag_color(flag)
		<< get_flag_identifier(flag)
		<< " [" << std::put_time(&local_tm, "%Y-%m-%dT%H:%M:%S") << "] "
		<< "@ " << this->header << ": "
		<< this->buffer.str() << RESET << std::endl;

	this->buffer.str("");
	this->buffer.clear();

	return *this;
}
#include <iostream>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "Logger.h"

using namespace handspired;


void Logger::write_to_log(
	LogLevel log_level,
	char *msg
) {
	if (this->log_level > log_level) {
		return;
	}

	time_t t = time(NULL);
	struct tm *time = localtime(&t);
	char time_string[64];
	strftime(time_string, sizeof(time_string), "%b %d %Y %X", time);

	const char *log_level_string;
	switch (log_level) {
		case LOGGER_DEBUG:
			log_level_string = "debug";
			break;
		case LOGGER_INFO:
			log_level_string = "info";
			break;
		case LOGGER_ERROR:
			log_level_string = "error";
			break;
		default:
			log_level_string = "???";
	}

	printf("%s [%s] :: %s\n", time_string, log_level_string, msg);
}

void Logger::write_to_log_f(
	LogLevel log_level,
	const std::string &fmt,
	va_list args
) {
	char fmt_cstring[fmt.length()+1];
	strcpy(fmt_cstring, fmt.c_str());

	char formatted_msg[128];
	vsnprintf(formatted_msg, 128, fmt_cstring, args);

	write_to_log(log_level, formatted_msg);
}

void Logger::debug(const std::string &msg) {
	debugf("%s", msg.c_str());
}

void Logger::debugf(const std::string &fmt, ...) {
	va_list args;
	va_start (args, fmt);

	write_to_log_f(LOGGER_DEBUG, fmt, args);

	va_end(args);
}

void Logger::info(const std::string &msg) {
	infof("%s", msg.c_str());
}

void Logger::infof(const std::string &fmt, ...) {
	va_list args;
	va_start (args, fmt);

	write_to_log_f(LOGGER_INFO, fmt, args);

	va_end(args);
}

void Logger::error(const std::string &msg) {
	infof("%s", msg.c_str());
}

void Logger::errorf(const std::string &fmt, ...) {
	va_list args;
	va_start (args, fmt);

	write_to_log_f(LOGGER_INFO, fmt, args);

	va_end(args);
}

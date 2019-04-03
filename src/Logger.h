#ifndef LOGGER_H
#define LOGGER_H

#include<string>
namespace handmadeish {

	enum LogLevel {
		LOGGER_DEBUG,
		LOGGER_INFO,
		LOGGER_ERROR
	};

	class Logger {
		private:
			LogLevel log_level = LOGGER_INFO;
			void write_to_log(LogLevel log_level, char *msg);
			void write_to_log_f(
				LogLevel log_level,
				const std::string &fmt,
				va_list args
			);

		public:
			Logger(LogLevel log_level) {
				this->log_level = log_level;
			}

			void debug(const std::string &msg);
			void debugf(const std::string &fmt, ...);

			void info(const std::string &msg);
			void infof(const std::string &fmt, ...);

			void error(const std::string &msg);
			void errorf(const std::string &fmt, ...);
	};

}

#endif

#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <iostream>
#include <string>

#define contextInfo                                                           \
	(std::string("\e[1m") + (__FILE__) + "\e[0m:\e[1m" +                      \
	 std::to_string(__LINE__) + "\e[0m-(\e[1m" + (__FUNCTION__) + "\e[0m)-")

class Logger {
	template <typename First> void output(First &&first) const;
	template <typename First, typename... Rest>
	void output(First &&first, Rest &&...rest) const;

  public:
	template <typename... Tp> void trace(Tp &&...args) const;
	template <typename... Tp> void debug(Tp &&...args) const;
	template <typename... Tp> void info(Tp &&...args) const;
	template <typename... Tp> void warn(Tp &&...args) const;
	template <typename... Tp> void error(Tp &&...args) const;
};

template <typename First> void Logger::output(First &&first) const {
	std::cerr << first;
}
template <typename First, typename... Rest>
void Logger::output(First &&first, Rest &&...rest) const {
	output(first), output(std::forward<Rest>(rest)...);
}

template <typename... Tp> void Logger::trace(Tp &&...args) const {
	this->output("[\e[36mtrace\e[0m]"), this->output(": ");
	this->output("\e[1m"), this->output(std::forward<Tp>(args)...),
		this->output("\e[0m\n");
}
template <typename... Tp> void Logger::debug(Tp &&...args) const {
	this->output("[\e[35mdebug\e[0m]"), this->output(": ");
	this->output("\e[1m"), this->output(std::forward<Tp>(args)...),
		this->output("\e[0m\n");
}
template <typename... Tp> void Logger::info(Tp &&...args) const {
	this->output("[\e[34minfo\e[0m]"), this->output(": ");
	this->output("\e[1m"), this->output(std::forward<Tp>(args)...),
		this->output("\e[0m\n");
}
template <typename... Tp> void Logger::warn(Tp &&...args) const {
	this->output("[\e[33mwarn\e[0m]"), this->output(": ");
	this->output("\e[1m"), this->output(std::forward<Tp>(args)...),
		this->output("\e[0m\n");
}
template <typename... Tp> void Logger::error(Tp &&...args) const {
	this->output("[\e[31merror\e[0m]"), this->output(": ");
	this->output("\e[1m"), this->output(std::forward<Tp>(args)...),
		this->output("\e[0m\n");
}

extern Logger logger;

#endif

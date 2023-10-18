#include "logger.hpp"
#include <iostream>

template <typename First> void Logger::output(First first) const {
	std::cerr << first;
}
template <typename First, typename Rest>
void Logger::output(First first, Rest rest...) const {
	output(first), output(rest);
}

template <typename Tp> void Logger::trace(Tp args...) const {
	this->output("[\e[36mtrace\e[0m]"), this->output(": ");
	this->output("\e[1m"), this->output(args), this->output("\e[0m\n");
}
template <typename Tp> void Logger::debug(Tp args...) const {
	this->output("[\e[35mdebug\e[0m]"), this->output(": ");
	this->output("\e[1m"), this->output(args), this->output("\e[0m\n");
}
template <typename Tp> void Logger::info(Tp args...) const {
	this->output("[\e[34minfo\e[0m]"), this->output(": ");
	this->output("\e[1m"), this->output(args), this->output("\e[0m\n");
}
template <typename Tp> void Logger::warn(Tp args...) const {
	this->output("[\e[33mwarn\e[0m]"), this->output(": ");
	this->output("\e[1m"), this->output(args), this->output("\e[0m\n");
}
template <typename Tp> void Logger::error(Tp args...) const {
	this->output("[\e[31merror\e[0m]"), this->output(": ");
	this->output("\e[1m"), this->output(args), this->output("\e[0m\n");
}

Logger logger;
#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <string>

#define contextInfo                                                           \
	(std::string("\e[1m") + (__FILE__) + "\e[0m:\e[1m" +                      \
	 std::to_string(__LINE__) + "\e[0m-(\e[1m" + (__FUNCTION__) + "\e[0m)-")

class Logger {
	template <typename First> void output(First) const;
	template <typename First, typename Rest> void output(First, Rest...) const;

  public:
	template <typename Tp> void trace(Tp...) const;
	template <typename Tp> void debug(Tp...) const;
	template <typename Tp> void info(Tp...) const;
	template <typename Tp> void warn(Tp...) const;
	template <typename Tp> void error(Tp...) const;
};
extern Logger logger;

#endif
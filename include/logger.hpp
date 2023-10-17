#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

class Logger {
	template <typename First> void output(First) const;
	template <typename First, typename Rest> void output(First, Rest...) const;

	void outputContextInfo() const;

  public:
	template <typename Tp> void trace(Tp...) const;
	template <typename Tp> void debug(Tp...) const;
	template <typename Tp> void info(Tp...) const;
	template <typename Tp> void warn(Tp...) const;
	template <typename Tp> void error(Tp...) const;
};
extern Logger logger;

#endif
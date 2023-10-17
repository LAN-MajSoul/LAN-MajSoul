#include "rules.hpp"

#include <string>

Card::operator std::string() const {
	return std::to_string(val) + (type == w	  ? "w"
								  : type == p ? "p"
								  : type == s ? "s"
											  : "z");
}
#ifndef CMC_PARSER_H
#define CMC_PARSER_H

#include <cmc/container.h>

namespace cmc {
	std::list<cmc::Enum> parseCode(const std::string& code, const std::vector<std::string>& args = std::vector<std::string>());
}

#endif
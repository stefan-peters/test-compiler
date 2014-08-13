#ifndef CMC_PARSER_H
#define CMC_PARSER_H

#include <cmc/container.h>

namespace cmc {
	std::list<cmc::Enum> parseCode(const char* code);
}

#endif
#ifndef COVERAGE_INSTRUMENT_H
#define COVERAGE_INSTRUMENT_H

#include <string>
#include <vector>

namespace coverage {
	typedef std::vector<std::string> ParameterList;
	std::string instrument(const std::string& code, const ParameterList& args = ParameterList());
}

#endif